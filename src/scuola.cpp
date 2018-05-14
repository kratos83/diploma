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
#include "scuola.h"
#include "ui_scuola.h"
#include <QDebug>
scuola::scuola(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scuola)
{
    ui->setupUi(this);
    setWindowTitle("Inserisci denominazione della scuola");
    connect(ui->chiudi,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->inserisci,SIGNAL(clicked(bool)),this,SLOT(clicca()));
    cerca();
}

void scuola::clicca()
{
    QSqlQuery Qctrl;
    Qctrl.prepare("SELECT * FROM scuola WHERE id = 1");

    Qctrl.exec();
    if(Qctrl.next()) //Se esiste già
    {
        //Tentativo di aggiornamento del record perché trovato
        aggiorna();
    }
    else
       {
          inserisci();
       }
    cerca();
}

void scuola::inserisci()
{
    QSqlQuery query;
    query.prepare("INSERT INTO scuola(id,denominazione,cap,citta,indirizzo,numero,dirigente) "
                  "VALUES('1','"+QString(ui->denom->text().toStdString().c_str()).replace("'","''")+"','"+ui->cap->text()+"','"+QString(ui->citta->text().toStdString().c_str()).replace("'","''")+"','"+QString(ui->indirizzo->text().toStdString().c_str()).replace("'","''")+"','"+ui->lineEdit->text()+"','"+QString(ui->dirigente->text().toStdString().c_str()).replace("'","''")+"')");
    if(query.exec())
          qDebug() << "Inserimento effettuato con successo";
    else
          qDebug() << "Inserimento fallito(table::scuola): " << query.lastError().text();
}

void scuola::aggiorna()
{
    QSqlQuery query;
    query.prepare("UPDATE scuola SET denominazione='"+QString(ui->denom->text().toStdString().c_str()).replace("'","''")+"',cap='"+ui->cap->text()+"',citta='"+QString(ui->citta->text().toStdString().c_str()).replace("'","''")+"', "
                  "indirizzo = '"+QString(ui->indirizzo->text().toStdString().c_str()).replace("'","''")+"',numero='"+ui->lineEdit->text()+"',dirigente='"+QString(ui->dirigente->text().toStdString().c_str()).replace("'","''")+"' "
                  "WHERE id='1'");
    if(query.exec())
          qDebug() << "Aggiornamento effettuato con successo";
    else
          qDebug() << "Aggiornamento fallito(table::scuola): " << query.lastError().text();
}

void scuola::cerca()
{
    QSqlQuery query;
    query.prepare("select * from scuola where id=1");
    query.exec();

    if(query.next()){
        ui->denom->setText(query.value(1).toString());
        ui->cap->setText(query.value(2).toString());
        ui->citta->setText(query.value(3).toString());
        ui->indirizzo->setText(query.value(4).toString());
        ui->lineEdit->setText(query.value(5).toString());
        ui->dirigente->setText(query.value(6).toString());
    }
    else
    {
        clear_text();
    }
}

void scuola::clear_text()
{
    ui->denom->setText("Inserisci denominazione della scuola");
    ui->cap->setText("CAP");
    ui->citta->setText("Inserisci città");
    ui->indirizzo->setText("Indirizzo");
    ui->lineEdit->setText("Numero via");
    ui->dirigente->setText("Inserisci il nome e cognome del dirigente");
}

scuola::~scuola()
{
    delete ui;
}
