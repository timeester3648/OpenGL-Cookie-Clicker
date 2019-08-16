#pragma once

#pragma comment(lib, "Psapi")

#include <Windows.h>
#include <Psapi.h>

namespace EOUL::Util {

	static MEMORYSTATUSEX memInfo;
	static bool initialized = false;

	/* returns if the given key is down */
	inline bool isKeyDown(int key) {

		return GetAsyncKeyState(key);

	}
	/* returns if the given key is up */
	inline bool isKeyUp(int key) {

		return !isKeyDown(key);

	}

	enum MemoryType {

		Physical,
		Virtual

	};

	/* returns how much ram is free */
	inline size_t ramFree(MemoryType type = MemoryType::Physical) {

		if (!initialized) {

			memInfo.dwLength = sizeof(MEMORYSTATUSEX);

			initialized = true;

		}

		GlobalMemoryStatusEx(&memInfo);

		if (type == MemoryType::Physical) {

			return memInfo.ullAvailPhys;

		} else {

			return memInfo.ullAvailVirtual;

		}

	}
	/*  returns how much ram is used */
	inline size_t ramUsed(MemoryType type = MemoryType::Physical) {

		if (!initialized) {

			memInfo.dwLength = sizeof(MEMORYSTATUSEX);

			initialized = true;

		}

		GlobalMemoryStatusEx(&memInfo);

		if (type == MemoryType::Physical) {

			return memInfo.ullTotalPhys - memInfo.ullAvailPhys;

		} else {

			return memInfo.ullTotalVirtual - memInfo.ullAvailVirtual;

		}

	}
	/* returns how much ram is used by current process */
	inline size_t ramUsedByCurrent() {

		PROCESS_MEMORY_COUNTERS pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

		return pmc.WorkingSetSize;

	}

}