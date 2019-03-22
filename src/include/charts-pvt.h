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

class TermChart : public Chart {
public:
  explicit TermChart(Portfolio *portfolio);
  virtual ~TermChart();
  virtual QWidget* widget() { return widget_; }

private:
  Portfolio *portfolio_;
  QWidget *widget_;

  // subcomponents and subwidgets
  QtCharts::QChart *chart_;

  static QtCharts::QPieSeries* create_series(Portfolio *portfolio);
};


// Helpers
template <class T>
int values_total(const QMap<T, int> &values) {
  int total = 0;
  for (auto i = values.cbegin(); i != values.cend(); ++i)
    total += i.value();
  return total;
}

template <class T>
QtCharts::QPieSeries* create_pie_series(const QMap<T, int> &mappings, QString (*to_label)(T)) {
  QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
  const int total = values_total(mappings);
  double tightness = 0.0;

  for (auto mapping: mappings.toStdMap()) {
    QString base_label = to_label(mapping.first);
    const int value = mapping.second;
    const double ratio = double(value) / total;

    QString label = QString("%1 (%2 of %3)").arg(base_label).arg(value).arg(total);
    QtCharts::QPieSlice *slice = series->append(label, value);
    if (ratio < 0.03) {
      // Labels on slices smaller than 3% of the total need to compensate for extra tightness.
      tightness = tightness + 0.1;
      slice->setLabelArmLengthFactor(tightness);
    } else {
      // Reset tightness to its default value for larger slices. Slices with intermediate sizes (3 to 5%)
      // add a a bit of extra tightness to the next slice.
      tightness = ratio < 0.05 ? 0.1 : 0.0;
      slice->setLabelArmLengthFactor(0.1);
    }
  }
  series->setLabelsVisible(true);
  return series;
}

QString int_to_qstring(const int value);
QString qstring_to_qstring(const QString qstring);

}; // namespace Charts
