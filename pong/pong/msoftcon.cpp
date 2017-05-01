
#include "stdafx.h"


HANDLE hConsole; //Дескрипторный тип данных
unsigned char fill_char;          //Символ для заливки
//--------------------------------------------------------------
void init_graphics()
   {
   COORD console_size = {74,27}; //Размер буфера консоли

   /*Функция CreateFile() открывает каталог
   -значение CONOUT$, чтобы определить консольный вывод данных
   -флаги GENERIC_WRITE | GENERIC_READ Открывают консоль для вывода/ввода данных.
   -флаги  FILE_SHARE_READ | FILE_SHARE_WRITE Разрешения для чтения и для записи
   -флаг OPEN_EXISTING открывает консоль
   -флаг FILE_ATTRIBUTE_NORMAL использование стандартных атрибутов*/
   
   hConsole = CreateFile(L"CONOUT$", GENERIC_WRITE | GENERIC_READ,
                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                   0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);

   SetConsoleScreenBufferSize(hConsole, console_size); //Устанавливаем размер экранного буфера консоли
   
   SetConsoleTextAttribute( hConsole, (WORD)((0 << 4) | 15) ); //Устанавливает атрибуты символов(цвет текста и фона) по умалчанию
 
   fill_char = '\xDB';  //Символ заполнения по умалчанию
   clear_screen(); //Очистка экрана
   }
//--------------------------------------------------------------
void set_color(color foreground, color background) //Окрас элемента и заднего фона
   {
   SetConsoleTextAttribute( hConsole,
                        (WORD)((background << 4) | foreground) ); //Устанавливает атрибуты символов(цвет текста и фона) по значению
   }  //end setcolor()
 
/* 0  Black          8  Dark gray
   1  Dark blue      9  Blue
   2  Dark green     10 Green
   3  Dark cyan      11 Cyan
   4  Dark red       12 Red
   5  Dark magenta   13 Magenta
   6  Brown          14 Yellow
   7  Light gray     15 White
*/
//--------------------------------------------------------------
void set_cursor_pos(int x, int y) //Устанавливаем курсор в позицию
   {
   COORD cursor_pos;              //Определяем координаты в буфере консоли
   cursor_pos.X = x - 1;          //Windows starts at (0, 0)
   cursor_pos.Y = y - 1;          //we start at (1, 1)
   SetConsoleCursorPosition(hConsole, cursor_pos); //Устанавливаем курсор в точку заданную координатами
   }
//--------------------------------------------------------------
void clear_screen() //Очищаем экран
   {
   set_cursor_pos(1, 25);  //.Устанавливаем курсор в заданные координаты
   for(int j=0; j<25; j++) //.
      _putch('\n'); 	   //Спускаемся на 24 строки вниз
   set_cursor_pos(1, 1);   //Устанавливаем курсор в заданные координаты
   }
//--------------------------------------------------------------
void wait(int milliseconds) //Ожидаем
   {
   Sleep(milliseconds); //Функция останавливает выполнение программы на заданное время
   }
//--------------------------------------------------------------
void clear_line()                    //Очищаем до конца строки
   {                                 //80 пробелов
   //......1234567890123456789012345678901234567890
   //......0........1.........2.........3.........4
   _cputs("                                        ");//.
   _cputs("                                        ");//.Выводим строку
   }
//--------------------------------------------------------------
void draw_rectangle(int left, int top, int right, int bottom) //Рисуем прямоугольник
{
	char temp[80]; //Строковый массив для фигуры(При превышение размера ошибка программы)
	int width = right - left + 1; //Возвращаем ширину к заданым параметрам и + 1
	for (int j = 0; j < width; j++)   //.
		temp[j] = fill_char;		  //.Печатаем строку квадрата на заданную длину
	temp[width] = 0;  //Завершаем строку нулем

	for (int y = top; y <= bottom; y++)  //Печатаем ширину по заданным пораметрам
	{
		set_cursor_pos(left, y);//Устанавливаем курсор в заданные координаты
		_cputs(temp); //Выводим созданную строку квадрата
	}
}
//--------------------------------------------------------------
void draw_circle(int xC, int yC, int radius/*=5*/) //Рисуем круг (для коректного отображения(есле !r=1) -> xC>=r*2+1, yC>=r+1, r>1)
   {

   double theta, increment, xF, pi=3.14159;
   int x, xN, yN;
 
   increment = 0.8 / static_cast<double>(radius); //Получем значение инкримента =0,16
   for(theta=0; theta <= pi/2 /*1,570795*/; theta+=increment/*+=0,16 на каждой итерации*/)  // Четверть окружности
      {
      xF = radius * cos(theta); //=5, 4.93614, 4.74618, 4.010487, 3.48353, 2.17841, 0.6521198
      xN = static_cast<int>(xF * 2 / 1); //=10, 9, 8, 6, 4, 5, 2 
      yN = static_cast<int>(radius * sin(theta) + 0.5); //=0, 1, 2, 3, 4, 5, 5
      x = xC-xN; //=30, 31, 31, 32, 34, 36, 39, 8 Находим координату X для начала строки
      while(x <= xC+xN)  //Отрисовываем две строки
         {                       
         set_cursor_pos(x,   yC-yN); _putch(fill_char);  //Верх (30,12)(31,11)(31,10)(32,9) (34,8) (36,7) (39,7)
         set_cursor_pos(x++, yC+yN); _putch(fill_char);  //Низ  (31,12)(32,13)(32,14)(33,15)(35,16)(37,17)(40,17)
         }
      }  //end for
   }
//--------------------------------------------------------------
void draw_line(int x1, int y1, int x2, int y2) //Рисуем линию
   {
   int w, z, t, w1, w2, z1, z2;
   double xDelta=x1-x2 /*Длинна*/, yDelta=y1-y2 /*Ширина*/, slope/*угал*/;
   bool isMoreHoriz; //Горизонтальная 1 или вертикальная 0
 
   if( fabs(xDelta) > fabs(yDelta)/*Сравниваем числа по модолю*/ ) //Горизонтальная линия
      {
      isMoreHoriz = true;
      slope = yDelta / xDelta;  // наклон
      w1=x1; z1=y1; w2=x2, z2=y2;    
      }
   else                              //Вертикалная линия
      {
      isMoreHoriz = false;
      slope = xDelta / yDelta; // наклон
      w1=y1; z1=x1; w2=y2, z2=x2;    
      }
 
   if(w1 > w2)           //Если начальные координаты больше конечных по Х
      {
      t=w1; w1=w2; w2=t;             //.меняем значения (w1,w2) (z1,z2) местами
      t=z1; z1=z2; z2=t;             //. 
      }
   for(w=w1/*5*/; w<=/*10*/w2; w++) //Запускаем цикл по отрисовке           
      {
      z = static_cast<int>(z1 + slope * (w-w1)); //Получаем координату по X с учетом отступа
      if( !(w==80 && z==25) )        //avoid scroll at 80,25
         {
         if(isMoreHoriz)
            set_cursor_pos(w, z); //Устанавливаем курсор на позицию
         else
            set_cursor_pos(z, w); //Устанавливаем курсор на позицию
         _putch(fill_char); //Отрисовываем символ
         }
      }
   }
//--------------------------------------------------------------
void draw_pyramid(int x1, int y1, int height) //Рисуем треугольник
   {
   int x, y;
   for(y=y1; y<y1+height; y++)
      {
      int incr = y - y1;
      for(x=x1-incr; x<=x1+incr; x++)
         {
         set_cursor_pos(x, y); //Устанавливаем курсор на позицию
         _putch(fill_char);	   //Отрисовываем символ
         }
      }
   }
//--------------------------------------------------------------
void set_fill_style(fstyle fs) //Тип заполнения(заливка)
   {
	
   switch(fs)
      {
      case SOLID_FILL:  fill_char = '\xDB'; break;
      case DARK_FILL:   fill_char = '\xB0'; break;
      case MEDIUM_FILL: fill_char = '\xB1'; break;
      case LIGHT_FILL:  fill_char = '\xB2'; break;
      case X_FILL:      fill_char = 'X';    break;
      case O_FILL:      fill_char = 'O';    break;
      }
   }
//--------------------------------------------------------------