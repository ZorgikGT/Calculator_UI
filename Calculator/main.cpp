#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("/home/akter/Atom/Calc.sqlite");

    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
    }
    MainWindow w;
    w.show();



    return a.exec();
}
