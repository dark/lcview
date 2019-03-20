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

#include "include/chartscontainer.h"

#include "include/chartscontainer-pvt.h"


ChartsContainer::ChartsContainer()
  : QTabWidget(nullptr) {
  add_one_tab(new GradeDistributionChartTab(this), tr("Grade distribution"));
  add_one_tab(new StatusDistributionChartTab(this), tr("Status distribution"));
  add_one_tab(new TermDistributionChartTab(this), tr("Term distribution"));
}


ChartsContainer::~ChartsContainer() {
  for (ChartTab *tab: tabs_)
    delete tab;
}


void ChartsContainer::add_one_tab(ChartTab *tab, QString label) {
  tabs_.append(tab);
  addTab(tab, label);
}


void ChartsContainer::update_displayed_portfolio(Portfolio *portfolio) {
  for (ChartTab *tab: tabs_)
    tab->update_displayed_portfolio(portfolio);
}


ChartTab::ChartTab(QWidget *parent)
  : QWidget(parent), chart_(nullptr) {
  main_layout_ = new QVBoxLayout();
  // This stretchable space will be replaced by the chart widget as needed
  main_layout_->addStretch();

  setLayout(main_layout_);
}


ChartTab::~ChartTab() {
  QLayoutItem *old_widget = main_layout_->takeAt(0);
  if (old_widget) {
    delete old_widget->widget();
    delete old_widget;
  }
}


void ChartTab::update_displayed_portfolio(Portfolio *portfolio) {
  if (!portfolio) {
    qWarning("Clearing chart since input portfolio is nullptr");
    set_chart(nullptr);
    return;
  }

  Chart *chart = generate_chart(portfolio);
  if (!chart)
    qWarning("null chart was generated");
  set_chart(chart);
}


void ChartTab::set_chart(Chart *chart) {
  chart_.reset(chart);

  QLayoutItem *old_widget = main_layout_->takeAt(0);
  if (old_widget) {
    delete old_widget->widget();
    delete old_widget;
  }

  if (chart) {
    main_layout_->addWidget(chart->widget());
  } else {
    // Just put a spacer.
    main_layout_->addStretch();
  }
}


// Specialized tabs
GradeDistributionChartTab::GradeDistributionChartTab(QWidget *parent)
  : ChartTab(parent) {}

Chart* GradeDistributionChartTab::generate_chart(Portfolio* portfolio) {
  return Charts::grade_distribution(portfolio);
}

StatusDistributionChartTab::StatusDistributionChartTab(QWidget *parent)
  : ChartTab(parent) {}

Chart* StatusDistributionChartTab::generate_chart(Portfolio* portfolio) {
  return Charts::status_distribution(portfolio);
}

TermDistributionChartTab::TermDistributionChartTab(QWidget *parent)
  : ChartTab(parent) {}

Chart* TermDistributionChartTab::generate_chart(Portfolio* portfolio) {
  return Charts::term_distribution(portfolio);
}
