#include "alunni.h"
#include "ui_alunni.h"
#include "settingsmanager.h"
#include <QDebug>
#include "print.h"

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
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(clickgrid()));
    connect(ui->stampa,SIGNAL(clicked(bool)),this,SLOT(stampa()));
    lista();
}

void alunni::clickgrid()
{
    QString id_new;
    int riga = ui->tableView->selectionModel()->currentIndex().row();
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
            ui->id->setText(query.value(0).toString());
            ui->nome->setText(query.value(1).toString());
            ui->cognome->setText(query.value(2).toString());
            ui->classe->setText(query.value(3).toString());
            ui->sezione->setText(query.value(4).toString());
            ui->anno->addItem(query.value(5).toString());
            ui->plesso->addItem(query.value(6).toString());
        }
}

void alunni::lista()
{
    SettingsManager *settings = new SettingsManager(this);
    model->setTable("alunni");
    model->setFilter("anno ='"+settings->generalValue("Scuola/Anno_scolastico",QVariant()).toString()+"'");
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"Nome");
    model->setHeaderData(2,Qt::Horizontal,"Cognome");
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
}

void alunni::open_excel()
{
    QMessageBox *box= new QMessageBox(this);
    box->setWindowTitle(tr("Diploma"));
    box->setText(tr("Il file csv\ndeve essere composto:\n"));
    box->setInformativeText(tr("Nome\nCognome\nClasse\nSezione\nAnno\nPlesso"));
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
    QString filePath = QFileDialog::getOpenFileName(0, "Apri file csv", QString(), "*.csv");
    if(filePath.isEmpty())
        qDebug() << "Impossibile aprire il file";
    QFile f(filePath);
    if(f.open (QIODevice::ReadOnly)){
        QSqlQuery query;
        QTextStream ts (&f);
        while(!ts.atEnd()){
            QString req = "INSERT INTO alunni(nome,cognome,classe,sezione,anno,plesso) VALUES('";
            QStringList line = ts.readLine().split(',');
            for(int i=0; i<line.length();++i){
                req.append(line.at(i));
                req.append("','");
            }
            req.chop(2);
            req.append(");");
            query.prepare(req);
            if(query.exec())
                qDebug() <<  "Inserimento effettuato";
            else
                qDebug() <<  "Inserimento non effettuato(table::alunni): " << query.lastError().text();
        }
        f.close ();
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

alunni::~alunni()
{
    delete ui;
}
