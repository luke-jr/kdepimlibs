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

#include "customfieldeditorwidget.h"
#include <QGridLayout>
#include <KLocalizedString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <KContacts/Addressee>

using namespace Akonadi;

CustomFieldEditorWidget::CustomFieldEditorWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    QLabel *label = new QLabel(i18n("Title Custom Type"), this);
    label->setObjectName(QStringLiteral("labeltitle"));

    topLayout->addWidget(label);

    QHBoxLayout *fieldLayout = new QHBoxLayout;
    topLayout->addLayout(fieldLayout);
    mFieldName = new QLineEdit(this);
    mFieldName->setObjectName(QStringLiteral("fieldname"));
    topLayout->addWidget(mFieldName);

    mFieldType = new QComboBox(this);
    //TODO fill it.
    mFieldType->setObjectName(QStringLiteral("fieldtype"));
    topLayout->addWidget(mFieldType);
    //TODO add type

    mAddField = new QPushButton(i18n("Add Field"), this);
    mAddField->setObjectName(QStringLiteral("addfield"));
    topLayout->addWidget(mAddField);
}

CustomFieldEditorWidget::~CustomFieldEditorWidget()
{

}

void CustomFieldEditorWidget::loadContact(const KContacts::Addressee &contact)
{
    //TODO
}

void CustomFieldEditorWidget::storeContact(KContacts::Addressee &contact) const
{
    //TODO
}

void CustomFieldEditorWidget::setReadOnly(bool readOnly)
{
    mFieldName->setReadOnly(readOnly);
    mAddField->setEnabled(!readOnly);
    mFieldType->setEnabled(!readOnly);
}
