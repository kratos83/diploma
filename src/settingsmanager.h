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
#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

//! Classe SettingsManager
/*!
  Descrizione della classe SettingsManager
  * \author Angelo e Calogero Scarnà
 */
#include <QObject>
#include <QMap>
#include <QSettings>
#include <QtGui>
#include <QDir>
#include <QVariant>

/*!
 * La classe SettingsManager è una finestra di dialogo
 * che eredita le funzioni dalla classe Qt
 * QObject.
 *
 *
 * \brief <b>class SettingsManager: public QObject</b>
 * \param QObject
 */
class SettingsManager: public QObject {
   /*!
    * Macro Qt
    *
    *
    * \brief Q_OBJECT
    */
  Q_OBJECT

public:
    
    /*!
     * Costruttore <b>SettingsManager(QObject *parent=0);</b>
     *
     * Questa classe registra i valori assegnati nel
     * file di configurazione del programma.
     *
     * \brief <b>SettingsManager(QObject *parent=0);</b>
     * \param parent = 0
     */
    SettingsManager(QObject *parent=0);
    
    /*!
     * La funzione generalValue() serve a leggere i valori
     * impostati nel file configurazione.
     *
     * \brief <b>QVariant generalValue(QString const &key, QVariant const &defaultValue = QVariant()) const;</b>
     * \param QString const &key;--------[<b>Il paramentro key legge il valore testo all'interno del file di configurazione</b>]
     * \param QVariant const &defaultValue;---------[<b>Il parametro defaultValue legge il valore numerico,booleano,ecce all'interno del file di configurazione</b>]
     * \return <b>QSettings::value(QString key,QVariant defaultValue);</b>
     */
    QVariant generalValue(QString const &key, QVariant const &defaultValue = QVariant()) const;
    
    /*!
     * La funzione setGeneralValue() serve a settare i parametri nel file di
     * configurazione.
     *
     * \brief <b>void setGeneralValue( QString const &key, QVariant const &value);</b>
     * \param QString const &key;--------[<b>Il paramentro key setta il valore testo all'interno del file di configurazione</b>]
     * \param QVariant const &value;---------[<b>Il parametro value setta il valore numerico,booleano,ecce all'interno del file di configurazione</b>]
     */
    void setGeneralValue( QString const &key, QVariant const &value);

    /*!
     * La funzione profilesDir() serve ad impostare la directory
     * di salvataggio del file di configurazione.
     *
     *
     * \brief <b>QDir *profilesDir() const;</b>
     * \return <b>QDir *profDir;</b>
     */
    QDir *profilesDir() const;

    /*!
     * Il puntatore *settingsDir serve a settare la
     * directory dei plugin e il loro relativo
     * di configurazione.
     *
     *
     * \brief <b>QDir *settingsDir;</b>
     */
    QDir *settingsDir, 
    
    /*!
      * Il puntatore *profDir serve a settare la directory
      * del file di configurazione.
      *
      *
      * \brief <b>QDir *profDir</b>
      */
    *profDir;
private:
    /*!
     * IL puntatore *general serve a settare i parametri di
     * confifurazione del software.
     *
     * \brief <b>QSettings *general;</b>
     */
    QSettings *general;
};

extern SettingsManager *settingsManager;

#endif
