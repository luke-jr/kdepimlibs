/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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

#include "phonecomboboxtype.h"
#include "phonewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <KLineEdit>
#include <QToolButton>
#include <editor/widgets/preferredlineeditwidget.h>

using namespace Akonadi;
PhoneWidget::PhoneWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    mPhoneNumberEdit = new PreferredLineEditWidget(this);
    mPhoneNumberEdit->setTrapReturnKey(true);
    mPhoneNumberEdit->setPlaceholderText(i18n("Add a Phone Number"));
    mPhoneNumberEdit->setObjectName(QStringLiteral("phonenumber"));
    layout->addWidget(mPhoneNumberEdit);
    connect(mPhoneNumberEdit, &PreferredLineEditWidget::preferredChanged, this, &PhoneWidget::slotPreferredChanged);

    mPhoneType = new PhoneComboBoxType(this);
    mPhoneType->setObjectName(QStringLiteral("phonetype"));
    layout->addWidget(mPhoneType);

    mAddButton = new QToolButton(this);
    mAddButton->setIcon(QIcon::fromTheme(QStringLiteral("list-add")));
    mAddButton->setToolTip(i18n("Add a Phone Number"));
    mAddButton->setObjectName(QStringLiteral("addbutton"));
    connect(mAddButton, &QToolButton::clicked, this, &PhoneWidget::slotAddPhone);
    layout->addWidget(mAddButton);

    mRemoveButton = new QToolButton(this);
    mRemoveButton->setObjectName(QStringLiteral("removebutton"));
    mRemoveButton->setToolTip(i18n("Remove Phone Number"));
    mRemoveButton->setIcon(QIcon::fromTheme(QStringLiteral("list-remove")));
    connect(mRemoveButton, &QToolButton::clicked, this, &PhoneWidget::slotRemovePhone);
    layout->addWidget(mRemoveButton);
}

PhoneWidget::~PhoneWidget()
{

}

void PhoneWidget::updateAddRemoveButton(bool addButtonEnabled)
{
    mAddButton->setEnabled(addButtonEnabled);
}

KContacts::PhoneNumber PhoneWidget::storePhone()
{
    KContacts::PhoneNumber number;
    number.setNumber(mPhoneNumberEdit->text());
    KContacts::PhoneNumber::Type currentType = mPhoneType->type();
    if (mPhoneNumberEdit->preferred()) {
        currentType |= KContacts::PhoneNumber::Pref;
    }
    number.setType(currentType);
    return number;
}

void PhoneWidget::loadPhone(const KContacts::PhoneNumber &number)
{
    mPhoneNumberEdit->setText(number.number());
    KContacts::PhoneNumber::Type currentType = number.type();
    mPhoneType->setType(number.type() & ~ KContacts::PhoneNumber::Pref);
    mPhoneNumberEdit->setPreferred(currentType & KContacts::PhoneNumber::Pref);
}

void PhoneWidget::slotAddPhone()
{
    Q_EMIT addWidget(this);
}

void PhoneWidget::slotRemovePhone()
{
    Q_EMIT removeWidget(this);
}

void PhoneWidget::clearWidget()
{
    mPhoneNumberEdit->clear();
    mPhoneType->resetToDefault();
}

void PhoneWidget::slotPreferredChanged()
{
    Q_EMIT preferredChanged(this);
}

void PhoneWidget::setPreferred(bool b)
{
    mPhoneNumberEdit->setPreferred(b);
}
