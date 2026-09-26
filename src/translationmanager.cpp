/*            translationmanager.cpp
 *
 *  This file is part of COLLATINUS.
 *
 *  COLLATINUS is free software; you can redistribute it and/or modify
 *  it under the terms of the Lesser GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  COLLATINVS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Lesser GNU General Public License for more details.
 *
 *  You should have received a copy of the Lesser GNU General Public License
 *  along with COLLATINUS; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "translationmanager.h"

#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>

#include "paths.h"

TranslationManager::TranslationManager(QObject *parent) : QObject(parent)
{
}

TranslationManager::~TranslationManager()
{
    if (m_translator)
    {
        QCoreApplication::removeTranslator(m_translator);
        delete m_translator;
    }
}

QStringList TranslationManager::locales()
{
    return QStringList() << QStringLiteral("fr") << QStringLiteral("en")
                         << QStringLiteral("zh_CN");
}

bool TranslationManager::isKnownLocale(const QString &locale)
{
    return locales().contains(locale);
}

QString TranslationManager::resolveInitialLocale(const QString &saved) const
{
    if (isKnownLocale(saved))
        return saved;

    // First launch: a Simplified-Chinese system locale selects Chinese,
    // otherwise keep the project's original default (SPEC 11.3).
    const QString sys = QLocale::system().name();
    if (sys.startsWith(QStringLiteral("zh"), Qt::CaseInsensitive))
        return QStringLiteral("zh_CN");
    return QStringLiteral("fr");
}

bool TranslationManager::tryLoad(QTranslator *translator, const QString &locale) const
{
    // 1. embedded catalog produced by CMake (qt_add_translations)
    if (translator->load(QStringLiteral(":/i18n/collatinus_") + locale
                         + QStringLiteral(".qm")))
        return true;

    // 2. catalog installed next to the data (or in the dev tree)
    const QString dir = Paths::instance().coreDataDir();
    if (!dir.isEmpty()
        && translator->load(QStringLiteral("collatinus_") + locale, dir))
        return true;

    // 3. legacy location next to the executable
    return translator->load(QStringLiteral("collatinus_") + locale,
                            QCoreApplication::applicationDirPath()
                                + QStringLiteral("/data"));
}

bool TranslationManager::setLocale(const QString &locale)
{
    if (m_translator)
    {
        QCoreApplication::removeTranslator(m_translator);
        delete m_translator;
        m_translator = nullptr;
    }

    m_locale = locale;
    if (locale.isEmpty())
        return false;

    QTranslator *candidate = new QTranslator(this);
    if (tryLoad(candidate, locale))
    {
        QCoreApplication::installTranslator(candidate);
        m_translator = candidate;
        return true;
    }

    // No catalog: the interface falls back to the source language (French).
    delete candidate;
    return false;
}
