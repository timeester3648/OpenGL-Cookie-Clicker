#pragma once

#pragma comment(lib, "Psapi")

#include <string>
#include <Psapi.h>
#include <Windows.h>
#include <TlHelp32.h>

namespace EOUL::Windows {

	class Window final {

		private:

			std::string name;
			HANDLE handle = 0;
			HWND window = 0;
			DWORD process = 0;

		public:

			Window(std::string name) : name(std::move(name)) {

				this->window = FindWindow(NULL, (LPCSTR) name.c_str());

				GetWindowThreadProcessId(this->window, &this->process);

				this->handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process);

			}

			Window(Window&& other) noexcept {

				this->swap(other);

			}

			~Window() {

				CloseHandle(this->handle);

			}

		public:

			/* swaps 2 Windows */
			inline void swap(Window& other) {

				std::swap(this->name, other.name);
				std::swap(this->handle, other.handle);
				std::swap(this->window, other.window);
				std::swap(this->process, other.process);

			}

			/* Keep arguments empty if the exe has the same name as the window, returns the base adress of the application */
			inline size_t getBaseAdress(std::string customExeName) const {

				HANDLE hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process);
				MODULEENTRY32 me32;
				size_t ba = 0;

				me32.dwSize = sizeof(MODULEENTRY32);

				Module32First(hsnapshot, &me32);

				if (customExeName.find(".exe") == std::string::npos) {

					customExeName += ".exe";

				} else if (customExeName.length() == 0) {

					customExeName = this->name + ".exe";

				}

				do {

					if (strstr((const char*)me32.szExePath, customExeName.c_str())) {

						ba = (size_t) me32.modBaseAddr;

						break;

					}

				} while (Module32Next(hsnapshot, &me32));

				CloseHandle(hsnapshot);

				return ba;

			}

			/* writes data to the given menory adress */
			template<typename T, typename enabled = std::enable_if_t<!std::is_array_v<T>>>
			inline size_t writeMemory(size_t adress, T* data, size_t count) const {

				size_t written = 0;

				WriteProcessMemory(this->handle, (LPVOID) adress, (LPCVOID) data, count * sizeof(T), &written);

				return written;

			}
			/* reads data from the given menory adress */
			template<typename T, typename enabled = std::enable_if_t<!std::is_array_v<T>>>
			inline size_t readMemory(size_t adress, T* buffer, size_t count) const {

				size_t read = 0;

				ReadProcessMemory(this->handle, (LPCVOID) adress, (LPVOID) buffer, count * sizeof(T), &read);

				return read;

			}

	};

}