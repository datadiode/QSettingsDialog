#ifndef CONTAINERELEMENT_H
#define CONTAINERELEMENT_H

#include <QString>
#include <QIcon>
#include <QSharedPointer>
#include "sortedmap.h"
#include "specialgroupmap.h"
#include "qsettingsentry.h"
#include "exceptions.h"

class QSettingsContainer;
struct SettingsGroup
{
	int displayId;
	QString name;
	QString tooltip;
	bool isOptional;

	SortedMap<int, QSettingsEntry> entries;

	inline SettingsGroup(int displayId, const QString &name) :
		displayId(displayId),
		name(name),
		tooltip(),
		isOptional(false),
		entries()
	{}
};

struct QSETTINGSDIALOGSHARED_EXPORT SettingsSection
{
	QString name;
	QIcon icon;
	QString tooltip;

	SpecialGroupMap groups;

	inline SettingsSection(const QString &name) :
		name(name),
		icon(),
		tooltip(),
		groups()
	{}

	static QSharedPointer<SettingsSection> createDefaultSection();
};

struct QSETTINGSDIALOGSHARED_EXPORT SettingsCategory
{
	QString name;
	QIcon icon;
	QString tooltip;

	QSharedPointer<SettingsSection> defaultSection;
	SortedMap<QString, SettingsSection> sections;

	inline SettingsCategory(const QString &name) :
		name(name),
		icon(),
		tooltip(),
		defaultSection(),
		sections()
	{}

	static QSharedPointer<SettingsCategory> createDefaultCategory();
};

struct SettingsRoot
{
	QSharedPointer<SettingsCategory> defaultCategory;
	SortedMap<QString, SettingsCategory> categories;
};

#endif // CONTAINERELEMENT_H
