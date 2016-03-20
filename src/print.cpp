#include "print.h"
#include "alunni.h"
#include <QDir>
#include <qdebug.h>
#include <QPen>
#include <QColor>
#include <QLocale>
#include <QPainter>
#include <QProcess>

print::print()
{
    printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageMargins(15.0,15.0,15.0,15.0,QPrinter::Millimeter);
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(254);
    stampaDlg = new QPrintDialog();
    stampaDlg->setEnabledOptions(QAbstractPrintDialog::PrintPageRange);
    local_settings = new QLocale(QLocale::system());
    painter = new QPainter();
}

void print::rettangolo_diploma_logo()
{
    //Immagine 1024x683 in pixel, in millimetri
    //uguale a 2650x1780
    QRect target(0,0,2650,1780);
    QImage img(":/images/screen.png");
    painter->drawImage(target,img);
    //Logo stato
    QRect logo(1280,100,150,150);
    QImage img_logo(":/images/logo_stato.png");
    painter->drawImage(logo,img_logo);

    QSqlQuery query;
    query.prepare("select * from scuola where id='1'");
    query.exec();
    if(query.next())
    {
        QString intestazione = query.value(1).toString()+"\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t"+
                               query.value(2).toString()+" "+query.value(3).toString()+
                               " - "+query.value(4).toString()+", "+query.value(5).toString();
        int id = QFontDatabase::addApplicationFont(":/font/Book Antiqua Regular.ttf");
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        painter->setFont(QFont(family,14,QFont::Bold,true));
        painter->setPen(QPen(Qt::black,1));
        painter->drawText(600,260,2000,400,Qt::AlignVCenter || Qt::AlignHCenter,intestazione);
        dirigente = query.value(6).toString();
    }
}

void print::stampa_diploma(QPrinter *printer, QSqlQueryModel *dataset,
                           QModelIndex *index)
{
    printer->setPageMargins(15.0,15.0,15.0,15.0,QPrinter::Millimeter);
    printer->setPaperSize(QPrinter::A4);
    printer->setResolution(254);
    printer->setOrientation(QPrinter::Landscape);
    painter->begin(printer);
    painter->setRenderHint(QPainter::Antialiasing,true);

    pagina();

    int recNo = 0;
    if(index->row() < dataset->rowCount())
    {
       for(int secRow=0; secRow < 1; ++secRow){
           QSqlRecord rec = dataset->record(index->row());
           if(!rec.isEmpty()){
                nome = rec.value("nome").toString();
                cognome = rec.value("cognome").toString();
                anno = rec.value("anno").toString();
                classe = rec.value("classe").toString();
                sezione = rec.value("sezione").toString();
                plesso = rec.value("plesso").toString();
           }
       }
    }

    if(recNo < dataset->rowCount()){
             pagina();
    }
    painter->end();
}

void print::pagina()
{
    //Visualizzo immagine e logo
    rettangolo_diploma_logo();
    painter->setRenderHint(QPainter::Antialiasing,true);
    //Visualizzo testo del diploma
    int id = QFontDatabase::addApplicationFont(":/font/Algerian.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    painter->setFont(QFont(family,48));
    painter->drawText(950,420,1000,300,Qt::AlignVCenter || Qt::AlignHCenter,"DIPLOMA");
    int f = QFontDatabase::addApplicationFont(":/font/OpenSans.ttf");
    QString open = QFontDatabase::applicationFontFamilies(f).at(0);
    painter->setFont(QFont(open,15,true,true));
    //Scrivo conseguito
    painter->drawText(200,700,600,100,Qt::AlignLeft,"Conseguito dall'alunno ");
    painter->drawText(200,900,1000,100,Qt::AlignLeft,"che ha frequentato nell'anno scolastico");
    painter->drawText(1600,900,300,100,Qt::AlignLeft,"la classe");
    painter->drawText(200,1100,600,100,Qt::AlignLeft,"della scuola primaria");
    painter->drawText(200,1500,600,100,Qt::AlignLeft,"GLI INSEGNANTI");
    painter->drawText(1800,1500,800,100,Qt::AlignLeft,"IL DIRIGENTE SCOLASTICO");
    painter->setFont(QFont(open,28,QFont::Bold,true));
    painter->drawText(800,1200,1000,300,Qt::AlignVCenter | Qt::AlignHCenter,"Congratulazioni");
    int av = QFontDatabase::addApplicationFont(":/font/Avalon Medium.ttf");
    QString av_f = QFontDatabase::applicationFontFamilies(av).at(0);
    painter->setFont(QFont(av_f,40,true,true));
    painter->drawText(900,650,800,200,Qt::AlignJustify | Qt::AlignJustify,nome+"  "+cognome);
    painter->drawText(1250,830,800,200,Qt::AlignJustify | Qt::AlignJustify,anno);
    painter->drawText(1900,830,800,200,Qt::AlignJustify | Qt::AlignJustify,classe+" "+sezione);
    painter->drawText(800,1050,600,200,Qt::AlignJustify | Qt::AlignJustify,plesso);
    int ul = QFontDatabase::addApplicationFont(":/font/ITCBLKAD.TTF");
    QString ul_f = QFontDatabase::applicationFontFamilies(ul).at(0);
    painter->setFont(QFont(ul_f,20,true,true));
    painter->drawText(1800,1600,800,100,Qt::AlignLeft,dirigente);
}

void print::update_stampa(QModelIndex index)
{
    QSqlQuery query;
    query.prepare("UPDATE alunni SET stampa='stampato' where id='"+QString::number(index.row()+1)+"'");
    if(query.exec())
        qDebug() << "Aggiornamento effettuato correnttamente...";
    else
        qDebug() << "Aggiornamento non effettuato...";
    m_alunni->lista();
}

QString print::getNome()
{
    return nome;
}

QString print::getCognome()
{
    return cognome;
}

QString print::getClasse()
{
    return classe;
}

QString print::getSezione()
{
    return sezione;
}

QString print::getPlesso()
{
    return plesso;
}

QString print::getAnno()
{
    return anno;
}

QString print::getDirigente()
{
    return dirigente;
}
