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
#ifndef ANNO_H
#define ANNO_H
//! Classe anno
/*!
  Descrizione della classe anno
  * \author Angelo e Calogero Scarnà
 */
#include <QDialog>
#include <QtSql>
#include "settingsmanager.h"
/*!
 * \brief namespace Ui{}
 * \param class anno;
 */
namespace Ui {
class anno;
}

/*!
 * La classe anno è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QDialog.
 * \brief <b>class anno: public QDdialog</b>
 * \param QDialog
 */
class anno : public QDialog
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
     * Costruttore <b>explicit anno(QWidget *parent = 0);</b>
     *
     * Questa classe visualizza le informazioni
     * relative al programma e al relativo autore.
     *
     *
     * \brief <b>explicit anno(QWidget *parent = 0);</b>
     * \param parent = 0
     */
    explicit anno(QWidget *parent = 0);
    
    //!Distruttore ~anno();
    /*!
      Il distruttore ~anno() serve a chiudere
      gli eventuali processi attivi.
     */
    ~anno();

public slots:
    /*!
     * La funzione visAnno() viene utilizzata per visualizzare
     * i dati presenti nel database.
     *
     * \brief <b>void visAnno();</b>
     */
    void visAnno();
    
    /*!
     * La funzione ApplyAnno() viene utilizzata per impostare
     * l'anno corrente.
     *
     * \brief <b>void ApplyAnno();</b>
     */
    void ApplyAnno();
    
    /*!
     * La funzione ReadAnno() viene utilizzata per leggere
     * l'anno corrente.
     *
     * \brief <b>void ReadAnno();</b>
     */
    void ReadAnno();
    
private:
    //! Variabile privata
   /*!
    * Variabile ui; Serve a visualizzare gli elementi
    * realizzati con il designer qt.
    *
    *
    * \brief <b>Ui::anno *ui;<b/>
    * \param ui;
    */
    Ui::anno *ui;
    
    SettingsManager *set;
};

#endif // ANNO_H
