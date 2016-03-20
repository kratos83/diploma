#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include "alunni.h"
#include "anno.h"
#include "scuola.h"
#include "settingsmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void informazioni();
    void leggi_settaggi();
    void add_scuola();
    void AddAlunni();
    void AddAnno();
private:
    Ui::MainWindow *ui;
    scuola *sc;
    alunni *al;
    anno *an;
    QAction *quit,*impo,*alu,*school,*about;
};

#endif // MAINWINDOW_H
