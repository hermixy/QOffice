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
#include <QOffice/Widgets/OfficeWidget.hpp>
#include <QOffice/Design/OfficeAccents.hpp>

// Qt headers
#include <QPainter>


QOFFICE_USING_NAMESPACE


OfficeWidget::OfficeWidget(QWidget* parent)
    : QWidget(parent)
{
    m_Accent = IOfficeWidget::Blue;
}


IOfficeWidget::Accent
OfficeWidget::accent() const
{
    return m_Accent;
}


void
OfficeWidget::setAccent(Accent accent)
{
    /*for (auto* widget : children())
    {
        // Determines whether this widget subclasses IOfficeWidget.
        auto* officeWidget = dynamic_cast<IOfficeWidget*>(widget);
        if (officeWidget != nullptr)
            officeWidget->setAccent(accent);
    }*/

    m_Accent = accent;
    update();
}


void
OfficeWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(OfficeAccents::get(accent()));
    painter.drawText(rect(), objectName(), QTextOption(Qt::AlignCenter));
}
