#include "settingslineedit.h"
#include <QUrl>
#include <QRegularExpressionValidator>
#include <QAction>

SettingsLineEdit::SettingsLineEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

bool SettingsLineEdit::hasValueChanged() const
{
	return this->isModified();
}

void SettingsLineEdit::resetValueChanged()
{
	this->setModified(false);
}

void SettingsLineEdit::setValue(const QVariant &value)
{
	this->setText(value.toString());
}

QVariant SettingsLineEdit::getValue() const
{
	return this->text();
}

void SettingsLineEdit::resetValue()
{
	this->clear();
}



SettingsByteLineEdit::SettingsByteLineEdit(QWidget *parent) :
	SettingsLineEdit(parent)
{}

void SettingsByteLineEdit::setValue(const QVariant &value)
{
	this->setText(QString::fromUtf8(value.toByteArray()));
}

QVariant SettingsByteLineEdit::getValue() const
{
	return this->text().toUtf8();
}



SettingsUrlLineEdit::SettingsUrlLineEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setValidator(new QUrlValidator(this));
	connect(this, &SettingsUrlLineEdit::editingFinished, this, [this](){
		QString text = this->text();
		this->validator()->fixup(text);
		this->setText(text);
	});
}

void SettingsUrlLineEdit::setValue(const QVariant &value)
{
	this->setText(value.toUrl().toString());
}

QVariant SettingsUrlLineEdit::getValue() const
{
	return QUrl(this->text());
}

void SettingsUrlLineEdit::resetValue()
{
	this->clear();
}



QUrlValidator::QUrlValidator(QObject *parent) :
	QValidator(parent)
{}

QValidator::State QUrlValidator::validate(QString &text, int &) const
{
	return QUrl::fromUserInput(text).isValid() ? Acceptable : Intermediate;
}

void QUrlValidator::fixup(QString &text) const
{
	text = QUrl::fromUserInput(text).toString();
}

SettingsUuidEdit::SettingsUuidEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	static const QRegularExpression regex(QStringLiteral(R"__(^\{?[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}\}?$)__"),
														 QRegularExpression::CaseInsensitiveOption);
	this->setValidator(new QRegularExpressionValidator(regex, this));
	connect(this, &SettingsUrlLineEdit::editingFinished, this, [this](){
		QString text = this->text();
		this->setText(toUuid(text).toString().toUpper());
	});

	auto action = this->addAction(QIcon(QStringLiteral(":/QSettingsDialog/icons/calc.ico")), QLineEdit::TrailingPosition);
	connect(action, &QAction::triggered,
			this, &SettingsUuidEdit::generateId);
}

void SettingsUuidEdit::setValue(const QVariant &value)
{
	this->setText(value.toUuid().toString().toUpper());
}

QVariant SettingsUuidEdit::getValue() const
{
	return toUuid(this->text());
}

void SettingsUuidEdit::resetValue()
{
	this->setText(QUuid().toString().toUpper());
}

void SettingsUuidEdit::generateId()
{
	this->setText(QUuid::createUuid().toString().toUpper());
}

QUuid SettingsUuidEdit::toUuid(QString text)
{
	if(!text.startsWith(QLatin1Char('{')))
		text.prepend(QLatin1Char('{'));
	if(!text.endsWith(QLatin1Char('}')))
		text.append(QLatin1Char('}'));
	return QUuid(text);
}
