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
	std::string buf;
	bool read_flag{ false };
	std::string fn{ "C:\\Users\\smirn\\source\\repos\\text_manip\\TextManip\\src\\Color.cpp" };

	while (true) {
		SetColor(ConsoleColor::LightCyan, ConsoleColor::Black);
		std::cout << "$ ";
		SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		option = _getch();
		std::cout << option << std::endl;

		switch (option) {
		case 'i': std::cout << "r - read\np - print\ns - save\nq - quit\ne - clear\nf - print free\nd - clear memory\n" <<
			"a - go to previous link\nz - go to next link\nx - go to down link\n1 - insert next line\n2 - insert next section\n" <<
			"3 - insert down line\n4 - insert down section\n5 - delete next link\n6 - delete down link\n"; break;
		case 'r': text.read(fn); 
				  if (text.get_pFirst() == NULL) 
				  { 
					  std::cout << "Reading error\n"; 
				  }
				  else 
				  {		
					  read_flag = true; 
					  std::cout << "Successful reading\n"; 
				  };
				  break;
		case 'p': TLink::clear_mem(text); 
				  clrscr(); text.print();
				  break;
		case 'd': if(read_flag) 
				  { 
				  	  TLink::clear_mem(text); 
					  std::cout << "Memory was cleared\n";
				  }
				  else 
				  std::cout << "There is nothing to clear\n"; 
				  break;
		case 's': text.write("Saved_text.txt"); break;
		case 'e': clrscr(); std::cout << "i - info\n"; break;
		case 'f': TLink::print_free();
				  break;
		case 'q': if (read_flag) 
					  TLink::clear_mem(text);
				  exit(0);
		case 'a': text.go_prev_link(); clrscr(); text.print(); break;
		case 'z': text.go_next_link(); clrscr(); text.print(); break;
		case 'x': text.go_down_link(); clrscr(); text.print(); break;
		case '1': std::cout << "Enter your line: "; std::getline(std::cin, buf); text.ins_next_line(buf); clrscr(); text.print(); break;
		case '2': std::cout << "Enter your line: "; std::getline(std::cin, buf); text.ins_next_section(buf); clrscr(); text.print(); break;
		case '3': std::cout << "Enter your line: "; std::getline(std::cin, buf); text.ins_down_line(buf); clrscr(); text.print(); break;
		case '4': std::cout << "Enter your line: "; std::getline(std::cin, buf); text.ins_down_section(buf); clrscr(); text.print(); break;
		case '5': text.del_next(); clrscr(); text.print(); break;
		case '6': text.del_down(); clrscr(); text.print(); break;
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