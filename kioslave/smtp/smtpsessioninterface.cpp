/*
    Copyright (c) 2010 Volker Krause <vkrause@kde.org>

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

#include "smtpsessioninterface.h"

using namespace KioSMTP;

SMTPSessionInterface::~SMTPSessionInterface()
{
}

void SMTPSessionInterface::parseFeatures(const KioSMTP::Response &ehloResponse )
{
  m_capabilities = Capabilities::fromResponse( ehloResponse );
}

const Capabilities& KioSMTP::SMTPSessionInterface::capabilities() const
{
  return m_capabilities;
}

void SMTPSessionInterface::clearCapabilities()
{
  m_capabilities.clear();
}

bool SMTPSessionInterface::haveCapability(const char* cap) const
{
  return m_capabilities.have( cap );
}

bool SMTPSessionInterface::canPipelineCommands() const
{
  return haveCapability("PIPELINING") && pipeliningRequested();
}

QString SMTPSessionInterface::createSpecialResponse() const
{
  return m_capabilities.createSpecialResponse( ( isUsingSsl() && !isAutoSsl() ) || haveCapability( "STARTTLS" ) );
}

bool KioSMTP::SMTPSessionInterface::eightBitMimeRequested() const
{
  return false;
}

bool KioSMTP::SMTPSessionInterface::pipeliningRequested() const
{
  return true;
}
