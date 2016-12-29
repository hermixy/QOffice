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


#ifndef QOFFICE_OFFICEWIDGET_HPP
#define QOFFICE_OFFICEWIDGET_HPP


// QOffice headers
#include <QOffice/Interfaces/IOfficeWidget.hpp>

// Qt headers
#include <QWidget>


QOFFICE_BEGIN_NAMESPACE


/**
 * This is the vanilla office widget that is used
 * as base class for many widgets with custom logic.
 *
 * @class OfficeWidget
 * @author Nicolas Kogler
 * @date December 25th, 2016
 *
 */
class QOFFICE_EXPORT OfficeWidget : public QWidget, public IOfficeWidget
{
public:

    /**
     * Initializes a new instance of OfficeWidget.
     *
     * @param parent The parent of this widget.
     *
     */
    OfficeWidget(QWidget* parent = nullptr);


    /**
     * Reimplemented pure virtual function from IOfficeWidget.
     * Retrieves the accent color for this office widget.
     *
     * @returns the current accent color.
     *
     */
    Accent accent() const override;

    /**
     * Reimplmented pure virtual function from IOfficeWidget.
     * Specifies the new accent color for this office widget.
     * Should never be called manually by the programmer, except
     * within the top-level OfficeWindow instance.
     *
     * @param accent New accent color of the office widget.
     *
     */
    void setAccent(Accent accent) override;


protected:

    /**
     * Renders the object name of this widget in the accent
     * color in order to test the IOfficeWidget interface.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;


private:

    Q_OBJECT
};


QOFFICE_END_NAMESPACE


#endif // QOFFICE_OFFICEWIDGET_HPP
