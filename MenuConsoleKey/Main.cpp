#include "head.h"
#include <iostream>
#include <windows.h>
#include <locale.h>
#include "../StatList.h"
#include <limits>
#include <stdlib.h>

void clearRow(int row)
{
	DWORD dw;
	COORD here;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	here.X = 2;
	here.Y = row;
	LPCSTR str = "       ";
	WriteConsoleOutputCharacter(hStdOut, str, 8, here, &dw);
}

const char* space = "\t\t";
HWND console = nullptr;
POINT PosConsole = { 100,100 };
POINT sizeConsole = { 1200,600 };

void FontsSettings(int width, int height) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontFamily = FF_DONTCARE; 
	cfi.FontWeight = 600;
	//std::wcscpy(cfi.FaceName, L"Sony Sketch EF");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


void loading()
{
	ProgressBar prog("", 0, 0);
	bool exit = true;
	while (exit)
	{	
		//cls();
		setCursorPosition(65, 16);
		setConsoleColour(0xA);
		std::wcout << "LOADING...";
		setCursorPosition(18, 18);
		prog.Show(0);
		Sleep(10);
		prog.ChangeValue(0);
		std::cout.flush();
		if (prog.value == 100.0F)
			exit = false;
	}

}


int menu(field* Array_field, int cout_Array_field)
{
	cls();

	//Exemple :)
	setConsoleColour(0xA);
	bool change = true;
	bool finish = false;
	int pos = 0;
	int max = 0;
	timer tmr1(100, true);

	while (!finish)
	{
		if (tmr1.timer_on())
		{
			if (change)
			{
				square(40, 5, 1, 0, 0);
				setCursorPosition(8, 0);
				size_t i = 0;
				
				std::cout << " GitHub @Yut-ka \r";
				std::cout << std::endl;
				int line_number = 8;

				for (field* ptr = Array_field; ptr <= &Array_field[cout_Array_field - 1]; ptr++) {
					setCursorPosition(2, line_number++);
					ptr->show(pos);
					++i;
				}
				max = i-1;
				change = false;
				
			}
	
			if (GetAsyncKeyState(VK_UP))
			{
				pos--;
				if (pos < 0)
					pos = max;
				change = true;

			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				++pos;
				if (pos > max)
					pos = 0;
				change = true; 
			}
			if (GetAsyncKeyState(VK_RETURN))
			{
				for (field* ptr = Array_field; ptr <= &Array_field[cout_Array_field - 1]; ptr++) {
					ptr->Press(pos);				
				}
				pos == max ? finish = true : finish = false;
				change = true;
				return pos;
			}
			setCursorPosition(2, 2);
			std::cout << "SAOD LAB3_3";
			setCursorPosition(2, 3);
			std::cout << "by Osipov Danil 4218";	
			setCursorPosition(2, 15);


			std::cout.flush();
		}
		Sleep(1);
	}
}


std::string text(textblock field)
{
	cls();

	//Exemple :)
	setConsoleColour(0xA);
	bool change = true;
	bool finish = false;
	int pos = 0;
	int max = 0;
	timer tmr1(100, true);
	

	while (!finish)
	{
		if (tmr1.timer_on())
		{
			
			std::string a;

			if (change)
			{
				square(40, 5, 1, 0, 0);
				setCursorPosition(8, 0);
				size_t i = 0;

				std::cout << " GitHub @Yut-ka \r" << std::endl;
				std::cout << std::endl;

				setCursorPosition(2, 2);
				std::cout << "SAOD LAB1" << std::endl;
				setCursorPosition(2, 3);
				std::cout << "by Osipov Danil 4218" << std::endl;

				setCursorPosition(2, 8);
				field.show(pos);
				setCursorPosition(2, 10);
				clearRow(10);
				getline(std::cin,a);
				std::cin.clear();
				std::cin.sync();
			}

			

			if (GetAsyncKeyState(VK_RETURN))
			{
				finish = true;
				return a;
			}

			
			
			std::cout.flush();
		}
		Sleep(0.5);
	}
}


std::string Get_el_console(std::string str) {
	textblock C = str;
	std::flush(std::cout);
	std::string A = text(C);
	return A;
}


int main()
{ 
	FontsSettings(0, 16);
	console = GetConsoleWindow();
	SetWindowPos(console, NULL, PosConsole.x, PosConsole.y, sizeConsole.x, sizeConsole.y, NULL);
	SetWindowLong(console, GWL_STYLE, WS_BORDER);
	ShowWindow(console, SW_SHOW);
	ExConsole();
	loading();		
				
	Stat_List* a = new Stat_List();

	while (1) {
		field A[6] = { "display the current LIST state on the screen", "search for an element by the information part", "add a new element after a special one", "add a new element before a special one","delete a specified element with a shift","Exit" };
		bool back = 0;
		int choice = menu(A, 6);
		if (choice == 0) {
			while (!back) {
				if (a->cout == 0) {
					field EMPTY[2] = { "List is empty!" ,"Back" };
					if (menu(EMPTY, 2) == 1) back = 1;
				}
				else {
					field SHOW[3] = { "Output of the entire LIST:", "Back", Show(a) };
					if (menu(SHOW, 3) == 1) back = 1;
				}
			}
		}
		else if (choice == 1) {
			while (!back) {
				int elem_get = stoi(Get_el_console("Enter a inf from element"));
				if (Get(a, elem_get) == -1) {
					field EMPTY[2] = { "Element not found!" ,"Back" };
					if (menu(EMPTY, 2) == 1) back = 1;
				}
				else {
					field SHOW[3] = { "Element with inf: " + std::to_string(elem_get) + " has a number:", "Back", std::to_string(Get(a,elem_get)) };
					if (menu(SHOW, 3) == 1) back = 1;
				}
			}
		}

		else if (choice == 2) {
			while (!back) {
				field ADD_AFTER[2] = { "New element added successfully!" ,"Back" };
				int index_elem = stoi(Get_el_console("Enter the index:"));
				int elem = stoi(Get_el_console("Enter the new item:"));
				int add_res = Push_after(a,index_elem, elem);
				if (add_res == 2) {
					ADD_AFTER[0].name = "List is full!";
				}
				if (add_res == 0) {
					ADD_AFTER[0].name = "Uncorrect enter!";
				}
				if (menu(ADD_AFTER, 2) == 1) back = 1;
			}
		}

		else if (choice == 3) {
			while (!back) {
				field ADD_AFTER[2] = { "New element added successfully!" ,"Back" };
				int index_elem = stoi(Get_el_console("Enter the index:"));
				int elem = stoi(Get_el_console("Enter the new item:"));
				int add_res = Push_before(a, index_elem, elem);
				if (add_res == 2) {
					ADD_AFTER[0].name = "List is full!";
				}
				if (add_res == 0) {
					ADD_AFTER[0].name = "Uncorrect enter!";
				}
				if (menu(ADD_AFTER, 2) == 1) back = 1;
			}
		}

		else if (choice == 4) {
			while (!back) {
				int del_elem = stoi(Get_el_console("Enter the number of the item to delete"));
				field DEL[2] = { "Element was succesfull deleted" , "Back" };
				int del_res = Delete(a, del_elem);
				if (del_res == 0) {
					DEL[0].name = "Element with that number not found";
				}
				else if (del_res == 1) {
					DEL[0].name = "Element was succesfull deleted";
				}
				if (menu(DEL, 3) == 1) back = 1;
			}
		}
		else if (choice == 5) {
			exit(0);
		}
	}
		
	
	return 0;
}

