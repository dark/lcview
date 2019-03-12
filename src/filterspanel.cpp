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

#include "include/filterspanel.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "include/attributes.h"
#include "include/lcview.h"


FiltersPanel::FiltersPanel(LCView* parent)
  : QWidget(nullptr), parent_(parent) {
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

  setLayout(filters_row);
}


void FiltersPanel::reset_view() {
  filter_text_->clear();
}


void FiltersPanel::on_apply_button_clicked() {
  // The NoteField is embedded in the QVariant attached to each element of the selector
  Attributes::NoteField field = filter_selector_->currentData().value<Attributes::NoteField>();
  QString value = filter_text_->text();

  Filter *filter = nullptr;
  if (!value.isEmpty())
    filter = new Filter(field, value);

  parent_->on_filter_updated(filter);
  delete filter;
}


void FiltersPanel::on_reset_button_clicked() {
  reset_view();
  parent_->on_filter_updated(nullptr);
}
