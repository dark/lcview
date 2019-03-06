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

#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>


#include "ui_lcview.h"


LCView::LCView(QWidget *parent)
  : QMainWindow(parent),
    ui_(new Ui::LCView),
    portfolio_(nullptr),
    display_portfolio_(nullptr),
    main_layout_(nullptr),
    charts_container_(nullptr),
    filter_selector_(nullptr),
    filter_text_(nullptr) {
  ui_->setupUi(this);

  build_main_layout();
}

LCView::~LCView() {
  ChartsContainer *charts_container = charts_container_;
  charts_container_ = nullptr;
  delete charts_container;

  // Do not delete this - it is only a "view" of the general portfolio, that will take care of cleanup
  display_portfolio_ = nullptr;

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
  QLabel *filter_label = new QLabel(tr("Filter:"));
  filter_selector_ = new QComboBox;
  filter_selector_->insertItem(1, "Grade",
                               QVariant::fromValue(Attributes::NoteField::GRADE));
  filter_selector_->insertItem(2, "Term",
                               QVariant::fromValue(Attributes::NoteField::TERM));
  filter_selector_->insertItem(3, "Status",
                               QVariant::fromValue(Attributes::NoteField::STATUS));

  filter_text_ = new QLineEdit;
  filter_text_->setPlaceholderText("enter filter condition here");

  // Buttons and their actions
  QPushButton *apply_button = new QPushButton(tr("Apply"));
  QPushButton *reset_button = new QPushButton(tr("Reset"));
  connect(apply_button, SIGNAL(clicked()), this, SLOT(on_apply_button_clicked()));
  connect(reset_button, SIGNAL(clicked()), this, SLOT(on_reset_button_clicked()));

  // Layout for the filters row
  QHBoxLayout *filters_row = new QHBoxLayout();
  filters_row->addWidget(filter_label);
  filters_row->addWidget(filter_selector_);
  filters_row->addWidget(filter_text_);
  filters_row->addWidget(apply_button);
  filters_row->addWidget(reset_button);

  // Widget for the main charts tabbed area
  charts_container_ = new ChartsContainer();

  main_layout_ = new QVBoxLayout();
  main_layout_->addLayout(filters_row);
  main_layout_->addWidget(charts_container_);

  // We need to wrap the layout in a widget that includes everything.
  // This is because the QMainWindow has a top-level layout that cannot be changed.
  QWidget *main_widget = new QWidget();
  main_widget->setLayout(main_layout_);

  setCentralWidget(main_widget);
}

Portfolio *LCView::apply_filters_to_portfolio() {
  if (!filter_selector_ || !filter_text_) {
    qWarning("Cannot apply filters, the UI is not setup!");
    return portfolio_;
  }

  // The NoteField is embedded in the QVariant attached to each element of the selector
  Attributes::NoteField field = filter_selector_->currentData().value<Attributes::NoteField>();
  QString value = filter_text_->text();
  if (value.isEmpty())
    // nothing to filter
    return portfolio_;

  Filter filter(field, value);

  return portfolio_->filter({filter});
}

void LCView::refresh_charts() {
  if (!charts_container_) {
    qWarning("Charts container is nullptr, ignoring refresh");
    return;
  }

  if (!portfolio_) {
    qWarning("Resetting charts container because portfolio is empty");
    charts_container_->update_displayed_portfolio(nullptr);
    return;
  }

  display_portfolio_ = apply_filters_to_portfolio();
  if (!display_portfolio_)
    qWarning("Resetting charts container because display portfolio is empty");
  charts_container_->update_displayed_portfolio(display_portfolio_);
}

void LCView::on_actionExit_triggered() {
  QCoreApplication::quit();
}

void LCView::on_actionLoad_triggered() {
  LCView::load_portfolio_from_file();
}

void LCView::on_apply_button_clicked() {
  refresh_charts();
}

void LCView::on_reset_button_clicked() {
  filter_text_->clear();
  refresh_charts();
}
