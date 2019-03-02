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

#include "lcview.h"

#include <QFileDialog>
#include <QMessageBox>
#include "ui_lcview.h"


LCView::LCView(QWidget *parent) :
  QMainWindow(parent),
  ui_(new Ui::LCView),
  portfolio_(nullptr)
{
  ui_->setupUi(this);
}

LCView::~LCView()
{
  delete portfolio_;
  portfolio_ = nullptr;
  delete ui_;
  ui_ = nullptr;
}

void LCView::load_portfolio_from_file()
{
  QString filename = QFileDialog::getOpenFileName(this, "Open portfolio file");
  if (filename.isEmpty()) {
    qInfo("User aborted portfolio load");
    return;
  }

  Portfolio *p = Portfolio::create_from_file(filename);
  if (p) {
    delete portfolio_;
    portfolio_ = p;
  } else {
    QMessageBox::warning(this, "Failed to load portfolio", "Failed to load portfolio from file: " + filename);
  }
}

void LCView::on_actionExit_triggered()
{
  QCoreApplication::quit();
}

void LCView::on_actionLoad_triggered()
{
  LCView::load_portfolio_from_file();
}
