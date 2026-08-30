#include "containerelements.h"
#include "settingsdisplaydialog.h"

QSharedPointer<SettingsSection> SettingsSection::createDefaultSection()
{
	return QSharedPointer<SettingsSection>(new SettingsSection(SettingsDisplayDialog::tr("General")));
}

QSharedPointer<SettingsCategory> SettingsCategory::createDefaultCategory()
{
	auto cat = new SettingsCategory(SettingsDisplayDialog::tr("General Settings"));
	cat->icon = QIcon(SettingsDisplayDialog::tr(":/QSettingsDialog/icons/settings.ico"));
	return QSharedPointer<SettingsCategory>(cat);
}
