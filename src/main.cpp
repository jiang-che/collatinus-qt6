/*            main.cpp
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
 *
 * © Yves Ouvrard, 2009 - 2019
 */

/**
 * \file main.cpp
 * \brief main
 * \author Yves Ouvrard
 * \version 11
 * \date 2016
 *
 * main
 */

#include <QApplication>
#include <QCommandLineParser>

#include "mainwindow.h"
#include "paths.h"

/**
 * \fn main (int argc, char *argv[])
 * \brief fonction principale de l'application.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // applicationName is the product name shown by --version; the user-data
    // location is kept stable independently (see Paths).
    QCoreApplication::setApplicationName(QStringLiteral(COLLATINUS_PRODUCT));
    QCoreApplication::setApplicationVersion(VERSION);

    QCommandLineParser parser;
    parser.setApplicationDescription(
        "Collatinus - Latin morphology and lemmatisation");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption dataDirOption(
        QStringList() << "data-dir",
        "Read the read-only data (lexica, models, documentation) from <path>.",
        "path");
    parser.addOption(dataDirOption);
    parser.process(app);

    Paths::instance().init(parser.value(dataDirOption));

    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
