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

#include <QString>
#include <QStringList>
#include <QVector>

#include "filter.h"
#include "note.h"

class Portfolio {
public:
  typedef QVector<Note>::iterator iterator;

  int size();
  Portfolio::iterator begin();
  Portfolio::iterator end();

  const QStringList get_attribute_names();

  static Portfolio* create_from_file(QString filename);

  Portfolio* filter(QList<Filter> filters);

private:
  QStringList attribute_names_;
  QVector<Note> notes_;

  Portfolio();
};

