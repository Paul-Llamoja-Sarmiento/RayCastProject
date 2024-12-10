#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

typedef struct Player
{
	float m_positionX;
	float m_positionY;
	int32_t m_width;
	int32_t m_height;
	float m_angleInRadians;
} Player;

#endif 
