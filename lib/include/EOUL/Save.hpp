#pragma once

#include <EOUL\File.hpp>

#include <string>
#include <fstream>
#include <vector>
#include <memory>

namespace EOUL::IO {

	class SaveData final {

		public:

			std::unique_ptr<char[]> data;
			unsigned long long size = 0;

		public:

			SaveData(std::unique_ptr<char[]>& data, unsigned long long size) : data(std::move(data)), size(size) {

			}

			SaveData(SaveData&& other) noexcept {

				this->swap(other);

			}

		public:

			/* swaps 2 SaveDatas */
			inline void swap(SaveData& other) {

				std::swap(this->data, other.data);
				std::swap(this->size, other.size);

			}

	};

	class SaveFile final : public File {

		private:

			struct SaveQueue final {

				char* ptr;
				size_t size;

				SaveQueue(char* ptr, size_t size) : ptr(ptr), size(size) {

				}

			};

			std::vector<SaveQueue> queued;

		public:

			SaveFile() = default;
			SaveFile(std::filesystem::path path) : File(std::move(path)) {

			}

			SaveFile(SaveFile&& other) noexcept {

				this->swap(other);

			}

		public:

			/* swaps 2 SaveFiles */
			inline void swap(SaveFile& other) {

				std::swap(this->queued, other.queued);

			}

			/* 

				opens the file, returns if the file is successfully opened.
				automatically adds the binary open flag.

			*/
			inline bool open(int mode = std::fstream::in | std::fstream::out) override {

				return File::open(mode | std::fstream::binary);

			}

			/* saves data to the file if the file exists and the file is opened */
			void save(char* data, unsigned long long size) const {

				if (!this->isOpen()) {

					return;

				}

				this->write((char*) &size, sizeof(size));
				this->write(data, size);

			}
			/* saves data to the file if the file exists and the file is opened */
			void save(const SaveData& data) const {

				this->save(data.data.get(), data.size);

			}

			/* adds save queue entry to be saved later, pointer still needs to be valid until saved */
			void saveQueued(char* data, size_t dataSize) {

				this->queued.emplace_back(data, dataSize);

			}
			/* saves all queued save entries if the file exists */
			void saveAllQueued() {

				if (!this->isOpen()) {

					return;

				}

				for (auto& data : this->queued) {

					this->save(data.ptr, data.size);

				}

				this->queued.clear();
				this->queued.shrink_to_fit();

			}

			/* returns a vector of all saved data */
			std::vector<SaveData> readData() const {

				if (!this->exists() || this->size() == 0 || !this->isOpen()) {

					return {};

				}

				unsigned long long fileSize = this->size();

				std::vector<SaveData> tmp;
				std::unique_ptr<char[]> data = std::make_unique<char[]>(fileSize);

				this->read(data.get());

				char* index = data.get();
				unsigned long long currentSize = 0;
				std::unique_ptr<char[]> currentData;

				while (true) {

					currentSize = *reinterpret_cast<uintptr_t*>(index);
					currentData = std::make_unique<char[]>(currentSize);

					index += sizeof(decltype(currentSize));

					memcpy(currentData.get(), index, currentSize);

					tmp.emplace_back(currentData, currentSize);

					index += currentSize;

					if (index >= data.get() + fileSize) {

						break;

					}

				}

				return tmp;

			}

	};

}