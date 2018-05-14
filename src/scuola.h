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
#ifndef SCUOLA_H
#define SCUOLA_H

//! Classe scuola
/*!
  Descrizione della classe scuola
  * \author Angelo e Calogero Scarnà
 */
#include <QDialog>
#include <QtSql>

/*!
 * \brief namespace Ui{}
 * \param class scuola;
 */
namespace Ui {
class scuola;
}

/*!
 * La classe scuola è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QDialog.
 * \brief <b>class scuola: public QDdialog</b>
 * \param QDialog
 */
class scuola : public QDialog
{
    /*!
     * Macro Qt
     *
     *
     * \brief Q_OBJECT
     */
    Q_OBJECT

public:
    /*!
     * Costruttore <b>explicit scuola(QWidget *parent = 0);</b>
     *
     * Questa classe visualizza le informazioni
     * relative al programma e al relativo autore.
     *
     *
     * \brief <b>explicit scuola(QWidget *parent = 0);</b>
     * \param parent = 0
     */
    explicit scuola(QWidget *parent = 0);
    
    //!Distruttore ~scuola();
    /*!
      Il distruttore ~scuola() serve a chiudere
      gli eventuali processi attivi.
     */
    ~scuola();

public slots:
    
    /*!
     * La funzione clicca() viene utilizzata per inserire
     * o aggiornare i dati presenti nel database.
     *
     *
     * \brief <b>void clicca();</b>
     */
    void clicca();
    
    /*!
     * La funzione inserisci() viene utilizzata per inserire
     * i dati impostati nelle QLineEdit all'interno del database.
     * Fa uso della funzione inserisci();
     *
     *
     * \brief <b>void inserisci();</b>
     */
    void inserisci();
    
    /*!
     * La funzione aggiorna() modifica i record
     * presenti nella tabella.
     * \brief <b>void aggiorna();</b>
     */
    void aggiorna();
    
    /*!
     * La funzione cerca() serve a visualizzare
     * sulla QTableView gli elementi trovati.
     * \brief <b>void cerca();</b>
     */
    void cerca();
    
    
    void clear_text();
private:
   //! Variabile privata
   /*!
    * Variabile ui; Serve a visualizzare gli elementi
    * realizzati con il designer qt.
    *
    *
    * \brief <b>Ui::scuola *ui;<b/>
    * \param ui;
    */
    Ui::scuola *ui;
};

#endif // SCUOLA_H
