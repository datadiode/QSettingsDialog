#include "settingspathparser.h"

const QRegularExpression SettingsPathParser::realIdRegex(QStringLiteral(R"__(^([0-9a-z_\-]+)$)__"),
														 QRegularExpression::CaseInsensitiveOption);
const QRegularExpression SettingsPathParser::allIdRegex(QStringLiteral(R"__(^([0-9a-z_\-]*|\.)$)__"),
														QRegularExpression::CaseInsensitiveOption);
const QRegularExpression SettingsPathParser::fullPathRegex(QStringLiteral(R"__(^(\.\.|([0-9a-z_\-]*|\.)\/([0-9a-z_\-]*|\.)(?:(\/)([0-9a-z_\-]*))?)?$)__"),
														   QRegularExpression::CaseInsensitiveOption);
const QRegularExpression SettingsPathParser::partialPathRegex(QStringLiteral(R"__(^(\.\.|([0-9a-z_\-]*|\.)(?:\/([0-9a-z_\-]*|\.)(?:\/([0-9a-z_\-]*|\.))?)?)?$)__"),
															  QRegularExpression::CaseInsensitiveOption);

void SettingsPathParser::validateId(const QString &id, bool realIdOnly)
{
	if(realIdOnly) {
		if(!realIdRegex.match(id).hasMatch())
			throw InvalidContainerPathException();
	} else {
		if(!allIdRegex.match(id).hasMatch())
			throw InvalidContainerPathException();
	}
}

QVector<QString> SettingsPathParser::parseFullPath(const QString &path)
{
	auto match = fullPathRegex.match(path);
	if(!match.hasMatch())
		throw InvalidContainerPathException();

	if(match.captured(1).isEmpty())
		return QVector<QString>(3, QString());
	else if(match.captured(1) == QStringLiteral(".."))
		return {QStringLiteral("."), QStringLiteral(".")};
	else {
		if(match.captured(4).isEmpty()) {
			return {
				match.captured(2),
				match.captured(3)
			};
		} else {
			return {
				match.captured(2),
				match.captured(3),
				match.captured(5)
			};
		}
	}
}

#include <QDebug>
QStringList SettingsPathParser::parsePartialPath(const QString &path)
{
	auto match = partialPathRegex.match(path);
	if(!match.hasMatch())
		throw InvalidContainerPathException();

	if(match.captured(1).isEmpty())
		return QVector<QString>(3, QString()).toList();
	else if(match.captured(1) == QStringLiteral(".."))
		return {QStringLiteral("."), QStringLiteral(".")};
	else {
		auto all = match.capturedTexts();
		all.removeFirst();
		qDebug() << all;
		return all;
	}
}

QString SettingsPathParser::createPath(const QString &categoryId, const QString &sectionId, const QString &groupId)
{
	validateId(categoryId, false);
	validateId(sectionId, false);
	if(groupId.isNull())
		return QStringList({categoryId, sectionId}).join(QLatin1Char('/'));
	else {
		validateId(groupId, false);
		return QStringList({categoryId, sectionId, groupId}).join(QLatin1Char('/'));
	}
}

QString SettingsPathParser::joinPath(const QString &sectionPath, const QString &groupId)
{
	auto elements = parseFullPath(sectionPath);
	if(elements.size() != 2)
		throw InvalidContainerPathException();

	validateId(groupId, false);
	elements.append(groupId);
	return elements.toList().join(QLatin1Char('/'));
}
