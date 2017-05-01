//msoftcon.h
//Объявления функций консольной графики от Lafore
//используются консольные функции Windows 

#ifndef _INC_WCONSOLE    //Деректива проверяет включение файла аналогично оператору if(!define)
#define _INC_WCONSOLE    //Имя _INC_WCONSOLE выбрано произвольно 
						 //Используются чтобы исключить повторное включение содержимого заголовочных файлов т.к. 
						 //include втупую подставляет всё содержимое по месту объявления. 
#include <windows.h>     //для консольных функций Windows Sleep()
#include <conio.h>       //для kbhit(), getche()
#include <math.h>        //для sin, cos fabs()

enum fstyle { SOLID_FILL, X_FILL, O_FILL, //Список возможных заполнений символами, заливок
	LIGHT_FILL, MEDIUM_FILL, DARK_FILL }; 

enum color { //Список цветавой палитры
   cBLACK=0,     cDARK_BLUE=1,  cDARK_GREEN=2, DARK_CYAN=3, 
   cDARK_RED=4,  cDARK_MAGENTA=5, cBROWN=6,  cLIGHT_GRAY=7,
   cDARK_GRAY=8, cBLUE=9,         cGREEN=10,     cCYAN=11, 
   cRED=12,      cMAGENTA=13,     cYELLOW=14,    cWHITE=15 };
//---------------------------------------------------------
void init_graphics();
void set_color(color fg, color bg = cBLACK); //Функция цвета(цвет элемента, цвет заднего фона)
void set_cursor_pos(int x, int y); //Функция установки курсора в заданные координаты
void clear_screen(); //Функция очистки экрана
void wait(int milliseconds); //Функция останавливает выполнение программы на заданное время
void clear_line(); //Очищаем строку
void draw_rectangle(int left, int top, int right, int bottom); //Рисуем прямоугольник по заданным пораметрам                    
void draw_circle(int x, int y, int rad); //Рисуем круг
void draw_line(int x1, int y1, int x2, int y2); //Рисуем линию
void draw_pyramid(int x1, int y1, int height); //Рисуем треугольник
void set_fill_style(fstyle); //Функция заливки

#endif /* _INC_WCONSOLE */


