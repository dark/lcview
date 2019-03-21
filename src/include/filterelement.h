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

#pragma once

#include <QComboBox>
#include <QFrame>
#include <QWidget>
#include "filter.h"

// fwd decls
class FilterValueWidget;
class FiltersPanel;

class FilterElement : public QFrame {
  Q_OBJECT

public:
  explicit FilterElement(FiltersPanel *parent);

  void reset_view();

  std::optional<Filter> get_filter();

private:
  FiltersPanel *parent_;
  // subcomponents and subwidgets
  QComboBox *filter_selector_;
  FilterValueWidget *filter_value_;

private slots:
  void on_filter_selection_changed(int index);
  void on_close_button_clicked();
};
