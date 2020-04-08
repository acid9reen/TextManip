#include "pch.h"
#include "TText.hpp"


TLink::TLink(const char* _str, TLink* _pNext,
	TLink* _pDown)
{
	pNext = _pNext;
	pDown = _pDown;

	if (!_str)
	{
		str[0] = '\0';
	}
	else
	{
		strncpy_s(str, _str, 80);
	}
}
/*
void* TLink::operator new(size_t s) {
	TLink* tmp = mem.pFree;

	if (tmp == NULL) {
		throw "pFree is NULL";
	}
	else {
		mem.pFree = mem.pFree->pNext;
	}
	return (void*)tmp;
}

void TLink::operator delete(void* p) {
	TLink* tmp = (TLink*)p;
	tmp->pNext = mem.pFree;
	mem.pFree = tmp;
}

void TLink::init_mem(size_t s) {
	int len = sizeof(TLink) * s;

	mem.pFirst = (TLink*) new char[len];
	mem.pFree = mem.pFirst;
	mem.pLast = mem.pFirst + (s - 1);

	TLink* tmp = mem.pFirst;
	for (int i = 0; i < s - 1; i++) {
		tmp->set_str();
		tmp->pNext = tmp + 1;
		tmp++;
	}
	mem.pLast->set_str();
	mem.pLast->pNext = NULL;
}

void TLink::clear_mem(TText& txt) {
	for (txt.reset(); !txt.is_end(); txt.go_next()) {
		txt.set_not_free();
	}

	TLink* tmp = mem.pFree;
	while (tmp != NULL) {
		tmp->is_free = false;
		tmp = tmp->pNext;
	}

	tmp = mem.pFirst;
	while (tmp != mem.pLast) {
		if (tmp->is_free) {
			delete tmp;
		}
		tmp++;
	}
}

void TLink::print_free() {
	TLink* tmp = mem.pFree;
	int i = 1;

	while (tmp->pNext) {
		std::cout << i << ") ";
		if (tmp->str[0] != '\0') {
			std::cout << tmp->str << std::endl;
		}
		else {
			std::cout << "\"Empty\"" << std::endl;
		}
		tmp = tmp->pNext;
		i++;
	}

	std::cout << i++ << ") ";
	mem.pLast->str[0] != '\0' ? std::cout << mem.pLast->str << std::endl : std::cout << "\"Empty\"" << std::endl;

	//cout << "\nCount of free links: " << i << endl;
}

void TLink::set_str(std::string _str) {
	strcpy_s(str, _str.c_str());
}
*/
/*********************************************************************************************/

TText::TText()
{
	pFirst = pCurr = NULL;
	stack = std::stack<TLink*>();
}

void TText::go_first_link()
{
	pCurr = pFirst;
	stack = std::stack<TLink*>();
}

void TText::go_next_link()
{
	if (!pCurr)
		throw - 1;

	if (!pCurr->pNext)
		return;

	stack.push(pCurr);
	pCurr = pCurr->pNext;
}

void TText::go_down_link()
{
	if (!pCurr)
		throw - 1;

	if (!pCurr->pDown)
		return;

	stack.push(pCurr);
	pCurr = pCurr->pDown;
}

void TText::go_prev_link()
{
	if (!pCurr)
		throw - 1;

	if (stack.empty())
		return;

	pCurr = stack.top();
	stack.pop();
}

void TText::set_line(std::string _str)
{
	if (!pCurr)
		throw - 1;

	strncpy_s(pCurr->str, _str.c_str(), 80);
}

std::string TText::get_line()
{
	if (!pCurr)
		throw - 1;

	return std::string(pCurr->str);
}

void TText::ins_next_line(std::string _str)
{
	if (!pCurr)
		throw - 1;

	auto new_link = new TLink(_str.c_str(), pCurr->pNext, NULL);
	pCurr->pNext = new_link;
}

void TText::ins_down_line(std::string _str)
{
	if (!pCurr)
		throw - 1;

	auto new_link = new TLink(_str.c_str(), pCurr->pDown, NULL);
	pCurr->pDown = new_link;
}

void TText::ins_next_section(std::string _str)
{
	if (!pCurr)
		throw - 1;

	auto new_link = new TLink(_str.c_str(), NULL, pCurr->pNext);
	pCurr->pNext = new_link;
}

void TText::ins_down_section(std::string _str)
{
	if (!pCurr)
		throw - 1;

	auto new_link = new TLink(_str.c_str(), NULL, pCurr->pDown);
	pCurr->pDown = new_link;
}

void TText::del_next()
{
	if (!pCurr || !pCurr->pNext)
		throw - 1;

	TLink* tmp = pCurr->pNext;
	pCurr->pNext = tmp->pNext;
	delete tmp;
}

void TText::del_down()
{
	if (!pCurr || !pCurr->pDown)
		throw - 1;

	TLink* tmp = pCurr->pDown;
	pCurr->pDown = tmp->pNext;
	delete tmp;
}

TLink* TText::read_recursively(std::ifstream& ifs)
{
	TLink* first{ NULL }, * tmp{ NULL };
	char buf[81];

	while (!ifs.eof())
	{
		ifs.getline(buf, 80, '\n');

		if (buf[0] == '}')
			break;
		else if (buf[0] == '{')
		{
			tmp->pDown = read_recursively(ifs);
		}
		else if (!first)
		{
			first = new TLink(buf);
			tmp = first;
		}
		else
		{
			tmp->pNext = new TLink(buf);
			tmp = tmp->pNext;
		}
	}

	return first;
}

void TText::read(std::string fn)
{
	std::ifstream ifs(fn);
	pFirst = read_recursively(ifs);
}

void TText::write_recursively(std::ofstream& ofs, TLink* tmp)
{
	ofs << tmp->str << std::endl;

	if (tmp->pDown)
	{
		ofs << '{' << std::endl;
		write_recursively(ofs, tmp->pDown);
		ofs << '}' << std::endl;
	}

	if (tmp->pNext)
	{
		write_recursively(ofs, tmp->pNext);
	}
}

void TText::write(std::string fn)
{
	std::ofstream ofs(fn);
	write_recursively(ofs, pFirst);
}

void TText::print_recursively(TLink* tmp)
{
	if (tmp != NULL) {
		if (tmp == pCurr) {
			SetColor(ConsoleColor::LightCyan, ConsoleColor::Black);
			std::cout << "->";
			SetColor(ConsoleColor::LightGray, ConsoleColor::Black);
		}
		else {
			std::cout << "  ";
		}

		for (int i = 0; i < level; i++)
			std::cout << "    ";

		std::cout << tmp->str << std::endl;
		level++;
		print_recursively(tmp->pDown);
		level--;
		print_recursively(tmp->pNext);
	}
}

void TText::print()
{
	level = 0;
	print_recursively(pFirst);
}

bool TText::is_end()
{
	return stack.empty();
}

bool TText::go_next()
{
	if (!is_end())
	{
		pCurr = stack.top();
		stack.pop();

		if (pCurr != pFirst)
		{
			if (pCurr->pNext != NULL)
				stack.push(pCurr->pNext);

			if (pCurr->pDown != NULL)
				stack.push(pCurr->pDown);
		}

		return true;
	}

	return false;
}

bool TText::reset()
{
	stack = std::stack<TLink*>();
	pCurr = pFirst;

	if (pCurr != NULL)
	{
		stack.push(pCurr);

		if (pCurr->pNext != NULL)
			stack.push(pCurr->pNext);

		if (pCurr->pDown != NULL)
			stack.push(pCurr->pDown);
	}

	return is_end();
}
/*
void TText::set_not_free()
{
	pCurr->is_free = false;
}*/
