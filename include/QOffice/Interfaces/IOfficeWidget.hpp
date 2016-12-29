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


#ifndef QOFFICE_IOFFICEWIDGET_HPP
#define QOFFICE_IOFFICEWIDGET_HPP


// QOffice headers
#include <QOffice/Config.hpp>


QOFFICE_BEGIN_NAMESPACE


/**
 * Defines the interface that should be inherited
 * by every QOffice widget publicly.
 *
 * @class IOfficeWidget
 * @author Nicolas Kogler
 * @date December 24th, 2016
 *
 */
class QOFFICE_EXPORT IOfficeWidget
{
public:

    /**
     * Defines all predefined accent colors
     * plus a customizable one.
     *
     * @enum Accent
     *
     */
    enum Accent
    {
        Blue,
        Red,
        Green,
        Orange,
        Purple,
        Custom
    };


    /**
     * Retrieves the accent color of this office widget.
     *
     * @returns the current accent color.
     *
     */
    virtual Accent accent() const = 0;

    /**
     * Specifies the new accent color for this office widget.
     * Recursively sets the accent for the child widgets, too.
     *
     * @param accent New accent color of the office widget.
     *
     */
    virtual void setAccent(Accent accent) = 0;


protected:

    // Members
    Accent m_Accent;
};


#define ACCENT_COLOR_END (IOfficeWidget::Custom + 1)


QOFFICE_END_NAMESPACE


#endif // QOFFICE_IOFFICEWIDGET_HPP
