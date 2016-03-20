#include <QDir>
#include <QSettings>
#include <QDebug>
#include "settingsmanager.h"

SettingsManager *settingsManager=0;

SettingsManager::SettingsManager(QObject *parent): QObject(parent) {

	settingsManager = this;

#ifdef Q_WS_WIN
    settingsDir = new QDir(QDir::homePath()+"/diploma_cong/");
#else
    settingsDir = new QDir(QDir::homePath()+"/.diploma_cong/");
#endif

	if(!settingsDir->exists())
		settingsDir->mkdir(settingsDir->path());

        general = new QSettings(settingsDir->path()+"/config.conf",QSettings::IniFormat);
}

QVariant SettingsManager::generalValue( const QString &key, const QVariant &defaultValue ) const
{
    return general->value(key,defaultValue);
}

void SettingsManager::setGeneralValue(QString const& key,  QVariant const& value ) {
	general->setValue(key,value);
	general->sync();
}

QDir* SettingsManager::profilesDir() const {
	return profDir;
}
