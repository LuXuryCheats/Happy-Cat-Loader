#pragma once
#include <iostream>
#include "skCrypt.hpp"
using namespace std;

void start_driver()
{
	driver().handle_driver();

	if (!driver().is_loaded())
	{
		cout << skCrypt("\n  Loading Driver..") << endl;
		mmap_driver();
	}

	driver().handle_driver();
	driver().is_loaded() ? cout << skCrypt("\n\n ") << endl : cout << skCrypt("\n\n Error 0x29 (Initalizing Failure)") << endl;
}