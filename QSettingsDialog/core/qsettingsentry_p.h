#ifndef QSETTINGSENTRY_P_H
#define QSETTINGSENTRY_P_H

#include "qsettingsentry.h"

class QSettingsEntryPrivate
{
public:
	struct LoaderDeleter {
		static void cleanup(QSettingsLoader *loader);
	};

	inline QSettingsEntryPrivate(int displaytype, QSettingsLoader *loader) :
		displaytype(displaytype),
		loader(loader),
		name(),
		optional(),
		hideable(),
		tooltip(),
		properties()
#ifndef QT_NO_DEBUG
		,refCounter(0)
#endif
	{}

	const int displaytype;
	QScopedPointer<QSettingsLoader, LoaderDeleter> loader;

	QString name;
	bool optional;
	bool hideable;
	QString tooltip;

	UiPropertyMap properties;

#ifndef QT_NO_DEBUG
	int refCounter;
#endif
};

#endif // QSETTINGSENTRY_P_H
