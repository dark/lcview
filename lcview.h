#ifndef LCVIEW_H
#define LCVIEW_H

#include <QMainWindow>

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
  Ui::LCView *ui;
};

#endif // LCVIEW_H
