#include "qasyncsettingscontainer.h"
#include "qasyncsettingscontainer_p.h"
#include "qsettingsdialog_p.h"
#include "settingspathparser.h"
#include "qsettingslayout.h"

#define d this->d_ptr

QAsyncSettingsContainer::QAsyncSettingsContainer(QSettingsDialog *settingsDialog, const QString &containerPath, QObject *parent) :
	QSettingsContainer(parent),
	d_ptr(new QAsyncSettingsContainerPrivate(settingsDialog, containerPath))
{}

QAsyncSettingsContainer::~QAsyncSettingsContainer() {}

QSettingsDialog *QAsyncSettingsContainer::dialog() const
{
	return d->settingsDialog;
}

QString QAsyncSettingsContainer::containerPath() const
{
	return d->containerPath;
}

int QAsyncSettingsContainer::elementCount() const
{
	int count = 0;
	QMetaObject::invokeMethod(d.data(), "count", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(int, count));
	return count;
}

bool QAsyncSettingsContainer::isEntry(int index) const
{
	QAsyncSettingsContainerPrivate::EntryInfo info = { false, -1, -1 };
	QMetaObject::invokeMethod(d.data(), "entryInfoFromIndex", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(QAsyncSettingsContainerPrivate::EntryInfo, info),
							  Q_ARG(int, index));
	return info.isEntry;
}

int QAsyncSettingsContainer::getEntryIndex(int id) const
{
	QAsyncSettingsContainerPrivate::EntryInfo info = { false, -1, -1 };
	QMetaObject::invokeMethod(d.data(), "entryInfoFromId", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(QAsyncSettingsContainerPrivate::EntryInfo, info),
							  Q_ARG(int, id));
	return info.index;
}

int QAsyncSettingsContainer::getEntryId(int index) const
{
	QAsyncSettingsContainerPrivate::EntryInfo info = { false, -1, -1 };
	QMetaObject::invokeMethod(d.data(), "entryInfoFromIndex", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(QAsyncSettingsContainerPrivate::EntryInfo, info),
							  Q_ARG(int, index));
	return info.id;
}

QSharedPointer<QSettingsEntry> QAsyncSettingsContainer::getEntry(int id) const
{
	QSharedPointer<QSettingsEntry> entry;
	QMetaObject::invokeMethod(d.data(), "getEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(QSharedPointer<QSettingsEntry>, entry),
							  Q_ARG(int, id),
							  Q_ARG(bool, true));
	return entry;
}

QSharedPointer<QSettingsEntry> QAsyncSettingsContainer::getEntryFromIndex(int index) const
{
	QSharedPointer<QSettingsEntry> entry;
	QMetaObject::invokeMethod(d.data(), "getEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(QSharedPointer<QSettingsEntry>, entry),
							  Q_ARG(int, index),
							  Q_ARG(bool, false));
	return entry;
}

bool QAsyncSettingsContainer::transferElement(int, QSettingsContainer *, int)
{
	return false;
}

int QAsyncSettingsContainer::appendEntry(QSettingsEntry *entry)
{
	int id = -1;
	QMetaObject::invokeMethod(d.data(), "insertEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(int, id),
							  Q_ARG(int, 0),
							  Q_ARG(QSharedPointer<QSettingsEntry>, QSharedPointer<QSettingsEntry>(entry)));
	return id;
}

int QAsyncSettingsContainer::prependEntry(QSettingsEntry *entry)
{
	int id = -1;
	QMetaObject::invokeMethod(d.data(), "insertEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(int, id),
							  Q_ARG(int, -1),
							  Q_ARG(QSharedPointer<QSettingsEntry>, QSharedPointer<QSettingsEntry>(entry)));
	return id;
}

int QAsyncSettingsContainer::insertEntry(int index, QSettingsEntry *entry)
{
	int id = -1;
	QMetaObject::invokeMethod(d.data(), "insertEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(int, id),
							  Q_ARG(int, index),
							  Q_ARG(QSharedPointer<QSettingsEntry>, QSharedPointer<QSettingsEntry>(entry)));
	return id;
}

int QAsyncSettingsContainer::insertEntry(int index, QSharedPointer<QSettingsEntry> entry)
{
	int id = -1;
	QMetaObject::invokeMethod(d.data(), "insertEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(int, id),
							  Q_ARG(int, index),
							  Q_ARG(QSharedPointer<QSettingsEntry>, entry));
	return id;
}

bool QAsyncSettingsContainer::removeEntry(int id)
{
	bool removed = false;
	QMetaObject::invokeMethod(d.data(), "removeEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(bool, removed),
							  Q_ARG(int, id),
							  Q_ARG(bool, true));
	return removed;
}

bool QAsyncSettingsContainer::removeElementFromIndex(int index)
{
	bool removed = false;
	QMetaObject::invokeMethod(d.data(), "removeEntry", Qt::BlockingQueuedConnection,
							  Q_RETURN_ARG(bool, removed),
							  Q_ARG(int, index),
							  Q_ARG(bool, false));
	return removed;
}

void QAsyncSettingsContainer::moveElement(int indexFrom, int indexTo)
{
	QMetaObject::invokeMethod(d.data(), "moveEntry", Qt::BlockingQueuedConnection,
							  Q_ARG(int, indexFrom),
							  Q_ARG(int, indexTo));
}

void QAsyncSettingsContainer::moveElementAsync(int indexFrom, int indexTo)
{
	QMetaObject::invokeMethod(d.data(), "moveEntry", Qt::QueuedConnection,
							  Q_ARG(int, indexFrom),
							  Q_ARG(int, indexTo));
}

void QAsyncSettingsContainer::appendEntryAsync(QSettingsEntry *entry)
{
	QMetaObject::invokeMethod(d.data(), "insertEntry", Qt::QueuedConnection,
							  Q_ARG(int, 0),
							  Q_ARG(QSharedPointer<QSettingsEntry>, QSharedPointer<QSettingsEntry>(entry)));
}

void QAsyncSettingsContainer::prependEntryAsync(QSettingsEntry *entry)
{
	QMetaObject::invokeMethod(d.data(), "insertEntry", Qt::QueuedConnection,
							  Q_ARG(int, -1),
							  Q_ARG(QSharedPointer<QSettingsEntry>, QSharedPointer<QSettingsEntry>(entry)));
}

bool QAsyncSettingsContainer::acceptEntry(int, int, QSharedPointer<QSettingsEntry>)
{
	return false;
}



QAsyncSettingsContainerPrivate::QAsyncSettingsContainerPrivate(QSettingsDialog *settingsDialog, const QString &containerPath) :
	QObject(nullptr),
	settingsDialog(settingsDialog),
	containerPath(containerPath),
	container(nullptr)
{
	auto elements = SettingsPathParser::parseFullPath(containerPath);

	this->moveToThread(settingsDialog->thread());
	QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection,
							  Q_ARG(QSettingsDialog *, settingsDialog),
							  Q_ARG(QString, containerPath),
							  Q_ARG(bool, elements.size() == 3));
}

int QAsyncSettingsContainerPrivate::count() const
{
	return this->container->elementCount();
}

QAsyncSettingsContainerPrivate::EntryInfo QAsyncSettingsContainerPrivate::entryInfoFromIndex(int index) const
{
	EntryInfo info;
	if(index < 0 || index >= this->container->elementCount()) {
		info.index = -1;
		info.id = -1;
		info.isEntry = false;
	} else {
		info.index = index;
		info.id = this->container->getEntryId(index);
		info.isEntry = this->container->isEntry(index);
	}
	return info;
}

QAsyncSettingsContainerPrivate::EntryInfo QAsyncSettingsContainerPrivate::entryInfoFromId(int id) const
{
	EntryInfo info;
	info.index = this->container->getEntryIndex(id);
	if(info.index == -1) {
		info.id = -1;
		info.isEntry = false;
	} else {
		info.id = id;
		info.isEntry = this->container->isEntry(info.index);
	}
	return info;
}

QSharedPointer<QSettingsEntry> QAsyncSettingsContainerPrivate::getEntry(int val, bool isId) const
{
	if(isId)
		return this->container->getEntry(val);
	else {
		if(val < 0 || val >= this->container->elementCount())
			return QSharedPointer<QSettingsEntry>();
		return this->container->getEntryFromIndex(val);
	}
}

int QAsyncSettingsContainerPrivate::insertEntry(int index, QSharedPointer<QSettingsEntry> entry)
{
	if(index == -1)
		index = this->container->elementCount();
	else if(index < 0 || index > this->container->elementCount())
		return -1;
	return this->container->insertEntry(index, entry);
}

bool QAsyncSettingsContainerPrivate::removeEntry(int val, bool isId)
{
	if(isId)
		return this->container->removeEntry(val);
	else {
		if(val < 0 || val >= this->container->elementCount())
			return false;
		return this->container->removeElementFromIndex(val);
	}
}

bool QAsyncSettingsContainerPrivate::moveEntry(int indexFrom, int indexTo)
{
	if(indexFrom < 0 || indexFrom >= this->container->elementCount() ||
	   indexTo < 0 || indexTo >= this->container->elementCount())
		return false;
	else {
		this->container->moveElement(indexFrom, indexTo);
		return true;
	}
}

void QAsyncSettingsContainerPrivate::init(QSettingsDialog *settingsDialog, const QString &containerPath, bool isGroup)
{
	if(isGroup)
		this->container = new QGroupSettingsContainer(settingsDialog, containerPath, this);
	else
		this->container = new QSectionSettingsContainer(settingsDialog, containerPath, this);

	connect(settingsDialog, &QSettingsDialog::destroyed, this, [this]() {
		this->settingsDialog = nullptr;
	}, Qt::DirectConnection);
}
