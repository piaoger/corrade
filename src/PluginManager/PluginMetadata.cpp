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

#include "PluginMetadata.h"

#include "Utility/Configuration.h"

namespace Corrade { namespace PluginManager {

PluginMetadata::PluginMetadata(const Utility::Configuration& conf) {
    /* Author(s), version */
    _authors = conf.values("author");
    _version = conf.value("version");

    /* Dependencies, replacements */
    _depends = conf.values("depends");
    _replaces = conf.values("replaces");

    const Utility::ConfigurationGroup* metadata = conf.group("metadata");
    translator.setFallback(metadata);
    translator.setPrimary(metadata, true);
    _name = translator.get("name");
    _description = translator.get("description");
}

std::string PluginMetadata::version() const { return _version; }

std::vector<std::string> PluginMetadata::usedBy() const { return _usedBy; }

std::vector<std::string> PluginMetadata::replacedWith() const { return _replacedWith; }

}}
