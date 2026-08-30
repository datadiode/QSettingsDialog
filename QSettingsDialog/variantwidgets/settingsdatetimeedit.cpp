#include "settingsdatetimeedit.h"
#include "settingsdisplaydialog.h"
#include <QCalendarWidget>
#include <QTableView>
#include <QToolButton>
#include <QHeaderView>
#include <QTimer>

static void setupCornerButton(QWidget *parent, QCalendarWidget *calendar);

SettingsDateEdit::SettingsDateEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setCalendarPopup(true);
	setupCornerButton(this, this->calendarWidget());
}

void SettingsDateEdit::setValue(const QVariant &value)
{
	this->setDate(value.toDate());
}

QVariant SettingsDateEdit::getValue() const
{
	return this->date();
}

void SettingsDateEdit::resetValue()
{
	this->setDate(QDate());
}



SettingsTimeEdit::SettingsTimeEdit(QWidget *parent) :
	QSettingsWidget(parent)
{}

void SettingsTimeEdit::setValue(const QVariant &value)
{
	qDebug("data");
	this->setTime(value.toTime());
}

QVariant SettingsTimeEdit::getValue() const
{
	return this->time();
}

void SettingsTimeEdit::resetValue()
{
	this->setTime(QTime());
}



SettingsDateTimeEdit::SettingsDateTimeEdit(QWidget *parent) :
	QSettingsWidget(parent)
{
	this->setCalendarPopup(true);
	setupCornerButton(this, this->calendarWidget());
}

void SettingsDateTimeEdit::setValue(const QVariant &value)
{
	this->setDateTime(value.toDateTime());
}

QVariant SettingsDateTimeEdit::getValue() const
{
	return this->dateTime();
}

void SettingsDateTimeEdit::resetValue()
{
	this->setDateTime(QDateTime());
}



static void setupCornerButton(QWidget *parent, QCalendarWidget *calendar)
{
	//setup calendar widget
	calendar->setVerticalHeaderFormat(QCalendarWidget::ISOWeekNumbers);
	auto viewTable = calendar->findChild<QTableView*>(QStringLiteral("qt_calendar_calendarview"));
	if(viewTable) {
		auto todayButton = new QToolButton(viewTable);
		todayButton->setAutoRaise(true);
		todayButton->setIcon(QIcon(SettingsDisplayDialog::tr(":/QSettingsDialog/icons/today.ico")));
		QObject::connect(todayButton, &QToolButton::clicked, calendar, [calendar](){
			calendar->setSelectedDate(QDate::currentDate());
		});

		auto vHeader = viewTable->verticalHeader();
		QObject::connect(vHeader, &QHeaderView::geometriesChanged,
				parent, [=](){
			todayButton->setFixedSize(todayButton->width(), vHeader->sectionSize(0));
		});

		auto hHeader = viewTable->horizontalHeader();
		QObject::connect(hHeader, &QHeaderView::geometriesChanged,
				parent, [=](){
			todayButton->setFixedSize(hHeader->sectionSize(0) - 1, todayButton->height());
		});
	}
}
