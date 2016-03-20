#include "mainwindow.h"
#include "settingsmanager.h"
#include <QApplication>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("diploma.db");
    db.open();

    MainWindow *w = new MainWindow;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-w->width()) / 2;
    int y = (screenGeometry.height()-w->height()) / 2;
    w->move(x, y);
    w->show();

    return a.exec();
}
