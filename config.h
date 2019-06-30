#pragma once
#include "../../dependencies/utilities/singleton.hpp"

class config : public singleton<config> {
public:
	bool test1 = false;
	bool test2 = false;
	bool test3 = false;
	bool test4 = false;
	bool test5 = false;
	int test6 = 0;
	int test7 = 0;
	int test8 = 0;
};