/*
    This file is part of the kcal library.

    Copyright (c) 2006 Allen Winter <winter@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include <qtest_kde.h>

#include <kdatetime.h>
#include "testduration.h"
#include "testduration.moc"

QTEST_KDEMAIN( DurationTest, NoGUI )

#include "kcal/duration.h"
using namespace KCal;

void DurationTest::testValidity()
{
  Duration d( KDateTime( QDate(2006, 8, 3), QTime(7, 0, 0), KDateTime::UTC ),
              KDateTime( QDate(2006, 8, 3), QTime(8, 0, 0), KDateTime::UTC ) );

  QCOMPARE( d.asSeconds(), 1*60*60 );
}

void DurationTest::testCompare()
{
  Duration d1( KDateTime( QDate(2006, 8, 3), QTime(7, 0, 0), KDateTime::UTC ),
               KDateTime( QDate(2006, 8, 3), QTime(8, 0, 0), KDateTime::UTC ) );
  //d1 has 1hr duration

  Duration d2( 2*60*60 ); // 2hr duration

  Duration d1copy( d1 ); // test copy constructor
  Duration d1assign = d1; // test operator=

  QVERIFY( d1.asSeconds() < d2.asSeconds() );
  QVERIFY( !( d1 == d2 ) );
  QVERIFY( d1copy == d1 );
  QVERIFY( d1assign == d1 );
}
