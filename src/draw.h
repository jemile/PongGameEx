#pragma once

class DRAW
{
private:
	float M_PI = 3.141592653589793238462643383279502884197f;

	bool inMenu = true;
	int m_width = 0;
	int m_height = 0;

	int leftWins = 0;
	int rightWins = 0;

	int left_x = 0;
	int right_x = 0;
	int left_y = 0;
	int right_y = 0;

	int ball_x = 0;
	int ball_y = 0;

	unsigned int windowWidth = 0;
	unsigned int windowHeight = 0;

	float toNDC(float value, int max) {
		return 2 * value / max - 1;
	}

public:
	enum GAME {
		LEFTWIN = 1,
		RIGHTWIN = 2
	};

	DRAW(unsigned int windowWidth, unsigned int windowHeight);
	void DrawWinCounter();
	void DrawLine(int verticies[]);
	void DrawCircle(float radius);
	void Update();

	bool getMenuFrame();
	void setMenuFrame(bool change);

	void addWin(GAME type);
	int getVirtualHeight();

	int getLeftHeight();
	void setLeftHeight(int left_y);

	int getRightHeight();
	void setRightHeight(int right_y);

	int* getBallCoordinates();
	void setBallCoordinates(int* coordinates);

	virtual ~DRAW();
};