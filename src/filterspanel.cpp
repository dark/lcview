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

#include "include/filterspanel.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "include/attributes.h"
#include "include/lcview.h"


FiltersPanel::FiltersPanel(LCView* parent)
  : QWidget(nullptr), parent_(parent) {
  // Label for the row
  QLabel *filter_label = new QLabel(tr("Filter:"));

  // Buttons and their actions
  QPushButton *plus_button = new QPushButton(tr("+"));
  plus_button->setFixedWidth(20);
  apply_button_ = new QPushButton(tr("Apply"));
  apply_button_->setEnabled(false);
  reset_button_ = new QPushButton(tr("Reset"));
  reset_button_->setEnabled(false);
  connect(plus_button, SIGNAL(clicked()), this, SLOT(on_plus_button_clicked()));
  connect(apply_button_, SIGNAL(clicked()), this, SLOT(on_apply_button_clicked()));
  connect(reset_button_, SIGNAL(clicked()), this, SLOT(on_reset_button_clicked()));

  // Layout for the filters row
  filters_row_ = new QHBoxLayout();
  filters_row_->setContentsMargins(0, 0, 0, 0);
  filters_row_->addWidget(filter_label);
  filters_row_->addWidget(plus_button);
  filters_row_->addStretch();
  filters_row_->addWidget(apply_button_);
  filters_row_->addWidget(reset_button_);

  setLayout(filters_row_);
}


void FiltersPanel::remove_element(FilterElement *filter) {
  for (auto i = filter_elements_.begin(); i != filter_elements_.end(); ++i) {
    if (*i == filter) {
      // This is the filter we want to remove
      filter_elements_.erase(i);
      filters_row_->removeWidget(filter);
      // This is needed because this function is likely called by a filter callback
      filter->deleteLater();
      break;
    }
  }

  if (filter_elements_.isEmpty()) {
    // That was the last filter
    apply_button_->setEnabled(false);
    reset_button_->setEnabled(false);
  }
}


void FiltersPanel::reset_filters() {
  for (auto element: filter_elements_) {
    filters_row_->removeWidget(element);
    delete element;
  }
  filter_elements_.clear();

  apply_button_->setEnabled(false);
  reset_button_->setEnabled(false);
}


void FiltersPanel::on_plus_button_clicked() {
  // Add new filter at the end of the other filters
  FilterElement *filter_element = new FilterElement(this);
  filter_elements_.append(filter_element);
  filters_row_->insertWidget(filter_elements_.size(), filter_element);

  apply_button_->setEnabled(true);
  reset_button_->setEnabled(true);
}


void FiltersPanel::on_apply_button_clicked() {
  QList<Filter> filters;
  for (auto element: filter_elements_) {
    std::optional<Filter> filter = element->get_filter();
    if (filter.has_value())
      filters.append(*filter);
  }
  parent_->on_filter_update(filters);
}


void FiltersPanel::on_reset_button_clicked() {
  reset_filters();
  parent_->on_filter_update(QList<Filter>());
}
