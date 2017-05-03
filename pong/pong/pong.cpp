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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
User::User(int ucX) {
	for (int i = 0; i < length; i++) {
		set_cursor_pos(ucX, ( location + i)); //respawn
		std::cout << chFill;
		cX = ucX;
	}
	set_cursor_pos(1,27);
}
int User::goUp() {
	if (location < cY_Max)
		return 0;
	else {
		for (int i = 0; i < length; i++) {
			set_cursor_pos(cX, (location + (i+1)));
			std::cout << ' ';
			set_cursor_pos(1, 27);
			set_cursor_pos(cX, (location - i));
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
			set_cursor_pos(cX, (location - (i + 1)));
			std::cout << ' ';
			set_cursor_pos(1, 27);
			set_cursor_pos(cX, (location + i));
			std::cout << chFill;
			set_cursor_pos(1, 27);
		}
		location++;
		return 1;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int main()
{	
	SetConsoleOutputCP(866); // установка кодовой страницы win-cp 866 в поток вывода
	SetConsoleOutputCP(866); // установка кодовой страницы win-cp 866 в поток вывода

	GamingField Game;
	User player1(5), player2(70);
	char gameControl;
	do
	{
		gameControl = _getch();

		switch (gameControl) {
		case 'w': player1.goUp(); break;
		case 's': player1.goDown(); break;
		default: break;
		}
		gameControl = _getch();
		
		switch (gameControl) {
		case 'o': player2.goUp(); break;
		case 'l': player2.goDown(); break;
		default: break;
		}
	} while (gameControl != 'q');

	Beep(294, 1000 / 8); //звук <windows.h>
	
	set_cursor_pos(1,27);

	system("pause");
    return 0;
}

