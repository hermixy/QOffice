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


#ifndef QOFFICE_OFFICEWINDOWENUMS_HPP
#define QOFFICE_OFFICEWINDOWENUMS_HPP


// QOffice headers
#include <QOffice/Config.hpp>


QOFFICE_BEGIN_NAMESPACE


/**
 * Holds the state of a window button.
 *
 * @enum WinButtonState
 * @author Nicolas Kogler
 * @date December 28th, 2016
 *
 */
enum class WinButtonState
{
    None,
    Hovered,
    Pressed,
    Special
};

/**
 * Holds the state of an OfficeWindow.
 *
 * @enum WindowState
 * @author Nicolas Kogler
 * @date December 28th, 2016
 *
 */
enum class WindowState
{
    None,
    Dragging,
    Resizing
};

/**
 * Holds the resizing direction of an OfficeWindow.
 *
 * @enum WinResizeDir
 * @author Nicolas Kogler
 * @date December 28th, 2016
 *
 */
enum class WinResizeDir
{
    None    = 0x0000,
    Left    = 0x0001,
    Top     = 0x0002,
    Right   = 0x0004,
    Bottom  = 0x0008
};


Q_DECLARE_FLAGS(WinResizeDirs, WinResizeDir)
QOFFICE_END_NAMESPACE
Q_DECLARE_OPERATORS_FOR_FLAGS(off::WinResizeDirs)


#endif // QOFFICE_OFFICEWINDOWENUMS_HPP
