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


#ifndef QOFFICE_OFFICEWINDOW_HPP
#define QOFFICE_OFFICEWINDOW_HPP


// QOffice headers
#include <QOffice/Interfaces/IOfficeWidget.hpp>
#include <QOffice/Widgets/Enums/OfficeWindowEnums.hpp>

// Qt headers
#include <QMainWindow>
#include <QTextOption>


QOFFICE_BEGIN_NAMESPACE


class WinResizeArea;


/**
 * This is the description of the class.
 *
 * @class OfficeWindow
 * @author Nicolas Kogler
 * @date December 24th, 2016
 *
 */
class QOFFICE_EXPORT OfficeWindow : public QWidget, public IOfficeWidget
{
public:

    enum AccentColor
    {
        BlueAccent,
        RedAccent,
        GreenAccent,
        OrangeAccent,
        PurpleAccent
    };


    /**
     * Initializes a new instance of OfficeWindow.
     *
     * @param parent The parent of this widget.
     *
     */
    OfficeWindow(QWidget* parent = nullptr);


    /**
     * Reimplemented pure virtual function from IOfficeWidget.
     * Retrieves the accent color for this office widget.
     *
     * @returns the current accent color.
     *
     */
    Accent accent() const override;

    /**
     * Retrieves the current accent color from OfficeWindow.
     * This function exists because the Qt designer cannot
     * handle or does not accept enums from other classes.
     *
     * @returns the current acccent color.
     *
     */
    AccentColor accentColor() const;

    /**
     * Determines whether this window has a close button.
     *
     * @returns true if it has.
     */
    bool hasCloseButton() const;

    /**
     * Determines whether this window has a maximize button.
     *
     * @returns true if it has.
     */
    bool hasMaximizeButton() const;

    /**
     * Determines whether this window has a minimize button.
     *
     * @returns true if it has.
     */
    bool hasMinimizeButton() const;

    /**
     * Determines whether this window is resizable.
     *
     * @returns true if it is.
     */
    bool canResize() const;


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

    /**
     * Alternative to the default setAccent() function, because
     * the Qt designer cannot handle or does not accept enums
     * from other classes.
     *
     * @param accent New accent color of the office window.
     *
     */
    void setAccentColor(AccentColor accent);


    /**
     * Defines that the window either has a close
     * button or not.
     *
     * @param close True if has close button.
     *
     */
    void setCloseButtonVisible(bool close);

    /**
     * Defines that the window either has a maximize
     * button or not.
     *
     * @param maximize True if has maximize button.
     *
     */
    void setMaximizeButtonVisible(bool maximize);

    /**
     * Defines that the window either has a minimize
     * button or not.
     *
     * @param minimize True if has minimize button.
     *
     */
    void setMinimizeButtonVisible(bool minimize);

    /**
     * Defines that the window can either be resized or not.
     *
     * @param resize True if able to resize.
     *
     */
    void setResizable(bool resize);


protected:

    /**
     * Renders the office window. It has the typical stripe
     * at the top of the window (colored in the accent color).
     * Also renders the drop-shadow, the border (in accent) and
     * all the icons and menu items on the title bar.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void paintEvent(QPaintEvent* event) override;

    /**
     * Updates the positions of the window buttons, the menu,
     * the title and other buttons. Pre-renders the drop shadow.
     *
     * @param event Holds the old widget size.
     *
     */
    virtual void resizeEvent(QResizeEvent* event) override;

    /**
     * Contains most of the window logic. Performs hit-tests on
     * the icon, the title bar, the window icons and also the
     * resizing areas.
     *
     * @param event Holds the current mouse position.
     *
     */
    virtual void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * Changes the state of the window buttons and initiates
     * resizing and moving the window.
     *
     * @param Holds the mouse position and pressed button.
     *
     */
    virtual void mousePressEvent(QMouseEvent* event) override;

    /**
     * Resets the state of the window buttons and cancels
     * any resizing or moving action.
     *
     * @param Holds the mouse position and released button.
     *
     */
    virtual void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * If the mouse-pointer is on the title bar and
     * the left mouse button is double clicked, then
     * the window is maximized or restored, depending
     * on its current state.
     *
     * @param event Holds the mouse position and clicked button.
     *
     */
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

    /**
     * Recursively changes the accent of all child widgets.
     *
     * @param event Holds nothing we need.
     *
     */
    virtual void showEvent(QShowEvent* event) override;


private:

    // Members
    WinButtonState m_CloseState;
    WinButtonState m_MaximState;
    WinButtonState m_MinimState;
    WindowState    m_State;
    WinResizeArea* m_ResizeTopLeft;
    WinResizeArea* m_ResizeTopRight;
    WinResizeArea* m_ResizeBottomLeft;
    WinResizeArea* m_ResizeBottomRight;
    WinResizeArea* m_ResizeTop;
    WinResizeArea* m_ResizeLeft;
    WinResizeArea* m_ResizeBottom;
    WinResizeArea* m_ResizeRight;
    QPixmap        m_DropShadow;
    QPixmap        m_CloseImage;
    QPixmap        m_MaximImage;
    QPixmap        m_MinimImage;
    QPixmap        m_RestoreImage;
    QTextOption    m_TitleOptions;
    QString        m_VisibleTitle;
    QPoint         m_InitialDragPos;
    QRect          m_ClientRect;
    QRect          m_TitleRect;
    QRect          m_DragRect;
    QRect          m_CloseRect;
    QRect          m_MaximRect;
    QRect          m_MinimRect;
    bool           m_HasCloseBtn;
    bool           m_HasMaximBtn;
    bool           m_HasMinimBtn;
    bool           m_CanResize;

    // Helpers
    void generateDropShadow();
    void repaintTitleBar();
    void updateButtonRects();
    void updateResizeRects();
    void updateVisibleTitle();
    void updateResizeWidgets();
    void updateLayoutPadding();
    auto centerRect(const QPixmap& img, const QRect& rc) -> QRect;
    bool mouseMoveDrag(const QPoint& p);
    bool mouseMoveSpecial(const QPoint& p);
    bool mouseMoveHitTest(const QPoint& p);
    bool mousePressDrag(const QPoint& p);
    bool mousePressHitTest(const QPoint& p);
    bool mouseReleaseDrag(const QPoint& p);
    bool mouseReleaseAction(const QPoint& p);

    // Metadata
    Q_OBJECT
    Q_ENUMS(AccentColor)
    Q_PROPERTY(bool CanResize READ canResize WRITE setResizable)
    Q_PROPERTY(bool HasCloseButton READ hasCloseButton WRITE setCloseButtonVisible)
    Q_PROPERTY(bool HasMaximizeButton READ hasMaximizeButton WRITE setMaximizeButtonVisible)
    Q_PROPERTY(bool HasMinimizeButton READ hasMinimizeButton WRITE setMinimizeButtonVisible)
    Q_PROPERTY(AccentColor Accent READ accentColor WRITE setAccentColor)

    // Friends
    friend class WinResizeArea;
};


/**
 * This class represents a resize area on the window.
 * Whenever it is hovered, it will change the cursor
 * and trigger a resize when it is pressed. Will change
 * back to normal cursor when the mouse leaves it.
 *
 * @class WinResizeArea
 * @author Nicolas Kogler
 * @date December 28th, 2016
 *
 */
class WinResizeArea : public QWidget
{
public:

    /**
     * Stores a reference to the window and determines
     * the cursor to use by the given direction.
     *
     * @param window Window owning this resizing area.
     * @param dir The resize direction to use.
     *
     */
    WinResizeArea(OfficeWindow* window, WinResizeDirs dir);


protected:

    /**
     * Resets the button state of all buttons.
     *
     * @param event Holds nothing we need.
     *
     */
    void enterEvent(QEvent* event) override;

    /**
     * Triggers the resizing mode of the window.
     *
     * @param event Holds the held button.
     *
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * Resets the state of the office window.
     *
     * @param event Holds the held button.
     *
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

    /**
     * Changes the size of the window, depending
     * on the direction in which it resizes.
     *
     * @param event Holds the global mouse position.
     *
     */
    void mouseMoveEvent(QMouseEvent* event) override;


private:

    // Members
    OfficeWindow* m_Window;
    WinResizeDirs m_Direction;
};


QOFFICE_END_NAMESPACE


// Metadata
Q_DECLARE_METATYPE(off::OfficeWindow::AccentColor)


#endif // QOFFICE_OFFICEWINDOW_HPP
