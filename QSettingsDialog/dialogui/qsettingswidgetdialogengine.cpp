#include "qsettingswidgetdialogengine.h"
#include "settingsdisplaydialog.h"
#include "settingsenumwidgetfactory.h"
#include "commonfactoryregistry.h"
#include <QMap>

#define d this->d_ptr

class QSettingsWidgetDialogEnginePrivate
{
public:
	static QList<QSharedPointer<QSettingsWidgetFactoryRegistry>> globalRegistries;
	static QHash<int, QSharedPointer<QSettingsGroupWidgetFactory>> globalGroupFactories;
	static QHash<int, UiPropertyMap> globalGroupProperties;

	QSharedPointer<CommonFactoryRegistry> commonFactory;
	QMultiMap<int, QSharedPointer<QSettingsWidgetFactoryRegistry>> currentRegistries;
	QHash<int, QSharedPointer<QSettingsGroupWidgetFactory>> groupFactories;
	QHash<int, UiPropertyMap> groupProperties;

	QSettingsWidgetDialogEnginePrivate() :
		commonFactory(new CommonFactoryRegistry()),
		currentRegistries(),
		groupFactories(globalGroupFactories),
		groupProperties(globalGroupProperties)
	{
		this->currentRegistries.insert(this->commonFactory->priority(), this->commonFactory);
		foreach(auto reg, globalRegistries)
			this->currentRegistries.insert(reg->priority(), reg);
	}
};

QList<QSharedPointer<QSettingsWidgetFactoryRegistry>> QSettingsWidgetDialogEnginePrivate::globalRegistries;
QHash<int, QSharedPointer<QSettingsGroupWidgetFactory>> QSettingsWidgetDialogEnginePrivate::globalGroupFactories;
QHash<int, UiPropertyMap> QSettingsWidgetDialogEnginePrivate::globalGroupProperties;

QSettingsWidgetDialogEngine::QSettingsWidgetDialogEngine() :
	d_ptr(new QSettingsWidgetDialogEnginePrivate())
{}

QSettingsWidgetDialogEngine::~QSettingsWidgetDialogEngine() {}

QSettingsDisplayInstance *QSettingsWidgetDialogEngine::createInstance()
{
	return new SettingsDisplayDialog(this);
}

QString QSettingsWidgetDialogEngine::searchStyleSheet() const
{
	return QStringLiteral("QLabel,QCheckBox{background-color:rgba(19,232,51,0.4);}");
}

void QSettingsWidgetDialogEngine::addFactory(int displayId, QSettingsWidgetFactory *factory)
{
	d->commonFactory->insertFactory(displayId, factory);
}

void QSettingsWidgetDialogEngine::addGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory, const UiPropertyMap &properties)
{
	d->groupFactories.insert(displayId, QSharedPointer<QSettingsGroupWidgetFactory>(factory));
	if(!properties.isEmpty())
		d->groupProperties.insert(displayId, properties);
}

void QSettingsWidgetDialogEngine::cloneGroupFactoryWithProperties(int originalId, int cloneId, const UiPropertyMap &properties)
{
	auto factory = d->groupFactories.value(originalId);
	if(factory) {
		d->groupFactories.insert(cloneId, factory);
		d->groupProperties.insert(cloneId, properties);
	}
}

QSettingsWidgetBase *QSettingsWidgetDialogEngine::createWidget(int displayId, const UiPropertyMap &properties, QWidget *parent) const
{
	QSettingsWidgetBase *widget = nullptr;

	foreach(auto registry, d->currentRegistries.values()) {
		auto factory = registry->tryResolve(displayId);
		if(factory) {
			widget = factory->createWidget(parent);
			if(widget)
				break;
		}
	}

	if(widget)
		widget->initialize(properties);
	return widget;
}

QSettingsGroupWidgetBase *QSettingsWidgetDialogEngine::createGroupWidget(int displayId, QWidget *parent) const
{
	auto factory = d->groupFactories.value(displayId);
	if(factory) {
		QSettingsGroupWidgetBase *widget = factory->createGroupWidget(parent);
		if(widget && d->groupProperties.contains(displayId))
			widget->initialize(d->groupProperties[displayId]);
		return widget;
	} else
		return nullptr;
}

void QSettingsWidgetDialogEngine::registerGlobalFactory(int displayId, QSettingsWidgetFactory *factory)
{
	CommonFactoryRegistry::addGlobalFactory(displayId, factory);
}

void QSettingsWidgetDialogEngine::registerGlobalGroupFactory(int displayId, QSettingsGroupWidgetFactory *factory)
{
	QSettingsWidgetDialogEnginePrivate::globalGroupFactories.insert(displayId, QSharedPointer<QSettingsGroupWidgetFactory>(factory));
}

void QSettingsWidgetDialogEngine::cloneGlobalGroupFactoryWithProperties(int originalId, int cloneId, const UiPropertyMap &properties)
{
	auto factory = QSettingsWidgetDialogEnginePrivate::globalGroupFactories.value(originalId);
	if(factory) {
		QSettingsWidgetDialogEnginePrivate::globalGroupFactories.insert(cloneId, factory);
		QSettingsWidgetDialogEnginePrivate::globalGroupProperties.insert(cloneId, properties);
	}
}

void QSettingsWidgetDialogEngine::addRegistry(QSettingsWidgetFactoryRegistry *registry)
{
	d->currentRegistries.insert(registry->priority(), QSharedPointer<QSettingsWidgetFactoryRegistry>(registry));
}

void QSettingsWidgetDialogEngine::registerGlobalRegistry(QSettingsWidgetFactoryRegistry *registry)
{
	QSettingsWidgetDialogEnginePrivate::globalRegistries.append(QSharedPointer<QSettingsWidgetFactoryRegistry>(registry));
}
