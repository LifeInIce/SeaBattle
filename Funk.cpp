#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime> // для рандома
#include "Header.h"
int stop = 0, raund = 0;
int sizeMap = 12;
char sNone = 126, sShip = 220, sMiss = 79, sHit = 88;



enum ConsoleColor {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

int chekFinish(char**& obj) { //проверка на снос всех палуб
	int N = 0; // переменная для работы
	for (int i = 0; i < sizeMap - 1; i++) for (int j = 0; j < sizeMap - 1; j++) if (obj[i][j] == sHit) N++; // подсчет целых палуб	
	return N; // снесено палуб
}
void makeMap(char**& obj1, char**& obj2) {	// cоздание карты
	obj1 = new char* [sizeMap]; // задаем указатели на массив игрока
	obj2 = new char* [sizeMap];// задаем указатели на массив бота
	for (int i = 0; i < sizeMap; i++) {
		obj1[i] = new char[sizeMap]; 
		obj2[i] = new char[sizeMap];
	}
	for (int i = 1; i < sizeMap - 1; i++) for (int j = 1; j < sizeMap - 1; j++) { obj1[i][j] = sNone; obj2[i][j] = sNone; } // заполняем массивы игрока и бота
}
void randShipAll(char**& obj1, char**& obj2) {	// авто расстановка кораблей
	raund = 1;
	makeMap(obj1, obj2);	// создаем карту
	autoFourDeck(obj1);		// устанавливаем 4х палубник игрока
	autoTreeDeck(obj1);		// устанавливаем 3х палубник игрока
	autoTwoDeck(obj1);		// устанавливаем 2х палубник игрока
	autoOneDeck(obj1);		// устанавливаем 1а палубник игрока
	autoFourDeck(obj2);		// устанавливаем 4х палубник бота
	autoTreeDeck(obj2);		// устанавливаем 3х палубник бота
	autoTwoDeck(obj2);		// устанавливаем 2х палубник бота
	autoOneDeck(obj2);		// устанавливаем 1а палубник бота
	showMap(obj1, obj2);	// отображаем карту
}
void manualShip(char**& obj1, char**& obj2) {	// ручная установка кораблей игроком
	makeMap(obj1, obj2);		// cоздание карты
	manualFourDeck(obj1, obj2);	// устанавливаем 4х палубник игрока
	manualTreeDeck(obj1, obj2); // устанавливаем 3х палубник игрока
	manualTwoDeck(obj1, obj2);	// устанавливаем 2х палубник игрока
	manualOneDeck(obj1, obj2);	// устанавливаем 1а палубник игрока
	autoFourDeck(obj2);			// устанавливаем 4х палубник бота
	autoTreeDeck(obj2);			// устанавливаем 3х палубник бота
	autoTwoDeck(obj2);			// устанавливаем 2х палубник бота
	autoOneDeck(obj2);			// устанавливаем 1а палубник бота
	showMap(obj1, obj2);		// отображаем карту

}	
void showMap(char**& obj1, char**& obj2) {	// отображение карты
	system("cls"); // очистка консоли
	setColor(4, Black);
	if (raund == 0) std :: cout << "\n\n\t\t\t ";
	else std :: cout << "\n\n\t\t\t        Raund : " << raund;
	std :: cout << "\n\t\tYour Map\t\t\t Bot Map\n\n"; 
	setColor(7, 0);
	for (int i = 0; i < sizeMap - 1; i++)//напечатать боковые линейки координат и сами поля
	{
		if (i == 0) std :: cout << "\t " << char(1) << " "; // смайлик в левом верхнем углу поле игрока
		else if (i == 10) std :: cout << "\t10 "; // корректное отображение цифры 10
		else std :: cout << "\t " << i << " ";
		for (int j = 0; j < sizeMap - 1; j++) {
			if (i == 0 && j != 0) std :: cout << j << " ";
			else if (i != 0 && j != 0)
				if (obj1[i][j] == sNone) {
					setColor(9, 0); std :: cout << obj1[i][j] << " "; setColor(7, 0); // указываем цвет пустой клетки
				}
				else if
					(obj1[i][j] == sHit) {
					setColor(4, 0); std :: cout << obj1[i][j] << " "; setColor(7, 0);// указываем цвет попадания
				}
				else if
					(obj1[i][j] == sMiss) {
					setColor(2, 0); std :: cout << obj1[i][j] << " "; setColor(7, 0);// указываем цвет промаха
				}
				else if (obj1[i][j] == sShip) {
					setColor(15, 0); std :: cout << obj1[i][j] << " "; setColor(7, 0); // указываем увет корабля
				}
				else  setColor(7, 0);
		}
		std :: cout << " \t";
		if (i == 0) std :: cout << " " << char(1) << " "; // смайлик в левом верхнем углу поле бота
		else if (i == 10) std :: cout << "10 "; // корректное отображение цифры 10
		else std :: cout << " " << i << " ";
		for (int j = 0; j < sizeMap - 1; j++) {
			if (i == 0 && j != 0) std :: cout << j << " ";
			else if (i != 0 && j != 0)
				if (obj2[i][j] == sNone) {
					setColor(9, 0); std :: cout << obj2[i][j] << " "; setColor(7, 0); // указываем цвет пустоты
				}
				else if
					(obj2[i][j] == sHit) {
					setColor(4, 0); std :: cout << obj2[i][j] << " "; setColor(7, 0);// указываем цвет попадания
				}
				else if
					(obj2[i][j] == sMiss) {
					setColor(2, 0); std :: cout << obj2[i][j] << " "; setColor(7, 0); // указываем цвет промаха
				}
				else if (obj2[i][j] == sShip) {
					setColor(9, 0); std :: cout << sNone << " "; setColor(7, 0); // скрываем вражеский кораблик
				}
				else  setColor(7, 0);

		}std :: cout << "\n";
	}std :: cout << "\n";
}
void shootPlayer(char**& obj1, char**& obj2) { // выстрел
	int t=0,x, y;	// переменные для работы
	while (t==0 && stop !=1) {
		if (chekFinish(obj2) == 20) { // проверка на выигрыш Игроком
			screensaverPlayer();
			stop++; // выход из боя
			break; // прерывание цикла
		}
		t = 0; // счетчик
		std :: cout << "\n\t\tEnter coord: x";
		std :: cin >> x;// считывание переменных
		std :: cout << "\t\tEnter coord: y";
		std :: cin >> y;// считывание переменных
		if (x == 0 && y == 0) stop++; // выход из боя
		else if (obj2[y][x] == sNone) {
			obj2[y][x] = sMiss; // отображение промаха
			t++; // счетчик
		}
		else if (obj2[y][x] == sShip) {
			obj2[y][x] = sHit; // отображение попадания	
			showMap(obj1, obj2);
		}
		else if (obj2[y][x] == sMiss)std :: cout << "\nY alraedy shoot for it coords\n";
		else std :: cout << "\t\tInvalid input.\n";
	} 
	raund++;
}
void shootBot(char**& obj1, char**& obj2) { // выстрел
	int t = 0, x, y;// переменные для работы
	while (t == 0 && stop != 1) {
		if (chekFinish(obj1) == 20) { // проверка на выигрыш Игроком
			screensaverBot();
			stop++;	// выход из боя
			break; // прерывание цикла
		}
		t = 0; // обнуление счетчика
		x = 1 + rand() % 10; // лимит вертикали
		y = 1 + rand() % 10; // лимит горизонтали	
		if (obj1[y][x] == sNone) { // отображение промаха
			obj1[y][x] = sMiss;
			t++; // счетчик
			showMap(obj1, obj2);
			std :: cout << "\t\tBot shoot: x,y - " << x << "." << y << std :: endl;
		}
		else if (obj1[y][x] == sShip) { // отображение попадания	
			obj1[y][x] = sHit;
			showMap(obj1, obj2);
			std :: cout << "\t\tBot shoot: x,y - " << x << "." << y << std :: endl;
		}
	} 
}
void KillAll(char**& obj) { // показать расположение всех кораблей
	for (int i = 0; i < sizeMap - 1; i++) for (int j = 0; j < sizeMap - 1; j++) if (obj[i][j] == sShip) obj[i][j] = sHit;
}
void autoOneDeck(char**& obj) {
	int k = 0, t, x, y;// переменные для работы
	while (k < 4) { // лимит кораблей
		x = 1 + rand() % 10; // лимит вертикали
		y = 1 + rand() % 10; // лимит горизонтали
		t = 0; // обнуление счетчика найденых соседей
		for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++) if (obj[x][y] == sNone && obj[x + i][y + j] != sShip)	 t++;// проверка соседей
		if (t == 9) { // "водоизмещение"
			obj[x][y] = sShip; // ставим кораблик
			k++; // счетчик вида кораблей
		}

	}
}
void autoTwoDeck(char**& obj) { // 2 палубы
	int k = 0, t, x, y, route;// переменные для работы
	while (k < 3) { // лимит кораблей
		route = rand() % 2; // верт или гориз
		if (route == 1) {  // горизонт
			x = 1 + rand() % 10;// лимит вертикали
			y = 1 + rand() % 9; // лимит горизонтали
			t = 0; // обнуление счетчика найденых соседей
			for (int i = -1; i < 2; i++) for (int j = -1; j < 3; j++) if (obj[x][y] == sNone && obj[x + i][y + j] != sShip) t++; // проверка соседей
			if (t == 12) { // "водоизмещение"
				for (int i = 0; i <= 1; i++) obj[x][y + i] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
		else {  // вертикаль
			x = 1 + rand() % 9; // лимит вертикали
			y = 1 + rand() % 10;// лимит горизонтали
			t = 0;// обнуление счетчика найденых соседей
			for (int i = -1; i < 3; i++) for (int j = -1; j < 2; j++) if (obj[x][y] == sNone && obj[x + i][y + j] != sShip)	 t++;// проверка соседей
			if (t == 12) { // "водоизмещение"
				for (int i = 0; i <= 1; i++) obj[x + i][y] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
	}
}
void autoTreeDeck(char**& obj) { // 3 палубы
	int k = 0, t, x, y, route; // переменные для работы
	while (k < 2) { // лимит кораблей
		route = rand() % 2; // верт или гориз
		if (route == 1) {  // горизонт
			x = 1 + rand() % 10;// лимит вертикали
			y = 1 + rand() % 8; // лимит горизонтали
			t = 0; // обнуление счетчика найденых соседей
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 4; j++) if (obj[x][y] == sNone && obj[x + i][y + j] != sShip) t++; // проверка соседей
			if (t == 15) { // "водоизмещение"
				for (int i = 0; i <= 2; i++) obj[x][y + i] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
		else {  // вертикаль
			x = 1 + rand() % 8; // лимит вертикали
			y = 1 + rand() % 10;// лимит горизонтали
			t = 0; // обнуление счетчика найденых соседей
			for (int i = -1; i < 4; i++) for (int j = -1; j < 2; j++) if (obj[x][y] == sNone && obj[x + i][y + j] != sShip)	 t++;// проверка соседей
			if (t == 15) { // "водоизмещение"
				for (int i = 0; i <= 2; i++) obj[x + i][y] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
	}
}
void autoFourDeck(char**& obj) { // 4 палубы
	int x, y, route;// переменные для работы
	route = 1 + rand() % 2; // верт или гориз
	if (route == 1) {  // горизонт
		x = 1 + rand() % 10;// лимит вертикали
		y = 1 + rand() % 7; // лимит горизонта
		for (int i = 0; i <= 3; i++) obj[x][y + i] = sShip; // ставим кораблик
	}
	else {  // вертикаль
		x = 1 + rand() % 7; // лимит вертикали
		y = 1 + rand() % 10;// лимит горизонтали
		for (int i = 0; i <= 3; i++) obj[x + i][y] = sShip; // ставим кораблик
	}
}
void manualOneDeck(char**& obj1, char**& obj2) {
	int k = 0, t, x, y;// переменные для работы	
	do { // лимит кораблей		
		do {
			showMap(obj1, obj2);
			std :: cout << "\t\tPut single-deck ship " << k << " / 4 \n";
			std :: cout << "\n\t\tEnter coord: x";
			std :: cin >> y;// считывание переменных 
			std :: cout << "\t\tEnter coord: y";
			std :: cin >> x;// считывание переменных
			if (x==0 && y==0)  menu(obj1, obj2);
		} while (x > 10 || x < 1 || y > 10 || y < 1);
		t = 0; // обнуление счетчика найденых соседей
		for (int i = -1; i < 2; i++) for (int j = -1; j < 2; j++) if (obj1[x][y] == sNone && obj1[x + i][y + j] != sShip)	 t++;// проверка соседей
		if (t == 9) { // "водоизмещение"
			obj1[x][y] = sShip; // ставим кораблик
			k++;
		}
	} while (k < 4);
	Sleep(500);
}
void manualTwoDeck(char**& obj1, char**& obj2) { // 2 палубы
	int k = 0, t, x, y, route;// переменные для работы	
	do {
		showMap(obj1, obj2);
		std :: cout << "\t\tPut double deck ship " << k << " / 3 \n";
		std :: cout << "\n\t\tEnter route\n\t\tGorizontal press 1\n\t\tVertical press 2\n\t\tExit press 0\n";
		std :: cout << "\t\tYour Choice: ";
		std :: cin >> route;// считывание переменных
		if (route == 1) {  // горизонталь
			do {
				std :: cout << "\n\t\tEnter coord: x";
				std :: cin >> y;// считывание переменных 
				std :: cout << "\t\tEnter coord: y";
				std :: cin >> x;// считывание переменных
			} while (x > 10 || x < 1 || y > 9 || y < 1);
			t = 0; // обнуление счетчика найденых соседей
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 3; j++) if (obj1[x][y] == sNone && obj1[x + i][y + j] != sShip) t++; // проверка соседей
			if (t == 12) { // "водоизмещение"
				for (int i = 0; i <= 1; i++) obj1[x][y + i] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
		else if (route == 2) {  // вертикаль
			do {
				std :: cout << "\n\t\tEnter coord: x";
				std :: cin >> y;// считывание переменных 
				std :: cout << "\t\tEnter coord: y";
				std :: cin >> x;// считывание переменных
			} while (x > 9 || x < 1 || y > 10 || y < 1);
			t = 0;
			for (int i = -1; i < 3; i++) for (int j = -1; j < 2; j++) if (obj1[x][y] == sNone && obj1[x + i][y + j] != sShip)	 t++;// проверка соседей
			if (t == 12) { // "водоизмещение"
				for (int i = 0; i <= 1; i++) obj1[x + i][y] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
		else if (route == 0) menu(obj1, obj2);
		else std :: cout << "\t\tInvalid input.\n";
	} while (k < 3);
}
void manualTreeDeck(char**& obj1, char**& obj2) { // 3 палубы
	int k = 0, t, x, y, route; // переменные для работы	
	do { // лимит кораблей		
		showMap(obj1, obj2);
		std :: cout << "\t\tPut three - deck ship " << k << " / 2 \n";
		std :: cout << "\n\t\tEnter route\n\t\tGorizontal press 1\n\t\tVertical press 2\n\t\tExit press 0\n";
		std :: cout << "\t\tYour Choice: ";
		std :: cin >> route;// считывание переменных
		if (route == 1) {  // горизонталь
			do {
				std :: cout << "\n\t\tEnter coord: x";
				std :: cin >> y;// считывание переменных 
				std :: cout << "\t\tEnter coord: y";
				std :: cin >> x;// считывание переменных
			} while (x > 10 || x < 1 || y > 8 || y < 1);
			t = 0; // обнуление счетчика найденых соседей
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 4; j++) if (obj1[x][y] == sNone && obj1[x + i][y + j] != sShip) t++; // проверка соседей
			if (t == 15) { // "водоизмещение"
				for (int i = 0; i <= 2; i++) obj1[x][y + i] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
		else  if (route == 2) {  // вертикаль
			do {
				std :: cout << "\n\t\tEnter coord: x";
				std :: cin >> y;// считывание переменных 
				std :: cout << "\t\tEnter coord: y";
				std :: cin >> x;// считывание переменных
			} while (x > 8 || x < 1 || y > 10 || y < 1);
			t = 0; // обнуление счетчика найденых соседей
			for (int i = -1; i < 4; i++) for (int j = -1; j < 2; j++) if (obj1[x][y] == sNone && obj1[x + i][y + j] != sShip)	 t++;// проверка соседей
			if (t == 15) { // "водоизмещение"
				for (int i = 0; i <= 2; i++) obj1[x + i][y] = sShip; // ставим кораблик
				k++; // счетчик вида корабля
			}
		}
		else if (route == 0)  menu(obj1, obj2);
		else std :: cout << "\t\tInvalid input.\n";
	} while (k < 2);
}
void manualFourDeck(char**& obj1, char**& obj2) { // 4 палубы
	int k = 0, x, y, route;// переменные для работы
	
	do {
		showMap(obj1, obj2);
		std :: cout << "\t\tPut four - deck ship \n";
		std :: cout << "\n\t\tEnter route\n\t\tGorizontal press 1\n\t\tVertical press 2\n\t\tExit press 0\n";
		std :: cout << "\t\tYour Choice: ";
		std :: cin >> route;// считывание переменных 
		if (route == 1) {  // горизонталь
			do {
				std :: cout << "\n\t\tEnter coord: x";
				std :: cin >> y;// считывание переменных 
				std :: cout << "\t\tEnter coord: y";
				std :: cin >> x;// считывание переменных
			} while (x > 10 || x < 1 || y > 7 || y < 1);
			for (int i = 0; i <= 3; i++) obj1[x][y + i] = sShip; // ставим кораблик
			k++;
		}
		else if (route == 2) {  // вертикаль
			do {
				std :: cout << "\n\t\tEnter coord: x";
				std :: cin >> y;// считывание переменных 
				std :: cout << "\t\tEnter coord: y";
				std :: cin >> x;// считывание переменных
			} while (x > 7 || x < 1 || y > 10 || y < 1);
			for (int i = 0; i <= 3; i++) obj1[x + i][y] = sShip; // ставим кораблик
			k++;
		}
		else if (route == 0)  menu(obj1, obj2);
		else std :: cout << "\t\tInvalid input.\n";
	} while (k == 0 && stop != 1);
}
void logo() { // Логотип
	{
		system("cls");
		//system("color 04"); // цвет текста красный
		std :: cout << "  " << "\n\n\n\n\n\n\n\n"
			<< "\t " << char(219) << char(219) << "        " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "       " << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << "    " << char(219) << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "     " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << "  \n"
			<< "\t " << char(219) << char(219) << "   " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "      " << char(219) << char(219) << "      " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "\t\t" << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << " \n"
			<< "\t  " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "      " << char(219) << char(219) << "      " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << "\t\t" << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << std :: endl
			<< "\t  " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "      " << char(219) << char(219) << "      " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "  " << char(219) << char(219) << "  " << char(219) << char(219) << " " << char(219) << char(219) << "\t\t" << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << " \n"
			<< "\t   " << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "      " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "        " << char(219) << char(219) << "     " << char(219) << char(219) << char(219) << char(219) << char(219) << "  \n\n\n\n"


			<< "  " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "    " << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "        " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "      " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "\n"
			<< "  " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "    " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "        " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "       " << char(219) << char(219) << "    " << char(219) << char(219) << "      " << char(219) << char(219) << "        " << char(219) << char(219)<<" " << char(219) << char(219) << "\n"
			<< "  " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "        " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "    " << char(219) << char(219) << "       " << char(219) << char(219) << "    " << char(219) << char(219) << "      " << char(219) << char(219) << char(219) << char(219) << char(219) << "     " << char(219) << char(219) << " " << char(219) << char(219) << "\n"
			<< "  " << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "        " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "       " << char(219) << char(219) << "    " << char(219) << char(219) << "      " << char(219) << char(219) << "\n"
			<< "  " << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "       " << char(219) << char(219) << "    " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "\n\n\n";
		Sleep(2000); // пауза в 2 сек
		system("cls");
		
	}
}
void fight(char**& obj1, char**& obj2) {
	do {
		shootPlayer(obj1, obj2);		
		shootBot(obj1, obj2);
	} while ( stop != 1);
}
void screensaverPlayer() {

	std :: cout << "\n\n\n\n\n"
		<< "\t " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "\t  " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "    " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "     " << char(219) << char(219) << "        " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "   " << char(219) << char(219) << " \n"
		<< "\t " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "      " << char(219) << char(219) << "   " << char(219) << char(219) << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "      " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "   " << char(219) << char(219) << " \n"
		<< "\t " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "\t" << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "      " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "  " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " \n"
		<< "\t " << char(219) << char(219) << "\t" << " " << char(219) << char(219) << "      " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "    " << char(219) << char(219) << "      " << char(219) << char(219) << "   " << char(219) << char(219) << "     " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << " " << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << "\n"
		<< "\t " << char(219) << char(219) << "\t" << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "    " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "      " << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "\n\n\n\n";
}
void screensaverBot() {

	std :: cout << "\n\n\n\n\n"
		<< "\t " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "    " << char(219) << char(219) << "        " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "   " << char(219) << char(219) << "\n"
		<< "\t " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "       " << char(219) << char(219) << "   " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "   " << char(219) << char(219) << "\n"
		<< "\t " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "        " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << " " << char(219) << char(219) << "  " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "\n"
		<< "\t " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "        " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << " " << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << "\n"
		<< "\t " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "     " << char(219) << char(219) << "         " << char(219) << char(219) << "    " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "\n\n\n\n";

}
void setColor(unsigned fg, unsigned bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((bg << 4) | fg));

}
void menu(char**& obj1, char**& obj2) {
	logo();
	int choice;
	do {
		system("cls"); // очистка консоли
		std :: cout << "\n\n\n\n\n\n\n\n\n\n\t\t\tHow do you want to arrange the ships ?\n";
		std :: cout << "\t\t\tSelf press 1  |   Auto press 2   |   Exit press 0\n";
		std :: cout << "\t\t\tYour Choice: ";
		std :: cin >> choice;
		switch (choice)
		{
		case 0:
			screensaverBye();
			return;
			break;
		case 1:
			manualShip(obj1, obj2);
			fight(obj1, obj2);
			break;
		case 2:
			randShipAll(obj1, obj2);
			fight(obj1, obj2);
			break;
		default:
			system("cls"); // очистка консоли
			
			
			break;
		}
	} while (choice != 0);
}
void screensaverBye() { 
	system("cls");
	std :: cout << "\n\n\n\n\n" << "          " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "        " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << "    " << char(219) << char(219) << " " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << std :: endl
		<< "\t " << char(219) << char(219) << "       " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "       " << char(219) << char(219) << "   " << char(219) << char(219) << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "  " << char(219) << char(219) << "        " << char(219) << char(219) << std :: endl
		<< "\t "<< char(219) << char(219) << "   " << char(219) << char(219) << "  " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "       " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "    " << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "     " << char(219) << char(219) << std :: endl
		<< "\t " <<char(219) << char(219) << "    " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << " " << char(219) << char(219) << "   " << char(219) << char(219) << "       " << char(219) << char(219) << "   " << char(219) << char(219) << "    " << char(219) << char(219) << "    " << char(219) << char(219) << std :: endl
		<< "\t  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << char(219) << char(219) << char(219) << "  " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "        " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "     " << char(219) << char(219) << "    " << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << "   " << char(219) << char(219) << "\n\n\n\n\n";
	Sleep(2000); // пауза в 2 сек
}