#ifndef ALUNNI_H
#define ALUNNI_H

#include <QDialog>
#include <QtWidgets>
#include <QtSql>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>

namespace Ui {
class alunni;
}

class alunni : public QDialog
{
    Q_OBJECT

public:
    explicit alunni(QWidget *parent = 0);
    ~alunni();

public slots:
    void open_excel();
    void excel();
    void lista();
    void clickgrid();
    void cerca();
    void stampa();
    void anteprima(QPrinter *printer);
private:
    Ui::alunni *ui;
    QSqlRelationalTableModel *model;
};

extern alunni *m_alunni;
#endif // ALUNNI_H
