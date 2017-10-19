#include "qmine.h"

MineInterface* QMine::lowMine = new Mine(10, 9, 9);
MineInterface* QMine::midMine = new Mine(40, 20, 20);
MineInterface* QMine::highMine = new Mine(40, 30, 30);

QMine::QMine() {
	mine_interface_ = lowMine;
  graph_ = new int*[MAX_SIZE];
  for (int i = 0; i < MAX_SIZE; ++i) {
    graph_[i] = new int[MAX_SIZE];
  }
}

QMine::~QMine() {
  for (int i = 0; i < MAX_SIZE; ++i) {
    delete[] graph_[i];
  }
  delete[] graph_;
	//delete mine_interface_;
}

void QMine::setLevel(int level) {
	switch (level) {
		case LOW: mine_interface_ = lowMine;
              break;
		case MID: mine_interface_ = midMine;
              break;
		case HIGH: mine_interface_ = highMine;
               break;
		default: break;
	}
}

/*
int QMine::getCellType(int x, int y) {
	return mine_interface_->getCellType(x, y);
}


int QMine::getColumn() {
	return mine_interface_->getColumn();
}

int QMine::getRow() {
	return mine_interface_->getRow();
}
*/

void QMine::testFlag() {
  int flag = mine_interface_->getStatus();
  if (flag > 0) {
    mine_interface_->win();
    emit win();
  } else if (flag < 0) {
    mine_interface_->lose();
    emit lose();
  }
}

void QMine::explore(int x, int y) {
  mine_interface_->explore(x, y);
  testFlag();
  mine_interface_->copyGraph(graph_, &column_, &row_);
  emit updateGraph(graph_, column_, row_);
  emit clicked ();
  /*
  int type = mine_interface_->getCellType(x, y);
  if (type == NO_DISCOVERY) {
    mine_interface_->explore(x, y);
  } else if (type != TAB) {
    mine_interface_->exploreFast(x, y);
  }
  */
}

void QMine::mark(int x, int y) {
  mine_interface_->mark(x, y);
  testFlag();
  mine_interface_->copyGraph(graph_, &column_, &row_);
  emit updateGraph(graph_, column_, row_);
  emit remainingMine(mine_interface_->getRemainingMine());
  /*
	try {
		mine_interface_->mark( x, y);
		if (mine_interface_->isWinned()) {
			emit win();
		}
		emit clicked(this);
		emit clicked();
	}
	catch( ErrorTab errorTab ) {
		emit tab();
	}
  */
}

void QMine::restart() {
	mine_interface_->restart();
  mine_interface_->copyGraph(graph_, &column_, &row_);
  emit updateGraph(graph_, column_, row_);
	emit remainingMine(mine_interface_->getRemainingMine() );
}
