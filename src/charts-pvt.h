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
#include <QtWidgets/QCheckBox>


namespace Charts {

class GradeChart : public Chart {
  Q_OBJECT

public:
  explicit GradeChart(Portfolio *portfolio);
  virtual ~GradeChart();
  virtual QWidget* widget() { return widget_; }

private slots:
  void on_coarse_button_toggled(bool checked);

private:
  static const QMap<QString, QColor> grade_colors_;
  Portfolio *portfolio_;
  QWidget *widget_;

  // subcomponents and subwidgets
  QtCharts::QChart *chart_;
  QCheckBox *coarse_checkbox_;

  static QtCharts::QPieSeries* create_series(Portfolio *portfolio, bool coarse);
};


class StatusChart : public Chart {
public:
  explicit StatusChart(Portfolio *portfolio);
  virtual ~StatusChart();
  virtual QWidget* widget() { return widget_; }

private:
  Portfolio *portfolio_;
  QWidget *widget_;

  // subcomponents and subwidgets
  QtCharts::QChart *chart_;

  static QtCharts::QPieSeries* create_series(Portfolio *portfolio);
};

}; // namespace Charts
