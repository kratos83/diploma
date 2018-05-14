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
#ifndef PRINT_H
#define PRINT_H

#include <QtSql>
#include <QPainter>
#include <QDialog>
#include <QLocale>
#include <QModelIndex>
#include <QtGui>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrintDialog>

/*!
 * La classe print è una classe
 * che eredita le funzioni dalla classe
 * QPrinter.
 * \brief <b>class printe<b>
 */
class print
{
public:
    /*!
     * Costruttore <b>print();</b>
     *
     * Questa classe visualizza la una finestra di dialogo
     * per la stampa dei documenti.
     *
     * \brief <b>print();</b>
     */
    print();

    /*!
     * La funzione rettangolo_diploma_logo(); visualizza 
     * il logo dello stato e la denominazione completa
     * della scuola compreso il nome del dirigente
     *
     * \brief <b>rettangolo_diploma_logo();</b>
     */
    void rettangolo_diploma_logo();
    
    /*!
     * La funzione stampa_diploma(QPrinter *printer,QSqlQueryModel *dataset, QModelIndex *index);
     * visualizza la stampa del diploma.
     *
     *\brief <b>void stampa_diploma(QPrinter *printer, QSqlQueryModel *dataset, QModelIndex *index);</b>
     *\param QPrinter *printer;------------[<b>Il paramatro painter serve a poter visualizzare la stampa grazie alla classe QPrinter,QPainter</b>]
     *\param QSqlQueryModel *dataset;------[<b>Il parametro dataset serve a visualizzare i record presenti nella tabella da stampare</b>]
     *\param QModelIndex *index;--------------[<b>Il parametro index serve a visualizzare l'alunno desiderato.</b>]
     */
    void stampa_diploma(QPrinter *printer, QSqlQueryModel *dataset, QModelIndex *index);
    
    /*!
     * La funzione pagina visualizza gli
     * oggetti disegnati dal painter.
     *
     * \brief <b>void pagina;</b>
     */
    void pagina();
    
    /*!
     * La funzione update_stampa(QModelIndex index);
     * visualizza l'aggiornamento stampato.
     *
     *\brief <b>void update_stampa(QModelIndex index);</b>
     *\param QModelIndex *index;--------------[<b>Il parametro index serve ad modificare i dati dell'allunno e 
     * inserendo il flag stampato.</b>]
     */
    void update_stampa(QModelIndex index);
    
    /*!
     * Il paramatro printer serve a poter visualizzare
     * la stampa grazie alla classe QPrinter,QPainter.
     *
     * \brief <b>QPrinter *printer</b>
     */
    QPrinter *printer;
    
    /*!
     * Il paramatro painter serve a poter visualizzare
     * la stampa grazie alla classe QPrinter,QPainter.
     *
     * \brief <b>QPainter *painter</b>
     */
    QPainter *painter;
    
    /*!
     * La variabile local_settings serve a visualizzare
     * i dati di tipo int, double, float, ecc.
     * \brief <b>QLocale local_settings;</b>
     */
    QLocale *local_settings;
    
    /*!
     * Il puntatore *stampaDlg serve a visualizzare
     * una finestra di dialogo con le caratteristiche
     * della stampa.
     * \brief <b>QDialog *stampaDlg</b>
     */
    QPrintDialog *stampaDlg;
    
    /*!
     *
     *\brief <b>QString nome,cognome,classe,anno,plesso,sezione,dirigente;</b>
     *\param QString cognome;--------------[<b>Il parametro cognome serve a visualizzare il cognome dell'alunno desiderato.</b>]
     *\param QString nome;-----------------[<b>Il parametro nome serve a visualizzare il nome dell'alunno desiderato.</b>]
     *\param QString classe;-----------------[<b>Il parametro classe serve a visualizzare la classe dell'alunno desiderato.</b>]
     *\param QString plesso;---------------[<b>Il parametro plesso serve a visualizzare il plesso dell'alunno desiderato.</b>]
     *\param QString anno;----------------[<b>Il parametro anno serve a visualizzare l'anno scolastico in corso dell'alunno desiderato.</b>]
     *\param QString sezione;---------------[<b>Il parametro sezione serve a visualizzare la sezione dell'alunno desiderato.</b>]
     *\param QString dirigente;-------------------[<b>Il parametro dirigente serve a visualizzare il/la dirigente della scuola.</b>]
     */
    QString nome,cognome,classe,anno,plesso,sezione,dirigente;
};

#endif // PRINT_H
