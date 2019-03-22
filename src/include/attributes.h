/*
 *  An offline viewer for LendingClub notes statistics
 *  Copyright (C) 2019  Marco Leogrande
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <QDate>
#include <QMetaType>
#include <QString>

namespace Attributes {
enum class NoteField {
  INTEREST,
  GRADE,
  TERM,
  STATUS,
  ADDRESS_STATE,
  LOAN_ISSUE_DATE
};

QString field_key(NoteField field);

int parse_term(QString s);
QString term_to_string(int term);

enum class NoteStatus {
  UNKNOWN = 0,
  CHARGED_OFF,
  CURRENT,
  DEFAULT,
  FULLY_PAID,
  GRACE_PERIOD,
  ISSUED,
  LATE_16_30,
  LATE_31_120
};

NoteStatus parse_status(QString s);
QString status_to_string(NoteStatus status);

QDate parse_loan_issue_date(QString s);

}; // namespace Attributes


// Needed to wrap NoteField in a QVariant
Q_DECLARE_METATYPE(Attributes::NoteField)
