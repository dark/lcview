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
#include <QMap>
#include <QString>

#include "attributes.h"

class Note {
public:
  Note();
  bool add_attribute(QString key, QString value);
  QString get_attribute(QString key) const;

  // Specific getters
  QString get_interest_rate() const;
  QString get_grade() const;
  int get_term() const;
  Attributes::NoteStatus get_status() const;
  QString get_address_state() const;
  QDate get_loan_issue_date() const;

private:
  QMap<QString, QString> attributes_;
};
