#ifndef SCUOLA_H
#define SCUOLA_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class scuola;
}

class scuola : public QDialog
{
    Q_OBJECT

public:
    explicit scuola(QWidget *parent = 0);
    ~scuola();

public slots:
    void clicca();
    void inserisci();
    void aggiorna();
    void cerca();
    void clear_text();
private:
    Ui::scuola *ui;
};

#endif // SCUOLA_H
