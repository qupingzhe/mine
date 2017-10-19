#ifndef STASTUS_DIALOG_H
#define STASTUS_DIALOG_H

#include <QDialog>

class QLabel;
class QLayout;
class QPushButton;

class StatusDialog : public QDialog {
public:
  StatusDialog(QString str);
  ~StatusDialog();
private:
  QLabel* label;
  QPushButton* okButton;
  QLayout* layout;
};

#endif
