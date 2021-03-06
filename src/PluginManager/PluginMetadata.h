#ifndef Corrade_PluginManager_PluginMetadata_h
#define Corrade_PluginManager_PluginMetadata_h
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
 * @brief Class Corrade::PluginManager::PluginMetadata
 */

#include <string>
#include <vector>
#include <map>

#include "Utility/Translator.h"
#include "corradePluginManagerVisibility.h"

namespace Corrade { namespace PluginManager {

/**
@brief Plugin metadata

This class stores metadata about particular plugin. The plugin metadata are
stored in plugin configuration file, which resides either besides the dynamic
plugin binary in a filesystem or is compiled directly into executable with an
static plugin. See @ref plugin-management for tutorial and brief introduction
into how plugins work.

The plugin configuration file has an simple syntax (see
@ref Utility::Configuration "Configuration" class documentation for full
specification). The file stores plugin name, description, list of authors,
plugin version, list of dependencies (if the plugin depends on another) and
list of replaced plugins (if the plugin can replace plugin and provide the
same or better functionality). Plugin name and description can be translated
into more languages just by adding a new subgroup named after that language
locale code. Full featured example:

    # Plugin version
    version=1.0

    # List of authors
    author=Vladimír Vondruš <mosra@centrum.cz>
    author=Some Random John Doe <john@doe.net>

    # Dependencies
    depends=SomeRandomJohnDoesPlugin
    depends=BaseMatrixPlugin
    depends=SkyNetPlugin

    # Replaced plugins
    replaces=CrashingMatrixPlugin
    replaces=AlphaMatrixPlugin

    # Metadata for default language (English)
    [metadata]
    name=Good Matrix
    description=My first matrix without bugs

    # Metadata in Czech
    [metadata/cs_CZ]
    name=Dobrý Matrix
    description=Můj první Matrix bez chyb v Matrixu
 */
class CORRADE_PLUGINMANAGER_EXPORT PluginMetadata {
    friend class AbstractManager;

    public:
        /**
         * @brief Constructor
         * @param conf          Configuration file with plugin metadata
         */
        explicit PluginMetadata(const Utility::Configuration& conf);

        /**
         * @brief Plugin name
         *
         * Descriptive name of plugin. Not to be confused with name under which
         * the plugin is loaded. If translation for current Translator::locale()
         * is present, returns the translated name.
         * @note This field is constant during whole plugin lifetime.
         */
        const std::string* name() const { return _name; }

        /**
         * @brief Plugin description
         *
         * More detailed description of plugin. If translation for current
         * Translator::locale() is present, returns the translated name.
         * @note This field is constant during whole plugin lifetime.
         */
        const std::string* description() const { return _description; }

        /**
         * @brief Plugin author(s)
         *
         * @note This field is constant during whole plugin lifetime.
         */
        const std::vector<std::string>& authors() const { return _authors; }

        /**
         * @brief Plugin version
         *
         * @note This field is constant during whole plugin lifetime.
         */
        std::string version() const;

        /**
         * @brief Plugins on which this plugin depend
         *
         * List of plugins which must be loaded before this plugin can be
         * loaded. See also @ref PluginMetadata::replaces().
         * @note Thus field is constant during whole plugin lifetime.
         */
        const std::vector<std::string>& depends() const { return _depends; }

        /**
         * @brief Plugins which depend on this plugin
         *
         * List of plugins which uses this plugin. This plugin cannot be
         * unloaded when any of these plugins are loaded.
         * @note This list is automatically created by plugin manager and can
         *      be changed in plugin lifetime.
         */
        std::vector<std::string> usedBy() const;

        /**
         * @brief Plugins which are replaced with this plugin
         *
         * Plugins which depends on them can be used with this plugin. The
         * plugin cannot be loaded when any of the replaced plugins are loaded.
         * @note Thus field is constant during whole plugin lifetime.
         */
        const std::vector<std::string>& replaces() const { return _replaces; }

        /**
         * @brief Plugins which replaces this plugin
         *
         * List of plugins which can replace this plugin. Every plugin which
         * depends on this plugin would work also with these.
         * @note This list is automatically created by plugin manager and can
         *      change in plugin lifetime.
         */
        std::vector<std::string> replacedWith() const;

    private:
        Utility::Translator translator;

        const std::string *_name,
            *_description;
        std::string _version;

        std::vector<std::string> _authors,
            _depends,
            _usedBy,
            _replaces,
            _replacedWith;
};

}}

#endif
