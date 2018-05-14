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
#include "anno.h"
#include "ui_anno.h"
#include <QDebug>

anno::anno(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::anno)
{
    ui->setupUi(this);
    setWindowTitle("Visualizza anno");
    connect(ui->chiudi,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->applica,SIGNAL(clicked(bool)),this,SLOT(ApplyAnno()));
    set = new SettingsManager(this);
    ReadAnno();
    visAnno();
}

void anno::visAnno()
{
    QSqlQuery query;
    QStringList m_anno;
    query.prepare("select * from anno");
    query.exec();
    while(query.next())
    {
        m_anno << query.value(1).toString();
    }
    ui->anno_ins->addItems(m_anno);
}

void anno::ApplyAnno()
{
    set->setGeneralValue("Scuola/Anno_scolastico",ui->anno_ins->currentText());
}

void anno::ReadAnno()
{
    ui->anno_ins->setCurrentText(set->generalValue("Scuola/Anno_scolastico",QVariant()).toString());
}

anno::~anno()
{
    delete ui;
}
