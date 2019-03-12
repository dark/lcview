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

#include "include/note.h"


bool Note::add_attribute(QString key, QString value)
{
  if (attributes_.contains(key))
    return false;

  attributes_.insert(key, value);
  return true;
}


QString Note::get_attribute(QString key) const {
  return attributes_.value(key);
}


// Specific getters
QString Note::get_interest_rate() const {
  return get_attribute(Attributes::field_key(Attributes::NoteField::INTEREST));
}

QString Note::get_grade() const {
  return get_attribute(Attributes::field_key(Attributes::NoteField::GRADE));
}

int Note::get_term() const {
  return Attributes::parse_term(get_attribute(Attributes::field_key(Attributes::NoteField::TERM)));
}

Attributes::NoteStatus Note::get_status() const {
  return Attributes::parse_status(get_attribute(Attributes::field_key(Attributes::NoteField::STATUS)));
}

QString Note::get_address_state() const {
  return get_attribute(Attributes::field_key(Attributes::NoteField::ADDRESS_STATE));
}

QDate Note::get_loan_issue_date() const {
  return Attributes::parse_loan_issue_date(get_attribute(Attributes::field_key(Attributes::NoteField::LOAN_ISSUE_DATE)));
}
