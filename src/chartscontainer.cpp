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

#include "chartscontainer.h"

#include "chartscontainer-pvt.h"


ChartsContainer::ChartsContainer()
  : QTabWidget(nullptr) {
  // Grade distribution chart tab
  ChartTab *tab = new ChartTab(this);
  tabs_.append(tab);
  addTab(tab, tr("Grade distribution"));
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

void ChartTab::update_displayed_portfolio(Portfolio *portfolio) {
  if (!portfolio) {
    qWarning("Clearing chart since input portfolio is nullptr");
    set_chart(nullptr);
    return;
  }

  Chart *chart = Charts::grade_distribution(portfolio);
  if (!chart)
    qWarning("null chart was generated");
  set_chart(chart);
}

void ChartTab::set_chart(Chart *chart) {
  delete chart_;
  chart_ = chart;

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
