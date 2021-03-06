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

#ifndef MARKASCOMMAND_H
#define MARKASCOMMAND_H

#include "commandbase.h"
#include "messagestatus.h"

#include <collection.h>
#include <item.h>

#include <QList>
#include "akonadi-mime_export.h"

class KJob;
namespace Akonadi
{
class MarkAsCommandPrivate;
class AKONADI_MIME_EXPORT MarkAsCommand : public CommandBase
{
    Q_OBJECT
public:
    MarkAsCommand(const Akonadi::MessageStatus &targetStatus, const Akonadi::Item::List &msgList, bool invert = false, QObject *parent = Q_NULLPTR);
    MarkAsCommand(const Akonadi::MessageStatus &targetStatus, const Akonadi::Collection::List &folders, bool invert = false, bool recursive = false, QObject *parent = Q_NULLPTR);
    ~MarkAsCommand();
    void execute() Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotCollectionFetchDone(KJob *job);
    void slotFetchDone(KJob *job);
    void slotModifyItemDone(KJob *job);

private:
    void markMessages();
    MarkAsCommandPrivate *const d;
};
}
#endif // MARKASCOMMAND_H
