#ifndef Corrade_Utility_String_h
#define Corrade_Utility_String_h
/*
    This file is part of Corrade.

    Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

/** @file
 * @brief Class Corrade::Utility::String
 */

#include <string>
#include <vector>

#include "corradeUtilityVisibility.h"

namespace Corrade { namespace Utility {

/** @brief %String utilities */
class CORRADE_UTILITY_EXPORT String {
    public:
        /**
         * @brief Whitespace characters
         *
         * Characters for which `std::isspace()` returns `true`. Equals to
         * <tt>" \t\f\v\r\n"</tt>.
         */
        static const std::string Whitespace;

        /**
         * @brief Byte-order marker (UTF-8)
         *
         * Equals to <tt>"\xEF\xBB\xBF"</tt>.
         */
        static const std::string Bom;

        String() = delete;

        /**
         * @brief Trim leading whitespace from string
         * @param str           %String to be trimmed
         * @param characters    Characters which will be trimmed
         *
         * @see rtrim(), trim()
         */
        static std::string ltrim(std::string str, const std::string& characters = Whitespace);

        /**
         * @brief Trim trailing whitespace from string
         * @param str           %String to be trimmed
         * @param characters    Characters which will be trimmed
         *
         * @see ltrim(), trim()
         */
        static std::string rtrim(std::string str, const std::string& characters = Whitespace);

        /**
         * @brief Trim leading and trailing whitespace from string
         * @param str           %String to be trimmed
         * @param characters    Characters which will be trimmed
         *
         * Equivalent to `ltrim(rtrim(str)`.
         */
        static std::string trim(std::string str, const std::string& characters = Whitespace);

        /**
         * @brief Split string on given character
         * @param str               %String to be splitted
         * @param delim             Delimiter
         * @param keepEmptyParts    Whether to keep empty parts
         * @return Vector of splitted strings
         */
        static std::vector<std::string> split(const std::string& str, char delim, bool keepEmptyParts = true);

        /**
         * @brief Convert string to lowercase
         * @param str               %String to be converted
         * @return Lowercase version of the string
         *
         * @attention Doesn't work with UTF-8.
         */
        static std::string lowercase(std::string str);

        /**
         * @brief Convert string to uppercase
         * @param str               %String to be converted
         * @return Uppercase version of the string
         *
         * @attention Doesn't work with UTF-8.
         */
        static std::string uppercase(std::string str);
};

}}

#endif
