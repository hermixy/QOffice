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


#ifndef QOFFICE_INVALIDACCENTEXCEPTION_HPP
#define QOFFICE_INVALIDACCENTEXCEPTION_HPP


// QOffice headers
#include <QOffice/Interfaces/IOfficeWidget.hpp>

// Standard headers
#include <stdexcept>


QOFFICE_BEGIN_NAMESPACE


/**
 * This class represents a C++ exception. It should be thrown
 * in functions that take an IOfficeWidget::Accent value as parameter.
 *
 * @class InvalidAccentException
 * @author Nicolas Kogler
 * @date December 25th, 2016
 *
 */
class QOFFICE_EXPORT InvalidAccentException : public std::exception
{
public:

    /**
     * Initializes a new instance of the InvalidAccentException class.
     * The first argument should always be the macro 'QOFFICE_FUNC' in
     * order to know the name of the function that threw the exception.
     *
     * @param func Signature of the function that threw the error.
     * @param value The enum value that caused the overflow.
     *
     */
    InvalidAccentException(std::string func, IOfficeWidget::Accent value) noexcept;

    /**
     * Retrieves the cause of the exception.
     *
     * @returns the cause as string.
     *
     */
    const char* what() const noexcept override;


private:

    // Members
    std::string m_What;
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_INVALIDACCENTEXCEPTION_HPP
