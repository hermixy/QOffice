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
#include <QOffice/Widgets/OfficeWindow.hpp>
#include <QOffice/Widgets/Constants/OfficeWindowConstants.hpp>
#include <QOffice/Design/OfficeAccents.hpp>
#include <QOffice/Design/OfficePalette.hpp>

// Qt headers
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QLayout>
#include <QtEvents>


QOFFICE_USING_NAMESPACE


OfficeWindow::OfficeWindow(QWidget* parent)
    : QWidget(parent)
    , m_CloseState(WinButtonState::None)
    , m_MaximState(WinButtonState::None)
    , m_MinimState(WinButtonState::None)
    , m_HasCloseBtn(true)
    , m_HasMaximBtn(true)
    , m_HasMinimBtn(true)
    , m_CanResize(true)

{
    // Manipulates the widget attributes and flags
    // in order to create a frameless window.
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // Enables mouse tracking.
    setMouseTracking(true);

    // Specifies the title rendering options.
    m_TitleOptions.setAlignment(Qt::AlignCenter);
    m_TitleOptions.setWrapMode(QTextOption::NoWrap);

    // Creates the resizing areas on the window.
    m_ResizeTopLeft     = new WinResizeArea(this, RESIZE_TL);
    m_ResizeTopRight    = new WinResizeArea(this, RESIZE_TR);
    m_ResizeBottomRight = new WinResizeArea(this, RESIZE_BR);
    m_ResizeBottomLeft  = new WinResizeArea(this, RESIZE_BL);
    m_ResizeTop         = new WinResizeArea(this, RESIZE_T);
    m_ResizeLeft        = new WinResizeArea(this, RESIZE_L);
    m_ResizeBottom      = new WinResizeArea(this, RESIZE_B);
    m_ResizeRight       = new WinResizeArea(this, RESIZE_R);

    // Loads all the window button images.
    m_CloseImage = QPixmap(":/qoffice/images/window/close.png");
    m_MaximImage = QPixmap(":/qoffice/images/window/max.png");
    m_MinimImage = QPixmap(":/qoffice/images/window/min.png");
    m_RestoreImage = QPixmap(":/qoffice/images/window/restore.png");
}


IOfficeWidget::Accent
OfficeWindow::accent() const
{
    return m_Accent;
}


OfficeWindow::AccentColor
OfficeWindow::accentColor() const
{
    return static_cast<AccentColor>(m_Accent);
}


bool
OfficeWindow::hasCloseButton() const
{
    return m_HasCloseBtn;
}


bool
OfficeWindow::hasMaximizeButton() const
{
    return m_HasMaximBtn;
}


bool
OfficeWindow::hasMinimizeButton() const
{
    return m_HasMinimBtn;
}


bool
OfficeWindow::canResize() const
{
    return m_CanResize;
}


void
OfficeWindow::setAccent(Accent accent)
{
    const QList<QWidget*> matches = findChildren<QWidget*>();
    for (auto* widget : matches)
    {
        auto* officeWidget = dynamic_cast<IOfficeWidget*>(widget);
        if (officeWidget != nullptr)
            officeWidget->setAccent(accent);
    }

    m_Accent = accent;
    update();
}


void
OfficeWindow::setAccentColor(AccentColor accent)
{
    setAccent(static_cast<Accent>(accent));
}


void
OfficeWindow::setCloseButtonVisible(bool close)
{
    m_HasCloseBtn = close;
    updateButtonRects();
    repaintTitleBar();
}


void
OfficeWindow::setMaximizeButtonVisible(bool maximize)
{
    m_HasMaximBtn = maximize;
    updateButtonRects();
    repaintTitleBar();
}


void
OfficeWindow::setMinimizeButtonVisible(bool minimize)
{
    m_HasMinimBtn = minimize;
    updateButtonRects();
    repaintTitleBar();
}


void
OfficeWindow::setResizable(bool resize)
{
    m_CanResize = resize;
    updateResizeRects();
    update();
}


void
OfficeWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QRect borderRect = m_ClientRect.adjusted(0, 0, -1, -1);

    // Retrieves the color of the current accent.
    const QColor& colorBackg = OfficePalette::get(OfficePalette::Background);
    const QColor& colorAccnt = OfficeAccents::get(accent());

    // Renders the drop shadow.
    if (!isMaximized() && m_State != WindowState::Resizing)
        painter.drawPixmap(QPoint(), m_DropShadow);

    // Renders the background and the border.
    painter.fillRect(m_ClientRect, colorBackg);
    painter.setPen(colorAccnt);
    painter.drawRect(borderRect);

    // Renders the title bar background and text.
    painter.fillRect(m_TitleRect, colorAccnt);
    painter.setFont(font());
    painter.setPen(colorBackg);
    painter.drawText(m_TitleRect, m_VisibleTitle, m_TitleOptions);

    // Renders the background color of the window buttons.
    if (m_CloseState == WinButtonState::Hovered)
        painter.fillRect(m_CloseRect, OfficeAccents::lighter(colorAccnt));
    else if (m_MaximState == WinButtonState::Hovered)
        painter.fillRect(m_MaximRect, OfficeAccents::lighter(colorAccnt));
    else if (m_MinimState == WinButtonState::Hovered)
        painter.fillRect(m_MinimRect, OfficeAccents::lighter(colorAccnt));
    else if (m_CloseState == WinButtonState::Pressed)
        painter.fillRect(m_CloseRect, OfficeAccents::darker(colorAccnt));
    else if (m_MaximState == WinButtonState::Pressed)
        painter.fillRect(m_MaximRect, OfficeAccents::darker(colorAccnt));
    else if (m_MinimState == WinButtonState::Pressed)
        painter.fillRect(m_MinimRect, OfficeAccents::darker(colorAccnt));

    // Renders the window button icons themselves.
    if (m_HasCloseBtn)
        painter.drawPixmap(centerRect(m_CloseImage, m_CloseRect), m_CloseImage);
    if (m_HasMinimBtn)
        painter.drawPixmap(centerRect(m_MinimImage, m_MinimRect), m_MinimImage);
    if (m_HasMaximBtn)
    {
        if (!isMaximized())
            painter.drawPixmap(centerRect(m_MaximImage, m_MaximRect), m_MaximImage);
        else
            painter.drawPixmap(centerRect(m_RestoreImage, m_MaximRect), m_RestoreImage);
    }
}


void
OfficeWindow::resizeEvent(QResizeEvent* event)
{
    // Does not generate a drop shadow if resizing
    // or currently being in maximized window mode.
    if (!isMaximized() && m_State != WindowState::Resizing)
        generateDropShadow();

    // Updates all rectangles, the title and the resize widgets.
    updateButtonRects();
    updateResizeRects();
    updateVisibleTitle();
    updateResizeWidgets();

    QWidget::resizeEvent(event);
}


void
OfficeWindow::mouseMoveEvent(QMouseEvent* event)
{
    bool reqUpdate = false;
    const QPoint p = event->pos();

    // Performs several hit-tests. If one of these
    // functions returns true, the title bar will be redrawn.
    if (mouseMoveDrag(p))
        return;
    if (mouseMoveSpecial(p))
        reqUpdate = true;
    if (mouseMoveHitTest(p))
        reqUpdate = true;

    if (reqUpdate)
        repaintTitleBar();
}


void
OfficeWindow::mousePressEvent(QMouseEvent* event)
{
    // Only the left button triggers events.
    if (event->button() != Qt::LeftButton)
        return;

    // Performs several hit-tests.
    const QPoint p = event->pos();
    if (mousePressDrag(p))
        return;
    if (mousePressHitTest(p))
        repaintTitleBar();
}


void
OfficeWindow::mouseReleaseEvent(QMouseEvent* event)
{
    // Only the left button triggers events.
    if (event->button() != Qt::LeftButton)
        return;

    // Performs several hit-tests.
    const QPoint p = event->pos();
    if (mouseReleaseDrag(p))
        return;
    if (mouseReleaseAction(p))
        repaintTitleBar();
}


void
OfficeWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    // Only maximizes/restores under certain conditions.
    if (event->button() == Qt::LeftButton &&
        m_DragRect.contains(event->pos()) &&
        m_CanResize && m_HasMaximBtn)
    {
        if (isMaximized())
        {
            showNormal();
            updateResizeRects();
        }
        else
        {
            showMaximized();
            updateResizeRects();
        }

        m_MaximState = WinButtonState::None;
        updateLayoutPadding();
        update();
    }
}


void
OfficeWindow::showEvent(QShowEvent*)
{
    setAccent(m_Accent);
}


void
OfficeWindow::generateDropShadow()
{
    // Creates a new pixmap that fills the entire widget.
    m_DropShadow = QPixmap(size());
    m_DropShadow.fill(Qt::transparent);

    QPainter painter(&m_DropShadow);
    QPainterPath path;

    // Defines the rounded rectangle.
    QRectF rounded(
            DROP_SHADOW_PADDING,
            DROP_SHADOW_PADDING,
            width()  - DROP_SHADOW_PADDING * 2,
            height() - DROP_SHADOW_PADDING * 2);

    // Renders the rounded rectangle.
    path.addRoundedRect(rounded, 4, 4);
    painter.fillPath(path, Qt::black);

    // Prepares the pixmap for blurring.
    QGraphicsScene scene;
    QGraphicsPixmapItem item(m_DropShadow);
    QGraphicsDropShadowEffect shadow;

    shadow.setBlurRadius(DROP_SHADOW * 2);
    shadow.setColor(Qt::black);
    shadow.setOffset(DROP_SHADOW_BLUR, DROP_SHADOW_BLUR);

    // Blurs the rectangle and renders it to the pixmap.
    item.setGraphicsEffect(&shadow);
    scene.addItem(&item);
    scene.render(&painter);
    painter.end();
}


void
OfficeWindow::repaintTitleBar()
{
    update(m_TitleRect);
}


void
OfficeWindow::updateButtonRects()
{
    const QSize& szClose = m_CloseImage.size();
    const QSize& szMaxim = m_MaximImage.size();
    const QSize& szMinim = m_MinimImage.size();

    // Calculates the initial button position.
    int paddingX = (isMaximized()) ? WINDOW_BUTTON_X : ICON_POSITION_X;
    int paddingY = (isMaximized()) ? WINDOW_BUTTON_Y : ICON_POSITION_Y;
    int initialX = width() - szClose.width() - paddingX;
    int initialY = paddingY;

    // Calculates the close button rectangle.
    if (m_HasCloseBtn)
    {
        m_CloseRect.setRect(
                    initialX - 10,
                    initialY - 8,
                    szClose.width()  + 20,
                    szClose.height() + 16);
        initialX -= (szMaxim.width() + 20);
    }

    // Calculates the maximize button rectangle.
    if (m_HasMaximBtn)
    {
        m_MaximRect.setRect(
                    initialX - 10,
                    initialY - 8,
                    szMaxim.width()  + 20,
                    szMaxim.height() + 16);
        initialX -= (szMinim.width() + 20);
    }

    // Calculates the minimize button rectangle.
    if (m_HasMinimBtn)
    {
        m_MinimRect.setRect(
                    initialX - 10,
                    initialY - 8,
                    szMinim.width()  + 20,
                    szMinim.height() + 16);
    }
}


void
OfficeWindow::updateResizeRects()
{
    // Changes the locations of the resize widgets.
    m_ResizeTopLeft->setGeometry(0, 0, 10, 10);
    m_ResizeTopRight->setGeometry(width() - 10, 0, 10, 10);
    m_ResizeBottomRight->setGeometry(width() - 10, height() - 10, 10, 10);
    m_ResizeBottomLeft->setGeometry(0, height() - 10, 10, 10);
    m_ResizeTop->setGeometry(10, 0, width() - 20, 10);
    m_ResizeRight->setGeometry(width() - 10, 10, 10, height() - 20);
    m_ResizeBottom->setGeometry(10, height() - 10, width() - 20, 10);
    m_ResizeLeft->setGeometry(0, 10, 10, height() - 20);

    // Determines the padding caused by the drop shadow.
    int dsPadding = (isMaximized()) ? 0 : DROP_SHADOW_PADDING;
    int dsAdjustm = (isMaximized()) ? DROP_SHADOW_PADDING : 0;
    int buttonWid = m_CloseRect.width() + m_MaximRect.width() + m_MinimRect.width();

    // Specifies the title dragging rectangle.
    m_DragRect.setRect(
                dsPadding,
                dsPadding,
                width() - /*MENU*/ buttonWid - dsPadding * 2,
                TITLE_HEIGHT);

    // Specifies the client rectangle.
    m_ClientRect.setRect(
                dsPadding,
                dsPadding,
                width()  - dsPadding * 2,
                height() - dsPadding * 2);

    // Specifies the title rectangle.
    m_TitleRect.setRect(
                dsPadding,
                dsPadding,
                width() - dsPadding * 2,
                TITLE_HEIGHT);

    // TODO: Menu
}


void
OfficeWindow::updateVisibleTitle()
{
    QString title = windowTitle();
    QFontMetrics metrics(font());

    // Retrieves the initial and the estimated width.
    int currentWidth = metrics.width(title);
    int estimated = ((m_DragRect.width() - currentWidth) / 2)
                  - TITLE_PADDING_X - DROP_SHADOW_PADDING;

    // Iterates until the desired with was reached.
    while (currentWidth > estimated && estimated > 0)
    {
        title.remove(title.length() - 1, 1);
        currentWidth = metrics.width(title);
    }

    // Displays dots behind the modified title.
    if (title.length() < 3 || estimated < currentWidth)
        title = QString("");
    else if (windowTitle().length() != title.length())
        title.remove(title.length() - 2, 2).append("...");

    m_VisibleTitle = title;
}


void
OfficeWindow::updateResizeWidgets()
{
    if (!m_CanResize || isMaximized())
    {
        if (m_ResizeTopLeft->isVisible()) m_ResizeTopLeft->hide();
        if (m_ResizeTopRight->isVisible()) m_ResizeTopRight->hide();
        if (m_ResizeBottomRight->isVisible()) m_ResizeBottomRight->hide();
        if (m_ResizeBottomLeft->isVisible()) m_ResizeBottomLeft->hide();
        if (m_ResizeTop->isVisible()) m_ResizeTop->hide();
        if (m_ResizeLeft->isVisible()) m_ResizeLeft->hide();
        if (m_ResizeBottom->isVisible()) m_ResizeBottom->hide();
        if (m_ResizeRight->isVisible()) m_ResizeRight->hide();
    }
    else
    {
        if (!m_ResizeTopLeft->isVisible()) m_ResizeTopLeft->show();
        if (!m_ResizeTopRight->isVisible()) m_ResizeTopRight->show();
        if (!m_ResizeBottomRight->isVisible()) m_ResizeBottomRight->show();
        if (!m_ResizeBottomLeft->isVisible()) m_ResizeBottomLeft->show();
        if (!m_ResizeTop->isVisible()) m_ResizeTop->show();
        if (!m_ResizeLeft->isVisible()) m_ResizeLeft->show();
        if (!m_ResizeBottom->isVisible()) m_ResizeBottom->show();
        if (!m_ResizeRight->isVisible()) m_ResizeRight->show();
    }
}


void
OfficeWindow::updateLayoutPadding()
{
    QLayout* winLayout = layout();

    // No drop shadow in maximized mode.
    if (isMaximized())
    {
        winLayout->setContentsMargins(1, TITLE_HEIGHT, 1, 1);
    }
    else
    {
        winLayout->setContentsMargins(
                    DROP_SHADOW_PADDING + 1,
                    TITLE_HEIGHT + DROP_SHADOW_PADDING,
                    DROP_SHADOW_PADDING + 1,
                    DROP_SHADOW_PADDING + 1);
    }
}


QRect
OfficeWindow::centerRect(const QPixmap& img, const QRect& rc)
{
    int dx = (rc.width()  - img.width())  / 2;
    int dy = (rc.height() - img.height()) / 2;

    QRect center;
          center.moveLeft(rc.x() + dx);
          center.moveTop(rc.y() + dy);
          center.setWidth(img.width());
          center.setHeight(img.height());

    return center;
}


bool
OfficeWindow::mouseMoveDrag(const QPoint& p)
{
    if (m_State == WindowState::Dragging && m_DragRect.contains(p))
    {
        auto g = mapToGlobal(p);
        if (isMaximized())
        {
            // Resets the window position on dragging.
            m_MaximState = WinButtonState::None;
            m_State = WindowState::None;
            showNormal();
            updateLayoutPadding();
            updateResizeRects();
        }
        else
        {
            // Moves the window by the amount of dx/dy pixels.
            move(g - m_InitialDragPos);
            updateGeometry();
        }

        return true;
    }

    return false;
}


bool
OfficeWindow::mouseMoveSpecial(const QPoint& p)
{
    // Switches from special state to pressed state.
    if (m_CloseState == WinButtonState::Special && m_CloseRect.contains(p))
    {
        m_CloseState = WinButtonState::Pressed;
        return true;
    }
    else if (m_MaximState == WinButtonState::Special && m_MaximRect.contains(p))
    {
        m_MaximState = WinButtonState::Pressed;
        return true;
    }
    else if (m_MinimState == WinButtonState::Special && m_MinimRect.contains(p))
    {
        m_MinimState = WinButtonState::Pressed;
        return true;
    }

    // Switches from pressed state to special state.
    if (m_CloseState == WinButtonState::Pressed && !m_CloseRect.contains(p))
    {
        m_CloseState = WinButtonState::Special;
        return true;
    }
    else if (m_MaximState == WinButtonState::Pressed && !m_MaximRect.contains(p))
    {
        m_MaximState = WinButtonState::Special;
        return true;
    }
    else if (m_MinimState == WinButtonState::Pressed && !m_MinimRect.contains(p))
    {
        m_MinimState = WinButtonState::Special;
        return true;
    }

    return false;
}


bool
OfficeWindow::mouseMoveHitTest(const QPoint& p)
{
    // Changes the button into hovered state if
    // the mouse pointer happens to hover it.
    if (m_CloseState != WinButtonState::Pressed &&
        m_CloseState != WinButtonState::Special &&
        m_MaximState != WinButtonState::Pressed &&
        m_MaximState != WinButtonState::Special &&
        m_MinimState != WinButtonState::Pressed &&
        m_MinimState != WinButtonState::Special)
    {
        // Determines whether one button has been hovered before.
        // If yes, do not perform a repaint of the title bar.
        bool initial = m_CloseState != WinButtonState::Hovered &&
                       m_MaximState != WinButtonState::Hovered &&
                       m_MinimState != WinButtonState::Hovered ;

        // Resets all current states.
        m_CloseState = WinButtonState::None;
        m_MaximState = WinButtonState::None;
        m_MinimState = WinButtonState::None;

        // Determines whether there is any new state.
        if (m_HasCloseBtn && m_CloseRect.contains(p))
        {
            m_CloseState = WinButtonState::Hovered;
            return true;
        }
        else if (m_HasMaximBtn && m_MaximRect.contains(p))
        {
            m_MaximState = WinButtonState::Hovered;
            return true;
        }
        else if (m_HasMinimBtn && m_MinimRect.contains(p))
        {
            m_MinimState = WinButtonState::Hovered;
            return true;
        }

        return initial;
    }

    return false;
}


bool
OfficeWindow::mousePressDrag(const QPoint& p)
{
    // Activates dragging if the dragging rectangle
    // is being pressed and moved later on.
    if (m_DragRect.contains(p))
    {
        m_InitialDragPos = p;
        m_State = WindowState::Dragging;
        return true;
    }

    return false;
}


bool
OfficeWindow::mousePressHitTest(const QPoint& p)
{
    // Determines whether one button has been pressed before.
    // If yes, do not perform a repaint of the title bar.
    bool initial = m_CloseState != WinButtonState::Pressed &&
                   m_MaximState != WinButtonState::Pressed &&
                   m_MinimState != WinButtonState::Pressed ;

    // Resets all the current states.
    m_CloseState = WinButtonState::None;
    m_MaximState = WinButtonState::None;
    m_MinimState = WinButtonState::None;

    // Determines whether there is any new state.
    if (m_HasCloseBtn && m_CloseRect.contains(p))
    {
        m_CloseState = WinButtonState::Pressed;
        return true;
    }
    else if (m_HasMaximBtn && m_MaximRect.contains(p))
    {
        m_MaximState = WinButtonState::Pressed;
        return true;
    }
    else if (m_HasMinimBtn && m_MinimRect.contains(p))
    {
        m_MinimState = WinButtonState::Pressed;
        return true;
    }

    return initial;
}


bool
OfficeWindow::mouseReleaseDrag(const QPoint&)
{
    if (m_State == WindowState::Dragging)
    {
        m_State = WindowState::None;
        return true;
    }

    return false;
}


bool
OfficeWindow::mouseReleaseAction(const QPoint& p)
{
    if (m_CloseState == WinButtonState::Pressed ||
        m_CloseState == WinButtonState::Special ||
        m_MaximState == WinButtonState::Pressed ||
        m_MaximState == WinButtonState::Special ||
        m_MinimState == WinButtonState::Pressed ||
        m_MinimState == WinButtonState::Special)
    {
        // Executes certain actions based on the clicked button.
        if (m_CloseState == WinButtonState::Pressed && m_CloseRect.contains(p))
        {
            close();
        }
        else if (m_MaximState == WinButtonState::Pressed && m_MaximRect.contains(p))
        {
            if (isMaximized())
            {
                showNormal();
                updateResizeRects();
            }
            else
            {
                showMaximized();
                updateResizeRects();
            }

            updateLayoutPadding();
            update();
        }
        else if (m_MinimState == WinButtonState::Pressed && m_MinimRect.contains(p))
        {
            showMinimized();
            updateLayoutPadding();
        }

        // Resets all the pressed states.
        m_CloseState = WinButtonState::None;
        m_MaximState  = WinButtonState::None;
        m_MinimState  = WinButtonState::None;

        return true;
    }

    return false;
}


WinResizeArea::WinResizeArea(OfficeWindow* window, WinResizeDirs dir)
    : QWidget(window)
    , m_Window(window)
    , m_Direction(dir)
{
    bool hasHorizontal = (dir & WinResizeDir::Left) ||
                         (dir & WinResizeDir::Right);

    // Determines the QCursor to use.
    if (hasHorizontal && (dir & WinResizeDir::Bottom))
    {
        if (dir & WinResizeDir::Left)
            setCursor(Qt::SizeBDiagCursor);
        else
            setCursor(Qt::SizeFDiagCursor);
    }
    else if (hasHorizontal && (dir & WinResizeDir::Top))
    {
        if (dir & WinResizeDir::Left)
            setCursor(Qt::SizeFDiagCursor);
        else
            setCursor(Qt::SizeBDiagCursor);
    }
    else if (hasHorizontal)
    {
        setCursor(Qt::SizeHorCursor);
    }
    else if ((dir & WinResizeDir::Top) || (dir & WinResizeDir::Bottom))
    {
        setCursor(Qt::SizeVerCursor);
    }
}


void
WinResizeArea::enterEvent(QEvent*)
{
    m_Window->m_CloseState = WinButtonState::None;
    m_Window->m_MaximState = WinButtonState::None;
    m_Window->m_MinimState = WinButtonState::None;
    m_Window->repaintTitleBar();
}


void
WinResizeArea::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_Window->canResize())
        m_Window->m_State = WindowState::Resizing;
}


void
WinResizeArea::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && m_Window->canResize())
    {
        m_Window->m_State = WindowState::None;
        m_Window->generateDropShadow();
        m_Window->update();
    }
}


void
WinResizeArea::mouseMoveEvent(QMouseEvent* event)
{
    if (m_Window->m_State == WindowState::Resizing)
    {
        QPoint g = event->globalPos();
        QRect r = m_Window->geometry();
        QSize min = m_Window->minimumSize();
        QSize max = m_Window->maximumSize();
        QRect orig = r;

        if (m_Direction & WinResizeDir::Left)
            r.setLeft(g.x());
        if (m_Direction & WinResizeDir::Right)
            r.setRight(g.x());
        if (m_Direction & WinResizeDir::Bottom)
            r.setBottom(g.y());
        if (m_Direction & WinResizeDir::Top)
            r.setTop(g.y());

        if (r.width() < min.width() || r.width() > max.width())
        {
            // Resets the horizontal geometry.
            r.setLeft(orig.left());
            r.setRight(orig.right());
        }
        if (r.height() < min.height() || r.height() > max.height())
        {
            // Resets the vertical geometry.
            r.setTop(orig.top());
            r.setBottom(orig.bottom());
        }

        m_Window->setGeometry(r);
    }
}
