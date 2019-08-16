#pragma once

#include <EOUL/Net.hpp>
#include <EOUL/Dll.hpp>
#include <EOUL/File.hpp>
#include <EOUL/Time.hpp>
#include <EOUL/Save.hpp>
#include <EOUL/Maths.hpp>
#include <EOUL/Color.hpp>
#include <EOUL/Utils.hpp>
#include <EOUL/Image.hpp>
#include <EOUL/String.hpp>
#include <EOUL/Parser.hpp>
#include <EOUL/Window.hpp>
#include <EOUL/Process.hpp>
#include <EOUL/Constants.hpp>
#include <EOUL/StdExpansion.hpp>

#if !defined(_HAS_CXX17) || !_HAS_CXX17
	#error C++17 support is needed!
#endif

#define EOUL_MAKE_VERSION(major, minor, patch) (unsigned int((major << 16) | (minor << 8) | (patch << 0)))
#define EOUL_VERSION_MAJOR 1
#define EOUL_VERSION_MINOR 24
#define EOUL_VERSION_PATCH 2
#define EOUL_GET_VERSION_MAJOR(version) (((version) >> 16) & 0xff)
#define EOUL_GET_VERSION_MINOR(version) (((version) >> 8) & 0xff)
#define EOUL_GET_VERSION_PATCH(version) (((version) >> 0) & 0xff)
#define EOUL_VERSION EOUL_MAKE_VERSION(EOUL_VERSION_MAJOR, EOUL_VERSION_MINOR, EOUL_VERSION_PATCH)

#ifdef EOUL_USE_ALL

	using namespace EOUL;

	using namespace IO;
	using namespace Net;
	using namespace Util;
	using namespace Math;
	using namespace Parser;
	using namespace Process;
	using namespace Windows;

#endif