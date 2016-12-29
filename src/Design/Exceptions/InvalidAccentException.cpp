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
#include <QOffice/Design/Exceptions/InvalidAccentException.hpp>


QOFFICE_USING_NAMESPACE


InvalidAccentException::InvalidAccentException(
      std::string func, IOfficeWidget::Accent value) noexcept
    : std::exception()
{
    m_What = std::string
             (
                std::string("An exception of type ") + QOFFICE_CLASS +
                std::string(" was thrown in function ") + func +
                std::string(". Message:\n The specified value of ") +
                std::string(std::to_string(value) + " is not valid.")
             );
}


const char*
InvalidAccentException::what() const noexcept
{
    return m_What.c_str();
}
