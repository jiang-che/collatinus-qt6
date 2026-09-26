/*            translationmanager.h
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

#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>

class QTranslator;

/**
 * \class TranslationManager
 * \brief UI language selection.
 *
 * Keeps the interface locale separate from the lemma-gloss language: this
 * class only deals with Qt translators (.qm catalogs); the `lemmes.*` data
 * and the target-language menu are managed elsewhere.
 *
 * Catalogs are looked up as embedded resources (`:/i18n/collatinus_<locale>.qm`,
 * produced by CMake) and, as a fallback, as files next to the data.
 */
class TranslationManager : public QObject
{
    Q_OBJECT

public:
    explicit TranslationManager(QObject *parent = nullptr);
    ~TranslationManager() override;

    /// UI locales offered in the menu, in order.
    static QStringList locales();
    static bool isKnownLocale(const QString &locale);

    /// Explicit saved locale if valid, else the system locale when it is a
    /// reasonable Simplified-Chinese one, else the built-in default ("fr").
    QString resolveInitialLocale(const QString &saved) const;

    /// Installs the translator for `locale`.  Returns true if a catalog was
    /// loaded; "fr" is the source language and needs no catalog.
    bool setLocale(const QString &locale);

    QString locale() const { return m_locale; }

private:
    bool tryLoad(QTranslator *translator, const QString &locale) const;

    QTranslator *m_translator = nullptr;
    QString m_locale;
};

#endif // TRANSLATIONMANAGER_H
