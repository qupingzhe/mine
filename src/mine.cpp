#include <stdlib.h>
#include <string.h>
#include <queue>
#include <time.h>

#include "mine.h"

Mine::Mine(int mineNumber, int row, int column) {
	row_ = row;
	column_ = column;
	mineNumber_ = mineNumber;
	remainingMine_ = mineNumber;
  status_ = 0;

	graph_ = new int*[row_];
	visibleGraph_ = new int*[row_];
	for (int i = 0; i < row_; ++i) {
		graph_[i] = new int[column_];
		visibleGraph_[i] = new int[column_];
	}
  initialize();
}

Mine::~Mine() {
	for (int i = 0; i < row_; ++i) {
		//delete[] graph_[i];
		//delete[] visibleGraph_[i];
	}
	//delete[] graph_;
	//delete[] visibleGraph_;
}

void Mine::initialize() {
  remainingMine_ = mineNumber_;
	for (int i = 0; i < row_; ++i) {
		for (int j = 0; j < column_; ++j) {
			graph_[i][j] = 0;
			visibleGraph_[i][j] = NO_DISCOVERY;
		}
	}
	buryMine();
	updateGraph();
}


void Mine::explore(int x, int y) {
  if (status_) {
    return ;
  }
	if (!isInScope(x, row_) || !isInScope(y, column_)) {
		//throw ErrorScope("Error_Scope");
    return ;
	} else if (graph_[x][y] == MINE) {
    visibleGraph_[x][y] = MINE;
		//throw ErrorMine("ERROR_MINE");
    return ;
	}

	if (visibleGraph_[x][y] == NO_DISCOVERY){
		visibleGraph_[x][y] = graph_[x][y];
		bfs(x, y);
	}
}

void Mine::exploreFast(int x, int y) {
  if (status_) {
    return;
  }
	if (!isInScope(x, row_) || !isInScope(y, column_) ) {
		//throw ErrorScope("Error_Scope");
    return ;
	}

	if (visibleGraph_[x][y] == getNeighborTabNumber(x, y)) {
		for (int i = 0; i < 8; ++i) {
			int newX = x + dx[i];
			int newY = y + dy[i];
			if (isInScope(newX, row_) && isInScope(newY, column_) &&
					visibleGraph_[newX][newY] != TAB) {
				explore(newX, newY);
			}
		}
	}
}

void Mine::mark(int x, int y) {
  if (status_) {
    return ;
  }
	if (!isInScope(x, row_) || !isInScope(y, column_)) {
		//throw ErrorScope("Error_Scope");
    return ;
	} else if (remainingMine_ == 0) {
		//throw ErrorTab("ERROR_TAB");
    return ;
	}
	if (visibleGraph_[x][y] == NO_DISCOVERY) {
		visibleGraph_[x][y] = TAB;
		--remainingMine_;
	} else if (visibleGraph_[x][y] == TAB) {
		visibleGraph_[x][y] = NO_DISCOVERY;
		++remainingMine_;
	}
}

int Mine::getRemainingMine() {
	return remainingMine_;
}

int Mine::getStatus() {
  status_ = 0;
  checkGame();
  return status_;
}

void Mine::restart() {
  initialize();
}

void Mine::win() {
}

void Mine::lose() {
}

void Mine::copyGraph(int** newGraph, int* column, int* row) {
  *column = column_;
  *row = row_;
  for (int i = 0; i < row_; ++i) {
    for (int j = 0; j < column_; ++j) {
      newGraph[i][j] = visibleGraph_[i][j];
    }
  }
}


void Mine::buryMine() {
  for (int i = 0; i < mineNumber_; ++i) {
    graph_[i / row_][i % column_] = MINE;
  }
  /*
	unsigned int t = time(NULL);
	srand(t);
	for (int i = 0; i < mineNumber_; ++i) {
		unsigned int newP = rand() % (row_ * column_);
		int nextX = newP / row_;
		int nextY = newP % row_;
		if (graph_[nextX][nextY] != MINE) {
			graph_[nextX][nextY] = MINE;
		} else {
			srand(t + 2U * rand());
      --i;
		}
	}
  */
}

void Mine::updateGraph() {
	for (int i = 0; i < row_; ++i) {
		for (int j = 0; j < column_; ++j) {
			if (graph_[i][j] != MINE) {
				graph_[i][j] = getNeighborMineNumber(i, j);
			}
		}
	}
}

int Mine::getNeighborMineNumber(int x, int y) {
	int count = 0;
	for(int i=0;i<8;i++) {	
		int newX = x + dx[i];
		int newY = y + dy[i];
		if (isInScope(newX,row_) && isInScope(newY,column_) &&
        graph_[newX][newY] == MINE) {
			++count;
		}
	}
	return count;
}

int Mine::getNeighborTabNumber(int x, int y) {
	int count = 0;
	for(int i=0;i<8;i++) {	
		int newX = x + dx[i];
		int newY = y + dy[i];
		if (isInScope(newX,row_) && isInScope(newY,column_) &&
        visibleGraph_[newX][newY] == TAB) {
			++count;
		}
	}
	return count;
}

void Mine::bfs(int startX, int startY) {
	if (graph_[startX][startY] != BLANK) {
		return ;
	}
	std::queue<int> qu;
	visibleGraph_[startX][startY] = graph_[startX][startY];
	qu.push(startX*row_ + startY);
	while (!qu.empty()) {
		int x = qu.front() / row_;
		int y = qu.front() % row_;
		for (int i = 0; i < 8; ++i) {	
			int newX = x + dx[i];
			int newY = y + dy[i];
			if (isInScope(newX,row_) && isInScope(newY,column_) &&
					visibleGraph_[newX][newY] == NO_DISCOVERY) {
				visibleGraph_[newX][newY] = graph_[newX][newY];
				if (graph_[newX][newY] == BLANK) {
					qu.push(newX*row_ + newY);
				}
			}
		}
		qu.pop();
	}
}

void Mine::checkGame() {
  status_ = 0;
  int tmp = 0;
  for (int i = 0; i < row_; ++i) {
    for (int j = 0; j < column_; ++j) {
      if (graph_[i][j] == MINE && visibleGraph_[i][j] == MINE) {
        status_ = -1;
        return ;
      } else if (graph_[i][j] == MINE && visibleGraph_[i][j] == TAB) {
        ++tmp;
      }
    }
  }
  if (tmp == mineNumber_) {
    status_ = 1;
  }
}


/*
bool Mine::isWinned() {
	for (int i = 0; i < row_; ++i) {
		for (int j = 0; j < column_; ++j) {
			if (graph_[i][j] == MINE && visibleGraph_[i][j] == NO_DISCOVERY) {
				return false;
			}
		}
	}
	return true;
}
int Mine::getCellType( int x, int y )
{
	if( isInScope(x,row_) && isInScope(y,column_) )
		return visibleGraph_[x][y];
	else return ERROR;
}

int Mine::getColumn( void )
{
	return column_;
}

int Mine::getRow( void )
{
	return row_;
}
*/

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
