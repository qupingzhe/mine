#include "status_dialog.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

StatusDialog::StatusDialog(QString str) {
  label = new QLabel(str);
  okButton = new QPushButton("OK");
  layout = new QVBoxLayout;
  layout->addWidget(label);
  layout->addWidget(okButton);
  setLayout(layout);
  connect(okButton, SIGNAL(clicked()),
      this, SLOT(hide()));
}

StatusDialog::~StatusDialog() {
  delete label;
  delete okButton;
}
