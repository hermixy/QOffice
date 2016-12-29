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


#ifndef QOFFICE_OFFICEPLUGINCOLLECTION_HPP
#define QOFFICE_OFFICEPLUGINCOLLECTION_HPP


// QOffice headers
#include <QOffice/Config.hpp>

// Qt headers
#include <QtDesigner/QtDesigner>
#include <QtCore/QtPlugin>


QOFFICE_BEGIN_NAMESPACE


/**
 * Wraps all plugins in one collection.
 *
 * @class OfficePluginCollection
 * @author Nicolas Kogler
 * @date December 28th, 2016
 *
 */
class OfficePluginCollection : public QObject,
                               public QDesignerCustomWidgetCollectionInterface
{
public:

    /**
     * Initializes a new instance of OfficePluginCollection.
     * Adds an instance of all custom plugins to a list.
     *
     * @param parent The qt designer as parent.
     *
     */
    OfficePluginCollection(QObject* parent = nullptr);

    /**
     * Retrieves a list of all custom plugins.
     *
     * @returns all instantiated plugins.
     *
     */
    QList<QDesignerCustomWidgetInterface *> customWidgets() const override;


private:

    // Members
    QList<QDesignerCustomWidgetInterface *> m_Plugins;

    // Metadata
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "at.kgl.QOffice.OfficePluginCollection")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEPLUGINCOLLECTION_HPP
