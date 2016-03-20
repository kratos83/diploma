#ifndef ANNO_H
#define ANNO_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class anno;
}

class anno : public QDialog
{
    Q_OBJECT

public:
    explicit anno(QWidget *parent = 0);
    ~anno();

public slots:
    void visAnno();
    void ApplyAnno();
private:
    Ui::anno *ui;
};

#endif // ANNO_H
