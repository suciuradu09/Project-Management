/********************************************************************************
** Form generated from reading UI file 'SuciuRadu_216.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUCIURADU_216_H
#define UI_SUCIURADU_216_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SuciuRadu_216Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SuciuRadu_216Class)
    {
        if (SuciuRadu_216Class->objectName().isEmpty())
            SuciuRadu_216Class->setObjectName(QString::fromUtf8("SuciuRadu_216Class"));
        SuciuRadu_216Class->resize(600, 400);
        menuBar = new QMenuBar(SuciuRadu_216Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SuciuRadu_216Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SuciuRadu_216Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SuciuRadu_216Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(SuciuRadu_216Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SuciuRadu_216Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SuciuRadu_216Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SuciuRadu_216Class->setStatusBar(statusBar);

        retranslateUi(SuciuRadu_216Class);

        QMetaObject::connectSlotsByName(SuciuRadu_216Class);
    } // setupUi

    void retranslateUi(QMainWindow *SuciuRadu_216Class)
    {
        SuciuRadu_216Class->setWindowTitle(QCoreApplication::translate("SuciuRadu_216Class", "SuciuRadu_216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SuciuRadu_216Class: public Ui_SuciuRadu_216Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUCIURADU_216_H
