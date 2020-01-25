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
#ifndef ALUNNI_H
#define ALUNNI_H
//! Classe alunni
/*!
  Descrizione della classe alunni
  * \author Angelo e Calogero Scarnà
 */

#include <QDialog>
#include <QtWidgets>
#include <QtSql>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include "InvioStampaDiplomaThread.h"
#include "settingsmanager.h"
#include "anno.h"

/*!
 * \brief namespace Ui{}
 * \param class alunni;
 */
namespace Ui {
class alunni;
}

/*!
 * La classe alunni è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QDialog.
 * \brief <b>class alunni: public QDdialog</b>
 * \param QDialog
 */
class alunni : public QDialog
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
     * Costruttore <b>explicit alunni(QWidget *parent = 0);</b>
     *
     * Questa classe visualizza le informazioni
     * relative al programma e al relativo autore.
     *
     *
     * \brief <b>explicit alunni(QWidget *parent = 0);</b>
     * \param parent = 0
     */
    explicit alunni(QWidget *parent = 0);
    
    //!Distruttore ~alunni();
    /*!
      Il distruttore ~alunni() serve a chiudere
      gli eventuali processi attivi.
     */
    ~alunni();

public slots:
    /*!
     * La funzione open_excel() serve a visualizzare
     * sullo schermo una finestra di dialogo contenente
     * le seguenti informazioni:
     * 
     * Il file excel deve essere composto nel seguente modo
     * \param cognome
     * \param nome
     * \param classe
     * \param sezione
     * \param anno
     * \param plesso
     * 
     * Tuttavia si deve prestare attenzione nella
     * composizione del file.
     * 
     * \brief <b>void open_excel();</b>
     */
    void open_excel();
    
    /*!
     * La funzione excel() serve a inserire
     * i dati presenti all'interno del file excel
     * all'interno del database.
     * Se vi sono degli errori presenti nel file
     * verrà visualizzato un messaggio di errore.
     * \brief <b>void execl();</b>
     */
    void excel();
    
    /*!
     * La funzione lista() visualizza tutti i record
     * presenti all'interno della tabella alunni.
     * \brief <b>void lista();</b>
     */
    void lista();
    
    /*!
     * La funzione clickgrid() si avvale della
     * funzione cerca() per poter visualizzare all'interno
     * delle QLineEdit i dati presenti nella QTableView.
     * \brief <b>void clickgrid();</b>
     */
    void clickgrid(QModelIndex index);
    
    /*!
     * La funzione cerca() serve a visualizzare
     * sulla QTableView gli elementi trovati.
     * \brief <b>void cerca();</b>
     */
    void cerca();
    
    /*!
     * La funzione stampa() visualizza un'anteprima, grazie
     * alla funzione anteprima(QPrinter *printer), del file
     * da stampare.
     * \brief <b>void stampa();</b>
     */
    void stampa();
    
    /*!
     * La funzione anteprima(Qprinter *printer) visualizza
     * un'anteprima del file da stampare.
     * \brief <b>void anteprima(QPrinter *printer);</b>
     * \param QPrinter *printer;
     *
     *
     * Il paramatro printer serve a poter visualizzare
     * la stampa grazie alla classe QPrinter,QPainter.
     */
    void anteprima(QPrinter *printer);
    
    /*!
     * La funzione clear_text serve a cancellare
     * i dati presenti all'interno della QLineEdit.
     * \brief <b>void clear_text();</b>
     */
    void clear_text();
    
    /*!
     * La funzione insert_alunni() viene utilizzata per inserire
     * i dati impostati nelle QLineEdit all'interno del database.
     * Fa uso della funzione insert_alunni();
     *
     *
     * \brief <b>void insert_alunni();</b>
     */
    void insert_alunni();
    
    /*!
     * La funzione inserisci() viene utilizzata per inserire
     * i dati impostati nelle QLineEdit all'interno del database.
     * Fa uso della funzione inserisci();
     *
     *
     * \brief <b>void inserisc();</b>
     */
    void inserisci();
    
    /*!
     * La funzione aggiorna() viene utilizzata per aggiornare
     * i dati impostati nelle QLineEdit all'interno del database.
     *
     *
     * \brief <b>void aggiorna();</b>
     */
    void aggiorna();
    
    /*!
     * La funzione nuovo() serve ad inizializzare il record da
     * inserire all'interno del database.
     *
     * \brief <b>void nuovo();</b>
     *
     * I record vengono inizializzati uno a uno.Esempio:
     *
     * se all'interno della tabella vi è 1, allora verrà
     * incrementato di 1 quindi uguale a 2.
     */
    void nuovo();
    
    void comboClasse();
    void comboSezione();
    void comboAnno();
    void comboPlesso();
    void filtro();
    
    //TableView row
    void currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void initTableView();
    QModelIndex getIndex();
    void avanti(bool ok);
    void inviaStampa();
    void inviaThreadChanged(QString _id);
    void labelText(QString testo);
    void stampaTutti();
private:
   //! Variabile privata
   /*!
    * Variabile ui; Serve a visualizzare gli elementi
    * realizzati con il designer qt.
    *
    *
    * \brief <b>Ui::alunni *ui;<b/>
    * \param ui;
    */
    Ui::alunni *ui;
    
    /*!
     * Variabile model. Serve a visualizzare tutti i dati presenti
     * nella tabella evidenziata mediante QSqlQuery.
     *
     *
     * \brief <b>QSqlRelationalTableModel model;</b>
     */
    QSqlRelationalTableModel *model;
    
    InvioStampaDiplomaThread *m_diploma;
    QString m_id,m_alunno,m_IdThread,m_testo;
    SettingsManager *manager;
    anno *m_anno;
signals:
     void inviaThread(QString _id);
};

extern alunni *m_alunni;
#endif // ALUNNI_H
