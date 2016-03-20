#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionEsci,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(informazioni()));
    connect(ui->scuola,SIGNAL(clicked(bool)),this,SLOT(add_scuola()));
    connect(ui->alunni,SIGNAL(clicked(bool)),this,SLOT(AddAlunni()));
    connect(ui->actionAnno_scolastico,SIGNAL(triggered(bool)),this,SLOT(AddAnno()));

    QToolBar *bar = ui->toolBar;
    bar->addSeparator();
    quit = ui->toolBar->addAction(QIcon(":/images/dialog-close.png"),"Esci dal\nprogramma");
    bar->addSeparator();
    impo = ui->toolBar->addAction(QIcon(":/images/calendario.png"),"Anno\nscolatico");
    bar->addSeparator();
    alu = ui->toolBar->addAction(QIcon(":/images/system-users.png"),"Inserisci\nalunni");
    bar->addSeparator();
    school = ui->toolBar->addAction(QIcon(":/images/scuola.png"),"Inserisci\nscuola");
    bar->addSeparator();
    about = ui->toolBar->addAction(QIcon(":/images/svn_status"),"Informazioni\nsoftware");
    bar->addSeparator();
    bar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    bar->setMovable(false);

    connect(quit,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(impo,SIGNAL(triggered(bool)),this,SLOT(AddAnno()));
    connect(alu,SIGNAL(triggered(bool)),this,SLOT(AddAlunni()));
    connect(school,SIGNAL(triggered(bool)),this,SLOT(add_scuola()));
    connect(about,SIGNAL(triggered(bool)),this,SLOT(informazioni()));
    leggi_settaggi();
}

void MainWindow::add_scuola()
{
    sc = new scuola(this);
    sc->exec();
}

void MainWindow::AddAlunni()
{
    al = new alunni(this);
    al->exec();
}

void MainWindow::AddAnno()
{
    an = new anno(this);
    an->exec();
}

void MainWindow::leggi_settaggi()
{
    int year = QDate::currentDate().year();
    QString data = QString::number(year)+"/"+QString::number(year+1);
    QSqlQuery query,query_ins;
    query.prepare("select count(id)+1,anno_ins from anno");
    query.exec();
    if(query.next())
    {
        if(query.value(1).toString() < data  || year < QDate::currentDate().year())
        {
            query_ins.prepare("INSERT INTO anno VALUES('"+query.value(0).toString()+"','"+QString::number(year)+"/"+QString::number(year+1)+"')");
            if(query_ins.exec())
                qDebug() << "Inserimento effettuato con successo";
            else
                qDebug() << "Inserimento fallito(table::anno): " << query_ins.lastError().text();
        }
    }
}

void MainWindow::informazioni()
{
    QMessageBox::information(this,"About","Software per la \nstampa degli auguri sui diplomi...\nVersione 0.1\n\n\n(C) 2016. Codelinsoft");
}

MainWindow::~MainWindow()
{
    delete ui;
}
