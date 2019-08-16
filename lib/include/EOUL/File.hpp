#pragma once

#include <EOUL\Parser.hpp>

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <filesystem>

#define NOMINMAX
#include <Windows.h>

namespace EOUL {

	namespace IO {

		class FileBase {

			friend std::ostream& operator<<(std::ostream& os, const FileBase& file);

			private:

				class Properties {

					friend class FileBase;

					private:

						DWORD props;

				};

			protected:

				std::filesystem::path path;
				Properties properties = {};

			public:

				FileBase() = default;
				FileBase(std::filesystem::path path) : path(std::move(path)) {

					this->properties.props = GetFileAttributesW(std::filesystem::absolute(this->path).wstring().c_str());

				}

				FileBase(FileBase&& other) noexcept {

					this->swap(other);

				}

				virtual ~FileBase() = default;

			protected:

				FileBase(std::filesystem::path path, Properties properties) : path(std::move(path)), properties(properties) {

				}

			public:

				inline bool operator==(const FileBase& other) const {

					return this->path == other.path;

				}

				inline bool operator!=(const FileBase& other) const {

					return !(*this == other);

				}

				inline FileBase& operator=(const FileBase& other) {

					this->path = other.path;
					this->properties = other.properties;

					return *this;

				}

			public:

				/* swaps 2 FileBases */
				inline void swap(FileBase& other) {

					std::swap(this->path, other.path);
					std::swap(this->properties, other.properties);

				}

				/* creates a new file from the given path, or recreates the existing one */
				inline static void create(const std::filesystem::path& path) {

					if (!exists(path)) {

						mkdirs(absolute(path).u8string().substr(0, absolute(path).u8string().length() - getFileName(absolute(path)).length()));

					}

					std::ofstream out(absolute(path), std::fstream::out | std::fstream::trunc);

				}

				/* returns if the given file exists */
				inline static bool exists(const std::filesystem::path& path) {

					return std::filesystem::exists(path);

				}
				/* returns if the given path is a file */
				inline static bool isFile(const std::filesystem::path& path) {

					return std::filesystem::is_regular_file(path);

				}
				/* returns if the given path is a directory */
				inline static bool isDirectory(const std::filesystem::path& path) {

					return std::filesystem::is_directory(path);

				}
				/* returns if the given path is succesfully removed */
				inline static bool remove(const std::filesystem::path& path) {

					return std::filesystem::remove_all(path);

				}
				/* returns if the given path successfully created */
				inline static bool mkdirs(const std::filesystem::path& path) {

					return std::filesystem::create_directories(path);

				}
				/* returns if the given path is successfully moved */
				inline static bool move(const std::filesystem::path& path, const std::filesystem::path& destination) {
					
					if (!exists(destination) && exists(path)) {

						mkdirs(destination);

					}

					if (!exists(path) || !isDirectory(destination)) {

						return false;

					} else {

						return !(std::rename(std::filesystem::absolute(path).u8string().c_str(), (absolute(destination).u8string() + "\\" + getFileName(path)).c_str()) < 0);

					}

				}

				/* returns the file/folder name from the given path */
				inline static std::string getFileName(std::filesystem::path path) {

					std::string tmp = std::move(path.u8string());

					if (tmp.at(tmp.length() - 1) == '\\' || tmp.at(tmp.length() - 1) == '/') {

						tmp.pop_back();

					}

					size_t pos = tmp.find_last_of("/\\");

					return tmp.substr(pos + 1, tmp.length() - pos - 1);

				}
				/* returns the absolute version of the given path */
				inline static std::filesystem::path absolute(const std::filesystem::path& path) {

					return std::filesystem::absolute(path);

				}
				/* returns the relative version of the given path, the origin is by default the running executable */
				inline static std::filesystem::path relative(const std::filesystem::path& path, const std::filesystem::path& origin = std::filesystem::current_path()) {

					return std::filesystem::relative(path, origin);

				}
				/* returns the extension of the given path, empty string returned when given a directory */
				inline static std::string extension(const std::filesystem::path& path) {

					std::string name = getFileName(path);

					if (!Util::contains(name, "."s) || isDirectory(path)) {

						return "";

					}
					
					unsigned long long i = name.length() - 1;

					while (name.at(i) != '.') {

						i--;

					}

					return name.substr(i, name.length() - i);

				}
				/* returns the parent path of the given path */
				inline static std::filesystem::path parent(const std::filesystem::path& path) {

					return std::filesystem::path(path).parent_path();

				}
				/* returns the current working directory */
				inline static std::filesystem::path currentPath() {

					return std::filesystem::current_path();

				}

				/* returns the size of the given path, it will return 0 if the file doesn't exist */
				inline static unsigned long long size(const std::filesystem::path& path) {

					if (isFile(path)) {

						return (exists(path) ? std::filesystem::file_size(std::filesystem::absolute(path)) : 0);

					} else if (isDirectory(path)) {

						unsigned long long folder_size = 0;

						for (auto& p : std::filesystem::recursive_directory_iterator(path)) {

							folder_size += p.file_size();

						}

						return folder_size;

					} else {

						return 0;

					}

				}

			public:

				/* creates a new file, or recreates the existing one */
				inline void create() const {

					create(this->path);

				}
				/* renames the file, returns the rename result */
				inline int rename(const std::filesystem::path& name) {

					std::wstring tmp = this->path.wstring().substr(0, this->path.wstring().length() - this->getFileName().length()).append(name);

					int result = std::rename(this->path.u8string().c_str(), std::filesystem::absolute(tmp).u8string().c_str());

					this->path = tmp;

					return result;

				}

				/* returns the path that this file is created with */
				inline const std::filesystem::path& getPath() const {

					return this->path;

				}
				/* returns the absolute path */
				inline std::filesystem::path getAbsolutePath() const {

					return std::filesystem::absolute(this->path);

				}
				/* returns the file's extension, empty string is returned when the file is a directory */
				inline 	const std::string extension() const {

					return extension(this->path);

				}
				/* returns the parent path */
				inline const std::filesystem::path parent() const {

					return parent(this->path);

				}

				/* returns the file/folder name */
				inline std::string getFileName() const {

					return getFileName(this->path);

				}

				/* returns if the file path exists */
				inline bool exists() const {

					return exists(this->path);

				}
				/* returns if this is a file */
				inline bool isFile() const {

					return isFile(this->path);

				}
				/* returns if the path is a directory */
				inline bool isDirectory() const {

					return isDirectory(this->path);

				}
				/* returns if the file is succesfully removed */
				inline bool remove() const {

					if (this->isFile()) {

						return std::filesystem::remove(this->path);

					} else if (this->isDirectory()) {

						return std::filesystem::remove_all(this->path);

					} else {

						return false;

					}

				}
				/* returns if the file path successfully created */
				inline 	bool mkdirs() const {

					std::wstring result = this->path;

					if (this->isFile()) {

						result.erase(0, result.length() - this->getFileName().length());

					}

					return mkdirs(result);

				}
				/* returns if the file path is successfully moved */
				inline bool move(const std::filesystem::path& destination) const {

					return move(this->path, destination);

				}

				/*

					A file or directory that is an archive file or directory.
					Applications typically use this attribute to mark files for backup or removal.

				*/
				inline bool isArchive() const {

					return this->properties.props & FILE_ATTRIBUTE_ARCHIVE;

				}
				/*

					A file or directory that is compressed.
					For a file, all of the data in the file is compressed. For a directory, compression is the default for newly created files and subdirectories.

				*/
				inline bool isCompressed() const {

					return this->properties.props & FILE_ATTRIBUTE_COMPRESSED;

				}
				/*

					A file or directory that is encrypted. For a file, all data streams in the file are encrypted.
					For a directory, encryption is the default for newly created files and subdirectories.

				*/
				inline bool isEncrypted() const {

					return this->properties.props & FILE_ATTRIBUTE_ENCRYPTED;

				}
				/*

					The file or directory is hidden.
					It is not included in an ordinary directory listing.

				*/
				inline bool isHidden() const {

					return this->properties.props & FILE_ATTRIBUTE_HIDDEN;

				}
				/*

					A file that does not have other attributes set.
					This attribute is valid only when used alone.

				*/
				inline bool isNormal() const {

					return this->properties.props & FILE_ATTRIBUTE_NORMAL;

				}
				/*

					A file that is read-only.
					Applications can read the file, but cannot write to it or delete it.
					This attribute is not honored on directories.

				*/
				inline bool isReadonly() const {

					return this->properties.props & FILE_ATTRIBUTE_READONLY;

				}
				/*

					A file or directory that the operating system uses a part of, or uses exclusively.

				*/
				inline bool isSystemFile() const {

					return this->properties.props & FILE_ATTRIBUTE_SYSTEM;

				}
				/*

					A file that is being used for temporary storage.
					File systems avoid writing data back to mass storage if sufficient cache memory is available, because typically, an application deletes a temporary file after the handle is closed.
					In that scenario, the system can entirely avoid writing the data.
					Otherwise, the data is written after the handle is closed.

				*/
				inline bool isTemporary() const {

					return this->properties.props & FILE_ATTRIBUTE_TEMPORARY;

				}

				/* returns the Windows file properties represented as a DWORD */
				inline const DWORD getProperies() const {

					return this->properties.props;

				}

				/* returns the file size, it will return 0 if the file doesn't exist */
				inline unsigned long long size() const {

					return size(this->path);

				}

		};

		inline std::ostream& operator<<(std::ostream& os, const FileBase& file) {

			return os << "File(" + file.getAbsolutePath().u8string() + ")";

		}

		class File : public FileBase {

			private:

				std::fstream* stream = nullptr;

			public:

				File() = default;
				File(std::filesystem::path path) : FileBase(std::move(path)) {

				}

				File(const File& other) : FileBase(other.path, other.properties) {

				}

				File(File&& other) noexcept {

					this->swap(other);

				}

				virtual ~File() {

					if (this->stream != nullptr) {

						if (this->stream->is_open()) {

							this->stream->close();

						}

					}

					delete this->stream;

				}

			public:

				/* swaps 2 files */
				inline void swap(File& other) {

					FileBase::swap(other);

					std::swap(this->stream, other.stream);

				}

				/* returns if the file is successfully opened */
				inline bool isOpen() const {

					if (this->stream == nullptr) {

						return false;

					}

					return this->stream->is_open();

				}

				/* opens the file, returns if the file is successfully opened */
				inline virtual bool open(int mode = std::fstream::in | std::fstream::out) {

					if (this->stream == nullptr) {

						this->stream = new std::fstream(this->getAbsolutePath(), mode);

					} else {

						if (!this->close()) {

							return false;

						}

						this->stream->open(this->getAbsolutePath(), mode);


					}

					return this->isOpen();

				}
				/* closes the file, returns if the file is successfully closed */
				inline bool close() {

					this->stream->close();

					return !this->isOpen();

				}

				/*

					returns a vector of all files in the directory if it is a directory.
					if includeSubDirectories is set to true, the subdirectories as folders will also get added to the std::vector

				*/
				inline std::vector<File> listFiles(bool recursive = false, bool includeSubDirectories = false) const {

					if (!this->isDirectory()) {

						return {};

					}

					std::vector<File> tmp;

					if (!recursive) {

						for (auto& p : std::filesystem::directory_iterator(this->path)) {

							if (!includeSubDirectories && p.is_directory()) {

								continue;

							}

							tmp.emplace_back(p.path().string());

						}

					} else {

						for (auto& p : std::filesystem::recursive_directory_iterator(this->path)) {

							if (!includeSubDirectories && p.is_directory()) {

								continue;

							}

							tmp.emplace_back(p.path().string());

						}

					}

					return tmp;

				}
				/*

					returns a vector of all files in the directory if it is a directory and has the given extension.
					if includeSubDirectories is set to true, the subdirectories as folders will also get added to the std::vector

				*/
				inline std::vector<File> listFiles(std::string suffix, bool recursive = false, bool includeSubDirectories = false) const {

					return this->listFiles(std::vector<std::string>(1, std::move(suffix)), recursive, includeSubDirectories);

				}
				/*

					returns a vector of all files in the directory if it is a directory and has one of the given extensions.
					if includeSubDirectories is set to true, the subdirectories as folders will also get added to the std::vector

				*/
				inline std::vector<File> listFiles(std::vector<std::string> suffixes, bool recursive = false, bool includeSubDirectories = false) const {

					for (auto& suffix : suffixes) {

						if (!Util::contains(suffix, "."s)) {

							suffix = "." + suffix;

						}

					}

					if (!this->isDirectory()) {

						return {};

					}

					std::vector<File> tmp;

					if (!recursive) {

						for (auto& p : std::filesystem::directory_iterator(this->path)) {

							bool can = true;
							for (unsigned long long i = 0; i < suffixes.size(); i++) {

								if (Util::endsWith(p.path().string(), suffixes[i])) {

									break;

								}

								if (i == suffixes.size() - 1) {

									can = false;

								}

							}

							if (can) {

								if (!includeSubDirectories && p.is_directory()) {

									continue;

								}

								tmp.emplace_back(p.path().string());

							}

						}

					} else {

						for (auto& p : std::filesystem::recursive_directory_iterator(this->path)) {

							bool can = true;
							for (unsigned long long i = 0; i < suffixes.size(); i++) {

								if (Util::endsWith(p.path().string(), suffixes[i])) {

									break;

								}

								if (i == suffixes.size() - 1) {

									can = false;

								}

							}

							if (can) {

								if (!includeSubDirectories && p.is_directory()) {

									continue;

								}

								tmp.emplace_back(p.path().string());

							}

						}

					}

					return tmp;

				}

				/* writes bytes to the file, if the file exists */
				inline void write(char* bytes, unsigned long long size) const {

					if (!this->isOpen()) {

						return;

					}

					this->stream->write(bytes, size);

				}
				/* reads all the bytes from the file to a buffer */
				inline void read(char* buffer) const {

					this->read(buffer, this->size(), 0ull);

				}
				/* reads a given amount of bytes from the file to a buffer, the offset is the byte to start reading the data */
				inline void read(char* buffer, unsigned long long size, unsigned long long offset = 0ull) const {

					this->stream->seekg(this->stream->beg + offset);
					this->stream->read(buffer, size);

				}
				/* reads all lines into a vector */
				inline std::vector<std::string> readLines() const {

					if (!this->exists()) {

						return {};

					}

					std::ifstream in(this->path);

					if (!in.is_open()) {

						return {};

					}

					std::vector<std::string> tmp;
					std::string line;

					while (std::getline(in, line)) {

						tmp.emplace_back(line);

					}

					return tmp;

				}

		};

		class TemporaryFile final : public File {

			public:

				TemporaryFile() = default;
				TemporaryFile(std::filesystem::path path) : File(path) {

				}

				~TemporaryFile() {

					this->remove();

				}

		};

		class PropertiesFile final : public File, public Parser::PropertiesParser {

			public:

				PropertiesFile(std::filesystem::path path) : PropertiesFile(File(path)) {

				}

				PropertiesFile(const File& file) : File(file), PropertiesParser(file.getAbsolutePath()) {

				}

				PropertiesFile(PropertiesFile&& other) noexcept : Parser::PropertiesParser("") {

					this->swap(other);

				}

			public:

				/* swaps 2 PropertiesFiles */
				inline void swap(PropertiesFile& other) {

					File::swap(other);
					PropertiesParser::swap(other);

				}

				/* adds a key and a value to the properties file, it will change the value of the key if the key already exists */
				inline void put(std::string key, std::string value) {

					if (this->exists()) {

						this->parse();

					} else {

						this->parsed = true;

					}

					this->values.insert(decltype(this->values)::value_type(key, value));

					if (!this->hasKey(key)) {

						std::ofstream out(File::path, std::ios::app);

						out << ("\n" + key + "=" + value);

					} else {

						this->values[key] = value;

						std::ofstream out(File::path);

						unsigned long long i = 0;
						for (auto& it : this->values) {

							out << ((i != 0 ? "\n" : "") + it.first + "=" + it.second);

							i++;

						}

					}

				}
				/* removes a key and its value from the properties file */
				inline void removeKey(std::string key) {

					if (this->exists()) {

						this->parse();

					}

					if (!this->hasKey(key)) {

						return;

					}

					this->values.erase(key);

					std::ofstream out(File::path);

					unsigned long long i = 0;
					for (auto& it : this->values) {

						out << ((i != 0 ? "\n" : "") + it.first + "=" + it.second);

						i++;

					}

				}

		};

		class ConfigFile final : public File, public Parser::ConfigParser {

			public:

				ConfigFile(std::filesystem::path path) : ConfigFile(File(path)) {

				}

				ConfigFile(const File& file) : File(file), ConfigParser(file.getAbsolutePath()) {

				}

				ConfigFile(ConfigFile&& other) noexcept : Parser::ConfigParser("") {

					this->swap(other);

				}

			public:

				/* swaps 2 ConfigFiles */
				inline void swap(ConfigFile& other) {

					File::swap(other);
					ConfigParser::swap(other);

				}

				/* adds a key and a value to the properties file, it will change the value of the key if the key already exists */
				inline void put(std::string key, std::string value) {

					if (this->exists()) {

						this->parse();

					} else {

						this->parsed = true;

					}

					this->values.insert(decltype(this->values)::value_type(key, value));

					if (!this->hasKey(key)) {

						std::ofstream out(File::path, std::ios::app);

						out << ("\n" + key + "=" + value);

					} else {

						this->values[key] = value;

						std::ofstream out(File::path);

						unsigned long long i = 0;
						for (auto& it : this->values) {

							out << ((i != 0 ? "\n" : "") + it.first + "=" + it.second);

							i++;

						}

					}

				}
				/* removes a key and its value from the properties file */
				inline void removeKey(std::string key) {

					if (this->exists()) {

						this->parse();

					}

					if (!this->hasKey(key)) {

						return;

					}

					this->values.erase(key);

					std::ofstream out(File::path);

					unsigned long long i = 0;
					for (auto& it : this->values) {

						out << ((i != 0 ? "\n" : "") + it.first + "=" + it.second);

						i++;

					}

				}

		};

		class IniFile final : public File, public Parser::IniParser {

			public:

				IniFile(std::filesystem::path path) : IniFile(File(path)) {

				}

				IniFile(const File& file) : File(file), IniParser(file.getAbsolutePath()) {

				}

				IniFile(IniFile&& other) noexcept : Parser::IniParser("") {

					this->swap(other);

				}

			public:

				/* swaps 2 IniFiles */
				inline void swap(IniFile& other) {

					File::swap(other);
					IniParser::swap(other);

				}

				/* adds a key, section and a value to the properties file if needed, keep section empty for no section, it will change the value of the key if the key already exists */
				inline void put(std::string section, std::string key, std::string value) {

					if (this->exists()) {

						this->parse();

					} else {

						this->parsed = true;

					}

					this->values[section].insert(std::make_pair(key, value));

					if (!this->hasKey(key, section)) {

						std::ofstream out(File::path);

						if (this->values.size() == 0 && this->values.find("") != this->values.end() && section.length() == 0) {

							unsigned long long i = 0;
							for (auto& it : this->values.at("")) {

								out << (std::string(i != 0 ? "\n" : "") + it.first + "=" + it.second);

								i++;

							}

						} else {

							unsigned long long i = 0;
							bool can_enter = false;
							for (auto& it : this->values) {

								if (it.first.length() != 0) {

									out << (std::string(i != 0 ? "\n" : "") + "[" + it.first + "]");

									can_enter = true;

								}

								for (auto& iter : it.second) {

									out << (std::string((i != 0 || can_enter) ? "\n" : "") + iter.first + "=" + iter.second);

									can_enter = true;

								}

								i++;

							}

						}

					} else {

						this->values[section][key] = value;

						std::ofstream out(File::path);

						unsigned long long i = 0;
						bool can_enter = false;
						for (auto& it : this->values) {

							if (it.first.length() != 0) {

								out << (std::string(i != 0 ? "\n" : "") + "[" + it.first + "]");

								can_enter = true;

							}

							for (auto& iter : it.second) {

								out << (std::string((i != 0 || can_enter) ? "\n" : "") + iter.first + "=" + iter.second);

								can_enter = true;

							}

							i++;

						}

					}

				}
				/* removes a key and its value from the properties file */
				inline void removeKey(std::string key) {

					if (this->exists()) {

						this->parse();

					}

					if (!this->hasKey(key)) {

						return;

					}

					for (auto& it : this->values) {

						if (it.second.find(key) != it.second.end()) {

							it.second.erase(key);

							break;

						}

					}

					std::ofstream out(File::path);

					unsigned long long i = 0;
					bool can_enter = false;
					for (auto& it : this->values) {

						if (it.first.length() != 0) {

							out << (std::string(i != 0 ? "\n" : "") + "[" + it.first + "]");

							can_enter = true;

						}

						for (auto& iter : it.second) {

							out << (std::string((i != 0 || can_enter) ? "\n" : "") + iter.first + "=" + iter.second);

							can_enter = true;

						}

						i++;

					}

				}

		};

	}

}