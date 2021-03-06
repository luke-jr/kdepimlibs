/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

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

#ifndef AKONADI_CONTACTGROUPEXPANDJOB_H
#define AKONADI_CONTACTGROUPEXPANDJOB_H

#include "akonadi-contact_export.h"

#include <kcontacts/addressee.h>
#include <kcontacts/contactgroup.h>
#include <kjob.h>

namespace Akonadi
{

/**
 * @short Job that expands a ContactGroup to a list of contacts.
 *
 * This job takes a KContacts::ContactGroup object or a name of a contact group and
 * expands it to a list of KContacts::Addressee objects by creating temporary KContacts::Addressee objects
 * for the KContacts::ContactGroup::Data objects of the group and fetching the
 * complete contacts from the Akonadi storage for the
 * KContacts::ContactGroup::ContactReferences of the group.
 *
 * @code
 *
 * const KContacts::ContactGroup group = ...;
 *
 * Akonadi::ContactGroupExpandJob *job = new Akonadi::ContactGroupExpandJob( group );
 * connect( job, SIGNAL(result(KJob*)), this, SLOT(expandResult(KJob*)) );
 * job->start();
 *
 * ...
 *
 * MyClass::expandResult( KJob *job )
 * {
 *   Akonadi::ContactGroupExpandJob *expandJob = qobject_cast<Akonadi::ContactGroupExpandJob*>( job );
 *   const KContacts::Addressee::List contacts = expandJob->contacts();
 *   // do something with the contacts
 * }
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupExpandJob : public KJob
{
    Q_OBJECT

public:
    /**
     * Creates a new contact group expand job.
     *
     * @param group The contact group to expand.
     * @param parent The parent object.
     */
    explicit ContactGroupExpandJob(const KContacts::ContactGroup &group, QObject *parent = Q_NULLPTR);

    /**
     * Creates a new contact group expand job.
     *
     * @param name The name of the contact group to expand.
     * @param parent The parent object.
     *
     * @since 4.5
     */
    explicit ContactGroupExpandJob(const QString &name, QObject *parent = Q_NULLPTR);

    /**
     * Destroys the contact group expand job.
     */
    ~ContactGroupExpandJob();

    /**
     * Returns the list of contacts.
     */
    KContacts::Addressee::List contacts() const;

    /**
     * Starts the expand job.
     */
    void start() Q_DECL_OVERRIDE;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;

    Q_PRIVATE_SLOT(d, void resolveGroup())
    Q_PRIVATE_SLOT(d, void fetchResult(KJob *))
    Q_PRIVATE_SLOT(d, void searchResult(KJob *))
    //@endcond
};

}

#endif
