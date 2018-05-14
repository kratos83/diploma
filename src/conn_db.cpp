/****************************************************************************
**
** Copyright (C) 2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
**
** This file is part of the project Diploma
**
** LGPL V3 License
**
**  You may use this file under the terms of the LGPL license as follows:
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
#include <QMessageBox>
#include <QSqlDatabase>
#include <QtSql>
#include "conn_db.h"
#include "mainwindow.h"

QSqlDatabase Database::connect(){

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QFile file("diploma.db");
    if(!file.exists()){
        db.setDatabaseName("diploma.db");
        creaQuery(db);
    }
    else{
            db.setDatabaseName("diploma.db");
	     if(db.open()){
		vis_mainwindow();
             }
              else{
              QMessageBox MsgBox;
              MsgBox.setText(QString::fromUtf8("Errore di connessione al DB"));
              MsgBox.setInformativeText(QString::fromUtf8("Impossibile aprire il database..."));
              MsgBox.setIcon(QMessageBox::Warning);
              MsgBox.exec();
 	      exit(0);
              }       
        }
    return db;
}

void Database::closeDb(){
    QSqlDatabase::removeDatabase("QSQLITE");
}

void Database::creaQuery(QSqlDatabase db)
{
    if(db.open())
    {
      QSqlQuery query;
      query.exec("CREATE TABLE anno ("
		 "id INTEGER NOT NULL,"
		 "anno_ins TEXT);");
      query.exec("INSERT INTO  anno VALUES('1', '2015/2016')");
      query.exec("CREATE TABLE scuola ("
		 "id INTEGER NOT NULL,"
		 "denominazione VARCHAR(300) NOT NULL,"
		 "cap TEXT NOT NULL,"
		 "citta VARCHAR(300) NOT NULL,"
		 "indirizzo TEXT NOT NULL,"
		 "numero TEXT NOT NULL,"
		 "dirigente VARCHAR(300) NOT NULL);");
      query.exec("CREATE TABLE alunni ("
		 "id INTEGER PRIMARY KEY AUTOINCREMENT,"
		 "nome TEXT NOT NULL,"
		 "cognome TEXT NOT NULL,"
		 "classe TEXT NOT NULL,"
		 "sezione TEXT NOT NULL,"
		 "anno TEXT NOT NULL,"
		 "plesso TEXT NOT NULL,"
		 "stampa TEXT);");
      messaggio();
      vis_mainwindow();
    }
    else
    {
      QMessageBox MsgBox;
      MsgBox.setText(QString::fromUtf8("Errore"));
      MsgBox.setInformativeText("Impossibile creare il database:\n "+db.lastError().text());
      MsgBox.setIcon(QMessageBox::Warning);
      MsgBox.exec();
    }
}

void Database::messaggio()
{
      QMessageBox MsgBox;
      MsgBox.setWindowTitle("Diploma");
      MsgBox.setText(QString::fromUtf8("Informazioni"));
      MsgBox.setInformativeText("Database creato correttamente.");
      MsgBox.setIcon(QMessageBox::Information);
      MsgBox.exec();
}

void Database::vis_mainwindow()
{
      MainWindow *w = new MainWindow;
      QRect screenGeometry = QApplication::desktop()->screenGeometry();
      int x = (screenGeometry.width()-w->width()) / 2;
      int y = (screenGeometry.height()-w->height()) / 2;
      w->move(x, y);
      w->show();
}

