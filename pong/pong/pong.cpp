// 01.05.2017 kozelmv@gmail.com

#include "stdafx.h"
#include "msoftcon.h"
#include <iostream>
#define _TEST system("pause"); 




enum { hor= -2, ver = -37, tone = 7};
//std::cout << static_cast<char>(-2); //символ заливки горизонт   ASCII-866
//std::cout << static_cast<char>(-37); //символ заливки вертикаль	ASCII-866
//std::cout << static_cast<char>(7) << std::endl; //звук			ASCII-866


class Game {
	enum { width = 72, height = 27 }; // Размер окна игры
	char sizeGame[width][height] = { ' ' }; //Массив окна игры
public:
	Game()  { 
		system("mode con:cols=74lines=27"); //Устанавливаем размер консоли
		init_graphics(); // Инициализация графики Лафоре
	}
	void sGame( char strArr[70][20], int startcX, int cY, int mcY, int sizStr) { // Наполняем cmd элементами по строчно
		for(int i=0; i < sizStr; i++, startcX++)
			*(*(sizeGame + startcX)+cY) = *(*(strArr + i) +mcY);
	}
	void dGame() { // Выводим все объекты в консоль
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++)
				std::cout << *(*(sizeGame + w) + h);
			std::cout << std::endl;
		}
	}
	
};

class GamingField: public Game {
private:
	enum { width = 70, height = 20 }; // Размер игравого поля
	char sizeField[width][height] = {' '};	// Размер поля
	//char filling[2] = { hor , ver };// Массив с символами для заполнения
public:
	GamingField() {
		// Наполнение массива---------------------------------------------------------------
			for (int i = 0; i < width; i++) // Наполнение массива вверх поля
				*(*(sizeField + i) + 0) = ver;
			for (int i = 0; i < height; i++)// Наполнение массива правая старана поля
				*(*(sizeField + width-1) + i) = ver;
			for (int i = 0; i < width; i++) // Наполнение массива низ поля
				*(*(sizeField + i) + height-1) = ver;
			for (int i = height; i > 0; i--)// Наполнение массива левая старана поля
				*(*(sizeField + 0) + i) = ver;
			for (int i = 1; i < height-1; i++)// Наполняет массив разделяющей линией 
				*(*(sizeField + ((width-2) / 2)) + i) = ':';
		// ----------------------------------------------------------------------------------
		// Отрисовываем массив в кансоль-----------------------------------------------------
		//		for (int h = 0; h < height; h++) {
		//			for (int w = 0; w < width; w++)
		//				std::cout << *(*(sizeField + w) + h);
		//			std::cout << std::endl;
		//		}	
		// ----------------------------------------------------------------------------------
			strGame();
	}
	// Передаем массив поля в массив игры------------------------------------------------
	void strGame() {
		for (int i = 7, c = 0; c < height; i++, c++)
			sGame(sizeField, 2, i, c, width);
		dGame(); // Отрисовываем поле
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
	//Конструктор
	User(int cX); 
	//Движение вверх
	int goUp();
	//Движение вниз
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
	if (switchTorD) { //Вверх
		if (right_or_leaft) { //Движение в право
			if (top_or_down() == 1) {
				if (!goalRight()) {
					goingTop();
				}
				else {	// Гол в правые варота с верху
					right_or_leaft = false; // Меняем направление движения
					Beep(800, 4 / 1);
				}
			}
		}
		else {// Движение в лево
			if (top_or_down() == 1) {
				if (!goalLeft()) { // Движение назад вверх
					goingTopLef();
				}
				else {	// Гол в левые варота с верху
					right_or_leaft = true; // Меняем направление движения
					Beep(800, 4 / 1);
				}
			}
		}
	}
	else if (!switchTorD) { // Движение вниз
		if (right_or_leaft) {
			if (top_or_down() == 2) {
				if (!goalRight()) {
					goingDown();
				}
				else { // Гол в правые ворота снизу
					right_or_leaft = false; // Меняем направление движения
					Beep(800, 4 / 1);
				}
			}
		}
		else { //Движение в лево
			if (top_or_down() == 2) {
				if (!goalLeft()) {
					goingDownLef();
				}
				else {	// Гол в левые варота снизу
					right_or_leaft = true; // Меняем направление движения
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
	SetConsoleOutputCP(866); // установка кодовой страницы win-cp 866 в поток вывода
	SetConsoleOutputCP(866); // установка кодовой страницы win-cp 866 в поток вывода

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

	Beep(294, 1000 / 8); //звук <windows.h>
	
	set_cursor_pos(1,27);

	system("pause");
    return 0;
}

