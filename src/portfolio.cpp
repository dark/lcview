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

#include "portfolio.h"

#include <QFile>
#include <QTextStream>
#include <QtDebug>


Portfolio::Portfolio() {}


int Portfolio::size() {
  return notes_.size();
}


Portfolio::iterator Portfolio::begin() {
  return notes_.begin();
}


Portfolio::iterator Portfolio::end() {
  return notes_.end();
}


const QStringList Portfolio::get_attribute_names() {
  return attribute_names_;
}


Portfolio* Portfolio::create_from_file(QString filename) {
  QFile inputFile(filename);
  if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    return nullptr;

  QTextStream in(&inputFile);
  QString attributes = in.readLine();
  if (attributes.isEmpty()) {
    qWarning() << "Could not load attributes from file:" << filename;
    return nullptr;
  }

  QStringList attribute_names = attributes.split(',', QString::KeepEmptyParts);
  if (attribute_names.isEmpty()) {
    qWarning() << "Empty list of attributes from file:" << filename;
    return nullptr;
  }

  Portfolio *p = new Portfolio;
  p->attribute_names_ = attribute_names;
  int lineno = 1;
  while (!in.atEnd()) {
    ++lineno;
    QString line = in.readLine();
    QStringList tokens = line.split(',', QString::KeepEmptyParts);
    if (tokens.size() != attribute_names.size()) {
      qWarning("Line %d has %d tokens, but %d were expected. Ignored.",
               lineno, tokens.size(), attributes.size());
      continue;
    }

    // create a Note from this line
    Note n;
    auto key = attribute_names.begin();
    auto value = tokens.begin();
    for (; key != attribute_names.end() && value != tokens.end(); ++key, ++value) {
      n.add_attribute(*key, *value);
    }

    p->notes_.append(n);
  }
  inputFile.close();

  return p;
}

