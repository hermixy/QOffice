###########################################################
#
#   QOffice: Office UI framework for Qt
#   Copyright (C) 2016-2017 Nicolas Kogler
#   License: Lesser General Public License 3.0
#
###########################################################

###########################################################
#
# QMAKE SETTINGS
###########################################################
TARGET          =       QOffice
TEMPLATE        =       lib
QT             +=       widgets uiplugin designer uitools
CONFIG         +=       plugin c++11
DEFINES        +=       QOFFICE_BUILD

###########################################################
#
# QMAKE SETTINGS (windows)
###########################################################
win32 {
    QMAKE_TARGET_COMPANY        =   Nicolas Kogler
    QMAKE_TARGET_PRODUCT        =   QOffice
    QMAKE_TARGET_DESCRIPTION    =   Office UI framework for Qt
    QMAKE_TARGET_COPYRIGHT      =   Copyright (C) 2016-2017 Nicolas Kogler
}

###########################################################
#
# COMPILER SETTINGS
###########################################################
gcc {
    QMAKE_LFLAGS        +=      -static-libgcc -static-libstdc++
}

###########################################################
#
# INCLUDE PATHS
###########################################################
INCLUDEPATH         +=      include \
                            include/QOffice \
                            include/QOffice/Widgets

###########################################################
#
# RESOURCES & MISCELLANEOUS
###########################################################
RESOURCES           +=      resources/qoffice_plugins.qrc \
                            resources/qoffice_images.qrc
DISTFILES           +=      resources/templates/class.txt \
                            resources/templates/enum.txt \
                            resources/templates/plugin.txt \
                            resources/templates/plugin_src.txt \
                            resources/templates/source.txt \
                            resources/templates/widget.txt \
                            resources/templates/widget_src.txt

###########################################################
#
# HEADER FILES
###########################################################
HEADERS             +=      include/QOffice/Config.hpp \
                            include/QOffice/Interfaces/IOfficeWidget.hpp \
                            include/QOffice/Design/OfficeAccents.hpp \
                            include/QOffice/Design/Exceptions/InvalidAccentException.hpp \
                            include/QOffice/Widgets/OfficeWidget.hpp \
                            include/QOffice/Widgets/OfficeWindow.hpp \
                            include/QOffice/Plugins/OfficeWidgetPlugin.hpp \
                            include/QOffice/Plugins/OfficeWindowPlugin.hpp \
                            include/QOffice/Plugins/OfficePluginCollection.hpp \
                            include/QOffice/Widgets/Enums/OfficeWindowEnums.hpp \
                            include/QOffice/Widgets/Constants/OfficeWindowConstants.hpp \
                            include/QOffice/Design/OfficePalette.hpp

###########################################################
#
# SOURCE FILES
###########################################################
SOURCES             +=      src/Design/Exceptions/InvalidAccentException.cpp \
                            src/Design/OfficeAccents.cpp \
                            src/Widgets/OfficeWidget.cpp \
                            src/Widgets/OfficeWindow.cpp \
                            src/Plugins/OfficeWidgetPlugin.cpp \
                            src/Plugins/OfficePluginCollection.cpp \
                            src/Plugins/OfficeWindowPlugin.cpp \
                            src/Design/OfficePalette.cpp
