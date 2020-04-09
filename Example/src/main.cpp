#include "TText.hpp"
#include <Windows.h>
#include <conio.h>

void clrscr(void);
void clreol(void);
void gotoxy(int x, int y);

TMem TLink::mem;
constexpr int LINK_COUNT { 100 };

int main()
{
	TLink::init_mem(LINK_COUNT);

	TText text = TText();
	char option;

	std::string fn = "C:\\Users\\smirn\\source\\repos\\text_manip\\TextManip\\src\\Color.cpp";

	while (true) {
		SetColor(ConsoleColor::LightGreen, ConsoleColor::Black);
		std::cout << "user: ";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		option = _getch();
		std::cout << option << std::endl;

		switch (option) {
		case 'i': std::cout << "r - read\np - print\ns - save\nc - copy\nq - quit\ne - clear\na - go to previous link\nz - go to next link\nx - " <<
			"go to down link\n1 - insert next line\n2 - insert next section\n3 - insert down line\n4 - insert down section\n" <<
			"5 - delete next link\n6 - delete down link\n"; break;
		case 'r': text.read(fn); break;
		case 'p': text.print(); break;
		//case 's': text.Save("C:\\Users\\User\\Documents\\GitHub projects\\Lab6-Text\\SavedText.txt"); break;
			//case 'c': TText tmp(text.Copy()); tmp.Save("C:\\Users\\User\\Documents\\GitHub projects\\Lab6-Text\\Copy.txt"); break;
		case 'e': clrscr(); std::cout << "i - info\n"; break;
		case 'q': exit(0);
		case 'a': text.go_prev_link(); text.print(); break;
		case 'z': text.go_next_link(); text.print(); break;
		case 'x': text.go_down_link(); text.print(); break;
		//case '1': std::cout << "Enter your line: "; std::cin >> buf; text.InsNextLine(buf); text.print(); break;
		//case '2': std::cout << "Enter your line: "; std::cin >> buf; text.InsNextSection(buf); text.print(); break;
		//case '3': cout << "Enter your line: "; cin >> buf; text.InsDownLine(buf); text.print(); break;
		//case '4': cout << "Enter your line: "; cin >> buf; text.InsDownSection(buf); text.print(); break;
		case '5': text.del_next(); text.print(); break;
		case '6': text.del_down(); text.print(); break;
		default: std::cout << "Input error\n";
		}
	}


	

	return 0;
}

void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	DWORD Count;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}

void clreol(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;

	COORD zpos = buf.dwCursorPosition;

	zpos.X = buf.dwCursorPosition.X + 1;
	zpos.Y = buf.dwCursorPosition.Y;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X - buf.dwCursorPosition.X - 1, zpos, &Count);
	SetConsoleCursorPosition(Console, buf.dwCursorPosition);
}

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}