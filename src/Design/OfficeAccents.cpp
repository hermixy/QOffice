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


// QOffice headers
#include <QOffice/Design/OfficeAccents.hpp>
#include <QOffice/Design/Exceptions/InvalidAccentException.hpp>


QOFFICE_USING_NAMESPACE


const QColor&
OfficeAccents::get(IOfficeWidget::Accent accent)
{
    if (accent >= ACCENT_COLOR_END)
        throw InvalidAccentException(QOFFICE_FUNC, accent);

    return g_Colors.at(accent);
}


const QColor
OfficeAccents::lighter(const QColor& accent)
{
    return QColor::fromRgba(accent.rgba() + 0x231f1f);
}


const QColor
OfficeAccents::darker(const QColor& accent)
{
    return QColor::fromRgba(accent.rgba() - 0x210b0c);
}


void
OfficeAccents::set(const QColor& color)
{
    g_Colors[IOfficeWidget::Custom] = color;
}


// Specifies the predefined accent colors.
std::vector<QColor> OfficeAccents::g_Colors =
{
    QColor(0x2b579a),
    QColor(0xa4373a),
    QColor(0x217346),
    QColor(0xb83B1d),
    QColor(0x68217a),
    QColor(0xf00bae)
};
