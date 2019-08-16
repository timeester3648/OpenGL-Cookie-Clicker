#pragma once

#define NOMINMAX
#include <Windows.h>
#include <filesystem>

namespace EOUL::Windows {

	class Dll {

		private:

			HMODULE library = 0;

		public:

			Dll() = default;
			Dll(const Dll& other) = delete;
			Dll(const std::filesystem::path& path) {

				this->load(path);

			}

			Dll(Dll&& other) noexcept {

				this->swap(other);

			}

			~Dll() {

				this->unload();

			}

		private:

			inline void* loadProcAdress(const std::string& symbol) const {

				return reinterpret_cast<void*>(GetProcAddress(this->library, symbol.c_str()));

			}

		public:

			/* swaps 2 dlls */
			inline void swap(Dll& other) {

				std::swap(this->library, other.library);

			}

			/* unloads dll */
			inline void unload() {

				if (this->library != 0) {

					FreeLibrary(this->library);

				}

				this->library = 0;

			}
			/* loads the given dll, unloads current dll if there is already a dll loaded, returns if succeeded */
			inline bool load(const std::filesystem::path& path) {

				this->unload();

				this->library = LoadLibraryW(path.c_str());

				return (this->library != 0);

			}

			/* returns function pointer to the given symbol name */
			template <typename T>
			inline T* get(const std::string& symbol) const {

				return reinterpret_cast<T*>(this->loadProcAdress(symbol));

			}


	};

}