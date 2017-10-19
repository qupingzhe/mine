#include "mine_gui.h"

#include "mine_field.h"
#include "qmine.h"
#include "mine_timer.h"
#include "status_dialog.h"

#include <QLCDNumber>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

//#include <iostream>

MineMainWindow::MineMainWindow() {
	createObject();
	setMainWidget();
	createMenuBar();
	connectMine();
	restart();
}

MineMainWindow::~MineMainWindow() {
	delete qmine;
	delete mineTimer;

	delete mainWidget;
	delete statusLayout;
	delete mainLayout;

	delete mineField;
	delete timeLCD;
	delete label;
	delete remainingMineLCD;

	delete menu;
	delete restartAction;
	delete lowAction;
	delete midAction;
	delete highAction;
	delete quitAction;
}

void MineMainWindow::createObject() {
	qmine = new QMine;
	mineTimer = new MineTimer;
	timeLCD = new QLCDNumber;
	label = new QLabel("AA");
	label->setPixmap( QPixmap(":/images/mark.png") );
	label->setScaledContents( true );
	remainingMineLCD = new QLCDNumber;
	mineField = new MineField(this);

  winDialog = new StatusDialog(QString("Win"));
  winDialog->hide();
  loseDialog = new StatusDialog(QString("Lose"));
  loseDialog->hide();
}

void MineMainWindow::connectMine() {
	connect(qmine, SIGNAL(clicked()),
			mineTimer, SLOT(start()));

	connect(qmine,
          SIGNAL(updateGraph(int** const, const int, const int)),
			    mineField,
          SLOT(updateGraph(int** const, const int, const int)));

	connect(qmine, SIGNAL(win()),
			this, SLOT(doWin()));
	connect(qmine, SIGNAL(lose()),
			this, SLOT(doLose()));

	connect(mineTimer, SIGNAL(changeTime(int)),
			timeLCD, SLOT(display(int)));
	connect(qmine, SIGNAL(remainingMine(int)),
		   remainingMineLCD, SLOT(display(int)));	

	connect(mineField, SIGNAL(explore(int,int)),
			qmine, SLOT(explore(int,int)));
	connect(mineField, SIGNAL(mark(int,int)),
			qmine, SLOT(mark(int,int)) );
}

void MineMainWindow::setMainWidget() {
	statusLayout = new QHBoxLayout;
	statusLayout->addWidget( timeLCD,1 );
	statusLayout->addStretch();
	statusLayout->addWidget( label );
	statusLayout->addStretch();
	statusLayout->addWidget( remainingMineLCD,1 );

	mainLayout = new QVBoxLayout;
	mainLayout->addLayout( statusLayout );
	mainLayout->addWidget( mineField );
	mainLayout->setStretch( 0, 1 );
	mainLayout->setStretch( 1, 9 );

	mainWidget = new QWidget(this);
	mainWidget->setLayout( mainLayout );
	setCentralWidget( mainWidget );
}

void MineMainWindow::createMenuBar() {
	restartAction = new QAction( tr("Restart"), this );
	connect( restartAction, SIGNAL(triggered()),
			this, SLOT(restart()) );
	connect( restartAction, SIGNAL(triggered()),
			this, SLOT(restart()) );

	lowAction = new QAction( tr("Low"), this );
	connect( lowAction, SIGNAL(triggered()),
			this, SLOT(low()) );
	connect( lowAction, SIGNAL(triggered()),
			this, SLOT(restart()) );

	midAction = new QAction( tr("Mid"), this );
	connect( midAction, SIGNAL(triggered()),
			this, SLOT(mid()) );
	connect( midAction, SIGNAL(triggered()),
			this, SLOT(restart()) );

	highAction = new QAction( tr("High"), this );
	connect( highAction, SIGNAL(triggered()),
			this, SLOT(high()) );
	connect( highAction, SIGNAL(triggered()),
			this, SLOT(restart()) );

	quitAction = new QAction( tr("Quit"), this );
	connect( quitAction, SIGNAL(triggered()),
			this, SLOT(close()) );

	menu = menuBar()->addMenu( tr("Menu") );
	menu->addAction( restartAction );
	menu->addAction( lowAction );
	menu->addAction( midAction );
	menu->addAction( highAction );
	menu->addAction( quitAction );
}

void MineMainWindow::restart() {
	mineTimer->restart();
	mineField->restart();
	qmine->restart();
}

void MineMainWindow::doWin() {
	mineTimer->stop();
  winDialog->show();
	//std::cout << "Win!!!" << std::endl;
}

void MineMainWindow::doLose() {
	mineTimer->stop();
  loseDialog->show();
	//std::cout << "Lose!!!" << std::endl;
}

void MineMainWindow::low() {
	qmine->setLevel(LOW);
	restart();
}

void MineMainWindow::mid() {
	qmine->setLevel( MID );
	restart();
}

void MineMainWindow::high() {
	qmine->setLevel( HIGH );
	restart();
}

