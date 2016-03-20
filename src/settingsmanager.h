#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QMap>
#include <QSettings>
#include <QtGui>
#include <QDir>
#include <QVariant>

class SettingsManager: public QObject {
Q_OBJECT

public:
	SettingsManager(QObject *parent=0);
    QVariant generalValue(QString const &key, QVariant const &defaultValue = QVariant()) const;
    void setGeneralValue( QString const &key, QVariant const &value);

    QDir *profilesDir() const;

    QDir *settingsDir, *profDir;
private:
	QSettings *general;
};

extern SettingsManager *settingsManager;

#endif
