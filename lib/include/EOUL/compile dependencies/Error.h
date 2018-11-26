#pragma once

#include <string>
#include <iostream>

#ifdef EOUL_ERRORS
	#define eoul_error(str) std::cout << str << std::endl
#else
	#define eoul_error(str)
#endif