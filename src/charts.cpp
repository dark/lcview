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

#include "charts.h"

#include <QPieSeries>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>

#include "aggregator.h"

Chart::Chart() {}
Chart::~Chart() {}

namespace Charts {

class GradeChart : public Chart {
public:
  explicit GradeChart(Portfolio *portfolio);
  virtual ~GradeChart();
  virtual QWidget* widget() { return widget_; }

private:
  static const QMap<QString, QColor> grade_colors_;
  Portfolio *portfolio_;
  QWidget *widget_;

  static QtCharts::QPieSeries* create_series(Portfolio *portfolio, bool coarse);
};

const QMap<QString, QColor> GradeChart::grade_colors_ = {
  {"A", QColor(82, 120, 165)},
  {"B", QColor(110, 198, 226)},
  {"C", QColor(90, 163, 53)},
  {"D", QColor(137, 197, 64)},
  {"E", QColor(234, 226, 0)},
  {"F", QColor(255, 202, 44)},
  {"G", QColor(247, 149, 30)},
};

GradeChart::GradeChart(Portfolio *portfolio)
  : portfolio_(portfolio) {
  QtCharts::QPieSeries *series = create_series(portfolio_, true);

  QtCharts::QChart *chart = new QtCharts::QChart();
  chart->addSeries(series);
  chart->setTitle("<h1>Node grade distribution</h1>");
  chart->legend()->hide();
  chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

  QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  // Buttons to make the chart interactive
  QCheckBox *checkbox = new QCheckBox();
  QFormLayout *chartSettingsLayout = new QFormLayout();
  chartSettingsLayout->addRow("Coarse", checkbox);

  // Add wrapper layout to put everything together
  QVBoxLayout *mainLayout = new QVBoxLayout();
  mainLayout->addLayout(chartSettingsLayout);
  mainLayout->addWidget(chartView);
  QWidget *mainWidget = new QWidget();
  mainWidget->setLayout(mainLayout);

  widget_ = mainWidget;
}


GradeChart::~GradeChart() {
  // none of the pointers is owned by this class
}


QtCharts::QPieSeries* GradeChart::create_series(Portfolio *portfolio, bool coarse) {
  QMap<QString, int> grades = Aggregator::grades(portfolio, coarse);

  QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
  for (auto grade: grades.toStdMap())
    series->append(grade.first, grade.second);
  series->setLabelsVisible(true);

  // Apply colors similar to those from the official website
  for (auto slice: series->slices()) {
    // Use the first char only to determine grade and color
    QString label = slice->label().at(0);
    QMap<QString, QColor>::const_iterator color = grade_colors_.find(label);
    if (color != grade_colors_.end())
      slice->setBrush(color.value());
  }

  return series;
}


// Creation functions
Chart* grade_distribution(Portfolio *portfolio) {
  return new GradeChart(portfolio);
}

} // namespace Charts
