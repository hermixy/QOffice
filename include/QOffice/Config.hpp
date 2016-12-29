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


#ifndef QOFFICE_CONFIG_HPP
#define QOFFICE_CONFIG_HPP


// Qt headers
#include <QtCore>

// Standard headers
#include <cstdint>
#include <cstring>


/**
 * This macro either exports or imports dynamic symbols
 * or does nothing if <em>QOFFICE_STATIC</em> is defined.
 * It furthermore only exports symbols if <em>QOFFICE_BUILD</em>
 * is defined, i.e. this library is being built.
 *
 * @def QOFFICE_EXPORT
 *
 */
#if !defined(QOFFICE_STATIC) && defined(QOFFICE_BUILD)
    #define QOFFICE_EXPORT Q_DECL_EXPORT
#else
    #define QOFFICE_EXPORT
#endif


/**
 * These macroes simplify the use of namespaces within QOffice.
 * They also ensure to change the scope of all classes whenever
 * a possible change of the QOffice namespaces occur. The macro
 * QOFFICE_USING_NAMESPACE might also be used if it is ensured
 * that there are no conflicting type names otherwise.
 *
 * @code
 *     QOFFICE_BEGIN_NAMESPACE
 *     // your code
 *     QOFFICE_END_NAMESPACE
 * @endcode
 *
 * @def QOFFICE_BEGIN_NAMESPACE QOFFICE_END_NAMESPACE QOFFICE_USING_NAMESPACE
 *
 */
#define QOFFICE_BEGIN_NAMESPACE     namespace off {
#define QOFFICE_END_NAMESPACE       }
#define QOFFICE_USING_NAMESPACE     using namespace off;


/**
 * As the GCC has no way of only retrieving scope and
 * function name (scope::func), we have to provide a
 * macro that converts <em>void scope::func(args)</em> to
 * <em>scope::func</em>. This macro makes use of the C++11
 * lambdas, which allow this function to be a one-liner and
 * therefore working for the following code:
 *
 * @code
 *     Exception ex(QOFFICE_FUNC);
 * @endcode
 *
 * @def QOFFICE_CONVERT_FUNC
 *
 */
#if defined(Q_CC_GNU)
    #define QOFFICE_CONVERT_FUNC(x) \
    {                               \
        [](const char *a) ->        \
        std::string {               \
            std::string s(a);       \
            std::size_t w =         \
            s.find_first_of(" ");   \
            s.erase(0, w+1);        \
            w=s.find_first_of("("); \
            s.erase(w, -1);         \
            return s;               \
        } (x)                       \
    }
#else
    #define QOFFICE_CONVERT_FUNC(x) (x)
#endif

/**
 * This macro tries to retrieve the current function
 * name and the scope of the function, too. Unfortunately,
 * there is no standard way to do this, therefore we use
 * compiler-specific macroes.
 *
 * @def QOFFICE_FUNC
 *
 */
#if defined(Q_CC_MSVC)
    #define QOFFICE_FUNC QOFFICE_CONVERT_FUNC(__FUNCTION__)
#elif defined(Q_CC_GNU)
    #define QOFFICE_FUNC QOFFICE_CONVERT_FUNC(__PRETTY_FUNCTION__)
#else
    #define QOFFICE_FUNC QOFFICE_CONVERT_FUNC(__func__) /* C99 standard */
#endif


/**
 * There is no pretty way of retrieving the class name
 * in c++, because every compiler has different mangling
 * conventions. This macro tries to find the class name
 * by looking at one of its pretty function names.
 *
 * @def QOFFICE_CONVERT_CLASS
 *
 */
#ifdef Q_CC_GNU
    #define QOFFICE_CONVERT_CLASS(x)\
    {                               \
        [](std::string a) ->        \
        std::string {               \
            std::string s(a);       \
            s.erase(s.find_last_of  \
                   ("::")-1,-1);    \
            return s;               \
        } (x);                      \
    }
#else
    #define QOFFICE_CONVERT_CLASS(x) (x)
#endif

/**
 * This macro tries to retrieve the current class
 * name and the scope of it, too. By using the QOFFICE_FUNC
 * macro - which returns scope::func - we are able to simply
 * cut off the last scope operator and the function name.
 *
 * @def QOFFICE_CLASS
 *
 */
#define QOFFICE_CLASS (QOFFICE_CONVERT_CLASS(QOFFICE_FUNC))


/* MSVC 2013 and lower do not support noexcept. */
#if defined(_MSC_VER) && _MSC_VER <= 1800
    #define noexcept
#endif


#endif // QOFFICE_CONFIG_HPP
