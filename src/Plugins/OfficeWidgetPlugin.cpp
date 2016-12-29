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
#include <QOffice/Plugins/OfficeWidgetPlugin.hpp>
#include <QOffice/Widgets/OfficeWidget.hpp>

// Qt headers
#include <QtPlugin>
#include <QFile>


QOFFICE_USING_NAMESPACE


OfficeWidgetPlugin::OfficeWidgetPlugin(QObject* parent)
    : QObject(parent)
    , m_IsInitialized(false)
{
}


bool
OfficeWidgetPlugin::isInitialized() const
{
    return m_IsInitialized;
}


bool
OfficeWidgetPlugin::isContainer() const
{
    return false;
}


QString
OfficeWidgetPlugin::name() const
{
    return "off::OfficeWidget";
}


QString
OfficeWidgetPlugin::group() const
{
    return "QOffice Base Widgets";
}


QString
OfficeWidgetPlugin::includeFile() const
{
    return "QOfficeWidget";
}


QString
OfficeWidgetPlugin::domXml() const
{
    QFile xmlFile(":/qoffice/plugins/officewidget.xml");
    if (xmlFile.open(QFile::ReadOnly) != true)
        throw "XML missing for this plugin!";

    return QString(xmlFile.readAll());
}


QString
OfficeWidgetPlugin::toolTip() const
{
    return "The base widget.";
}


QString
OfficeWidgetPlugin::whatsThis() const
{
    return "OfficeWidget is the base class for all QOffice widgets.";
}


QIcon
OfficeWidgetPlugin::icon() const
{
    return QIcon(":/qoffice/plugins/officewidget.png");
}


QWidget*
OfficeWidgetPlugin::createWidget(QWidget* parent)
{
    return new OfficeWidget(parent);
}


void
OfficeWidgetPlugin::initialize(QDesignerFormEditorInterface*)
{
    if (m_IsInitialized)
        return;

    m_IsInitialized = true;
}
