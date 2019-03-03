/*
 *  A better viewer for Lending Club notes
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
#include <QString>

#define NOTE_KEY_INTEREST "InterestRate"
#define NOTE_KEY_GRADE "Grade"
#define NOTE_KEY_TERM "Term"
#define NOTE_KEY_STATUS "Status"
#define NOTE_KEY_ADDRESS_STATE "addr_state"
#define NOTE_KEY_LOAN_ISSUE_DATE "Loan Issue Date"

namespace Attributes {
enum class NoteField {
  INTEREST,
  GRADE,
  TERM,
  STATUS,
  ADDRESS_STATE,
  LOAN_ISSUE_DATE
};

inline QString field_key(NoteField field) {
  switch (field) {
    case NoteField::INTEREST:
      return NOTE_KEY_INTEREST;
    case NoteField::GRADE:
      return NOTE_KEY_GRADE;
    case NoteField::TERM:
      return NOTE_KEY_TERM;
    case NoteField::STATUS:
      return NOTE_KEY_STATUS;
    case NoteField::ADDRESS_STATE:
      return NOTE_KEY_ADDRESS_STATE;
    case NoteField::LOAN_ISSUE_DATE:
      return NOTE_KEY_LOAN_ISSUE_DATE;
  }
  return "<key-error>";
}

inline int parse_term(QString s) {
  return s.toInt();
}

inline QString term_to_string(int term) {
  return QString::number(term);
}

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

inline NoteStatus parse_status(QString s) {
  if (s == "Charged Off")
    return NoteStatus::CHARGED_OFF;
  else if (s == "Current")
    return NoteStatus::CURRENT;
  else if (s == "Default")
    return NoteStatus::DEFAULT;
  else if (s == "Fully Paid")
    return NoteStatus::FULLY_PAID;
  else if (s == "In Grace Period")
    return NoteStatus::GRACE_PERIOD;
  else if (s == "Issued")
    return NoteStatus::ISSUED;
  else if (s == "Late (16-30 days)")
    return NoteStatus::LATE_16_30;
  else if (s == "Late (31-120 days)")
    return NoteStatus::LATE_31_120;
  return NoteStatus::UNKNOWN;
}

inline QString status_to_string(NoteStatus status) {
  switch (status) {
    case NoteStatus::UNKNOWN:
      return "<unknown-status>";
    case NoteStatus::CHARGED_OFF:
      return "Charged Off";
    case NoteStatus::CURRENT:
      return "Current";
    case NoteStatus::DEFAULT:
      return "Default";
    case NoteStatus::FULLY_PAID:
      return "Fully Paid";
    case NoteStatus::GRACE_PERIOD:
      return "In Grace Period";
    case NoteStatus::ISSUED:
      return "Issued";
    case NoteStatus::LATE_16_30:
      return "Late (16-30 days)";
    case NoteStatus::LATE_31_120:
      return "Late (31-120 days)";
  }
  return "<status-error>";
}

inline QDate parse_loan_issue_date(QString s) {
  return QDate::fromString(s, "MM/dd/yyyy");
}

}; // namespace Attributes
