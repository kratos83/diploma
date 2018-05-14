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
#ifndef CONN_DB_H
#define CONN_DB_H
#include <QtSql>


/*!
 * La classe Database è una classe
 * che eredita le funzioni dalla classe
 * QSqlDatabase.
 * \brief <b>class Database<b>
 */
class Database {

public:

    /*!
     * La funzione connect() serve a connettere
     * il softawre al database diploma.db.
     *
     *
     * \brief <b>QSqlDatabase connect();</b>
     * \return <b>db;</b>
     */
    QSqlDatabase connect();

    /*!
     * La funzione closeDb() serve a chiudere
     * la connessione al database.
     * \brief <b>void closeDb();</b>
     */
    void closeDb();
    
     /*!
     * La funzione creaQuery(QSqlDatabase db) serve a creare
     * le tabelle all'interno del database.
     * \brief <b>void creaQuery(QSqlDatabase db);</b>
     */
    void creaQuery(QSqlDatabase db);
    
    /*!
     * La funzione messaggio() serve a visualizzare
     * il messaggio della creazione del database.
     * \brief <b>void messaggio();</b>
     */
    void messaggio();
    
    /*!
     * La funzione vis_mainwindow() serve a visualizzare
     * la schermata iniziale.
     * \brief <b>void vis_mainwindow();</b>
     */
    void vis_mainwindow();
};


#endif // CONN_DB_H
