#include "GUI.h"

void GUI::initializareGUI()
{
	QHBoxLayout* hLMain = new QHBoxLayout;
	this->setLayout(hLMain);

	QVBoxLayout* right = new QVBoxLayout;
	QVBoxLayout* left = new QVBoxLayout;
	QWidget* dreapta = new QWidget;
	QWidget* stanga = new QWidget;

	dreapta->setLayout(right);
	stanga->setLayout(left);

	// tabel initializare
	int col = 4;
	int row = 11;
	tabelTaskuri = new QTableWidget{ row, col };
	// header tabel
	tabelTaskuri->setHorizontalHeaderLabels({ "ID", "Descriere", "Programatori", "Stare" });

	right->addWidget(tabelTaskuri);

	// partea stanga adaugare
	QWidget* widgetAdaugare = new QWidget;
	QFormLayout* adaugareLayout = new QFormLayout;

	widgetAdaugare->setLayout(adaugareLayout);
	// labeluri de adaugare
	adaugareLayout->addRow(lblId, textId);
	adaugareLayout->addRow(lblDescriere, textDescriere);
	adaugareLayout->addRow(lblProgramatori, textProgramatori);
	adaugareLayout->addRow(lblStare, textStare);

	adaugareLayout->addWidget(btnAdd);
	left->addWidget(widgetAdaugare);
	// widget de filtrare
	QWidget* widgetFiltrare = new QWidget;
	QFormLayout* filtrareLayout = new QFormLayout;

	widgetFiltrare->setLayout(filtrareLayout);
	filtrareLayout->addRow(textFiltrare, btnFiltrare);

	left->addWidget(widgetFiltrare);
	left->addWidget(btnReload);

	hLMain->addWidget(stanga);
	hLMain->addWidget(dreapta);
}

void GUI::connectSignalSlot()
{
	serv.addObserver(this);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &GUI::guiAddTask);
	QObject::connect(btnFiltrare, &QPushButton::clicked, this, &GUI::filterTask);
	QObject::connect(btnReload, &QPushButton::clicked, this, [&]() {
		this->reloadTasks(this->serv.sortStare());
		});
	QObject::connect(tabelTaskuri, &QTableWidget::itemSelectionChanged, [=]() {
		if (tabelTaskuri->selectedItems().empty())
		{
			textId->setText("");
			textDescriere->setText("");
			textProgramatori->setText("");
			textStare->setText("");
			return;
		}
		int row = tabelTaskuri->selectedItems().at(0)->row();
		tabelTaskuri->selectRow(row);

		int id = tabelTaskuri->item(row, 0)->text().toInt();
		string desc = tabelTaskuri->item(row, 1)->text().toStdString();
		string stare = tabelTaskuri->item(row, 3)->text().toStdString();
		string prog = "";
		prog += this->serv.getAllTasksService()[row].getProgramatori().at(0);
		for (int i = 1; i < serv.getAllTasksService()[row].getProgramatori().size(); i++)
			prog += ',' + serv.getAllTasksService()[row].getProgramatori()[i];

		textId->setText(QString::number(id));
		textDescriere->setText(QString::fromStdString(desc));
		textProgramatori->setText(QString::fromStdString(prog));
		textStare->setText(QString::fromStdString(stare));
		});
}

void GUI::reloadTasks(vector<Task> taskuri)
{
	vector<Task> taske = taskuri;
	tabelTaskuri->clearContents();
	tabelTaskuri->setRowCount(static_cast<int>(taske.size()));

	int linenum = 0;
	for (const auto& t : taske) {
		tabelTaskuri->setItem(linenum, 0, new QTableWidgetItem(QString::number(t.getID())));
		tabelTaskuri->setItem(linenum, 1, new QTableWidgetItem(QString::fromStdString(t.getDescriere())));
		tabelTaskuri->setItem(linenum, 2, new QTableWidgetItem(QString::number(t.getProgramatori().size())));
		tabelTaskuri->setItem(linenum, 3, new QTableWidgetItem(QString::fromStdString(t.getStare())));
		linenum++;
	}
}

void GUI::guiAddTask()
{
	try {
		// se preiau valorile din lineedituri
		int id = textId->text().toInt();
		string descriere = textDescriere->text().toStdString();
		string prog = textProgramatori->text().toStdString();
		string stare = textStare->text().toStdString();

		textId->clear();
		textDescriere->clear();
		textProgramatori->clear();
		textStare->clear();


		vector<string> programatori;
		string curent, elem;
		stringstream fin(prog);
		while (getline(fin, curent, ','))
		{
			string nume;
			programatori.push_back(curent);
		}

		this->serv.store(id, descriere, programatori, stare);
		this->reloadTasks(this->serv.sortStare());

		QMessageBox::information(this, "Information", QString::fromStdString("Task adaugat cu succes"));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessage()));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}

void GUI::filterTask()
{
	try {
		// se preia valoarea din linedit
		string programator = textFiltrare->text().toStdString();

		textFiltrare->clear();

		this->reloadTasks(this->serv.filterProgramer(programator));
		QMessageBox::information(this, "Info", QString::fromStdString("Succes!"));
	}
	catch (RepoException& re)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString("Programatorul nu exista"));
	}
}