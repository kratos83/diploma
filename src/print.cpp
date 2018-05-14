/****************************************************************************
**
** Copyright (C) 2006-2018 Angelo e Calogero Scarna
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
#include "print.h"
#include "alunni.h"
#include <QDir>
#include <qdebug.h>
#include <QPen>
#include <QColor>
#include <QLocale>
#include <QPainter>
#include <QProcess>

print::print()
{
    printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageMargins(15.0,15.0,15.0,15.0,QPrinter::Millimeter);
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(254);
    stampaDlg = new QPrintDialog();
    stampaDlg->setEnabledOptions(QAbstractPrintDialog::PrintPageRange);
    local_settings = new QLocale(QLocale::system());
    painter = new QPainter();
}

void print::rettangolo_diploma_logo()
{
    //Immagine 1024x683 in pixel, in millimetri
    //uguale a 2650x1780
    QRect target(0,0,2650,1780);
    QImage img(":/images/screen.png");
    painter->drawImage(target,img);
    //Logo stato
    QRect logo(1230,100,150,150);
    QImage img_logo(":/images/logo_stato.png");
    painter->drawImage(logo,img_logo);

    QSqlQuery query;
    query.prepare("select * from scuola where id='1'");
    query.exec();
    if(query.next())
    {
        QString intestazione = query.value(1).toString()+"\n"+
                               query.value(2).toString()+" "+query.value(3).toString()+
                               " - "+query.value(4).toString()+", "+query.value(5).toString();
        int id = QFontDatabase::addApplicationFont(":/font/Book Antiqua Regular.ttf");
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        painter->setFont(QFont(family,14,QFont::Bold,true));
        painter->setPen(QPen(Qt::black,1));
        painter->drawText(900,260,2000,400,Qt::AlignVCenter || Qt::AlignHCenter,intestazione);
        dirigente = query.value(6).toString();
    }
}

void print::stampa_diploma(QPrinter *printer, QSqlQueryModel *dataset,
                           QModelIndex *index)
{
    printer->setPageMargins(15.0,15.0,15.0,15.0,QPrinter::Millimeter);
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(254);
    printer->setOrientation(QPrinter::Landscape);
    painter->begin(printer);
    painter->setRenderHint(QPainter::Antialiasing,true);

    pagina();

    int recNo = 0;
    if(index->row() < dataset->rowCount())
    {
       for(int secRow=0; secRow < 1; ++secRow){
           QSqlRecord rec = dataset->record(index->row());
           if(!rec.isEmpty()){
                nome = rec.value("nome").toString();
                cognome = rec.value("cognome").toString();
                anno = rec.value("anno").toString();
                classe = rec.value("classe").toString();
                sezione = rec.value("sezione").toString();
                plesso = rec.value("plesso").toString();
           }
       }
    }

    if(recNo < dataset->rowCount()){
             pagina();
    }
    painter->end();
}

void print::pagina()
{
    //Visualizzo immagine e logo
    rettangolo_diploma_logo();
    painter->setRenderHint(QPainter::Antialiasing,true);
    //Visualizzo testo del diploma
    int id = QFontDatabase::addApplicationFont(":/font/Algerian.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    painter->setFont(QFont(family,48));
    painter->drawText(950,420,1000,300,Qt::AlignVCenter || Qt::AlignHCenter,"DIPLOMA");
    int f = QFontDatabase::addApplicationFont(":/font/OpenSans.ttf");
    QString open = QFontDatabase::applicationFontFamilies(f).at(0);
    painter->setFont(QFont(open,15,true,true));
    //Scrivo conseguito
    painter->drawText(200,700,600,100,Qt::AlignLeft,"Conseguito dall'alunno ");
    painter->drawText(200,900,1000,100,Qt::AlignLeft,"che ha frequentato nell'anno scolastico");
    painter->drawText(1600,900,300,100,Qt::AlignLeft,"la classe");
    painter->drawText(200,1100,600,100,Qt::AlignLeft,"della scuola primaria");
    painter->drawText(200,1500,600,100,Qt::AlignLeft,"GLI INSEGNANTI");
    painter->drawText(1800,1500,800,100,Qt::AlignLeft,"IL DIRIGENTE SCOLASTICO");
    painter->setFont(QFont(open,28,QFont::Bold,true));
    painter->drawText(800,1200,1000,300,Qt::AlignVCenter | Qt::AlignHCenter,"Congratulazioni");
    painter->setFont(QFont(open,18,QFont::Bold,true));
    painter->drawText(900,680,2000,500,Qt::AlignJustify | Qt::AlignJustify,nome+"  "+cognome);
    painter->drawText(1200,885,800,500,Qt::AlignJustify | Qt::AlignJustify,anno);
    painter->drawText(1900,885,800,200,Qt::AlignJustify | Qt::AlignJustify,classe+" "+sezione);
    painter->drawText(800,1085,600,200,Qt::AlignJustify | Qt::AlignJustify,plesso);
    int ul = QFontDatabase::addApplicationFont(":/font/ITCBLKAD.TTF");
    QString ul_f = QFontDatabase::applicationFontFamilies(ul).at(0);
    painter->setFont(QFont(ul_f,20,true,true));
    painter->drawText(1800,1600,800,100,Qt::AlignLeft,dirigente);
}

void print::update_stampa(QModelIndex index)
{
    QSqlQuery query;
    query.prepare("UPDATE alunni SET stampa='stampato' where id='"+QString::number(index.row()+1)+"'");
    if(query.exec())
        qDebug() << "Aggiornamento effettuato correnttamente...";
    else
        qDebug() << "Aggiornamento non effettuato...";
    m_alunni->lista();
}
