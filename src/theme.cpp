/*            theme.cpp
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

#include "theme.h"

#include <QApplication>
#include <QColor>
#include <QStyle>
#include <QStyleFactory>

namespace Theme
{

QPalette lightPalette()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor(0xf2, 0xf2, 0xf2));
    p.setColor(QPalette::WindowText, QColor(0x1a, 0x1a, 0x1a));
    p.setColor(QPalette::Base, QColor(0xff, 0xff, 0xff));
    p.setColor(QPalette::AlternateBase, QColor(0xe9, 0xe9, 0xe9));
    p.setColor(QPalette::Text, QColor(0x1a, 0x1a, 0x1a));
    p.setColor(QPalette::Button, QColor(0xe6, 0xe6, 0xe6));
    p.setColor(QPalette::ButtonText, QColor(0x1a, 0x1a, 0x1a));
    p.setColor(QPalette::ToolTipBase, QColor(0xff, 0xff, 0xdc));
    p.setColor(QPalette::ToolTipText, QColor(0x1a, 0x1a, 0x1a));
    p.setColor(QPalette::Highlight, QColor(0x30, 0x78, 0xc8));
    p.setColor(QPalette::HighlightedText, QColor(0xff, 0xff, 0xff));
    p.setColor(QPalette::Link, QColor(0x00, 0x5c, 0xc0));
    p.setColor(QPalette::PlaceholderText, QColor(0x80, 0x80, 0x80));
    p.setColor(QPalette::Disabled, QPalette::Text, QColor(0x9a, 0x9a, 0x9a));
    p.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(0x9a, 0x9a, 0x9a));
    p.setColor(QPalette::Disabled, QPalette::WindowText, QColor(0x9a, 0x9a, 0x9a));
    return p;
}

void applyLight()
{
    // A stable style is required for the palette to take effect everywhere
    // (native styles such as gtk3 may ignore an application palette).
    if (QApplication::style()
        && QApplication::style()->objectName().compare(
               QStringLiteral("fusion"), Qt::CaseInsensitive) != 0)
    {
        if (QStyle *fusion = QStyleFactory::create(QStringLiteral("Fusion")))
            QApplication::setStyle(fusion);
    }
    QApplication::setPalette(lightPalette());
}

} // namespace Theme
