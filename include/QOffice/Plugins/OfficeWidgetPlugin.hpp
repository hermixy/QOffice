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


#ifndef QOFFICE_OFFICEWIDGETPLUGIN_HPP
#define QOFFICE_OFFICEWIDGETPLUGIN_HPP


// QOffice headers
#include <QOffice/Config.hpp>

// Qt headers
#include <QtUiPlugin/QDesignerCustomWidgetInterface>
#include <QObject>


QOFFICE_BEGIN_NAMESPACE


/**
 * Specifies the office widget as a plugin.
 *
 * @class OfficeWidgetPlugin
 * @author Nicolas Kogler
 * @date December 28th, 2016
 *
 */
class OfficeWidgetPlugin : public QObject,
                           public QDesignerCustomWidgetInterface
{
public:

    /**
     * Initializes a new instance of OfficeWidgetPlugin.
     *
     * @param parent The qt designer as object.
     *
     */
    explicit OfficeWidgetPlugin(QObject* parent = nullptr);


    /**
     * Determines whether this plugin has been
     * initialized by the Qt designer.
     *
     * @returns true if this plugin is initialized.
     *
     */
    bool isInitialized() const override;

    /**
     * Determines whether the underlying widget is a
     * container and is capable of holding other widgets.
     *
     * @returns true if the underlying widget is a container.
     *
     */
    bool isContainer() const override;

    /**
     * Retrieves the name of the underlying widget.
     * This must be equal to the class name of the widget.
     *
     * @returns the name of the underlying widget.
     *
     */
    QString name() const override;

    /**
     * Retrieves the group in which this widget is
     * located within the toolbox of the Qt designer.
     *
     * @returns the group in which the widget resides.
     *
     */
    QString group() const override;

    /**
     * Retrieves the header file in which the underlying
     * widget class is contained. QOFFICE provides headers
     * with an include statement directly in 'include/'.
     *
     * @returns the path to the header file to include.
     *
     */
    QString includeFile() const override;

    /**
     * Retrieves the XML code that is integrated in the
     * UI file when creating an instance of this widget.
     *
     * @returns the XML code for the Qt designer.
     *
     */
    QString domXml() const override;

    /**
     * Retrieves the tooltip message to show.
     *
     * @returns the tooltip message.
     *
     */
    QString toolTip() const override;

    /**
     * Provides a short description on
     * the widget.
     *
     * @returns a summary of the widget.
     *
     */
    QString whatsThis() const override;

    /**
     * Retrieves the icon to display for this
     * widget within the designer.
     *
     * @returns the designer icon for this widget.
     *
     */
    QIcon icon() const override;

    /**
     * Instantiates a new object of sp::widgets::Widget
     * on the heap and returns its location.
     *
     * @param parent The parent container.
     * @returns the newly created widget.
     *
     */
    QWidget* createWidget(QWidget* parent) override;

    /**
     * This method is called by the Qt designer. It attempts
     * to initialize this plugin. For simple widgets without
     * extensions, absolutely does nothing.
     *
     * @param core Class exposing the extension interface.
     *
     */
    void initialize(QDesignerFormEditorInterface* core) override;


private:

    // Members
    bool m_IsInitialized;

    // Metadata
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEWIDGETPLUGIN_HPP
