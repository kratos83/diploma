#include "alunni.h"
#include "ui_alunni.h"
#include "settingsmanager.h"
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
#include <QDebug>
#include "print.h"
#include "../xlsx/xlsxdocument.h"

using namespace QXlsx;

alunni *m_alunni = 0;

alunni::alunni(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alunni)
{
    m_alunni = this;
    ui->setupUi(this);
    setWindowTitle("Inserisci alunni");
    model = new QSqlRelationalTableModel(this);
    connect(ui->chiudi,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->excel,SIGNAL(clicked(bool)),this,SLOT(open_excel()));
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickgrid(QModelIndex)));
    connect(ui->stampa,SIGNAL(clicked(bool)),this,SLOT(stampa()));
    connect(ui->nuovo,SIGNAL(clicked(bool)),this,SLOT(nuovo()));
    connect(ui->ins_alu,SIGNAL(clicked(bool)),this,SLOT(insert_alunni()));
    connect(ui->cerca,&QPushButton::clicked,this,&alunni::filtro);
    connect(ui->cancella,&QPushButton::clicked,this,&alunni::lista);
    connect(ui->sel_tutti,&QPushButton::clicked,ui->tableView,&QTableView::selectAll);
    connect(ui->del_tutti,&QPushButton::clicked,ui->tableView,&QTableView::clearSelection);
    connect(ui->stampa_tutti,&QPushButton::clicked,this,&alunni::stampaTutti);
    lista();
}

void alunni::clickgrid(QModelIndex index)
{
    QString id_new;
    int riga = index.row();
    QModelIndex elemento = model->index(riga,0,QModelIndex());

    id_new = model->data(elemento).toString();
    ui->id->setText(id_new);

    cerca();
}

void alunni::cerca()
{
    QSqlQuery query;
        query.prepare("SELECT * FROM alunni WHERE id='"+ui->id->text()+"'");
        query.exec();

        if(query.next()){
	    clear_text();
            ui->id->setText(query.value(0).toString());
            ui->nome->setText(query.value(1).toString());
            ui->cognome->setText(query.value(2).toString());
            ui->classe->setText(query.value(3).toString());
            ui->sezione->setText(query.value(4).toString());
            ui->anno->addItem(query.value(5).toString());
            ui->plesso->addItem(query.value(6).toString());
        }
}

void alunni::nuovo()
{
    QSqlQuery query;
    query.prepare("select count(id+1) from alunni");
    query.exec();
    if(query.next())
    {
	if(query.value(0).toInt() == 0){
	   ui->id->setText("1");
	}
	else{
        QString text = query.value(0).toString();
        ui->id->setText(text);
	}
    }
}

void alunni::insert_alunni()
{
    if(ui->id->text().isEmpty())
        QMessageBox::warning(this,"Diploma","Clicca su nuovo per poter inserire");
    else{
        QSqlQuery query;
        query.prepare("select * from alunni where id='"+ui->id->text()+"'");
        query.exec();
        if(query.next())
        {
        //Se esiste aggiorno
        aggiorna();
        }
        else{
        //Se non esiste inserisco alunno
        inserisci();
        }
        lista();
    }
}

void alunni::inserisci()
{
    QSqlQuery query_ins;
    QString ins = "INSERT INTO alunni(id,nome,cognome,classe,sezione,anno,plesso) "
		      "VALUES('"+ui->id->text()+"','"+QString(ui->nome->text().toStdString().c_str()).replace("'","''")+"','"+QString(ui->cognome->text().toStdString().c_str()).replace("'","''")+
		      "','"+ui->classe->text()+"','"+ui->sezione->text()+"','"+ui->anno->currentText()+
		      "','"+QString(ui->plesso->currentText().toStdString().c_str()).replace("'","''")+"')";
    query_ins.prepare(ins);
    if(query_ins.exec()){
      qDebug() << "Inserimento effettuato con successo";
      clear_text();
    }
    else
      QMessageBox::warning(this,"Diploma","Errore Inserimento:\n "+query_ins.lastError().text());
}

void alunni::aggiorna()
{
    QSqlQuery query_up;
    QString up = "UPDATE alunni SET nome='"+QString(ui->nome->text().toStdString().c_str()).replace("'","''")+"',"
		     "cognome='"+QString(ui->cognome->text().toStdString().c_str()).replace("'","''")+"',"
		     "classe='"+ui->classe->text()+"', sezione='"+ui->sezione->text()+"', "
		     "anno='"+ui->anno->currentText()+"',"+
		     "plesso='"+QString(ui->plesso->currentText().toStdString().c_str()).replace("'","''")+"' "
		     " WHERE id='"+ui->id->text()+"'";
    query_up.prepare(up);
    if(query_up.exec()){
      qDebug() << "Aggiornamento effettuato con successo";
      clear_text();
    }
    else
      QMessageBox::warning(this,"Diploma","Errore aggiornamento:\n "+query_up.lastError().text());
}

void alunni::clear_text()
{
    ui->id->clear();
    ui->nome->clear();
    ui->cognome->clear();
    ui->classe->clear();
    ui->sezione->clear();
    ui->anno->clear();
    ui->plesso->clear();
}

void alunni::lista()
{
    model->setTable("alunni");
    model->setFilter("classe='"+ui->comboBox->currentText()+"' and sezione='"+ui->comboBox_2->currentText()+"' "
                                    "and plesso='"+ui->comboBox_4->currentText()+"' and anno ='"+ui->comboBox_3->currentText()+"'");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Cognome");
    model->setHeaderData(2,Qt::Horizontal,"Nome");
    model->setHeaderData(3,Qt::Horizontal,"Classe");
    model->setHeaderData(4,Qt::Horizontal,"Sezione");
    model->setHeaderData(5,Qt::Horizontal,"Anno");
    model->setHeaderData(6,Qt::Horizontal,"Plesso");
    model->setHeaderData(7,Qt::Horizontal,"Stampa");

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnHidden(7,true);
    comboAnno();
    comboClasse();
    comboPlesso();
    comboSezione();
    initTableView();
    clickgrid(getIndex());
}

void alunni::comboAnno()
{
    ui->comboBox_3->clear();
    QSqlQuery query;
    QStringList m_anno;
    query.prepare("select * from anno");
    query.exec();
    while(query.next())
    {
        m_anno << query.value(1).toString();
    }
    ui->comboBox_3->addItems(m_anno);
}

void alunni::comboClasse()
{
    ui->comboBox->clear();
    QSqlQuery query;
    QStringList m_anno;
    query.prepare("select classe from alunni");
    query.exec();
    while(query.next())
    {
        m_anno << query.value(0).toString();
    }
    m_anno.removeDuplicates();
    
    ui->comboBox->addItems(m_anno);
}

void alunni::comboPlesso()
{
    ui->comboBox_4->clear();
    QSqlQuery query;
    QStringList m_anno;
    query.prepare("select plesso from alunni");
    query.exec();
    while(query.next())
    {
        m_anno << query.value(0).toString();
    }
    m_anno.removeDuplicates();
    
    ui->comboBox_4->addItems(m_anno);
}

void alunni::comboSezione()
{
    ui->comboBox_2->clear();
    QSqlQuery query;
    QStringList m_anno;
    query.prepare("select sezione from alunni");
    query.exec();
    while(query.next())
    {
        m_anno << query.value(0).toString();
    }
    m_anno.removeDuplicates();
    
    ui->comboBox_2->addItems(m_anno);
}

void alunni::filtro()
{
    model->setFilter("classe='"+ui->comboBox->currentText()+"' and sezione='"+ui->comboBox_2->currentText()+"' "
                                    "and plesso='"+ui->comboBox_4->currentText()+"' and anno ='"+ui->comboBox_3->currentText()+"'");
    initTableView();
    clickgrid(getIndex());
}

void alunni::open_excel()
{
    QMessageBox *box= new QMessageBox(this);
    box->setWindowTitle(tr("Diploma"));
    box->setText(tr("Il file excel\ndeve essere composto:\n"));
    box->setInformativeText(tr("Cognome\nNome\nClasse\nSezione\nAnno\nPlesso"));
    box->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    box->setDefaultButton(QMessageBox::Ok);
    int ret = box->exec();
    switch(ret){
    case QMessageBox::Ok:
         //Open file excel
         excel();
         box->close();
         break;
    case QMessageBox::Cancel:
         //Close
         box->close();
         break;
    }
}

void alunni::excel()
{
    
    QString filePath = QFileDialog::getOpenFileName(0, "Apri file excel", QString(), "*.xlsx");
    if(filePath.isEmpty())
        QMessageBox::warning(this,"Diploma","Non hai aperto nesssun file");
    else{
    Document xlsx(filePath);
        
    for(int i=1; i <= xlsx.dimension().rowCount(); i++)
    {
      QProgressDialog progressDialog(this);
      progressDialog.setRange(0, xlsx.dimension().rowCount());
      progressDialog.setWindowModality(Qt::WindowModal);
      progressDialog.setWindowTitle(tr("Inserimento alunni"));
      progressDialog.setValue(i);
      progressDialog.setLabelText(tr("Inserimento alunni %1 di %2...")
                                    .arg(i).arg(xlsx.dimension().rowCount()));
      qApp->processEvents();
      QSqlQuery query;
      QString req = "INSERT INTO alunni(nome,cognome,classe,sezione,anno,plesso) VALUES('";
      if(Cell *name = xlsx.cellAt(i,1)){
	 req.append(QString(name->value().toString().toStdString().c_str()).replace("'","''"));
	 req.append("','");
      }
      if(Cell *lastname = xlsx.cellAt(i,2)){
	 req.append(QString(lastname->value().toString().toStdString().c_str()).replace("'","''"));
	 req.append("','");
      }
      if(Cell *cl = xlsx.cellAt(i,3)){
	 req.append(cl->value().toString());
	 req.append("','");
      }
      if(Cell *sez = xlsx.cellAt(i,4)){
	 req.append(sez->value().toString());
	 req.append("','");
      }
      if(Cell *year = xlsx.cellAt(i,5)){
	 req.append(year->value().toString());
	 req.append("','");
      }
      if(Cell *plexus = xlsx.cellAt(i,6)){
	 req.append(QString(plexus->value().toString().toStdString().c_str()).replace("'","''"));
	 req.append("','");
      }
      req.chop(2);
      req.append(");");
      query.prepare(req);
      progressDialog.show();
      progressDialog.update();
      if(query.exec())
           qDebug() <<  "Inserimento effettuato";
      else
           QMessageBox::warning(this,"Diploma","Errore Inserimento:\n "+query.lastError().text());  
    }
    }
    lista();
}

void alunni::stampa()
{
    if(!ui->tableView->selectionModel()->currentIndex().isValid()){
            QMessageBox::warning(this,"Diploma","Seleziona una riga per stampare....");
    }
    else{
            QPrinter *printer = new QPrinter(QPrinter::HighResolution);
	    printer->setOutputFormat(QPrinter::NativeFormat);
            QPrintPreviewDialog *preview = new QPrintPreviewDialog(printer,this);
            preview->setWindowFlags(Qt::Window);
            connect(preview,SIGNAL(paintRequested(QPrinter*)),SLOT(anteprima(QPrinter*)));
            if(preview->exec() == QPrintPreviewDialog::Accepted)
            {
                print *pr = new print();
                QModelIndex in = ui->tableView->selectionModel()->currentIndex();
                int riga = in.row();
                QModelIndex newindex = in.sibling(riga,0);
                ui->tableView->setCurrentIndex(newindex);
                ui->tableView->selectRow(riga);
                pr->update_stampa(newindex);
            }
    }
}

void alunni::anteprima(QPrinter *printer)
{
    Q_UNUSED(printer);
    QModelIndex in = ui->tableView->selectionModel()->currentIndex();
    int riga = in.row();
    QModelIndex newindex = in.sibling(riga,0);
    ui->tableView->setCurrentIndex(newindex);
    ui->tableView->selectRow(riga);
    print *pr = new print();
    pr->stampa_diploma(printer,model,&newindex);
}

void alunni::currentRowChanged(const QModelIndex& current, const QModelIndex& previous)
{
    if(current.row() != -1){
         ui->tableView->setCurrentIndex(current);
         clickgrid(current);
     }
     else{
         ui->tableView->setCurrentIndex(previous);
         clickgrid(previous);
    }
}

QModelIndex alunni::getIndex()
{
    QModelIndex index = ui->tableView->model()->index(0,0);
    ui->tableView->selectionModel()->setCurrentIndex(index,QItemSelectionModel::Rows);//setCurrentIndex(index);
    ui->tableView->setFocus();
    
    return index;
}

void alunni::initTableView()
{
    QItemSelectionModel *sm = ui->tableView->selectionModel();
    connect(sm, SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)),
            this, SLOT(currentRowChanged(const QModelIndex &,const QModelIndex &)));
}

void alunni::avanti(bool ok)
{
    if(ok){
            int  riga = ui->tableView->currentIndex().row()+1;
            QModelIndex index = ui->tableView->model()->index(riga,0);
            ui->tableView->selectionModel()->setCurrentIndex(index,QItemSelectionModel::Rows);
            ui->tableView->setFocus();
            if(riga == model->rowCount() && ok)
            {
                QMessageBox::information(this,"Diploma", "Tutte i diplomi sono stati stampati");
            }
            else
                 inviaStampa();
        }
}

void alunni::stampaTutti()
{
     if(ui->tableView->selectionModel()->currentIndex().isValid()){
            inviaStampa();
        }
        else
            QMessageBox::warning(this,"Diploma","Seleziona una o più righe");
}

void alunni::inviaStampa()
{
    if(ui->tableView->selectionModel()->currentIndex().isValid()){
            QModelIndex index = ui->tableView->selectionModel()->currentIndex();
            for(int i= 0; i <  index.row()+1  && i < model->rowCount(); ++i){
                m_id = model->data(model->index(i,0),Qt::DisplayRole).toString();
                m_alunno = model->data(model->index(i,1),Qt::DisplayRole).toString()+" "+model->data(model->index(i,2),Qt::DisplayRole).toString();
            }
                QPrinter *printer = new QPrinter(QPrinter::HighResolution);
                printer->setPageSize(QPrinter::A4);
                printer->setOrientation(QPrinter::Portrait);
                QModelIndexList indexList = ui->tableView->selectionModel()->selectedRows();
                m_diploma = new InvioStampaDiplomaThread(indexList,m_alunno,model,printer,m_id.toInt());
                connect(m_diploma,&InvioStampaDiplomaThread::inviaThread,this,&alunni::inviaThreadChanged);
                connect(m_diploma,&InvioStampaDiplomaThread::inviaTesto,this,&alunni::labelText);
                connect(m_diploma,&InvioStampaDiplomaThread::execStampa,this,&alunni::avanti);
                m_diploma->start();
        }
        else{
            QMessageBox::warning(this,"Diploma","Seleziona una riga per poter stampare");
        }
}

void alunni::inviaThreadChanged(QString _id)
{
    m_IdThread = _id;
}

void alunni::labelText(QString testo)
{
    m_testo = testo;
    ui->labelInviata->setText(m_testo);
}

alunni::~alunni()
{
    delete ui;
}
