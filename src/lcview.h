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

#include <QMainWindow>

#include "charts.h"
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

private slots:
  void on_actionExit_triggered();

  void on_actionLoad_triggered();

private:
  Ui::LCView *ui_;
  Portfolio *portfolio_;
  Chart *chart_;

  void load_portfolio_from_file();
  void refresh_charts();
};
