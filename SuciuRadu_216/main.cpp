//#include "SuciuRadu_216.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "test.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test();
    RepoFile repo{"fisier.txt"};
    validator val;
    Service serv{ repo, val };
    GUI gui{ serv };
    gui.show();
    return a.exec();
}
