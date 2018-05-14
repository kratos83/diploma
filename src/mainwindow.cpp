/****************************************************************************
**
** Copyright (C) 2006-2016 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
**
** This file is part of the project Diploma
**
** LGPLv3 License
**
**  You may use this file under the terms of the LGPLv3 license as follows:
*
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Codelinsoft and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/
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
    quit = bar->addAction(QIcon(":/images/dialog-close.png"),"Esci dal\nprogramma");
    bar->addSeparator();
    impo = bar->addAction(QIcon(":/images/calendario.png"),"Anno\nscolatico");
    bar->addSeparator();
    alu = bar->addAction(QIcon(":/images/system-users.png"),"Inserisci\nalunni");
    bar->addSeparator();
    school = bar->addAction(QIcon(":/images/scuola.png"),"Inserisci\nscuola");
    bar->addSeparator();
    about = bar->addAction(QIcon(":/images/svn_status"),"Informazioni\nsoftware");
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
    sc->show();
}

void MainWindow::AddAlunni()
{
    al = new alunni(this);
    al->show();
}

void MainWindow::AddAnno()
{
    an = new anno(this);
    an->ReadAnno();
    an->show();
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
    QMessageBox::information(this,"About","Software per la \nstampa degli auguri sui diplomi...\nVersione 0.4\n\n\n(C) 2006-2018. Codelinsoft.");
}

MainWindow::~MainWindow()
{
    delete ui;
}
