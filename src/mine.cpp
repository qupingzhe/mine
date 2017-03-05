#include <stdlib.h>
#include <string.h>
#include <queue>
#include <time.h>

#include "mine.h"

Mine::Mine( int mineNumber, int row, int column )
{
	this->row = row;
	this->column = column;

	this->mineNumber = mineNumber;
	this->remainingMine = mineNumber;

	graph = new int*[row];
	visibleGraph = new int*[row];
	for( int i=0; i<row; i++ ) {
		graph[i] = new int[column];
		visibleGraph[i] = new int[column];
	}
	for( int i=0; i<row; i++ ) {
		for( int j=0; j<column; j++ ) {
			graph[i][j] = 0;
			visibleGraph[i][j] = NO_DISCOVERY;
		}
	}

	buryMine();
	updateGraph();
}

Mine::~Mine( void )
{
	for( int i=0; i<row; i++ ) {
		delete graph[i];
		delete visibleGraph[i];
	}
	delete graph;
	delete visibleGraph;
}

void Mine::buryMine( void )
{
	unsigned int t = time(NULL);
	srand( t );
	for( int i=0; i<mineNumber; i++ ) {
		unsigned int newP = rand()%(row*column);
		int nextX = newP/row;
		int nextY = newP%row;
		if( graph[nextX][nextY] != MINE ) {
			graph[nextX][nextY] = MINE;
		}
		else {
			srand( t+2U*rand() );
			i--;
		}
	}
}

void Mine::updateGraph( void )
{
	for( int i=0; i<row; i++ ) {
		for( int j=0; j<column; j++ ) {
			if( graph[i][j] != MINE ) {
				graph[i][j] = getNeighborMineNumber( i, j );
			}
		}
	}
}



void Mine::explore( int x, int y )
{
	if( !isInScope( x, row) || !isInScope( y, column ) ) {
		throw ErrorScope( "Error_Scope" );
	}
	else if( graph[x][y] == MINE ) {
		throw ErrorMine( "ERROR_MINE" );
	}

	if( visibleGraph[x][y] == NO_DISCOVERY ){
		visibleGraph[x][y] = graph[x][y];
		bfs( x, y );
	}
}

void Mine::exploreFast( int x, int y )
{
	if( !isInScope( x, row) || !isInScope( y, column ) ) {
		throw ErrorScope( "Error_Scope" );
	}

	if( visibleGraph[x][y] == getNeighborTabNumber( x, y ) ) {
		for( int i=0; i<8; i++ ) {
			int newX = x + dx[i];
			int newY = y + dy[i];
			if( isInScope( newX, row) && isInScope( newY, column ) &&
					visibleGraph[newX][newY] != TAB ) {
				explore( newX, newY );
			}
		}
	}
}

void Mine::mark( int x, int y )
{
	if( !isInScope( x, row) || !isInScope( y, column ) ) {
		throw ErrorScope( "Error_Scope" );
	}
	else if( remainingMine == 0 ) {
		throw ErrorTab( "ERROR_TAB" );
	}
	if( visibleGraph[x][y] == NO_DISCOVERY ) {
		visibleGraph[x][y] = TAB;
		remainingMine--;
	}
	else if( visibleGraph[x][y] == TAB ) {
		visibleGraph[x][y] = NO_DISCOVERY;
		remainingMine++;
	}
}

bool Mine::isWinned( void )
{
	for( int i=0; i<row; i++ ) {
		for( int j=0; j<column; j++ ) {
			if( graph[i][j] == MINE && visibleGraph[i][j] == NO_DISCOVERY ) {
				return false;
			}
		}
	}
	return true;
}

void Mine::restart( void )
{
	for( int i=0; i<row; i++ ) {
		for( int j=0; j<column; j++ ) {
			visibleGraph[i][j] = NO_DISCOVERY;
		}
	}
	remainingMine = mineNumber;
}



int Mine::getCellType( int x, int y )
{
	if( isInScope(x,row) && isInScope(y,column) )
		return visibleGraph[x][y];
	else return ERROR;
}

int Mine::getColumn( void )
{
	return column;
}

int Mine::getRow( void )
{
	return row;
}

int Mine::getRemainingMine( void )
{
	return remainingMine;
}



int Mine::getNeighborMineNumber( int x, int y )
{
	int count = 0;
	for(int i=0;i<8;i++) {	
		int newX = x + dx[i];
		int newY = y + dy[i];
		if( isInScope(newX,row) && isInScope(newY,column) && graph[newX][newY] == MINE ) {
			count++;
		}
	}
	return count;
}

int Mine::getNeighborTabNumber( int x, int y )
{
	int count = 0;
	for(int i=0;i<8;i++) {	
		int newX = x + dx[i];
		int newY = y + dy[i];
		if( isInScope(newX,row) && isInScope(newY,column) && visibleGraph[newX][newY] == TAB ) {
			count++;
		}
	}
	return count;
}

void Mine::bfs( int startX, int startY )
{
	if( graph[startX][startY] != BLANK ) {
		return ;
	}
	std::queue<int> qu;
	visibleGraph[startX][startY] = graph[startX][startY];
	qu.push( startX*row + startY );
	while( !qu.empty() ) {
		int x = qu.front()/row;
		int y = qu.front()%row;
		for(int i=0;i<8;i++ ) {	
			int newX = x + dx[i];
			int newY = y + dy[i];
			if( isInScope(newX,row) && isInScope(newY,column) &&
					visibleGraph[newX][newY] == NO_DISCOVERY ) {
				visibleGraph[newX][newY] = graph[newX][newY];
				if( graph[newX][newY] == BLANK ) {
					qu.push( newX*row + newY );
				}
			}
		}
		qu.pop();
	}
}


/*
void showMine( Mine &mine )
{
	int width = mine.getWidth();
	int length = mine.getLength();
	//system("cls");
	printf(" #| ");
	for( int i=0; i<width; i++ ) {
		printf("%d ", i );
	}
	printf("\n");

	printf("   ");
	for( int i=0; i<width; i++ ) {
		printf("__");
	}
	printf("_\n");

	for( int i=0; i<length; i++ ) {
		printf("%d | ", i );
		for( int j=0; j<width; j++ ) {
			if( mine.getCellType(i,j) == NO_DISCOVERY ) {
				printf(".");
			}
			else if( mine.getCellType(i,j) == TAB ) {
				printf( "#" );
			}
			else if( mine.getCellType(i,j) == BLANK ) {
				printf( " " );
			}
			else {
				printf( "%d", mine.getCellType(i,j) );
			}
			printf(" ");
		}
		printf("|\n" );
	}
	printf("   ");
	for( int i=0; i<width; i++ ) {
		printf("--");
	}
	printf("-\n");

	if( mine.isWinned() ) {
		printf( "Win!!!!\n" );
		exit( 0 );
	}
}


int main()
{
	char cmd[20];
	Mine mine;
	int x,y;
	showMine( mine );
	while( scanf("%s%d%d", cmd, &x, &y ) != EOF ) {
		if( !strcmp( cmd, "z" ) ) {
			mine.explore( x, y );
		}
		else if( !strcmp( cmd, "y" ) ) {
			mine.mark( x, y );
		}
		showMine( mine );
	}
	return 0;
}
*/
