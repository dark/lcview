#include "lcview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  LCView w;
  w.show();

  return a.exec();
}
