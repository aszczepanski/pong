#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <common/Mutex.h>
#include <common/Ball.h>
#include <common/Player.h>
#include <common/CursorPosition.h>

namespace common
{

class SharedMemory
{
public:
	SharedMemory();

	void getBall(Ball&) const;
	void setBall(const Ball&);

	void getPlayer(Player&, int nr) const;
	void setPlayer(const Player&, int nr);

	void getPlayerCursorPosition(CursorPosition&, int nr) const;
	void setPlayerCursorPosition(const CursorPosition&, int nr);

	void getPlayerCameraPosition(int&, int nr) const;
	void setPlayerCameraPosition(const int&, int nr);

	void getCurrentState(Ball&, Player&, Player&) const;
	void setCurrentState(const Ball&, const Player&, const Player&);

	void getStarted(bool&) const;
	void setStarted(bool);

	void getEnded(bool&) const;
	void setEnded(bool);

private:
	Ball ball;
	Player player[2];
	CursorPosition cursorPosition[2];
	int cameraPosition[2];

	bool started, ended;

	mutable Mutex mutex;
};

}

#endif // SHARED_MEMORY_H
