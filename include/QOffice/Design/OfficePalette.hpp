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


#ifndef QOFFICE_OFFICEPALETTE_HPP
#define QOFFICE_OFFICEPALETTE_HPP


// QOffice headers
#include <QOffice/Config.hpp>

// Qt headers
#include <QColor>


QOFFICE_BEGIN_NAMESPACE


/**
 * Holds common color values used by QOffice.
 *
 * @class OfficePalette
 * @author Nicolas Kogler
 * @date December 29th, 2016
 *
 */
class QOFFICE_EXPORT OfficePalette
{
public:

    /**
     * Holds all palette roles available in OfficePalette.
     *
     * @enum PaletteRole
     *
     */
    enum PaletteRole
    {
        Background,
        Foreground,
        DisabledText,
        Max
    };


    /**
     * Retrieves the color in the palette that
     * corresponds to the given palette role.
     *
     * @param role The role of the color to retrieve.
     * @returns the color defined by \p role.
     * @throws InvalidPaletteRoleException
     *
     */
    static const QColor& get(PaletteRole role);


private:

    // Static members
    static std::vector<QColor> g_Colors;
};


QOFFICE_END_NAMESPACE


/**
 * @ingroup Base
 *
 * Usage example:
 * @code
 *     const QColor& c = OfficePalette::get(PaletteRole::Background);
 * @endcode
 *
 * @sa OfficePalette::PaletteRole
 *
 */

#endif // QOFFICE_OFFICEPALETTE_HPP
