#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <sstream>
#include <fstream>
#include <vector>
#include "service.h"
#include "observer.h"
using std::vector;
using std::stringstream;

/// <summary>
/// clasa specifica Ferestrei
/// </summary>
class Window : public QWidget, public Observer {
private:
	Service& serv;

	//initializare componente componenta window

	QListWidget* lstTaskuri;
	string title;

	QPushButton* btnOpen = new QPushButton(QString::fromStdString("Open"));
	QPushButton* btnInprogress = new QPushButton(QString::fromStdString("Inprogress"));
	QPushButton* btnClosed = new QPushButton(QString::fromStdString("Closed"));

	//componente obligatorii
	void initializare() {
		setWindowTitle(QString::fromStdString(this->title));
		QVBoxLayout* hLMain = new QVBoxLayout;
		this->setLayout(hLMain);

		QWidget* principala = new QWidget;
		QVBoxLayout* layout = new QVBoxLayout;

		principala->setLayout(layout);

		//lista initializare
		lstTaskuri = new QListWidget;
		layout->addWidget(lstTaskuri);

		QWidget* butoane = new QWidget;
		QHBoxLayout* butoaneLayout = new QHBoxLayout();
		butoane->setLayout(butoaneLayout);

		butoaneLayout->addWidget(btnOpen);
		butoaneLayout->addWidget(btnInprogress);
		butoaneLayout->addWidget(btnClosed);

		hLMain->addWidget(principala);
		hLMain->addWidget(butoane);
	}
	void connectSignalSlot() {
		// legaturi intre ferestre cu observer
	}
	void reloadTasks(vector<Task> taskuri) {
		lstTaskuri->clear();
		const vector<Task>& taske = taskuri;
		for (auto& t : taske) {
			QString itm = QString::fromStdString(std::to_string(t.getID()) + "\t" + t.getDescriere());
			QListWidgetItem* item = new QListWidgetItem{ itm };
			if (t.getStare() == "open")
				item->setBackground(Qt::green);
			if (t.getStare() == "inprogress")
				item->setBackground(Qt::yellow);
			if (t.getStare() == "closed")
				item->setBackground(Qt::red);
			lstTaskuri->addItem(item);
		}
	}
public:
	void update() override {
		this->reloadTasks(this->serv.sortStare());
	}
	Window(Service& s, string title) : serv{ s }, title{ title } {
		serv.addObserver(this);
		initializare();
		connectSignalSlot();
		reloadTasks(this->serv.sortStare());
		show();
	};
	~Window() {
		serv.removeObserver(this);
	}
};

/// <summary>
/// interfata principala utilizator
/// </summary>
class GUI : public QWidget, public Observer {
private:
	Service& serv;
	Window* openWindow;
	Window* closeWindow;
	Window* inprogressWindow;

	//initializare componente interfata principala
	QTableWidget* tabelTaskuri;


	QLineEdit* textId = new QLineEdit;
	QLineEdit* textDescriere = new QLineEdit;
	QLineEdit* textProgramatori = new QLineEdit;
	QLineEdit* textStare = new QLineEdit;

	QLabel* lblId = new QLabel{ "Id" };
	QLabel* lblDescriere = new QLabel{ "Descriere " };
	QLabel* lblProgramatori = new QLabel{ "Programatori " };
	QLabel* lblStare = new QLabel{ "Stare " };

	QPushButton* btnAdd = new QPushButton(QString::fromStdString("Adauga"));
	QPushButton* btnFiltrare = new QPushButton(QString::fromStdString("Filtrare programatori"));
	QLineEdit* textFiltrare = new QLineEdit;

	QPushButton* btnReload = new QPushButton(QString::fromStdString("Reload Table"));

	//componente obligatorii
	void initializareGUI();
	void connectSignalSlot();
	void reloadTasks(vector<Task> taskuri);

public:
	void update() override {
		reloadTasks(this->serv.sortStare());
	}
	GUI(Service& s) : serv{ s } {
		serv.addObserver(this);
		initializareGUI();
		connectSignalSlot();
		reloadTasks(this->serv.sortStare());
		openWindow = new Window{ serv, "open" };
		closeWindow = new Window{ serv, "closed" };
		inprogressWindow = new Window{ serv, "inprogress" };
	}
	~GUI() {
		delete openWindow;
		delete closeWindow;
		delete inprogressWindow;
		serv.removeObserver(this);
	}
	void guiAddTask();
	void filterTask();
};



