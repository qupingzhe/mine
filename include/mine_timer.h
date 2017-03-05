#ifndef MINE_TIMER_H
#define MINE_TIMER_H

#include <QObject>

class QTimer;

class MineTimer : public QObject
{
	Q_OBJECT
public:
	MineTimer( void );
	~MineTimer( void );
signals:
	void changeTime( int time );
public slots:
	void start( void );
	void stop( void );
	void restart( void );
private slots:
	void updateTime( void );
private:
	int time;
	bool startedFlag;
	QTimer* timer;
};

#endif
