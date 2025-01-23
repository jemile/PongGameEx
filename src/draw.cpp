#include "glad.h"
#include <GLFW/glfw3.h>
#include "ImGui/imgui.h"
#include <iostream>
#include <cmath>
#include <string>

#include "draw.h"

// Constructor will initialize all variables
DRAW::DRAW(unsigned int windowWidth, unsigned int windowHeight)
{
	m_height = 70;
	
	left_x = 30;
	left_y = 280;
	right_x = 570;
	right_y = 280;

	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	ball_x = windowWidth / 2;
	ball_y = windowHeight / 2;
}

void DRAW::addWin(GAME type)
{
	if (type == LEFTWIN)
		leftWins++;
	if (type == RIGHTWIN)
		rightWins++;
}

void DRAW::DrawWinCounter()
{
	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	std::string text = std::to_string(leftWins) + " | " + std::to_string(rightWins);

	drawList->AddText(ImVec2(windowWidth / 2 - (1 + text.length() / 2), 8.0f), ImColor(255, 255, 255, 255), text.c_str());
}

void DRAW::DrawCircle(float radius)
{
	int numSegments = 100;

	glBegin(GL_POLYGON);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < numSegments; i++)
	{
		float theta = (2.0f * M_PI * i) / numSegments;
		float dx = radius * cosf(theta);
		float dy = radius * sinf(theta);
		glVertex2f(ball_x + dx, ball_y + dy);
	}
	glEnd();
	
}

void DRAW::DrawLine(int verticies[])
{
	glLineWidth(5);
	
	glBegin(GL_LINES);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Set color to white
	glVertex2f(verticies[0], verticies[1]);     // Starting point
	glVertex2f(verticies[2], verticies[3]);     // Ending point
	glEnd();
}

void DRAW::Update()
{
	// line dimensions
	int firstLine[] = {
		left_x, left_y,
		left_x, left_y + m_height
	};

	int secondLine[] = {
		right_x, right_y,
		right_x, right_y + m_height
	};

	float centerX = toNDC(ball_x, windowWidth);
	float centerY = toNDC(ball_y, windowHeight);


	// draw player paddles
	DrawLine(firstLine);
	DrawLine(secondLine);
	DrawCircle(7.f);
	DrawWinCounter();
}

bool DRAW::getMenuFrame()
{
	return inMenu;
}

int DRAW::getLeftHeight()
{
	return left_y;
}

int DRAW::getRightHeight()
{
	return right_y;
}

int DRAW::getVirtualHeight()
{
	return m_height;
}

void DRAW::setMenuFrame(bool change)
{
	this->inMenu = change;
}

void DRAW::setLeftHeight(int left_y)
{
	this->left_y = left_y;
}

void DRAW::setRightHeight(int right_y)
{
	this->right_y = right_y;
}

int* DRAW::getBallCoordinates()
{
	int* coordinates = new int[2];
	coordinates[0] = ball_x;
	coordinates[1] = ball_y;

	return coordinates;
}

void DRAW::setBallCoordinates(int* coordinates)
{
	ball_x = coordinates[0];
	ball_y = coordinates[1];
}

DRAW::~DRAW()
{

}
