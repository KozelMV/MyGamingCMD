// 01.05.2017 kozelmv@gmail.com

#include "stdafx.h"
#include "msoftcon.h"
#include <iostream>
#define _TEST system("pause"); 




enum { hor= -2, ver = -37, tone = 7};
//std::cout << static_cast<char>(-2); //������ ������� ��������   ASCII-866
//std::cout << static_cast<char>(-37); //������ ������� ���������	ASCII-866
//std::cout << static_cast<char>(7) << std::endl; //����			ASCII-866


class Game {
	enum { width = 72, height = 27 }; // ������ ���� ����
	char sizeGame[width][height] = { ' ' }; //������ ���� ����
public:
	Game()  { 
		system("mode con:cols=74lines=27"); //������������� ������ �������
		init_graphics(); // ������������� ������� ������
	}
	void sGame( char strArr[70][20], int startcX, int cY, int mcY, int sizStr) { // ��������� cmd ���������� �� �������
		for(int i=0; i < sizStr; i++, startcX++)
			*(*(sizeGame + startcX)+cY) = *(*(strArr + i) +mcY);
	}
	void dGame() { // ������� ��� ������� � �������
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++)
				std::cout << *(*(sizeGame + w) + h);
			std::cout << std::endl;
		}
	}
	
};

class GamingField: public Game {
private:
	enum { width = 70, height = 20 }; // ������ �������� ����
	char sizeField[width][height] = {' '};	// ������ ����
	//char filling[2] = { hor , ver };// ������ � ��������� ��� ����������
public:
	GamingField() {
		// ���������� �������---------------------------------------------------------------
			for (int i = 0; i < width; i++) // ���������� ������� ����� ����
				*(*(sizeField + i) + 0) = ver;
			for (int i = 0; i < height; i++)// ���������� ������� ������ ������� ����
				*(*(sizeField + width-1) + i) = ver;
			for (int i = 0; i < width; i++) // ���������� ������� ��� ����
				*(*(sizeField + i) + height-1) = ver;
			for (int i = height; i > 0; i--)// ���������� ������� ����� ������� ����
				*(*(sizeField + 0) + i) = ver;
			for (int i = 1; i < height-1; i++)// ��������� ������ ����������� ������ 
				*(*(sizeField + ((width-2) / 2)) + i) = ':';
		// ----------------------------------------------------------------------------------
		// ������������ ������ � �������-----------------------------------------------------
		//		for (int h = 0; h < height; h++) {
		//			for (int w = 0; w < width; w++)
		//				std::cout << *(*(sizeField + w) + h);
		//			std::cout << std::endl;
		//		}	
		// ----------------------------------------------------------------------------------
			strGame();
	}
	// �������� ������ ���� � ������ ����------------------------------------------------
	void strGame() {
		for (int i = 7, c = 0; c < height; i++, c++)
			sGame(sizeField, 2, i, c, width);
		dGame(); // ������������ ����
	}
	// ----------------------------------------------------------------------------------
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class User {
private:
	char chFill = ver;
	int length = 3;
	int cX;
	int cY_Max = 10;
	int cY_Min = 25;
	int location = (((cY_Max + cY_Min) / 2)-2);
public:
	//�����������
	User(int cX); 
	//�������� �����
	int goUp();
	//�������� ����
	int goDown();
};
//+++++++++++++++++++++++++++++++++
User::User(int ucX) {
	cX = ucX;
	for (int i = 0; i < length; i++) {
		set_cursor_pos(ucX, ( location + i)); //respawn
		std::cout << chFill;	
	}
	location++;
	set_cursor_pos(1,27);
}
int User::goUp() {
	if (location < cY_Max)
		return 0;
	else {
		for (int i = 0; i < length; i++) {
			set_cursor_pos(cX, (location + 1));
			std::cout << '.';
			set_cursor_pos(1, 27);
			set_cursor_pos(cX, (location - 2));
			std::cout << chFill;
			set_cursor_pos(1, 27);
		}
		location--;
		return 1;
	}
}
int User::goDown() {
	if ((location + (length - 1)) > cY_Min)
		return 0;
	else {
		for (int i = 0; i < length; i++) {
			set_cursor_pos(cX, (location - 1));
			std::cout << '.';
			set_cursor_pos(1, 27);
			set_cursor_pos(cX, (location + 2));
			std::cout << chFill;
			set_cursor_pos(1, 27);
		}
		location++;
		return 1;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Ball {
private:
	char b_chFill = hor;
	char chClear = ' ';
	int speed = 15;													  // Wait millsec
	enum Angle { angleX = 3, angleY = 1 };							  // The flying angle the ball 
	enum Border { cY_Min = 7, cY_Max = 26, cX_Min = 5, cX_Max = 70 }; // The border of the ball
	short cY, cX;													  // The ball coordinate
public:
	Ball();
	Ball(int x, int y);
	void show();
	void clear();
	
	void going();
	void goingTop();
	void goingTopLef();
	void goingDown();
	void goingDownLef();
	
	int top_or_down();			// Test on walls. Top and down
	bool switchTorD = 1;		// The ball going to top or down
	bool right_or_leaft = 1;	// The ball going to right(true) or left(false)		

	bool goalRight();
	bool goalLeft();
};
//+++++++++++++++++++++++++++++++++
Ball::Ball() {
	cX = cX_Min + 2;
	cY = cY_Min + 9;
	show();
}
Ball::Ball(int x, int y) {
	cX = x;
	cY = y;
	show();
}
void Ball::show() {
	set_cursor_pos(cX, cY);
	std::cout << b_chFill;
	set_cursor_pos(1, 27);
}
void Ball::clear() {
	wait(speed);
	set_cursor_pos(cX, cY);
	std::cout << chClear;
	set_cursor_pos(1, 27);
}

int Ball::top_or_down() {
	if(switchTorD) {
		if ((cY - 1) != cY_Min) {
			return 1;
		}
		else {
			switchTorD = !switchTorD;
			Beep(800, 4 / 1);
			return 0;
		}
	}
	else if (!switchTorD) {
		if ((cY + 1) != cY_Max) {
			return 2;
		}
		else {
			switchTorD = !switchTorD;
			Beep(800, 4 / 1);
			return 3;
		}
	}
	else {
		std::cout << "Warning 5";
		return 5;
	}
}

bool Ball::goalRight() {
	if (cX + 1 >= cX_Max)
		return 1;
	else
		return 0;
}
bool Ball::goalLeft() {
	if (cX - 1 <= cX_Min)
		return 1;
	else
		return 0;
}

void Ball::going() {
	if (switchTorD) { //�����
		if (right_or_leaft) { //�������� � �����
			if (top_or_down() == 1) {
				if (!goalRight()) {
					goingTop();
				}
				else {	// ��� � ������ ������ � �����
					right_or_leaft = false; // ������ ����������� ��������
					Beep(800, 4 / 1);
				}
			}
		}
		else {// �������� � ����
			if (top_or_down() == 1) {
				if (!goalLeft()) { // �������� ����� �����
					goingTopLef();
				}
				else {	// ��� � ����� ������ � �����
					right_or_leaft = true; // ������ ����������� ��������
					Beep(800, 4 / 1);
				}
			}
		}
	}
	else if (!switchTorD) { // �������� ����
		if (right_or_leaft) {
			if (top_or_down() == 2) {
				if (!goalRight()) {
					goingDown();
				}
				else { // ��� � ������ ������ �����
					right_or_leaft = false; // ������ ����������� ��������
					Beep(800, 4 / 1);
				}
			}
		}
		else { //�������� � ����
			if (top_or_down() == 2) {
				if (!goalLeft()) {
					goingDownLef();
				}
				else {	// ��� � ����� ������ �����
					right_or_leaft = true; // ������ ����������� ��������
					Beep(800, 4 / 1);
				}
			}
		}
	}

}
void Ball::goingTop() {
	clear();
	cX += angleX; cY-= angleY;
	show();
}
void Ball::goingDown() {
	clear();
	cX += angleX; cY+= angleY;
	show();
}
void Ball::goingTopLef() {
	clear();
	cX -= angleX; cY-= angleY;
	show();
}
void Ball::goingDownLef() {
	clear();
	cX -= angleX; cY+=angleY;
	show();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{	
	SetConsoleOutputCP(866); // ��������� ������� �������� win-cp 866 � ����� ������
	SetConsoleOutputCP(866); // ��������� ������� �������� win-cp 866 � ����� ������

	GamingField Game;
	User player1(5), player2(70);
	Ball b,b1(45,25),b2(20,20),b3(15,15);
	char gameControl = ' ';
	bool user1 = true;
	bool user2 = true;

	do
	{
		b.going();
		b1.going();
		b2.going();
		b3.going();
		//gameControl = _getch();
		//
		//if (gameControl == 'w') {
		//	player1.goUp();
		////	gameControl = _getch();
		//	if (gameControl == 'o')
		//		player2.goUp();
		//}
		//	if (gameControl == 's')
		//		player1.goDown();
		//
		////gameControl = _getch();
		//	if (gameControl == 'o')
		//		player2.goUp();
		//	if (gameControl == 'l')
		//		player2.goDown();
		


	} while (gameControl != 'q');

	Beep(294, 1000 / 8); //���� <windows.h>
	
	set_cursor_pos(1,27);

	system("pause");
    return 0;
}

