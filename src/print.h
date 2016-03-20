#ifndef PRINT_H
#define PRINT_H

#include <QtSql>
#include <QPainter>
#include <QDialog>
#include <QLocale>
#include <QModelIndex>
#include <QtGui>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrintDialog>

class print
{
public:
    print();

    void rettangolo_diploma_logo();
    void stampa_diploma(QPrinter *printer, QSqlQueryModel *dataset, QModelIndex *index);
    void pagina();
    void update_stampa(QModelIndex index);
    QString getNome();
    QString getCognome();
    QString getClasse();
    QString getAnno();
    QString getPlesso();
    QString getSezione();
    QString getDirigente();
    QPrinter *printer;
    QPainter *painter;
    QLocale *local_settings;
    QPrintDialog *stampaDlg;
    QString nome,cognome,classe,anno,plesso,sezione,dirigente;
};

#endif // PRINT_H
