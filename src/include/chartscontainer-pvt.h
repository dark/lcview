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

#include <QVBoxLayout>
#include <QWidget>

#include "charts.h"
#include "portfolio.h"


class ChartTab : public QWidget {
  Q_OBJECT

public:
  explicit ChartTab(QWidget *parent);
  ~ChartTab();

  virtual void update_displayed_portfolio(Portfolio* portfolio);

private:
  QVBoxLayout *main_layout_;

  Chart *chart_;

  void set_chart(Chart *chart);
  virtual Chart* generate_chart(Portfolio* portfolio) = 0;
};


class GradeDistributionChartTab : public ChartTab {
public:
  explicit GradeDistributionChartTab(QWidget *parent);
private:
  virtual Chart* generate_chart(Portfolio* portfolio) override;
};


class StatusDistributionChartTab : public ChartTab {
public:
  explicit StatusDistributionChartTab(QWidget *parent);
private:
  virtual Chart* generate_chart(Portfolio* portfolio) override;
};


class TermDistributionChartTab : public ChartTab {
public:
  explicit TermDistributionChartTab(QWidget *parent);
private:
  virtual Chart* generate_chart(Portfolio* portfolio) override;
};
