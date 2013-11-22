#ifndef PROTOCOL_H
#define PROTOCOL_H

const unsigned char START = 0x00;
const unsigned char END = 0x01;

const unsigned char CURSOR_POSITION = 0x10;

const unsigned char STATE = 0x20;

struct CursorPosition
{
	int x, y;
};

struct StateInfo
{
	int ballX, ballY;
	int curPlayerX, curPlayerY;
	int opPlayerX, opPlayerY;
};

#endif // PROTOCOL_H