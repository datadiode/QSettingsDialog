#ifndef QSETTINGSWIDGET_H
#define QSETTINGSWIDGET_H

#include "qsettingsdialog_global.h"
#include <QWidget>
#include <QVariant>
#include <QRegularExpression>
#include "qsettingsentry.h"

//! The base class for edit widgets in the settings dialog @ingroup grp_dialogui
class QSETTINGSDIALOGSHARED_EXPORT QSettingsWidgetBase
{
public:
	//! Constructor
	QSettingsWidgetBase();
	//! Virtual Destructor
	virtual ~QSettingsWidgetBase();

	//! Must return this as QWidget (a cast)
	virtual QWidget *asWidget() = 0;
	//! Will be called to initialize the widgets properties with the given ones
	virtual void initialize(const UiPropertyMap &uiPropertyMap, bool hideable) = 0;

	//! Whether to hide the widget if it does not match the current search pattern
	virtual bool isHideable() const = 0;

	//! Will be called to determine, whether the value has changed or not
	virtual bool hasValueChanged() const;
	//! Resets the value changed status to unchanged
	virtual void resetValueChanged();

	//! Sets the edit widgets "value"
	virtual void setValue(const QVariant &value) = 0;
	//! Gets the edit widgets "value"
	virtual QVariant getValue() const = 0;
	//! Resets the edit widgets "value"
	virtual void resetValue() = 0;

	//! Will be called to search for a specific expression inside the edit widget
	virtual inline bool searchExpression(const QRegularExpression &regex) {
		return regex.pattern().isEmpty();
	}

private:
	QVariant changedCache;
};

//! Generic base class for settings widgets @ingroup grp_dialogui
template <class TWidget>
class QSettingsWidget : public TWidget, public QSettingsWidgetBase
{
public:
	//! Creates a new widget
	using TWidget::TWidget;

	inline QWidget *asWidget() final {
		return this;
	}
	void initialize(const UiPropertyMap &uiPropertyMap, bool hideable) override {
		for(UiPropertyMap::const_iterator it = uiPropertyMap.constBegin(), end = uiPropertyMap.constEnd(); it != end; ++it)
			this->setProperty(it.key().toLocal8Bit().constData(), it.value());
		this->hideable = hideable;
	}
	bool isHideable() const override {
		return hideable;
	}
private:
	bool hideable = false;
};

Q_DECLARE_METATYPE(QSettingsWidgetBase*)

#endif // QSETTINGSWIDGET_H
