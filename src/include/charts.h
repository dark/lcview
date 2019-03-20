/*
 *  An offline viewer for Lending Club notes
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

#include <QWidget>

#include "portfolio.h"

class Chart : public QObject {
public:
  Chart() = default;
  virtual ~Chart() = default;
  virtual QWidget* widget() = 0;
};

namespace Charts {

Chart* grade_distribution(Portfolio *p);
Chart* status_distribution(Portfolio *p);
Chart* term_distribution(Portfolio *p);

}; // namespace Charts
