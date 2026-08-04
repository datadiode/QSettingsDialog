#include "qsettingssettingsloader.h"

#define d this->d_ptr

class QSettingsSettingsLoaderPrivate
{
public:
	QSettingsSettingsLoaderPrivate(QSettings *settings, const QString &key, bool own);
	~QSettingsSettingsLoaderPrivate();

	QSettings *settings;
	bool deleteSettings;
	QString key;
};

QSettingsSettingsLoader::QSettingsSettingsLoader(const QString &key) :
	d_ptr(new QSettingsSettingsLoaderPrivate(new QSettings(), key, true))
{}

QSettingsSettingsLoader::QSettingsSettingsLoader(QSettings *settings, const QString &key, bool ownSettings) :
	d_ptr(new QSettingsSettingsLoaderPrivate(settings, key, ownSettings))
{}

QSettingsSettingsLoader::~QSettingsSettingsLoader() {}


bool QSettingsSettingsLoader::load(QVariant &data, bool &userEdited)
{
	if(!d->settings)
		return false;
	data = d->settings->value(d->key);
	userEdited = d->settings->contains(d->key);
	return true;
}

bool QSettingsSettingsLoader::save(const QVariant &data)
{
	if(!d->settings)
		return false;
	d->settings->setValue(d->key, data);
	return true;
}

bool QSettingsSettingsLoader::reset()
{
	if(!d->settings)
		return false;
	d->settings->remove(d->key);
	return true;
}

QHash<QString, QSettingsSettingsLoader *> QSettingsSettingsLoader::createLoaders(QSettings *settings, const QString &rootKey, bool recursive)
{
	if(!rootKey.isEmpty())
		settings->beginGroup(rootKey);

	auto resMap = createLoadersImpl(settings, rootKey, recursive);

	if(!rootKey.isEmpty())
		settings->endGroup();
	return resMap;
}

QHash<QString, QSettingsSettingsLoader *> QSettingsSettingsLoader::createLoadersImpl(QSettings *settings, const QString &rootKey, bool recursive)
{
	auto beginBase = rootKey.isEmpty() ? QString() : rootKey + QLatin1Char('/');
	QHash<QString, QSettingsSettingsLoader *> resMap;

	foreach(auto key, settings->childKeys())
		resMap.insert(beginBase + key, new QSettingsSettingsLoader(settings, beginBase + key));

	if(recursive) {
		foreach(auto group, settings->childGroups()) {
			auto newKey = beginBase + group;
			settings->beginGroup(rootKey);
			resMap.insert(createLoadersImpl(settings, newKey, true));
			settings->endGroup();
		}
	}

	return resMap;
}



QSettingsSettingsLoaderPrivate::QSettingsSettingsLoaderPrivate(QSettings *settings, const QString &key, bool own) :
	settings(settings),
	deleteSettings(own),
	key(key)
{}

QSettingsSettingsLoaderPrivate::~QSettingsSettingsLoaderPrivate()
{
	if(this->deleteSettings)
		this->settings->deleteLater();
}
