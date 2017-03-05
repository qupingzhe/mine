#include "qmine.h"

Mine* QMine::lowMine = new Mine( 10, 10, 10 );
Mine* QMine::midMine = new Mine( 20, 20, 20 );
Mine* QMine::highMine = new Mine( 30, 30, 30 );

QMine::QMine( void )
{
	mine = lowMine;
}

QMine::~QMine( void )
{
	delete mine;
}

void QMine::setLevel( int level )
{
	switch( level ) {
		case LOW: mine = lowMine;
				  break;
		case MID: mine = midMine;
				  break;
		case HIGH: mine = highMine;
				   break;
		default:
				   break;
	}
}

int QMine::getCellType( int x, int y )
{
	return mine->getCellType( x, y );
}

int QMine::getColumn( void )
{
	return mine->getColumn();
}

int QMine::getRow( void )
{
	return mine->getRow();
}

void QMine::explore( int x, int y )
{
	try{
		
		int type = mine->getCellType( x, y );
		if( type == NO_DISCOVERY ) {
			mine->explore( x, y );
		}
		else if( type != TAB ) {
			mine->exploreFast( x, y );
		}
		emit clicked (this);
		emit clicked ();
	}
	catch( ErrorMine errorMine ) {
		emit lose();
	}
}

void QMine::mark( int x, int y )
{
	try {
		mine->mark( x, y );
		if( mine->isWinned() ) {
			emit win();
		}
		emit remainingMine( mine->getRemainingMine() );
		emit clicked( this );
		emit clicked();
	}
	catch( ErrorTab errorTab ) {
		emit tab();
	}
}

void QMine::restart( void )
{
	mine->restart();
	emit remainingMine( mine->getRemainingMine() );
}
