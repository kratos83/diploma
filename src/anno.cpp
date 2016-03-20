#include "anno.h"
#include "ui_anno.h"
#include "settingsmanager.h"
#include <QDebug>

anno::anno(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::anno)
{
    ui->setupUi(this);
    setWindowTitle("Visualizza anno");
    connect(ui->chiudi,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->applica,SIGNAL(clicked(bool)),this,SLOT(ApplyAnno()));
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
    SettingsManager *set = new SettingsManager;
    set->setGeneralValue("Scuola/Anno_scolastico",ui->anno_ins->currentText());
}

anno::~anno()
{
    delete ui;
}
