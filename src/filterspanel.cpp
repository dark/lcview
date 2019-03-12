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
#include "include/filterspanel-pvt.h"
#include "include/lcview.h"


FiltersPanel::FiltersPanel(LCView* parent)
  : QWidget(nullptr), parent_(parent) {
  QLabel *filter_label = new QLabel(tr("Filter:"));
  filter_selector_ = new QComboBox;
  filter_selector_->insertItem(1, "(none)",
                               QVariant());
  filter_selector_->insertItem(2, "Grade",
                               QVariant::fromValue(Attributes::NoteField::GRADE));
  filter_selector_->insertItem(3, "Term",
                               QVariant::fromValue(Attributes::NoteField::TERM));
  filter_selector_->insertItem(4, "Status",
                               QVariant::fromValue(Attributes::NoteField::STATUS));
  connect(filter_selector_, SIGNAL(activated(int)), this, SLOT(on_filter_selection_changed(int)));

  filter_value_ = new FilterValueWidget;

  // Buttons and their actions
  QPushButton *apply_button = new QPushButton(tr("Apply"));
  QPushButton *reset_button = new QPushButton(tr("Reset"));
  connect(apply_button, SIGNAL(clicked()), this, SLOT(on_apply_button_clicked()));
  connect(reset_button, SIGNAL(clicked()), this, SLOT(on_reset_button_clicked()));

  // Layout for the filters row
  QHBoxLayout *filters_row = new QHBoxLayout();
  filters_row->setContentsMargins(0, 0, 0, 0);
  filters_row->addWidget(filter_label);
  filters_row->addWidget(filter_selector_);
  filters_row->addWidget(filter_value_);
  filters_row->addWidget(apply_button);
  filters_row->addWidget(reset_button);

  setLayout(filters_row);
}


void FiltersPanel::reset_view() {
  filter_selector_->setCurrentIndex(0);
  filter_value_->clear_active_filter();
}


void FiltersPanel::on_filter_selection_changed(int /* unused */) {
  if (!filter_selector_ || !filter_value_) {
    qCritical("Filter selection changed while the UI is not setup");
    return;
  }

  QVariant data = filter_selector_->currentData();
  if (data.isValid())
    filter_value_->set_active_filter(data.value<Attributes::NoteField>());
  else
    filter_value_->clear_active_filter();
}


void FiltersPanel::on_apply_button_clicked() {
  Filter *filter = nullptr;

  // The NoteField is embedded in the QVariant attached to each element of the selector
  QVariant data = filter_selector_->currentData();
  if (data.isValid()) {
    Attributes::NoteField field = data.value<Attributes::NoteField>();
    filter = filter_value_->value(field);
  }

  parent_->on_filter_updated(filter);
  delete filter;
}


void FiltersPanel::on_reset_button_clicked() {
  reset_view();
  parent_->on_filter_updated(nullptr);
}


FilterValueWidget::FilterValueWidget() : QWidget(nullptr), filter_text_(nullptr) {
  // This container takes care of the placement of the children widgets
  main_layout_ = new QHBoxLayout();
  // Do not waste available space with margins
  main_layout_->setContentsMargins(0, 0, 0, 0);

  // This stretchable space will be replaced by the actual value widget as needed
  main_layout_->addStretch();

  setLayout(main_layout_);
}


void FilterValueWidget::set_active_filter(Attributes::NoteField field) {
  remove_filter_widget();

  // The actual editable part
  filter_text_ = new QLineEdit;
  filter_text_->setPlaceholderText("enter filter condition here");

  main_layout_->addWidget(filter_text_);
}


void FilterValueWidget::clear_active_filter() {
  remove_filter_widget();

  // Just put a spacer.
  main_layout_->addStretch();
}


Filter* FilterValueWidget::value(Attributes::NoteField field) const {
  if (!filter_text_) {
    qCritical("invalid state: filter text widget is null when filter '%s' is received",
              qUtf8Printable(Attributes::field_key(field)));
    return nullptr;
  }

  QString value = filter_text_->text();
  if (value.isEmpty())
    return nullptr;

  return new Filter(field, value);
}


void FilterValueWidget::remove_filter_widget() {
  QLayoutItem *old_widget = main_layout_->takeAt(0);
  if (old_widget) {
    delete old_widget->widget();
    delete old_widget;
  }

  // Make all optional widgets null
  filter_text_ = nullptr;
}
