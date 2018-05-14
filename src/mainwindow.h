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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//! Classe MainWindow
/*!
  Descrizione della classe MainWindow
  * \author Angelo e Calogero Scarnà
 */
#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>
#include "alunni.h"
#include "anno.h"
#include "scuola.h"
#include "settingsmanager.h"

/*!
 * \brief namespace Ui{}
 * \param class MainWindow;
 */
namespace Ui {
class MainWindow;
}

/*!
 * La classe MainWindow è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QMainWindow.
 *
 * Ui::MainWindow è la parte creata automaticamente da
 * qtcreator in fase di programmazione e realizzazione
 * dell'interfaccia.
 *
 *
 * \brief <b>class MainWindow : public QMainWindow</b>
 * \param public QMainWindow
 */
class MainWindow : public QMainWindow
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
     *
     * Costruttore <b>explicit MainWindow(QWidget *parent = 0);</b>
     *
     * Il costruttore MainWindow inizializza tutti i dati
     * presenti nel programma, oltre ad avere svariati pulsanti
     * e menu per l'interfaccia grafica.
     *
     *
     * \brief <b>explicit MainWindow(QWidget *parent = 0);</b>
     * \param QWidget *parent=0;
     */
    explicit MainWindow(QWidget *parent = 0);
    
    //!Distruttore ~MainWindow();
    /*!
      Il distruttore ~MainWindow() serve a chiudere
      gli eventuali processi attivi
     *\brief <b>~MainWindow();</b>
     */
    ~MainWindow();

public slots:
    /*!
     * La funzione informazioni() viene utilizzata per 
     * visualizzare le informazioni relative al
     * software.
     *
     *
     * \brief <b>void informazioni();</b>
     */
    void informazioni();
    
    /*!
     * La funzione leggi_settaggi() viene utilizzata per 
     * leggere le impostazioni salvate all'interno del
     * file config.
     *
     *
     * \brief <b>void leggi_settaggi();</b>
     */
    void leggi_settaggi();
    
    /*!
     * La funzione add_scuola() viene utilizzata per 
     * visualizzare la finestra di dialogo relativa
     * alla scuola.
     *
     *
     * \brief <b>void add_scuola();</b>
     */
    void add_scuola();
    
    /*!
     * La funzione AddAlunni() viene utilizzata per 
     * visualizzare la finestra di dialogo relativa
     * agli alunni.
     *
     *
     * \brief <b>void AddAlunni();</b>
     */
    void AddAlunni();
    
    /*!
     * La funzione AddAnno() viene utilizzata per 
     * visualizzare la finestra di dialogo relativa
     * all'anno.
     *
     *
     * \brief <b>void AddAnno();</b>
     */
    void AddAnno();
    
private:
    //! Variabile privata
   /*!
    * Variabile ui; Serve a visualizzare gli elementi
    * realizzati con il designer qt.
    *
    *
    * \brief <b>Ui::MainWindow *ui;<b/>
    * \param ui;
    */
    Ui::MainWindow *ui;
    
    /*!
     * Apre una window con dentro le
     * impostazioni della finestra scuola.
     *
     * \brief <b>scuola *sc;</b>
     */
    scuola *sc;
    
    /*!
     * Apre una window con dentro le
     * impostazioni della finestra alunni.
     *
     * \brief <b>alunni *al;</b>
     */
    alunni *al;
    
    /*!
     * Apre una window con dentro le
     * impostazioni della finestra anno.
     *
     * \brief <b>anno *an;</b>
     */
    anno *an;
    
    /*!
     * L'azione quit serve a
     * chiudere la MainWindow
     *
     * \brief <b>QAction *quit;</b>
     */
    QAction *quit,
    
    /*!
     * L'azione impo serve a
     * visualizzare le impostazioni
     *
     * \brief <b>QAction *impo;</b>
     */
    *impo,
    
    /*!
     * L'azione alu serve a
     * visualizzare la finestra di
     * dialogo degli alunni
     *
     * \brief <b>QAction *alu;</b>
     */
    *alu,
    
    /*!
     * L'azione school serve a
     * visualizzare la finestra di
     * dialogo della scuola
     *
     * \brief <b>QAction *school;</b>
     */
    *school,
    
    /*!
     * L'azione plex serve a
     * visualizzare la finestra di
     * dialogo del plesso
     *
     * \brief <b>QAction *plex;</b>
     */
    *plex,
    
    /*!
     * L'azione about serve a
     * visualizzare la finestra di
     * dialogo delle informazioni
     *
     * \brief <b>QAction *about;</b>
     */
    *about;
};

#endif // MAINWINDOW_H
