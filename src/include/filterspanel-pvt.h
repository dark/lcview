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

#include <QHBoxLayout>
#include <QLineEdit>
#include <QWidget>
#include <QtWidgets/QCheckBox>
#include "attributes.h"
#include "filter.h"


// Base class for all components that can be used to select the value of the filter
class FilterValueComponent : public QObject {
public:
  FilterValueComponent() = default;
  virtual ~FilterValueComponent() = default;
  virtual QWidget* widget() const = 0;
  virtual QStringList values() const = 0;
};


// Allows the user to select a term
class TermSelectorComponent : public FilterValueComponent {
public:
  TermSelectorComponent();
  virtual ~TermSelectorComponent();
  virtual QWidget* widget() const;
  virtual QStringList values() const;

private:
  QWidget *widget_;

  // subcomponents and subwidgets
  QCheckBox *term_36_checkbox_, *term_60_checkbox_;
};


// Uses a simple text editor to enter the requested information
class TextEditorComponent : public FilterValueComponent {
public:
  TextEditorComponent();
  virtual ~TextEditorComponent();
  virtual QWidget* widget() const;
  virtual QStringList values() const;

private:
  QLineEdit *line_edit_;
};


// Wrapper around all available, filter-dependant widgets
class FilterValueWidget : public QWidget {
  Q_OBJECT

public:
  FilterValueWidget();

  void set_active_filter(Attributes::NoteField field);
  void clear_active_filter();
  Filter* filter(Attributes::NoteField field) const;

private:
  QHBoxLayout *main_layout_;
  FilterValueComponent *filter_value_component_;

  void remove_filter_widget();
};
