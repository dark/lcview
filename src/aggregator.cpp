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

#include "include/aggregator.h"


namespace Aggregator {

QMap<QString, int> grades(Portfolio *p, bool coarse) {
  QMap<QString, int> grades;
  if (!p)
    return grades;

  for (auto note = p->begin(); note != p->end(); ++note) {
    QString grade = note->get_grade();
    ++grades[grade];
  }

  if (!coarse)
    // Return grades without further processing.
    return grades;

  // Reduce grades to a coarser aggregation.
  QMap<QString, int> coarse_grades;
  for (const auto &grade: grades.toStdMap()) {
    QString coarse = grade.first.at(0);
    coarse_grades[coarse] += grade.second;
  }
  return coarse_grades;
}


QMap<Attributes::NoteStatus, int> statuses(Portfolio *p) {
  QMap<Attributes::NoteStatus, int> statuses;
  if (!p)
    return statuses;

  for (auto note = p->begin(); note != p->end(); ++note) {
    Attributes::NoteStatus status = note->get_status();
    ++statuses[status];
  }

  return statuses;
}


QMap<int, int> terms(Portfolio *p) {
  QMap<int, int> terms;
  if (!p)
    return terms;

  for (auto note = p->begin(); note != p->end(); ++note)
    ++terms[note->get_term()];

  return terms;
}

}; // namespace Aggregator
