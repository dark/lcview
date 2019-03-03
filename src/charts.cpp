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

#include "aggregator.h"


QtCharts::QChart *Charts::grade_distribution(Portfolio *p) {
  QMap<QString, int> grades = Aggregator::grades(p, true);

  QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
  for (auto grade: grades.toStdMap())
    series->append(grade.first, grade.second);
  series->setLabelsVisible(true);

  QtCharts::QChart *chart = new QtCharts::QChart();
  chart->addSeries(series);
  chart->setTitle("Node grade distribution");
  chart->legend()->hide();
  chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

  return chart;
}
