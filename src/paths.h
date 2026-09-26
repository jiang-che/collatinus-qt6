/*            paths.h
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

#ifndef PATHS_H
#define PATHS_H

#include <QString>
#include <QStringList>

/**
 * \class Paths
 * \brief Resolves the directories used by Collatinus.
 *
 * Read-only core data (modeles, lemmes, morphos, ...) is searched in this
 * order:
 *   1. the value of the --data-dir command-line option;
 *   2. the COLLATINUS_DATA_DIR environment variable;
 *   3. the directory compiled in at install time;
 *   4. a development-tree fallback next to the executable (<appdir>/data).
 *
 * The user data directory uses QStandardPaths (AppDataLocation, i.e.
 * ~/.local/share/collatinus on Linux) and holds lexical modules and
 * downloaded dictionaries, so the installed system data stays read-only.
 *
 * Dictionaries are searched in the user directory first (allowing updates
 * and overrides) and then in the system data directory.  Core parser and
 * morphology files are never resolved from the user directory, so ordinary
 * user files cannot accidentally shadow the engine.
 *
 * All directories returned here end with a '/'.
 */
class Paths
{
public:
    static Paths &instance();

    /// Must be called once before any other method; cliDataDir is the value
    /// of --data-dir (possibly empty).
    void init(const QString &cliDataDir = QString());

    /// The first configured --data-dir, if any (for diagnostics).
    QString commandLineDataDir() const { return m_cliDataDir; }

    /// Read-only engine data.  Empty if none could be found.
    QString coreDataDir() const;

    /// Writable user directory (created on demand).
    QString userDataDir() const;

    /// Writable directory for lexical modules.
    QString moduleDir() const;

    /// Directories to search for dictionaries, user first.
    QStringList dictionaryDirs() const;

    /// Where downloaded/installed dictionaries must be written.
    QString writableDictionaryDir() const;

    /// HTML documentation directory (empty if not found).
    QString docDir() const;

private:
    Paths() = default;

    static QString withSlash(QString p);
    static QString firstExistingDir(const QStringList &candidates);

    QString m_cliDataDir;
};

#endif // PATHS_H
