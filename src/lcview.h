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
#include <QMainWindow>
#include <QVBoxLayout>


#include "chartscontainer.h"
#include "portfolio.h"

namespace Ui {
class LCView;
}

class LCView : public QMainWindow
{
  Q_OBJECT

public:
  explicit LCView(QWidget *parent = nullptr);
  ~LCView();

private:
  Ui::LCView *ui_;
  // This is the portfolio loaded from file.
  Portfolio *portfolio_;
  // This is the portfolio, as filtered and displayed.
  Portfolio *display_portfolio_;
  QVBoxLayout *main_layout_;

  // subcomponents and subwidgets
  ChartsContainer *charts_container_;
  QComboBox *filter_selector_;
  QLineEdit *filter_text_;

  void load_portfolio_from_file();
  void build_main_layout();
  Portfolio *apply_filters_to_portfolio();
  void refresh_charts();

private slots:
  void on_actionExit_triggered();
  void on_actionLoad_triggered();
  void on_actionAbout_triggered();
  void on_apply_button_clicked();
  void on_reset_button_clicked();
};
