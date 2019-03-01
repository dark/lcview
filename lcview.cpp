#include "lcview.h"
#include "ui_lcview.h"

LCView::LCView(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::LCView)
{
  ui->setupUi(this);
}

LCView::~LCView()
{
  delete ui;
}
