/*
 *  An offline viewer for Lending Club notes statistics
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

#include <QMainWindow>
#include <QVBoxLayout>


#include "chartscontainer.h"
#include "filterspanel.h"
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

  void on_filter_update(QList<Filter> filters);

private:
  Ui::LCView *ui_;
  // This is the portfolio loaded from file.
  Portfolio *portfolio_;
  // This is the portfolio, as filtered and displayed.
  Portfolio *display_portfolio_;
  QVBoxLayout *main_layout_;

  // subcomponents and subwidgets
  FiltersPanel *filters_panel_;
  ChartsContainer *charts_container_;

  void load_portfolio_from_file();
  void build_main_layout();
  void refresh_charts(QList<Filter> filters);
  static Portfolio* apply_filters_to_portfolio(Portfolio* portfolio, QList<Filter> filters);

private slots:
  void on_actionExit_triggered();
  void on_actionLoad_triggered();
  void on_actionAbout_triggered();
};
