#ifndef QASYNCSETTINGSCONTAINER_P_H
#define QASYNCSETTINGSCONTAINER_P_H

#include "qsettingscontainer.h"

class QAsyncSettingsContainerPrivate : public QObject
{
	Q_OBJECT

public:
	struct EntryInfo {
		bool isEntry;
		int id;
		int index;
	};

	QAsyncSettingsContainerPrivate(QSettingsDialog *settingsDialog, const QString &containerPath);

	QSettingsDialog *settingsDialog;
	const QString containerPath;

	Q_INVOKABLE int count() const;
	Q_INVOKABLE QAsyncSettingsContainerPrivate::EntryInfo entryInfoFromIndex(int index) const;
	Q_INVOKABLE QAsyncSettingsContainerPrivate::EntryInfo entryInfoFromId(int id) const;

	Q_INVOKABLE QSharedPointer<QSettingsEntry> getEntry(int val, bool isId) const;

	Q_INVOKABLE int insertEntry(int index, QSharedPointer<QSettingsEntry> entry);

	Q_INVOKABLE bool removeEntry(int val, bool isId);
	Q_INVOKABLE bool moveEntry(int indexFrom, int indexTo);

private:
	QSettingsContainer *container;

	Q_INVOKABLE void init(QSettingsDialog *settingsDialog, const QString &containerPath, bool isGroup);
};

Q_DECLARE_METATYPE(QAsyncSettingsContainerPrivate::EntryInfo)
Q_DECLARE_OPAQUE_POINTER(QSettingsDialog*)
Q_DECLARE_METATYPE(QSettingsDialog*)

#endif // QASYNCSETTINGSCONTAINER_P_H
