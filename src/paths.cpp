/*            paths.cpp
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

#include "paths.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

// Injected by CMake; e.g. "/usr/share/collatinus".  Empty when undefined.
#ifndef COLLATINUS_INSTALL_DATADIR
#  define COLLATINUS_INSTALL_DATADIR ""
#endif

Paths &Paths::instance()
{
    static Paths paths;
    return paths;
}

QString Paths::withSlash(QString p)
{
    if (!p.isEmpty() && !p.endsWith('/'))
        p.append('/');
    return p;
}

QString Paths::firstExistingDir(const QStringList &candidates)
{
    for (const QString &candidate : candidates)
    {
        if (candidate.isEmpty())
            continue;
        QFileInfo fi(candidate);
        if (fi.exists() && fi.isDir())
            return withSlash(fi.absoluteFilePath());
    }
    return QString();
}

void Paths::init(const QString &cliDataDir)
{
    m_cliDataDir = cliDataDir;
}

QString Paths::coreDataDir() const
{
    const QString env = QString::fromLocal8Bit(qgetenv("COLLATINUS_DATA_DIR"));
    const QString installed =
        QStringLiteral(COLLATINUS_INSTALL_DATADIR);
    return firstExistingDir(QStringList()
        << m_cliDataDir
        << env
        << QStringLiteral(COLLATINUS_INSTALL_DATADIR "/data")
        << installed
        << QCoreApplication::applicationDirPath() + QStringLiteral("/data")
    );
}

QString Paths::userDataDir() const
{
    // The application identifier is kept independent from the display name
    // (SPEC 10.3), so the user data location stays ~/.local/share/collatinus.
    QString base =
        QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    if (base.isEmpty())
        base = QDir::homePath() + QStringLiteral("/.local/share");
    base += QStringLiteral("/collatinus");
    QDir().mkpath(base);
    return withSlash(base);
}

QString Paths::moduleDir() const
{
    return userDataDir();
}

QStringList Paths::dictionaryDirs() const
{
    QStringList dirs;
    dirs << withSlash(userDataDir() + QStringLiteral("/dicos"));
    const QString core = coreDataDir();
    if (!core.isEmpty())
        dirs << withSlash(core + QStringLiteral("dicos"));
    return dirs;
}

QString Paths::writableDictionaryDir() const
{
    const QString dir = userDataDir() + QStringLiteral("dicos/");
    QDir().mkpath(dir);
    return dir;
}

QString Paths::docDir() const
{
    QStringList candidates;
    candidates << QCoreApplication::applicationDirPath() + QStringLiteral("/doc");
    const QString core = coreDataDir();
    if (!core.isEmpty())
        candidates << QDir(core).absoluteFilePath(QStringLiteral("../doc"));
    candidates << QStringLiteral(COLLATINUS_INSTALL_DATADIR "/doc");
    candidates << QStringLiteral("/usr/share/doc/collatinus-qt6");
    return firstExistingDir(candidates);
}
