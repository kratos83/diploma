#include "InvioStampaDiplomaThread.h"
#include "print.h"
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
//Thread stampa
InvioStampaDiplomaThread::InvioStampaDiplomaThread(QModelIndexList index, QString _cliente,QSqlRelationalTableModel *model, QPrinter* printer, int id, QObject* parent) :
    QThread(parent),
    m_id(id),
    m_index(index),
    _cliente_(_cliente),
    m_model(model),
    m_printer(printer)
{
    m_stop = false;
}

void InvioStampaDiplomaThread::run()
{
    QModelIndex mIndex;
    for(int i=0; i < m_index.size(); ++i){
        mIndex = m_index.at(i);
    }
    
    print *pr = new print();
    pr->stampa_diploma(m_printer,m_model,&mIndex);
    emit inviaThread(QString::number(m_id));
    emit inviaTesto("Alunno  "+_cliente_);
    emit execStampa(true);
    msleep(2);
}

void InvioStampaDiplomaThread::stopProcess()
{
    mutex.lock();
    m_stop = true;
    mutex.unlock();
}

InvioStampaDiplomaThread::~InvioStampaDiplomaThread()
{
    mutex.lock();
    m_stop = true;
    mutex.unlock();

    wait();
}
