/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 Laurent Montel <montel@kde.org>

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

#ifndef PREFEREDLINEEDITWIDGET_H
#define PREFEREDLINEEDITWIDGET_H

#include <KLineEdit>
#include <QIcon>
class QAction;
namespace Akonadi
{
class PreferredLineEditWidget : public KLineEdit
{
    Q_OBJECT
public:
    explicit PreferredLineEditWidget(QWidget *parent = Q_NULLPTR);
    ~PreferredLineEditWidget();

    bool preferred() const;

    void setPreferred(bool preferred);

Q_SIGNALS:
    void preferredChanged(QWidget *w);

private Q_SLOTS:
    void slotPreferredStatusChanged();

private:
    void updatePreferredIcon();
    bool mPreferred;
    QIcon mIconEnabled;
    QIcon mIconDisabled;
    QAction *mPreferredAction;
};
}
#endif // PREFEREDLINEEDITWIDGET_H
