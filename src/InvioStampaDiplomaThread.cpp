#include "InvioStampaDiplomaThread.h"
#include "print.h"

//Thread stampa
InvioStampaDiplomaThread::InvioStampaDiplomaThread(QModelIndexList index, QString _cliente,QSqlRelationalTableModel *model, QPrinter* printer, int id, QObject* parent) :
    QThread(parent),
    m_id(id),
    m_index(index),
    _cliente_(_cliente),
    m_model(model),
    m_printer(printer)
{
    m_stop = false;
}

void InvioStampaDiplomaThread::run()
{
    QModelIndex mIndex;
    for(int i=0; i < m_index.size(); ++i){
        mIndex = m_index.at(i);
    }
    
    print *pr = new print();
    pr->stampa_diploma(m_printer,m_model,&mIndex);
    emit inviaThread(QString::number(m_id));
    emit inviaTesto("Alunno  "+_cliente_);
    emit execStampa(true);
    msleep(2);
}

void InvioStampaDiplomaThread::stopProcess()
{
    mutex.lock();
    m_stop = true;
    mutex.unlock();
}

InvioStampaDiplomaThread::~InvioStampaDiplomaThread()
{
    mutex.lock();
    m_stop = true;
    mutex.unlock();

    wait();
}
