/*
    Copyright (c) 2008 Volker Krause <vkrause@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef AKONADI_ERROROVERLAY_H
#define AKONADI_ERROROVERLAY_H

#include <QWidget>
#include <QPointer>

class QLabel;

namespace Akonadi {

/**
 * @internal
 * Overlay widget to block Akonadi-dependent widgets if the Akonadi server
 * is unavailable.
 * @todo handle intial parent == 0 case correctly, reparent later and hide as long as parent widget is 0
 * @todo fix hiding in dock widget tabs
 */
class ErrorOverlay : public QWidget
{
  Q_OBJECT
  public:
    /**
     * Create an overlay widget for @p baseWidget.
     * @p baseWidget must not be null.
     * @p parent must not be equal to @p baseWidget
     */
    explicit ErrorOverlay( QWidget *baseWidget, QWidget *parent = 0 );

  protected:
    bool eventFilter( QObject *object, QEvent *event );

  private:
    void reposition();

  private slots:
    void linkActivated();
    void started();
    void stopped();

  private:
    QPointer<QWidget> mBaseWidget;
    QLabel *mIconLabel;
    QLabel *mDescLabel;
    bool mPreviousState;
    bool mOverlayActive;

};

}

#endif
