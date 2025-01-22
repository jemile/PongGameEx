#pragma once

#include "draw.h"

typedef struct POSITION
{
	int m_leftPosChange = 0;
	int m_rightPosChange = 0;
} POSITION;

typedef struct BALL_POSITION
{
	int m_xChange = -5;
	int m_yChange = -5;
} BALL_POSITION;

class MOVEMENT
{
private:
	bool m_running = false;
	DRAW* draw;
	POSITION position;
	BALL_POSITION ballpos;
	GLFWwindow* window;

	unsigned int windowWidth;
	unsigned int windowHeight;

public:
	MOVEMENT(GLFWwindow* window, DRAW* draw, unsigned int windowWidth, unsigned int windowHeight);
	void StartMovement();
	void GetKeyState();
	void CaptureBallMovement();
	void SetNewPosition();
	void ResetPaddleMovement();
	void ResetBallPosition();
	virtual ~MOVEMENT();
};