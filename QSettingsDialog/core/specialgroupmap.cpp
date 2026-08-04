#include "specialgroupmap.h"
#include "containerelements.h"

SpecialGroupMap::SpecialGroupMap() :
	groups(),
	customGroups(),
	totalOrder()
{}

SpecialGroupMap::~SpecialGroupMap() {}

int SpecialGroupMap::size() const
{
	return this->totalOrder.size();
}

bool SpecialGroupMap::hasIndex(int index) const
{
	return (index < this->totalOrder.size() &&
			index >= 0);
}

QVariant SpecialGroupMap::id(int index) const
{
	Q_ASSERT(index < this->totalOrder.size());
	return this->totalOrder[index];
}

int SpecialGroupMap::index(const QVariant &id) const
{
	return this->totalOrder.indexOf(id);
}

QList<SpecialGroupMap::Entry> SpecialGroupMap::entries() const
{
	QList<Entry> entries;
	for(int i = 0, max = this->totalOrder.size(); i < max; ++i)
		entries.append(this->entry(i));
	return entries;
}

SpecialGroupMap::Entry SpecialGroupMap::entry(int index) const
{
	Q_ASSERT(index < this->totalOrder.size());
	auto key = this->totalOrder[index];
	Entry entry;
	entry.first = key;
    if(key.type() == QVariant::Int)
		entry.second.second = this->customGroups.value(key.toInt());
	else
		entry.second.first = this->groups.value(key.toString());
	return entry;
}

bool SpecialGroupMap::remove(int index)
{
	Q_ASSERT(index < this->totalOrder.size());
	auto key = this->totalOrder.takeAt(index);
    if(key.type() == QVariant::Int)
		return this->customGroups.remove(key.toInt());
	else
		return this->groups.remove(key.toString());
}

SpecialGroupMap::Entry SpecialGroupMap::take(int index)
{
	Q_ASSERT(index < this->totalOrder.size());
	auto key = this->totalOrder.takeAt(index);
	Entry entry;
	entry.first = key;
    if(key.type() == QVariant::Int)
		entry.second.second = this->customGroups.take(key.toInt());
	else
		entry.second.first = this->groups.take(key.toString());
	return entry;
}

void SpecialGroupMap::move(int indexFrom, int indexTo)
{
	Q_ASSERT(indexFrom < this->totalOrder.size());
	Q_ASSERT(indexTo < this->totalOrder.size());
	this->totalOrder.move(indexFrom, indexTo);
}

QSharedPointer<SettingsGroup> SpecialGroupMap::append(const QString &id, SettingsGroup *entry)
{
	QSharedPointer<SettingsGroup> entryElement(entry);
	this->append(id, entryElement);
	return entryElement;
}

void SpecialGroupMap::append(const QString &id, const QSharedPointer<SettingsGroup> &entry)
{
	this->groups.insert(id, entry);
	this->cleanTotal(id);
	this->totalOrder.append(id);
}

QSharedPointer<SettingsGroup> SpecialGroupMap::prepend(const QString &id, SettingsGroup *entry)
{
	QSharedPointer<SettingsGroup> entryElement(entry);
	this->prepend(id, entryElement);
	return entryElement;
}

void SpecialGroupMap::prepend(const QString &id, const QSharedPointer<SettingsGroup> &entry)
{
	this->groups.insert(id, entry);
	this->cleanTotal(id);
	this->totalOrder.prepend(id);
}

QSharedPointer<SettingsGroup> SpecialGroupMap::insert(int index, const QString &id, SettingsGroup *entry)
{
	QSharedPointer<SettingsGroup> entryElement(entry);
	this->insert(index, id, entryElement);
	return entryElement;
}

void SpecialGroupMap::insert(int index, const QString &id, const QSharedPointer<SettingsGroup> &entry)
{
	Q_ASSERT(index <= this->totalOrder.size());
	this->groups.insert(id, entry);
	this->cleanTotal(id);
	this->totalOrder.insert(index, id);
}

int SpecialGroupMap::index(const QString &id) const
{
	int rIndex = -1;
	do {
		rIndex = this->totalOrder.indexOf(id, rIndex + 1);
		if(rIndex == -1)
			return -1;
        if(this->totalOrder[rIndex].type() != QVariant::String)
			continue;
	} while (false);
	return rIndex;
}

bool SpecialGroupMap::contains(const QString &id) const
{
	return this->groups.contains(id);
}

QList<QString> SpecialGroupMap::groupKeys() const
{
	return this->groups.keys();
}

QList<QSharedPointer<SettingsGroup> > SpecialGroupMap::groupValues() const
{
	return this->groups.values();
}

SortedMap<QString, SettingsGroup> SpecialGroupMap::createGroupMap() const
{
	SortedMap<QString, SettingsGroup> map;
	foreach(auto key, this->totalOrder) {
        if(key.type() == QVariant::String) {
			auto str = key.toString();
			map.append(str, this->groups.value(str));
		}
	}
	return map;
}

QSharedPointer<SettingsGroup> SpecialGroupMap::valueId(const QString &id) const
{
	return this->groups.value(id);
}

bool SpecialGroupMap::removeId(const QString &id)
{
	if(this->groups.remove(id)) {
		auto index = this->index(id);
		Q_ASSERT(index >= 0);
		this->totalOrder.removeAt(index);
		return true;
	} else
		return false;
}

QSharedPointer<SettingsGroup> SpecialGroupMap::takeId(const QString &id)
{
	auto group = this->groups.take(id);
	if(!group.isNull()) {
		auto index = this->index(id);
		Q_ASSERT(index >= 0);
		this->totalOrder.removeAt(index);
	}
	return group;
}

QSharedPointer<QSettingsEntry> SpecialGroupMap::append(const int &id, QSettingsEntry *entry)
{
	QSharedPointer<QSettingsEntry> entryElement(entry);
	this->append(id, entryElement);
	return entryElement;
}

void SpecialGroupMap::append(const int &id, const QSharedPointer<QSettingsEntry> &entry)
{
	this->customGroups.insert(id, entry);
	this->cleanTotal(id);
	this->totalOrder.append(id);
}

QSharedPointer<QSettingsEntry> SpecialGroupMap::prepend(const int &id, QSettingsEntry *entry)
{
	QSharedPointer<QSettingsEntry> entryElement(entry);
	this->prepend(id, entryElement);
	return entryElement;
}

void SpecialGroupMap::prepend(const int &id, const QSharedPointer<QSettingsEntry> &entry)
{
	this->customGroups.insert(id, entry);
	this->cleanTotal(id);
	this->totalOrder.prepend(id);
}

QSharedPointer<QSettingsEntry> SpecialGroupMap::insert(int index, const int &id, QSettingsEntry *entry)
{
	QSharedPointer<QSettingsEntry> entryElement(entry);
	this->insert(index, id, entryElement);
	return entryElement;
}

void SpecialGroupMap::insert(int index, const int &id, const QSharedPointer<QSettingsEntry> &entry)
{
	Q_ASSERT(index <= this->totalOrder.size());
	this->customGroups.insert(id, entry);
	this->cleanTotal(id);
	this->totalOrder.insert(index, id);
}

int SpecialGroupMap::index(const int &id) const
{
	int rIndex = -1;
	do {
		rIndex = this->totalOrder.indexOf(id, rIndex + 1);
		if(rIndex == -1)
			return -1;
        if(this->totalOrder[rIndex].type() != QVariant::Int)
			continue;
	} while (false);
	return rIndex;
}

bool SpecialGroupMap::contains(const int &id) const
{
	return this->customGroups.contains(id);
}

QList<int> SpecialGroupMap::customKeys() const
{
	return this->customGroups.keys();
}

QList<QSharedPointer<QSettingsEntry> > SpecialGroupMap::customValues() const
{
	return this->customGroups.values();
}

SortedMap<int, QSettingsEntry> SpecialGroupMap::createCustomMap() const
{
	SortedMap<int, QSettingsEntry> map;
	foreach(auto key, this->totalOrder) {
        if(key.type() == QVariant::Int) {
			auto id = key.toInt();
			map.append(id, this->customGroups.value(id));
		}
	}
	return map;
}

QSharedPointer<QSettingsEntry> SpecialGroupMap::valueId(const int &id) const
{
	return this->customGroups.value(id);
}

bool SpecialGroupMap::removeId(const int &id)
{
	if(this->customGroups.remove(id)) {
		auto index = this->index(id);
		Q_ASSERT(index >= 0);
		this->totalOrder.removeAt(index);
		return true;
	} else
		return false;
}

QSharedPointer<QSettingsEntry> SpecialGroupMap::takeId(const int &id)
{
	auto entry = this->customGroups.take(id);
	if(!entry.isNull()) {
		auto index = this->index(id);
		Q_ASSERT(index >= 0);
		this->totalOrder.removeAt(index);
	}
	return entry;
}

SpecialGroupMap::const_iterator SpecialGroupMap::begin() const
{
	return const_iterator(*this, 0);
}

SpecialGroupMap::const_iterator SpecialGroupMap::end() const
{
	return const_iterator(*this, this->totalOrder.size());
}

void SpecialGroupMap::cleanTotal(const QVariant &value)
{
	int rIndex = -1;
	do {
		rIndex = this->totalOrder.indexOf(value, rIndex + 1);
		if(rIndex == -1)
			return;
		if(this->totalOrder[rIndex].type() != value.type())
			continue;
	} while (false);
	this->totalOrder.removeAt(rIndex);
}

SpecialGroupMap::Entry SpecialGroupMap::const_iterator::operator*()
{
	return this->map.entry(index);
}

bool SpecialGroupMap::const_iterator::operator!=(const SpecialGroupMap::const_iterator &other) const
{
	return this->index != other.index;
}

SpecialGroupMap::const_iterator &SpecialGroupMap::const_iterator::operator++()
{
	this->index++;
	return (*this);
}

SpecialGroupMap::const_iterator::const_iterator(const SpecialGroupMap &map, int index) :
	map(map),
	index(index)
{}
