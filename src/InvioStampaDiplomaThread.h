#ifndef INVIOSTAMPADIPLOMATHREAD_H
#define INVIOSTAMPADIPLOMATHREAD_H

#include <QtCore>
#include <QtSql>
#include <QtPrintSupport>

class InvioStampaDiplomaThread : public QThread
{
    Q_OBJECT 
public:
    InvioStampaDiplomaThread(QModelIndexList index, QString _cliente, QSqlRelationalTableModel* model, QPrinter* printer, int id, QObject* parent=0);
    ~InvioStampaDiplomaThread();
    
public slots:
    void stopProcess();
    
protected:
    void run();
    
private:
    int m_id;
    QModelIndexList m_index;
    QMutex mutex;
    QString _cliente_;
    QSqlRelationalTableModel *m_model;
    QPrinter *m_printer;
    bool m_stop;
    
signals:
    void inviaThread(QString _id);
    void inviaTesto(QString errore);
    void execStampa(bool vero);
};

#endif // INVIOSTAMPADIPLOMATHREAD_H
