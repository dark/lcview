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

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "filterelement.h"

// fwd decls
class LCView;

class FiltersPanel : public QWidget {
  Q_OBJECT

public:
  explicit FiltersPanel(LCView* parent);

  void remove_element(FilterElement* filter);
  void reset_filters();

private:
  LCView *parent_;
  QList<FilterElement*> filter_elements_;
  QHBoxLayout *filters_row_;

  // subcomponents and subwidgets
  QPushButton *apply_button_;
  QPushButton *reset_button_;

private slots:
  void on_plus_button_clicked();
  void on_apply_button_clicked();
  void on_reset_button_clicked();
};
