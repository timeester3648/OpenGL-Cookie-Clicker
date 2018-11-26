#pragma once

#include <EOUL\compile dependencies\Error.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <filesystem>

namespace EOUL {

	namespace IO {

		class FileBase {

			friend std::ostream& operator<<(std::ostream& os, const FileBase& file);

			protected:

				std::string path = "", absolute_path = "";

			public:

				FileBase() = default;
				FileBase(std::string path);

				virtual ~FileBase() = default;

			public:

				bool operator==(const FileBase& other) const;
				bool operator==(FileBase& other) const;

				bool operator!=(const FileBase& other) const;
				bool operator!=(FileBase& other) const;

				FileBase& operator=(const FileBase& other);

			public:

				/* creates a new file from the given path, or recreates the existing one */
				static void createNewFile(std::string path);

				/* returns if the given file exists */
				static bool exists(std::string path);
				/* returns if the given path is a file */
				static bool isFile(std::string path);
				/* returns if the given path is a directory */
				static bool isDirectory(std::string path);
				/* returns if the given path is succesfully removed */
				static bool remove(std::string path);
				/* returns if the given path successfully created */
				static bool mkdirs(std::string path);
				/* returns if the given path is successfully moved */
				static bool move(std::string path, std::string destination);

				/* returns the file/folder name from the given path */
				static std::string getFileName(std::string path);
				/* returns the absolute version of the given path */
				static std::string absolute(std::string path);
				/* returns the relative version of the given path, origin is by default the running executable */
				static std::string relative(std::string path, std::string origin = std::filesystem::current_path().u8string());

				/* returns the size of the given path, it will return 0 if the file doesn't exist */
				static unsigned long long size(std::string path);

			public:

				/* creates a new file, or recreates the existing one */
				void createNewFile() const;
				/* renames the file */
				void rename(std::string name);
				
				/* returns the path that this file is created with */
				const std::string& getPath() const;
				/* returns the absolute path */
				const std::string& getAbsolutePath() const;

				/* returns the file/folder name */
				std::string getFileName() const;

				/* returns the file path exists */
				bool exists() const;
				/* returns this is a file */
				bool isFile() const;
				/* returns the path is a directory */
				bool isDirectory() const;
				/* returns the file is succesfully removed */
				bool remove() const;
				/* returns the file path successfully created */
				bool mkdirs() const;
				/* returns the file path is successfully moved */
				bool move(std::string destination) const;

				/* returns the file, it will return 0 if the file doesn't exist */
				unsigned long long size() const;
				
		};

		class File : public FileBase {

			public:

				File() = default;
				File(std::string path);

				virtual ~File() = default;

			public:

				/* returns a vector of all files if the directory if it is a directory */
				std::vector<File> listFiles() const;
				/* returns a vector of all files if the directory if it is a directory and has the given extension */
				std::vector<File> listFiles(std::string suffix) const;

				/* writes bytes to the file */
				void write(char* bytes, unsigned long long size, bool addToFile = false) const;
				/* reads all the bytes from the file to a buffer */
				void read(char*& buffer) const;
				/* reads a given amount of bytes from the file to a buffer */
				void read(char*& buffer, unsigned long long size) const;

		};

		class ZipFile : public FileBase {

			public:

				ZipFile() = default;
				ZipFile(std::string path);

			public:

				/* adds a file/folder to the zip file */
				void add(std::string path) const;
				/* adds a file/folder to the zip file */
				void add(File file) const;

				/* extracts all the files/folders to the given destination, the default destination is the same directory as the zip file itself */
				void extractAll(std::string destination = "") const;
				/* extracts all the files/folders to the given destination, the default destination is the same directory as the zip file itself */
				void extractAll(File destination) const;

				/* extracts a file/folder with the given name to the given destination, the default destination is the same directory as the zip file itself */
				void extract(std::string fileName, std::string destination = "") const;
				/* extracts a file/folder with the given name to the given destination, the default destination is the same directory as the zip file itself */
				void extract(std::string fileName, File destination) const;

		};

	}

}