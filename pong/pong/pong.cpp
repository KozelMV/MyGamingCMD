// 01.05.2017 kozelmv@gmail.com

#include "stdafx.h"
#include "msoftcon.h"
#include <iostream>


enum { hor= -2, ver = -37, tone = 7};
//std::cout << static_cast<char>(-2); //������ ������� ��������   ASCII-866
//std::cout << static_cast<char>(-37); //������ ������� ���������	ASCII-866
//std::cout << static_cast<char>(7) << std::endl; //����			ASCII-866


class Game {
	enum { width = 72, height = 27 }; // ������ ���� ����
	char sizeGame[width][height] = { ' ' }; //������ ���� ����
public:
	Game()  { 
		system("mode con:cols=74 lines=27"); //������������� ������ �������
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
	char filling[2] = { hor , ver };// ������ � ��������� ��� ����������
public:
	GamingField() {
		// ���������� �������---------------------------------------------------------------
			for (int i = 0; i < width; i++) // ���������� ������� ����� ����
				*(*(sizeField + i) + 0) = *(filling + 1);
			for (int i = 0; i < height; i++)// ���������� ������� ������ ������� ����
				*(*(sizeField + width-1) + i) = *(filling + 1);
			for (int i = 0; i < width; i++) // ���������� ������� ��� ����
				*(*(sizeField + i) + height-1) = *(filling + 1);
			for (int i = height; i > 0; i--)// ���������� ������� ����� ������� ����
				*(*(sizeField + 0) + i) = *(filling + 1);
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
		// �������� ������ ���� � ������ ����------------------------------------------------
			for(int i = 7 , c = 0; c < height; i++, c++)
				sGame(sizeField,2,i,c,width);
		// ----------------------------------------------------------------------------------
	}
	
};


int main()
{	
	SetConsoleOutputCP(866); // ��������� ������� �������� win-cp 866 � ����� ������
	SetConsoleOutputCP(866); // ��������� ������� �������� win-cp 866 � ����� ������

	GamingField g1;
	g1.dGame();
	

		Beep(294, 1000 / 8); //���� <windows.h>
	

	//std::cout << std::endl;
	system("pause");
    return 0;
}

