#pragma once

#include "pch.h"
#include "Color.hpp"


class TLink;
class TText;

struct TMem
{
	TLink* pFirst;
	TLink* pFree;
	TLink* pLast;
};

class TLink
{
public:
	TLink* pNext, * pDown;
	char str[80];
	bool is_free;
	
	static TMem mem;

	TLink(const char* _str = NULL, TLink* _pNext = NULL, TLink* _pDown = NULL);
	~TLink() {};
	
	void* operator new(size_t s);
	void operator delete(void* p);

	static void init_mem(size_t s);
	static void clear_mem(TText& txt);

	static void print_free();
	void set_str(std::string _str = "\0");
	
};


class TText
{
	TLink* pFirst, * pCurr;
	std::stack<TLink*> stack;
	int level;

public:
	TText();
	void go_first_link();
	void go_next_link();
	void go_down_link();
	void go_prev_link();

	void set_line(std::string _str);
	std::string get_line();

	void ins_next_line(std::string _str);
	void ins_down_line(std::string _str);
	void ins_next_section(std::string _str);
	void ins_down_section(std::string _str);

	void del_next();
	void del_down();

	TLink* read_recursively(std::ifstream& ifs);
	void read(std::string fn);

	void write_recursively(std::ofstream& ofs, TLink* tmp);
	void write(std::string fn);

	void print_recursively(TLink* tmp);
	void print();

	bool is_end();
	bool go_next();
	bool reset();

	void set_not_free();
};
