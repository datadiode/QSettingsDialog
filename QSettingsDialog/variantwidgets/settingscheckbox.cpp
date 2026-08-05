#include "settingscheckbox.h"

SettingsCheckBox::SettingsCheckBox(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setStyleSheet(QString("QCheckBox::indicator{height:%1;}").arg(this->fontMetrics().height() * 3 / 2));
}

void SettingsCheckBox::setValue(const QVariant &value)
{
	this->setChecked(value.toBool());
}

QVariant SettingsCheckBox::getValue() const
{
	return this->isChecked();
}

void SettingsCheckBox::resetValue()
{
	this->setChecked(false);
}
