#pragma once

#include <string>
#include <Windows.h>

namespace EOUL {

	namespace Windows {

		class Window {

			public:

				std::string name;
				HANDLE handle;
				HWND window;
				DWORD process;

			public:

				Window(std::string name);

			public:

				/* Keep arguments empty if the exe has the same name as the window, returns the base adress of the application */
				unsigned long long getBaseAdress(std::string customExeName = "") const;

				/* writes data to the given menory adress */
				void writeMemory(unsigned long long adress, void* data, unsigned long long size) const;
				/* reads data from the given menory adress */
				void readMemory(unsigned long long adress, void* buffer, unsigned long long size) const;

		};

	}

}