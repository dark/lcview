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

#include "include/filterelement.h"
#include "include/filterelement-pvt.h"

#include <QHBoxLayout>
#include <QToolButton>


FilterElement::FilterElement(): QFrame() {
  // Filter key
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

  // Context-dependent filter value
  filter_value_ = new FilterValueWidget;

  // This is to remove the filter
  QIcon close_icon(":/images/images/close.png");
  QToolButton *close_button = new QToolButton();
  close_button->setIcon(close_icon);

  // Layout for the element
  QHBoxLayout *layout = new QHBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(filter_selector_);
  layout->addWidget(filter_value_);
  layout->addWidget(close_button);

  setLayout(layout);
  setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  setLineWidth(1);
}


void FilterElement::reset_view() {
  filter_selector_->setCurrentIndex(0);
  filter_value_->clear_active_filter();
}


std::optional<Filter> FilterElement::get_filter() {
  // The NoteField is embedded in the QVariant attached to each element of the selector
  QVariant data = filter_selector_->currentData();
  if (!data.isValid())
    return {};

  Attributes::NoteField field = data.value<Attributes::NoteField>();
  return filter_value_->get_filter(field);
}


void FilterElement::on_filter_selection_changed(int /* unused */) {
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


FilterValueWidget::FilterValueWidget() : QWidget(nullptr), filter_value_component_(nullptr) {
  // This container takes care of the placement of the children widgets
  main_layout_ = new QHBoxLayout();
  // Do not waste available space with margins
  main_layout_->setContentsMargins(0, 0, 0, 0);

  setLayout(main_layout_);
}


FilterValueWidget::~FilterValueWidget() {
  remove_filter_widget();
}


void FilterValueWidget::set_active_filter(Attributes::NoteField field) {
  remove_filter_widget();

  switch (field) {
    case Attributes::NoteField::TERM:
      filter_value_component_ = new TermSelectorComponent;
      break;

    case Attributes::NoteField::INTEREST:
    case Attributes::NoteField::ADDRESS_STATE:
    case Attributes::NoteField::LOAN_ISSUE_DATE:
      qWarning("Field '%s' unsupported, displaying generic text editor instead",
               qUtf8Printable(Attributes::field_key(field)));
      // fallthrough on purpose
      [[clang::fallthrough]];
    case Attributes::NoteField::GRADE:
    case Attributes::NoteField::STATUS:
      filter_value_component_ = new TextEditorComponent;
      break;
  }
  main_layout_->addWidget(filter_value_component_->widget());
}


void FilterValueWidget::clear_active_filter() {
  remove_filter_widget();
}


std::optional<Filter> FilterValueWidget::get_filter(Attributes::NoteField field) const {
  if (!filter_value_component_) {
    qCritical("invalid state: filter text widget is null when filter '%s' is received",
              qUtf8Printable(Attributes::field_key(field)));
    return {};
  }

  QStringList values = filter_value_component_->values();
  if (values.isEmpty())
    return {};

  return Filter(field, values);
}


void FilterValueWidget::remove_filter_widget() {
  delete filter_value_component_;
  filter_value_component_ = nullptr;

  QLayoutItem *old_widget = main_layout_->takeAt(0);
  if (old_widget) {
    delete old_widget->widget();
    delete old_widget;
  }
}


TermSelectorComponent::TermSelectorComponent() {
  term_36_checkbox_ = new QCheckBox("36 months");
  term_60_checkbox_ = new QCheckBox("60 months");

  // Add wrapper layout to put everything together
  QHBoxLayout *mainLayout = new QHBoxLayout();
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(term_36_checkbox_);
  mainLayout->addWidget(term_60_checkbox_);
  QWidget *mainWidget = new QWidget();
  mainWidget->setLayout(mainLayout);

  widget_ = mainWidget;
}


TermSelectorComponent::~TermSelectorComponent() {
  // none of the pointers is owned by this class
}


QWidget* TermSelectorComponent::widget() const {
  return widget_;
}


QStringList TermSelectorComponent::values() const {
  QStringList values;
  if (term_36_checkbox_->isChecked())
    values.append("36");
  if (term_60_checkbox_->isChecked())
    values.append("60");
  return values;
}


TextEditorComponent::TextEditorComponent() {
  line_edit_ = new QLineEdit;
  line_edit_->setPlaceholderText("enter filter condition here");
}


TextEditorComponent::~TextEditorComponent() {
  // none of the pointers is owned by this class
}


QWidget* TextEditorComponent::widget() const {
  return line_edit_;
}


QStringList TextEditorComponent::values() const {
  QString value = line_edit_->text();
  if (value.isEmpty())
    // an empty value should be treated as being "no" value
    return QStringList();
  return QStringList(value);
}
