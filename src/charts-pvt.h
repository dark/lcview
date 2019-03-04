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

#include "charts.h"

#include <QPieSeries>

namespace Charts {

class GradeChart : public Chart {
  Q_OBJECT

public:
  explicit GradeChart(Portfolio *portfolio);
  virtual ~GradeChart();
  virtual QWidget* widget() { return widget_; }

private slots:
  void on_coarse_button_clicked();

private:
  static const QMap<QString, QColor> grade_colors_;
  Portfolio *portfolio_;
  QWidget *widget_;

  static QtCharts::QPieSeries* create_series(Portfolio *portfolio, bool coarse);
};

}; // namespace Charts
