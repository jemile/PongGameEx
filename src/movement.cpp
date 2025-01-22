#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include "movement.h"

MOVEMENT::MOVEMENT(GLFWwindow* window, DRAW* draw, unsigned int windowWidth, unsigned int windowHeight)
{
	m_running = true;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
	this->window = window;
	this->draw = draw;
}

void MOVEMENT::SetNewPosition()
{
	draw->setLeftHeight(draw->getLeftHeight() + position.m_leftPosChange);
	draw->setRightHeight(draw->getRightHeight() + position.m_rightPosChange);
	
	int* ballPos = new int[2];
	ballPos[0] = draw->getBallCoordinates()[0] + ballpos.m_xChange;
	ballPos[1] = draw->getBallCoordinates()[1] + ballpos.m_yChange;
	draw->setBallCoordinates(ballPos);

}

void MOVEMENT::ResetBallPosition()
{
	int coords[] = { (int)windowWidth / 2, (int)windowHeight / 2 };
	draw->setBallCoordinates(coords);
	std::this_thread::sleep_for(_CHRONO milliseconds(100));
}

void MOVEMENT::ResetPaddleMovement()
{
	position.m_leftPosChange = 0;
	position.m_rightPosChange = 0;
}

void MOVEMENT::GetKeyState()
{
	int wPressed = glfwGetKey(window, GLFW_KEY_W);
	int sPressed = glfwGetKey(window, GLFW_KEY_S);

	int upPressed = glfwGetKey(window, GLFW_KEY_UP);
	int downPressed = glfwGetKey(window, GLFW_KEY_DOWN);

	if (wPressed == GLFW_PRESS && sPressed != GLFW_PRESS && draw->getLeftHeight() < (int)windowHeight - 80)
	{
		position.m_leftPosChange = 8;
	}
	if (sPressed == GLFW_PRESS && wPressed != GLFW_PRESS && draw->getLeftHeight() > 10)
	{
		position.m_leftPosChange = -8;
	}
	if (upPressed == GLFW_PRESS && downPressed != GLFW_PRESS && draw->getRightHeight() < (int)windowHeight - 80)
	{
		position.m_rightPosChange = 8;
	}
	if (downPressed == GLFW_PRESS && upPressed != GLFW_PRESS && draw->getRightHeight() > 10)
	{
		position.m_rightPosChange = -8;
	}
}

void MOVEMENT::CaptureBallMovement()
{
	if (draw->getBallCoordinates()[1] < 20)
	{
		ballpos.m_yChange = 5;
	}

	if (draw->getBallCoordinates()[1] > (int)windowHeight - 20)
	{
		ballpos.m_yChange = -5;
	}

	//  bounces off the right paddle
	if (draw->getBallCoordinates()[0] > (int)windowWidth - 45 && draw->getBallCoordinates()[0] < (int)windowWidth - 20 && draw->getBallCoordinates()[1] <= draw->getRightHeight() + draw->getVirtualHeight() && draw->getBallCoordinates()[1] >= draw->getRightHeight())
	{
		ballpos.m_xChange = -5;
	}

	// left wins
	else if (draw->getBallCoordinates()[0] > (int)windowWidth - 5) {
		draw->addWin(DRAW::GAME::LEFTWIN);
		ResetBallPosition();
		ballpos.m_xChange = -5;
	}

	// bounces off the left paddle
	if (draw->getBallCoordinates()[0] < 45 && draw->getBallCoordinates()[0] > 20  &&  draw->getBallCoordinates()[1] <= draw->getLeftHeight() + draw->getVirtualHeight() && draw->getBallCoordinates()[1] >= draw->getLeftHeight())
	{
		ballpos.m_xChange = 5;
	}

	// right wins
	else if (draw->getBallCoordinates()[0] < 5) {
		draw->addWin(DRAW::GAME::RIGHTWIN);
		ResetBallPosition();
		ballpos.m_xChange = 5;
	}

}

void MOVEMENT::StartMovement()
{
	while (m_running)
	{
		GetKeyState();
		CaptureBallMovement();
		SetNewPosition();
		ResetPaddleMovement();

		std::this_thread::sleep_for(_CHRONO milliseconds(2));
	}
}

MOVEMENT::~MOVEMENT()
{
	m_running = false;
}