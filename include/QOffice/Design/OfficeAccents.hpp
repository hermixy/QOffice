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


#ifndef QOFFICE_OFFICEACCENTS_HPP
#define QOFFICE_OFFICEACCENTS_HPP


// QOffice headers
#include <QOffice/Interfaces/IOfficeWidget.hpp>

// Qt headers
#include <QColor>


QOFFICE_BEGIN_NAMESPACE


/**
 * This class holds all the accent colors available
 * in QOffice, plus a customizable one.
 *
 * @class OfficeAccents
 * @author Nicolas Kogler
 * @date December 25th, 2016
 *
 */
class QOFFICE_EXPORT OfficeAccents
{
public:

    /**
     * Retrieves a predefined accent color or the custom one.
     * The enum value may not be greater than or equal to ACCENT_COLOR_END.
     *
     * @param accent The accent color type to retrieve.
     * @returns the specified accent color as QColor.
     * @throws InvalidAccentException
     *
     */
    static const QColor& get(IOfficeWidget::Accent accent);

    /**
     * Lightens up the given accent color.
     *
     * @param accent Accent color to enlight.
     *
     */
    static const QColor lighter(const QColor& accent);

    /**
     * Darkens the given accent color.
     *
     * @param accent Accent color to endark.
     *
     */
    static const QColor darker(const QColor& accent);

    /**
     * Modifies the custom accent color. The predefined accent colors
     * can not be modified this way. If one desires to have multiple
     * custom accent colors, they should implemenent a settings menu
     * in which the custom accent can be modified.
     *
     * @param color Color to set as custom accent color.
     *
     */
    static void set(const QColor& color);


private:

    // Static variables
    static std::vector<QColor> g_Colors;
};


QOFFICE_END_NAMESPACE


/**
 * @ingroup Base
 *
 * Usage example:
 * @code
 *     const QColor& c = OfficeAccents::get(IOfficeWidget::Red);
 *     OfficeAccents::set(QColor(...));
 * @endcode
 *
 * @sa IOfficeWidget::Accent
 *
 */

#endif // QOFFICE_OFFICEACCENTS_HPP
