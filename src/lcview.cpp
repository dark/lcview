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

#include "lcview.h"

#include <QComboBox>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>


#include "ui_lcview.h"


LCView::LCView(QWidget *parent)
  : QMainWindow(parent),
    ui_(new Ui::LCView),
    portfolio_(nullptr),
    chart_(nullptr),
    main_layout_(nullptr) {
  ui_->setupUi(this);

  build_main_layout();
}

LCView::~LCView() {
  Chart *chart = chart_;
  chart_ = nullptr;
  delete chart;

  Portfolio *portfolio = portfolio_;
  portfolio_ = nullptr;
  refresh_charts();
  delete portfolio;

  delete ui_;
  ui_ = nullptr;
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
    refresh_charts();
    delete old_portfolio;
  } else {
    QMessageBox::warning(this, "Failed to load portfolio", "Failed to load portfolio from file: " + filename);
  }
}

void LCView::build_main_layout() {
  // Setup filters panel
  QLabel *label = new QLabel(tr("Filters:"));
  QComboBox *filter_selector = new QComboBox;
  filter_selector->addItem(tr("Grade"));
  filter_selector->addItem(tr("Term"));
  filter_selector->addItem(tr("Status"));

  QLineEdit *filter_text= new QLineEdit;
  filter_text->setPlaceholderText("enter filter condition here");

  QHBoxLayout *filters_row = new QHBoxLayout();
  filters_row->addWidget(label);
  filters_row->addWidget(filter_selector);
  filters_row->addWidget(filter_text);
  main_layout_ = new QVBoxLayout();
  main_layout_->addLayout(filters_row);
  main_layout_->addStretch();

  // We need to wrap the layout in a widget that includes everything.
  // This is because the QMainWindow has a top-level layout that cannot be changed.
  QWidget *main_widget = new QWidget();
  main_widget->setLayout(main_layout_);

  setCentralWidget(main_widget);
}

void LCView::set_chart_widget(QWidget *chart) {
  if (!main_layout_) {
    qWarning("Cannot set chart widget before main layout is setup!");
    return;
  }

  QLayoutItem *old_widget = main_layout_->takeAt(1);
  if (old_widget)
    delete old_widget;
  if (chart) {
    main_layout_->addWidget(chart);
  } else {
    // Just put a spacer.
    main_layout_->addStretch();
  }
}

void LCView::refresh_charts() {
  if (!portfolio_) {
    qWarning("Resetting chart widget because portfolio is empty");
    set_chart_widget(nullptr);
    return;
  }

  Chart *chart = Charts::grade_distribution(portfolio_);
  if (!chart) {
    qWarning("Nothing to do with a null chart");
    return;
  }
  delete chart_;
  chart_ = chart;

  set_chart_widget(chart->widget());
}

void LCView::on_actionExit_triggered() {
  QCoreApplication::quit();
}

void LCView::on_actionLoad_triggered() {
  LCView::load_portfolio_from_file();
}
