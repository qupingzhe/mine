#include "mine_timer.h"

#include <QTimer>

MineTimer::MineTimer( void )
{
	time = 0;
	startedFlag = false;
	timer = new QTimer;
	connect( timer, SIGNAL(timeout()),
			this, SLOT(updateTime()) );
}

MineTimer::~MineTimer( void )
{
	delete timer;
}

void MineTimer::start( void )
{
	if( !startedFlag ) {
		timer->start( 1000 );
		startedFlag = true;
	}
}

void MineTimer::updateTime( void )
{
	emit changeTime( ++time );
	timer->start( 1000 );
}

void MineTimer::restart( void )
{
	time = 0;
	startedFlag = false;
	timer->stop();
	emit changeTime( time );
}

void MineTimer::stop( void )
{
	timer->stop();
}
