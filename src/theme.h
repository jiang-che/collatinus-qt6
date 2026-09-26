/*            theme.h
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

#ifndef THEME_H
#define THEME_H

#include <QPalette>

/**
 * \namespace Theme
 * \brief Fixed light appearance.
 *
 * Collatinus is rendered with a consistent Fusion style and a light palette
 * so that it looks the same whatever the desktop theme is.  There is no
 * dark mode: switching only part of the widgets turned out to be unreliable.
 */
namespace Theme
{
/// Applies the light appearance (Fusion style + light palette).
void applyLight();

QPalette lightPalette();
}

#endif // THEME_H
