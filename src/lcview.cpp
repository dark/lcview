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

#include "include/lcview.h"

#include <QFileDialog>
#include <QMessageBox>

#include "ui_lcview.h"


LCView::LCView(QWidget *parent)
  : QMainWindow(parent),
    ui_(new Ui::LCView),
    portfolio_(nullptr),
    display_portfolio_(nullptr),
    main_layout_(nullptr),
    filters_panel_(nullptr),
    charts_container_(nullptr) {
  ui_->setupUi(this);

  build_main_layout();
}


LCView::~LCView() {
  ChartsContainer *charts_container = charts_container_;
  charts_container_ = nullptr;
  delete charts_container;

  FiltersPanel *filters_panel = filters_panel_;
  filters_panel_ = nullptr;
  delete filters_panel;

  if (display_portfolio_ != portfolio_)
    // If no filter was applied, both pointers point at the same object
    delete display_portfolio_;
  display_portfolio_ = nullptr;

  delete portfolio_;
  portfolio_ = nullptr;

  delete ui_;
  ui_ = nullptr;
}


void LCView::on_filter_update(QList<Filter> filters) {
  refresh_charts(filters);
}


void LCView::load_portfolio_from_file() {
  QString filename = QFileDialog::getOpenFileName(this, "Open portfolio file");
  if (filename.isEmpty()) {
    qInfo("User aborted portfolio load");
    return;
  }

  Portfolio *p = Portfolio::create_from_file(filename);
  if (p) {
    Portfolio *old_portfolio = portfolio_;
    portfolio_ = p;
    filters_panel_->reset_filters();
    refresh_charts(QList<Filter>());
    delete old_portfolio;
  } else {
    QMessageBox::warning(this, "Failed to load portfolio", "Failed to load portfolio from file: " + filename);
  }
}


void LCView::build_main_layout() {
  // Setup filters panel
  filters_panel_ = new FiltersPanel(this);

  // Widget for the main charts tabbed area
  charts_container_ = new ChartsContainer();

  main_layout_ = new QVBoxLayout();
  main_layout_->addWidget(filters_panel_);
  main_layout_->addWidget(charts_container_);

  // We need to wrap the layout in a widget that includes everything.
  // This is because the QMainWindow has a top-level layout that cannot be changed.
  QWidget *main_widget = new QWidget();
  main_widget->setLayout(main_layout_);

  setCentralWidget(main_widget);
}


void LCView::refresh_charts(QList<Filter> filters) {
  if (!charts_container_) {
    qWarning("Charts container is nullptr, ignoring refresh");
    return;
  }

  if (!portfolio_) {
    qWarning("Resetting charts container because portfolio is empty");
    charts_container_->update_displayed_portfolio(nullptr);
    return;
  }

  display_portfolio_ = apply_filters_to_portfolio(portfolio_, filters);
  if (!display_portfolio_)
    qWarning("Resetting charts container because display portfolio is empty");
  charts_container_->update_displayed_portfolio(display_portfolio_);
}


Portfolio *LCView::apply_filters_to_portfolio(Portfolio* portfolio, QList<Filter> filters) {
  if (!portfolio || filters.isEmpty())
    return portfolio;

  return portfolio->filter(filters);
}


void LCView::on_actionExit_triggered() {
  QCoreApplication::quit();
}


void LCView::on_actionLoad_triggered() {
  LCView::load_portfolio_from_file();
}


void LCView::on_actionAbout_triggered() {
  QMessageBox::about(this,
                     "About lcview",
                     "lcview: A better viewer for Lending Club notes \n" \
                     "\n" \
                     "Copyright (C) 2019 Marco Leogrande");
}
