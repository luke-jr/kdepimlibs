/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 KDAB
    Author: Tobias Koenig <tokoe@kde.org>

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

#ifndef AKONADI_EMAILADDRESSSELECTIONDIALOG_H
#define AKONADI_EMAILADDRESSSELECTIONDIALOG_H

#include "akonadi-contact_export.h"

#include "emailaddressselectionwidget.h"

#include <QDialog>

namespace Akonadi
{

/**
 * @short A dialog to select email addresses from Akonadi.
 *
 * This dialog allows the user to select an name and email address from
 * the Akonadi storage.
 * The selected addresses are returned as EmailAddressSelectionWidget::Selection objects
 * which encapsulate the name, email address and the Akonadi item that has been selected.
 *
 * Example:
 *
 * @code
 *
 * Akonadi::EmailAddressSelectionDialog dlg( this );
 * if ( dlg.exec() ) {
 *   const Akonadi::EmailAddressSelectionWidget::Selection::List selections = dlg.selectedAddresses();
 *   foreach ( const Akonadi::EmailAddressSelectionWidget::Selection &selection, selections ) {
 *     qCDebug(AKONADICONTACT_LOG) << "Name:" << selection.name() << "Email:" << selection.email();
 *   }
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.5
 */
class AKONADI_CONTACT_EXPORT EmailAddressSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Creates a new email address selection dialog.
     *
     * @param parent The parent widget.
     */
    explicit EmailAddressSelectionDialog(QWidget *parent = Q_NULLPTR);

    /**
     * Creates a new email address selection dialog.
     *
     * @param model A custom, ContactsTreeModel based model to use.
     * @param parent The parent widget.
     */
    explicit EmailAddressSelectionDialog(QAbstractItemModel *model, QWidget *parent = Q_NULLPTR);

    /**
     * Destroys the email address selection dialog.
     */
    ~EmailAddressSelectionDialog();

    /**
     * Returns the list of selected email addresses.
     */
    EmailAddressSelection::List selectedAddresses() const;

    /**
     * Returns the email address selection view that is used.
     */
    EmailAddressSelectionWidget *view() const;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};

}

#endif
