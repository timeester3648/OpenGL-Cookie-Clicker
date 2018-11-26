#pragma once

#include <EOUL\Maths.h>
#include <EOUL\Save.h>
#include <EOUL\Image.h>
#include <EOUL\Window.h>
#include <EOUL\String.h>
#include <EOUL\Color.h>
#include <EOUL\File.h>
#include <EOUL\Time.h>
#include <EOUL\Net.h>
#include <EOUL\Utils.h>

#include <string>

#if !defined(_HAS_CXX17) || !_HAS_CXX17
	#error "C++17 support is needed!"
#endif

namespace EOUL {

	const std::string version = "1.7";

}

#ifdef EOUL_USE_ALL

	using namespace EOUL;
	using namespace Math;
	using namespace IO;
	using namespace Util;
	using namespace Net;

#endif