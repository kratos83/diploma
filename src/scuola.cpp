#include "scuola.h"
#include "ui_scuola.h"
#include <QDebug>
scuola::scuola(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scuola)
{
    ui->setupUi(this);
    setWindowTitle("Inserisci denominazione della scuola");
    connect(ui->chiudi,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->inserisci,SIGNAL(clicked(bool)),this,SLOT(clicca()));
    cerca();
}

void scuola::clicca()
{
    QSqlQuery Qctrl;
    Qctrl.prepare("SELECT * FROM scuola WHERE id = 1");

    Qctrl.exec();
    if(Qctrl.next()) //Se esiste già
    {
        //Tentativo di aggiornamento del record perché trovato
        aggiorna();
    }
    else
       {
          inserisci();
       }
    cerca();
}

void scuola::inserisci()
{
    QSqlQuery query;
    query.prepare("INSERT INTO scuola(id,denominazione,cap,citta,indirizzo,numero,dirigente) "
                  "VALUES('1','"+QString(ui->denom->text().toStdString().c_str()).replace("'","''")+"','"+ui->cap->text()+"','"+QString(ui->citta->text().toStdString().c_str()).replace("'","''")+"','"+QString(ui->indirizzo->text().toStdString().c_str()).replace("'","''")+"','"+ui->lineEdit->text()+"','"+QString(ui->dirigente->text().toStdString().c_str()).replace("'","''")+"')");
    if(query.exec())
          qDebug() << "Inserimento effettuato con successo";
    else
          qDebug() << "Inserimento fallito(table::scuola): " << query.lastError().text();
}

void scuola::aggiorna()
{
    QSqlQuery query;
    query.prepare("UPDATE scuola SET denominazione='"+QString(ui->denom->text().toStdString().c_str()).replace("'","''")+"',cap='"+ui->cap->text()+"',citta='"+QString(ui->citta->text().toStdString().c_str()).replace("'","''")+"', "
                  "indirizzo = '"+QString(ui->indirizzo->text().toStdString().c_str()).replace("'","''")+"',numero='"+ui->lineEdit->text()+"',dirigente='"+QString(ui->dirigente->text().toStdString().c_str()).replace("'","''")+"' "
                  "WHERE id='1'");
    if(query.exec())
          qDebug() << "Aggiornamento effettuato con successo";
    else
          qDebug() << "Aggiornamento fallito(table::scuola): " << query.lastError().text();
}

void scuola::cerca()
{
    QSqlQuery query;
    query.prepare("select * from scuola where id=1");
    query.exec();

    if(query.next()){
        ui->denom->setText(query.value(1).toString());
        ui->cap->setText(query.value(2).toString());
        ui->citta->setText(query.value(3).toString());
        ui->indirizzo->setText(query.value(4).toString());
        ui->lineEdit->setText(query.value(5).toString());
        ui->dirigente->setText(query.value(6).toString());
    }
    else
    {
        clear_text();
    }
}

void scuola::clear_text()
{
    ui->denom->setText("Inserisci denominazione della scuola");
    ui->cap->setText("CAP");
    ui->citta->setText("Inserisci città");
    ui->indirizzo->setText("Indirizzo");
    ui->lineEdit->setText("Numero via");
    ui->dirigente->setText("Inserisci il nome e cognome del dirigente");
}

scuola::~scuola()
{
    delete ui;
}
