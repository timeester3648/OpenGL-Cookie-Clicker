#pragma once

#include "File.h"

#include <string>
#include <fstream>
#include <vector>
#include <memory>

namespace EOUL {

	namespace IO {

		class SaveData {

			public:

				std::unique_ptr<char> data;
				size_t size = 0;

			public:

				SaveData(char* data, size_t size);

		};

		class SaveFile : public FileBase {

			private:

				struct SaveQueue {

					char* ptr;
					size_t size;

				};

				std::vector<SaveQueue> queued;

			public:

				SaveFile() = default;
				SaveFile(std::string path);

			public:

				/* saves data to the file */
				void save(char* data, unsigned long long dataSize, bool addToFile = false) const;
				/* saves data to the file */
				void save(SaveData& data, bool addToFile = false) const;

				/* adds save queue entry to be saved later */
				void save_queued(char* data, unsigned long long dataSize);
				/* saves all queued save entries */
				void save_all_queued();

				/* returns a vector of all saved data */
				std::vector<SaveData> readData() const;

		};

	}

}