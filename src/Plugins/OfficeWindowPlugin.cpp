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
#include <QOffice/Plugins/OfficeWindowPlugin.hpp>
#include <QOffice/Widgets/OfficeWindow.hpp>

// Qt headers
#include <QtPlugin>
#include <QFile>


QOFFICE_USING_NAMESPACE


OfficeWindowPlugin::OfficeWindowPlugin(QObject* parent)
    : QObject(parent)
    , m_IsInitialized(false)
{
}


bool
OfficeWindowPlugin::isInitialized() const
{
    return m_IsInitialized;
}


bool
OfficeWindowPlugin::isContainer() const
{
    return true;
}


QString
OfficeWindowPlugin::name() const
{
    return "off::OfficeWindow";
}


QString
OfficeWindowPlugin::group() const
{
    return "QOffice Dialogs";
}


QString
OfficeWindowPlugin::includeFile() const
{
    return "QOfficeWindow";
}


QString
OfficeWindowPlugin::domXml() const
{
    QFile xmlFile(":/qoffice/plugins/officewindow.xml");
    if (xmlFile.open(QFile::ReadOnly) != true)
        throw "XML missing for this plugin!";

    return QString(xmlFile.readAll());
}


QString
OfficeWindowPlugin::toolTip() const
{
    return "The base widget.";
}


QString
OfficeWindowPlugin::whatsThis() const
{
    return "Defines the main office window.";
}


QIcon
OfficeWindowPlugin::icon() const
{
    return QIcon(":/qoffice/plugins/officewindow.png");
}


QWidget*
OfficeWindowPlugin::createWidget(QWidget* parent)
{
    return new OfficeWindow(parent);
}


void
OfficeWindowPlugin::initialize(QDesignerFormEditorInterface*)
{
    if (m_IsInitialized)
        return;

    m_IsInitialized = true;
}
