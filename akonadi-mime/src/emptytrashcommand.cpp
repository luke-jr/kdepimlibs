/*
    Copyright (c) 2010 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
    Copyright (c) 2010 Andras Mantia <andras@kdab.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "emptytrashcommand.h"
#include "util_p.h"
#include "imapsettings.h"
#include "specialmailcollections.h"

#include "akonadi_mime_debug.h"
#include <KLocalizedString>
#include <KMessageBox>

#include <entitytreemodel.h>
#include <itemfetchjob.h>
#include <itemdeletejob.h>
#include <agentmanager.h>
#include <kmime/kmime_message.h>
using namespace Akonadi;
EmptyTrashCommand::EmptyTrashCommand(const QAbstractItemModel *model, QObject *parent)
    : CommandBase(parent)
    , mModel(model)
    , the_trashCollectionFolder(-1)
    , mNumberOfTrashToEmpty(0)
{
}

EmptyTrashCommand::EmptyTrashCommand(const Akonadi::Collection &folder, QObject *parent)
    : CommandBase(parent)
    , mModel(0)
    , the_trashCollectionFolder(-1)
    , mFolder(folder)
    , mNumberOfTrashToEmpty(0)
{
}

void EmptyTrashCommand::execute()
{
    if (!mFolder.isValid() && !mModel) {
        emitResult(Failed);
        return;
    }

    if (!mFolder.isValid()) {   //expunge all
        const QString title = i18n("Empty Trash");
        const QString text = i18n("Are you sure you want to empty the trash folders of all accounts?");
        if (KMessageBox::warningContinueCancel(0, text, title,
                                               KStandardGuiItem::cont(), KStandardGuiItem::cancel(),
                                               QStringLiteral("confirm_empty_trash"))
                != KMessageBox::Continue) {
            emitResult(OK);
            return;
        }
        Akonadi::Collection trash = trashCollectionFolder();
        QVector<Akonadi::Collection> trashFolder;
        trashFolder << trash;

        const Akonadi::AgentInstance::List lst = agentInstances();
        foreach (const Akonadi::AgentInstance &type, lst) {
            if (type.identifier().contains(IMAP_RESOURCE_IDENTIFIER)) {
                if (type.status() == Akonadi::AgentInstance::Broken) {
                    continue;
                }
                OrgKdeAkonadiImapSettingsInterface *iface = Util::createImapSettingsInterface(type.identifier());
                if (iface->isValid()) {
                    const int trashImap = iface->trashCollection();
                    if (trashImap != trash.id()) {
                        trashFolder << Akonadi::Collection(trashImap);
                    }
                }
                delete iface;
            }
        }
        mNumberOfTrashToEmpty = trashFolder.count();
        for (int i = 0; i < mNumberOfTrashToEmpty; ++i) {
            expunge(trashFolder.at(i));
        }
    } else {
        if (folderIsTrash(mFolder)) {
            mNumberOfTrashToEmpty++;
            expunge(mFolder);
        } else {
            emitResult(OK);
        }

    }
}

void EmptyTrashCommand::expunge(const Akonadi::Collection &col)
{
    if (col.isValid()) {
        Akonadi::ItemFetchJob *job = new Akonadi::ItemFetchJob(col, this);
        connect(job, &Akonadi::ItemFetchJob::result, this, &EmptyTrashCommand::slotExpungeJob);
    } else {
        qCDebug(AKONADIMIME_LOG) << " Try to expunge an invalid collection :" << col;
        emitResult(Failed);
    }
}

void EmptyTrashCommand::slotExpungeJob(KJob *job)
{
    if (job->error()) {
        Util::showJobError(job);
        emitResult(Failed);
        return;
    }
    Akonadi::ItemFetchJob *fjob = qobject_cast<Akonadi::ItemFetchJob *>(job);
    if (!fjob) {
        emitResult(Failed);
        return;
    }
    const Akonadi::Item::List lstItem = fjob->items();
    if (lstItem.isEmpty()) {
        emitResult(OK);
        return;
    }
    Akonadi::ItemDeleteJob *jobDelete = new Akonadi::ItemDeleteJob(lstItem, this);
    connect(jobDelete, &Akonadi::ItemDeleteJob::result, this, &EmptyTrashCommand::slotDeleteJob);

}

void EmptyTrashCommand::slotDeleteJob(KJob *job)
{
    if (job->error()) {
        Util::showJobError(job);
        emitResult(Failed);
    }
    emitResult(OK);
}

Akonadi::AgentInstance::List EmptyTrashCommand::agentInstances()
{
    Akonadi::AgentInstance::List relevantInstances;
    foreach (const Akonadi::AgentInstance &instance, Akonadi::AgentManager::self()->instances()) {
        if (instance.type().mimeTypes().contains(KMime::Message::mimeType()) &&
                instance.type().capabilities().contains(QStringLiteral("Resource")) &&
                !instance.type().capabilities().contains(QStringLiteral("Virtual"))) {
            relevantInstances << instance;
        }
    }
    return relevantInstances;
}

Akonadi::Collection EmptyTrashCommand::collectionFromId(Collection::Id id) const
{
    const QModelIndex idx = Akonadi::EntityTreeModel::modelIndexForCollection(
                                mModel, Akonadi::Collection(id));
    return idx.data(Akonadi::EntityTreeModel::CollectionRole).value<Akonadi::Collection>();
}

Akonadi::Collection EmptyTrashCommand::trashCollectionFolder()
{
    if (the_trashCollectionFolder < 0) {
        the_trashCollectionFolder = Akonadi::SpecialMailCollections::self()->defaultCollection(Akonadi::SpecialMailCollections::Trash).id();
    }
    return collectionFromId(the_trashCollectionFolder);
}

bool EmptyTrashCommand::folderIsTrash(const Akonadi::Collection &col)
{
    if (col == Akonadi::SpecialMailCollections::self()->defaultCollection(Akonadi::SpecialMailCollections::Trash)) {
        return true;
    }
    const Akonadi::AgentInstance::List lst = agentInstances();
    foreach (const Akonadi::AgentInstance &type, lst) {
        if (type.status() == Akonadi::AgentInstance::Broken) {
            continue;
        }
        if (type.identifier().contains(IMAP_RESOURCE_IDENTIFIER)) {
            OrgKdeAkonadiImapSettingsInterface *iface = Util::createImapSettingsInterface(type.identifier());
            if (iface->isValid()) {
                if (iface->trashCollection() == col.id()) {
                    delete iface;
                    return true;
                }
            }
            delete iface;
        }
    }
    return false;
}

void EmptyTrashCommand::emitResult(Result value)
{
    Q_EMIT result(value);
    mNumberOfTrashToEmpty--;
    if (mNumberOfTrashToEmpty <= 0) {
        deleteLater();
    }
}
