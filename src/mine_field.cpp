#include "mine_field.h"
#include "mine.h"
#include "qmine.h"

#include <QImage>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

MineField::MineField( QMine* qmine, QWidget* parent ) : QWidget( parent )
{
	this->row = qmine->getRow();
	this->column = qmine->getColumn();

	flag = false;

	cellImage[0] = new QPixmap( ":/images/0.png" );
	cellImage[1] = new QPixmap( ":/images/1.png" );
	cellImage[2] = new QPixmap( ":/images/2.png" );
	cellImage[3] = new QPixmap( ":/images/3.png" );
	cellImage[4] = new QPixmap( ":/images/4.png" );
	cellImage[5] = new QPixmap( ":/images/5.png" );
	cellImage[6] = new QPixmap( ":/images/6.png" );
	cellImage[7] = new QPixmap( ":/images/7.png" );
	cellImage[8] = new QPixmap( ":/images/8.png" );
	cellImage[13] = new QPixmap( ":/images/lost.png" );
	cellImage[18] = new QPixmap( ":/images/mark.png" );
	cellImage[21] = new QPixmap( ":/images/no.png" );

	createCells();
}

MineField::~MineField( void )
{
	deleteCells();
}

void MineField::deleteCells( void )
{
	for( int i=0; i<row; i++ ) {
		for( int j=0; j<column; j++ ) {
			delete cells[i][j];
		}
		delete cells[i];
		delete hlayout[i];
	}
	delete cells;
	delete hlayout;
	delete mainLayout;
}

void MineField::createCells( void )
{
	mainLayout = new QVBoxLayout;
	hlayout = new QHBoxLayout*[row];

	cells = new QLabel** [row];
	for( int i=0; i<row; i++ ) {
		cells[i] = new QLabel* [column];
		hlayout[i] = new QHBoxLayout;
		for( int j=0; j<column; j++ ) {
			cells[i][j] = new QLabel;
			cells[i][j]->setScaledContents( true );

			hlayout[i]->addWidget( cells[i][j] );
		}
		mainLayout->addLayout( hlayout[i] );
	}
	this->setLayout( mainLayout );

}

void MineField::mousePressEvent( QMouseEvent* event )
{
	if( !flag ) {
		flag = true;
		start();
	}
	int sizeX = width() / column;
	int sizeY = height() / row;
	if( event->button() == Qt::LeftButton ) {
		emit explore( event->y()/sizeY, event->x()/sizeX );
	}
	else if( event->button() == Qt::RightButton ) {
		emit mark( event->y()/sizeY, event->x()/sizeX );

	}
	else {
		//error
	}
}

void MineField::updateGraph( QMine* qmine )
{
	for( int i=0; i<qmine->getRow(); i++ ) {
		for( int j=0; j<qmine->getColumn(); j++ ) {
			cells[i][j]->setPixmap( *cellImage[qmine->getCellType(i,j)] );
			cells[i][j]->show();
		}
	}
}

void MineField::restart( QMine* qmine )
{
	flag = false;
	deleteCells();
	row = qmine->getRow();
	column = qmine->getColumn();
	createCells();

	updateGraph( qmine );
}
