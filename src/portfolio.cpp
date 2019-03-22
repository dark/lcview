/*
 *  An offline viewer for Lending Club notes statistics
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

#include "include/portfolio.h"

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


QStringList tokenize_line(QString line, char separator, char quote) {
  QStringList tokens;
  QString token;

  enum class State {
    INSIDE_TOKEN,
    INSIDE_QUOTED_TOKEN,
    CLOSING_QUOTED_TOKEN,
  };

  State state = State::INSIDE_TOKEN;
  auto cursor = line.begin();
  do {
    switch (state) {
      case State::INSIDE_TOKEN:
        if (cursor == line.end() || *cursor == separator) {
          tokens.append(token);
          token.clear();
        } else if (*cursor == quote) {
          state = token.isEmpty()? State::INSIDE_QUOTED_TOKEN : state;
          token.append(*cursor);
        } else {
          token.append(*cursor);
        }
        break;

      case State::INSIDE_QUOTED_TOKEN:
        if (cursor != line.end() && *cursor == quote)
          state = State::CLOSING_QUOTED_TOKEN;

        token.append(*cursor);
        break;

      case State::CLOSING_QUOTED_TOKEN:
        if (cursor == line.end() || *cursor == separator) {
          // Trim the first and last character (the quotes) first.
          token = token.mid(1, token.size() - 2);
          tokens.append(token);
          token.clear();
        } else {
          token.append(*cursor);
        }
        state = State::INSIDE_TOKEN;
        break;
    }
    if (cursor == line.end())
      break;
    ++cursor;
  } while (true);

  return tokens;
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
  if (attribute_names.size() < 2) {
    qWarning() << "Empty list of attributes from file:" << filename;
    return nullptr;
  }

  Portfolio *p = new Portfolio;
  p->attribute_names_ = attribute_names;
  int lineno = 1;
  while (!in.atEnd()) {
    ++lineno;
    QString line = in.readLine();
    QStringList tokens = tokenize_line(line, ',', '"');
    if (tokens.size() != attribute_names.size()) {
      qWarning("Line %d has %d tokens, but %d were expected. Ignored.",
               lineno, tokens.size(), attribute_names.size());
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

  qInfo() << "Loaded" << p->notes_.size() << "notes from file:" << filename
          << "(skipped" << (lineno - p->notes_.size() - 1) << "lines)";
  return p;
}


Portfolio* Portfolio::filter(QList<Filter> filters) {
  Portfolio *filtered = new Portfolio;
  filtered->attribute_names_ = this->attribute_names_;

  for (const Note &note: this->notes_) {
    bool matches = true;

    // Each note must match all provided filters.
    for (auto f = filters.begin(); matches && f != filters.end(); ++f)
      matches = f->match(note);

    if (matches)
      filtered->notes_.append(note);
  }

  qInfo("Filtered down from %d notes to %d notes.", this->notes_.size(), filtered->notes_.size());
  return filtered;
}

