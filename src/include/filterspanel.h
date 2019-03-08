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

#include <QComboBox>
#include <QLineEdit>
#include <QWidget>

class LCView; // fwd decl

class FiltersPanel : public QWidget
{
  Q_OBJECT

public:
  explicit FiltersPanel(LCView* parent);

  void reset_view();

private:
  LCView *parent_;
  // subcomponents and subwidgets
  QComboBox *filter_selector_;
  QLineEdit *filter_text_;

private slots:
  void on_apply_button_clicked();
  void on_reset_button_clicked();
};
