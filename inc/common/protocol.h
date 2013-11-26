#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>

const std::string port = "6060";


const unsigned char BEGIN_MESSAGE = 0xAB;

const unsigned char REQUEST_START = 0x10;
const unsigned char REQUEST_END = 0x11;
const unsigned char REQUEST_GAME_STATUS = 0x12;

const unsigned char REQUEST_CURSOR_POSITION = 0x40;

const unsigned char REQUEST_STATE = 0x50;

const unsigned char REQUEST_RECEIVE_PLAYER0 = 0x80;
const unsigned char REQUEST_RECEIVE_PLAYER1 = 0x81;
const unsigned char REQUEST_RECEIVE_BALL = 0x82;
const unsigned char REQUEST_RECEIVE_CURSOR_POSITION = 0x84;


#endif // PROTOCOL_H
