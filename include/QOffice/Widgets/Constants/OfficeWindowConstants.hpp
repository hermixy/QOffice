/*
 *  QOffice: Office UI framework for Qt
 *  Copyright (C) 2016-2017 Nicolas Kogler
 *
 *  This file is part of QOffice.
 *
 *  QOffice is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QOffice is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with QOffice. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#ifndef QOFFICE_OFFICEWINDOWCONSTANTS_HPP
#define QOFFICE_OFFICEWINDOWCONSTANTS_HPP


// QOffice headers
#include <QOffice/Config.hpp>


QOFFICE_BEGIN_NAMESPACE


#define DROP_SHADOW         5   ///< Drop shadow size, in pixels
#define TITLE_PADDING_X     24  ///< Horizontal title padding
#define TITLE_PADDING_Y     10  ///< Vertical title padding
#define WINDOW_BUTTON_X     11  ///< Horizontal window button distance
#define WINDOW_BUTTON_Y     9   ///< Vertical window button distance
#define TITLE_HEIGHT        36  ///< Height of the title bar
#define MENU_ITEM_SPACING   16  ///< Spacing between menu items
#define MENU_ITEM_HEIGHT    16  ///< Height (font size) of the menu items
#define MENU_ICON_Y         6   ///< Initial Y-position of the menu icons

#define DROP_SHADOW_PADDING DROP_SHADOW * 2
#define DROP_SHADOW_BLUR   -DROP_SHADOW / 4 + 1
#define ICON_POSITION_X     WINDOW_BUTTON_X + DROP_SHADOW_PADDING
#define ICON_POSITION_Y     WINDOW_BUTTON_Y + DROP_SHADOW_PADDING

#define RESIZE_TL           WinResizeDir::Top|WinResizeDir::Left
#define RESIZE_TR           WinResizeDir::Top|WinResizeDir::Right
#define RESIZE_BR           WinResizeDir::Bottom|WinResizeDir::Right
#define RESIZE_BL           WinResizeDir::Bottom|WinResizeDir::Left
#define RESIZE_T            WinResizeDir::Top
#define RESIZE_L            WinResizeDir::Left
#define RESIZE_B            WinResizeDir::Bottom
#define RESIZE_R            WinResizeDir::Right


QOFFICE_END_NAMESPACE


/**
 * @ingroup Base
 *
 * Usage example:
 * @code
 *     // code
 * @endcode
 *
 * @sa
 *
 */


#endif // QOFFICE_OFFICEWINDOWCONSTANTS_HPP
