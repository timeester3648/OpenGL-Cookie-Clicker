#pragma once

#include <EOUL/String.hpp>

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std::string_literals;

namespace EOUL::Parser {

	enum class ParseResult : unsigned char {

		ParseUnknownError,
		ParseFileStreamNotOpen,
		ParseSyntaxError,
		ParseKeyDuplicate,
		ParseSuccessful

	};

	class BaseParser {

		protected:

			bool parsed = false;
			std::filesystem::path path;

		protected:

			BaseParser() = default;

		public:

			BaseParser(std::filesystem::path path) : path(std::move(path)) {

			}

			BaseParser(BaseParser&& other) noexcept {

				this->swap(other);

			}

			virtual ~BaseParser() = default;

		public:

			/* swaps 2 BaseParsers */
			inline void swap(BaseParser& other) {

				std::swap(this->path, other.path);
				std::swap(this->parsed, other.parsed);

			}

			/* parses the file content */
			virtual ParseResult parse() = 0;

			/* returns if the file has been parsed */
			inline bool isParsed() const {

				return this->parsed;

			}

	};

	class PropertiesParser : public BaseParser {

		protected:

			std::unordered_map<std::string, std::string> values;

		public:

			PropertiesParser(std::filesystem::path path) : BaseParser(path) {

			}

			PropertiesParser(PropertiesParser&& other) noexcept {

				this->swap(other);

			}

		public:

			/* swaps 2 PropertiesParsers */
			inline void swap(PropertiesParser& other) {

				BaseParser::swap(other);

				std::swap(this->values, other.values);

			}

			/* parses the file content */
			inline virtual ParseResult parse() override {

				this->parsed = false;

				this->values.clear();

				std::vector<std::string> lines;
				std::string current_line = "";
				std::ifstream in = std::ifstream(this->path);

				if (!in.is_open()) {

					this->values.clear();

					return ParseResult::ParseFileStreamNotOpen;

				}

				while (std::getline(in, current_line)) {

					if (Util::startsWith(current_line, "#"s) || current_line.length() == 0) {

						continue;

					}

					std::string tmp = current_line;

					while (tmp.at(tmp.length() - 1) == '\\') {

						std::string l;

						std::getline(in, l);

						while (l.length() > 0 && l.at(0) == ' ' || l.length() > 0 && l.at(0) == '\t') {

							l.erase(0, 1);

						}

						tmp.erase(tmp.length() - 1, 1);

						tmp += l;

					}

					lines.emplace_back(tmp);

				}

				in.close();

				for (auto& line : lines) {

					std::vector<std::string> splitted;

					for (size_t i = 0; i < line.length(); i++) {

						if (line.at(i) == '=') {

							splitted.emplace_back(line.substr(0, i - (line.at(i) == ' ' ? 1 : 0)));
							splitted.emplace_back(line.substr(i + 1, line.length() - (i + 1)));

							break;

						}

					}

					if (splitted.size() != 2) {

						this->values.clear();

						return ParseResult::ParseSyntaxError;

					} else {

						if (splitted[0].length() > 0) {

							if (splitted[0].at(splitted[0].length() - 1) == ' ') {

								splitted[0] = splitted[0].substr(0, splitted[0].length() - 1);

							}

						} else {

							this->values.clear();

							return ParseResult::ParseSyntaxError;

						}

						if (splitted[1].length() > 0) {

							if (splitted[1].at(0) == ' ') {

								splitted[1] = splitted[1].substr(1, splitted[1].length() - 1);

							}

						}

					}

					if (this->values.find(splitted[0]) != this->values.end()) {

						this->values.clear();

						return ParseResult::ParseKeyDuplicate;

					}

					this->values.insert(std::unordered_map<std::string, std::string>::value_type(splitted[0], splitted[1]));

				}

				if (this->values.size() != lines.size()) {

					this->values.clear();

					return ParseResult::ParseUnknownError;

				}

				this->parsed = true;

				return ParseResult::ParseSuccessful;

			}

			/* returns the parsed values as a const unordered_map reference */
			inline const std::unordered_map<std::string, std::string>& getParsedValues() const {

				return this->values;

			}
			/* returns the value of the key if it exists */
			inline const std::string& getValue(std::string key) const {

				return this->values.at(key);

			}

			/* returns if the given key is parsed from the file */
			inline bool hasKey(std::string key) const {

				return this->values.find(key) != this->values.end();

			}

	};

	class ConfigParser : public BaseParser {

		protected:

			std::unordered_map<std::string, std::string> values;

		public:

			ConfigParser(std::filesystem::path path) : BaseParser(path) {

			}

			ConfigParser(ConfigParser&& other) noexcept {

				this->swap(other);

			}

		public:

			/* swaps 2 PropertiesParsers */
			inline void swap(ConfigParser& other) {

				BaseParser::swap(other);

				std::swap(this->values, other.values);

			}

			/* parses the file content */
			inline virtual ParseResult parse() override {

				this->parsed = false;

				this->values.clear();

				std::vector<std::string> lines;
				std::string current_line = "";
				std::ifstream in = std::ifstream(this->path);

				if (!in.is_open()) {

					this->values.clear();

					return ParseResult::ParseFileStreamNotOpen;

				}

				while (std::getline(in, current_line)) {

					if (current_line.length() == 0) {

						continue;

					}

					lines.emplace_back(current_line);

				}

				in.close();

				for (auto& line : lines) {

					std::vector<std::string> splitted;

					for (size_t i = 0; i < line.length(); i++) {

						if (line.at(i) == '=') {

							splitted.emplace_back(line.substr(0, i - (line.at(i) == ' ' ? 1 : 0)));
							splitted.emplace_back(line.substr(i + 1, line.length() - (i + 1)));

							break;

						}

					}

					if (splitted.size() != 2) {

						this->values.clear();

						return ParseResult::ParseSyntaxError;

					} else {

						if (splitted[0].length() > 0) {

							if (splitted[0].at(splitted[0].length() - 1) == ' ') {

								splitted[0] = splitted[0].substr(0, splitted[0].length() - 1);

							}

						} else {

							this->values.clear();

							return ParseResult::ParseSyntaxError;

						}

						if (splitted[1].length() > 0) {

							if (splitted[1].at(0) == ' ') {

								splitted[1] = splitted[1].substr(1, splitted[1].length() - 1);

							}

						}

					}

					if (this->values.find(splitted[0]) != this->values.end()) {

						this->values.clear();

						return ParseResult::ParseKeyDuplicate;

					}

					this->values.insert(std::unordered_map<std::string, std::string>::value_type(splitted[0], splitted[1]));

				}

				if (this->values.size() != lines.size()) {

					this->values.clear();

					return ParseResult::ParseUnknownError;

				}

				this->parsed = true;

				return ParseResult::ParseSuccessful;

			}

			/* returns the parsed values as a const unordered_map reference */
			inline const std::unordered_map<std::string, std::string>& getParsedValues() const {

				return this->values;

			}
			/* returns the value of the key if it exists */
			inline const std::string& getValue(std::string key) const {

				return this->values.at(key);

			}

			/* returns if the given key is parsed from the file */
			inline bool hasKey(std::string key) const {

				return this->values.find(key) != this->values.end();

			}

	};

	class IniParser : public BaseParser {

		protected:

			std::unordered_map<std::string, std::unordered_map<std::string, std::string>> values;

		public:

			IniParser(std::filesystem::path path) : BaseParser(path) {

			}

			IniParser(IniParser&& other) noexcept {

				this->swap(other);

			}

		public:

			/* swaps 2 PropertiesParsers */
			inline void swap(IniParser& other) {

				BaseParser::swap(other);

				std::swap(this->values, other.values);

			}

			/* parses the file content */
			inline virtual ParseResult parse() override {

				this->parsed = false;

				this->values.clear();

				std::unordered_map<std::string, std::vector<std::string>> lines;
				std::string current_line = "", current_section = "";
				std::ifstream in = std::ifstream(this->path);

				if (!in.is_open()) {

					this->values.clear();

					return ParseResult::ParseFileStreamNotOpen;

				}

				while (std::getline(in, current_line)) {

					if (Util::startsWith(current_line, "["s) && !Util::endsWith(current_line, "]"s)) {

						this->values.clear();

						return ParseResult::ParseSyntaxError;

					} else if (Util::startsWith(current_line, "["s) && Util::endsWith(current_line, "]"s)) {

						current_section = current_line.substr(1, current_line.length() - 2);

						continue;

					}

					if (current_line.length() == 0 || Util::startsWith(current_line, ";"s)) {

						continue;

					}

					lines[current_section].emplace_back(current_line);

				}

				in.close();

				for (auto& it : lines) {

					for (auto& line : it.second) {

						std::vector<std::string> splitted;

						for (size_t i = 0; i < line.length(); i++) {

							if (line.at(i) == '=') {

								splitted.emplace_back(line.substr(0, i - (line.at(i) == ' ' ? 1 : 0)));
								splitted.emplace_back(line.substr(i + 1, line.length() - (i + 1)));

								break;

							}

						}

						if (splitted.size() != 2) {

							this->values.clear();

							return ParseResult::ParseSyntaxError;

						} else {

							if (splitted[0].length() > 0) {

								if (splitted[0].at(splitted[0].length() - 1) == ' ') {

									splitted[0] = splitted[0].substr(0, splitted[0].length() - 1);

								}

							} else {

								this->values.clear();

								return ParseResult::ParseSyntaxError;

							}

							if (splitted[1].length() > 0) {

								if (splitted[1].at(0) == ' ') {

									splitted[1] = splitted[1].substr(1, splitted[1].length() - 1);

								}

							}

						}

						if (this->hasSection(it.first)) {

							if (this->values[it.first].find(splitted[0]) != this->values[it.first].end()) {

								this->values.clear();

								return ParseResult::ParseKeyDuplicate;

							}

						}

						this->values[it.first].insert(std::make_pair(splitted[0], splitted[1]));

					}

				}

				size_t len = 0;
				size_t len_l = 0;

				for (auto& it : this->values) {

					len += it.second.size();

				}

				for (auto& it : lines) {

					len_l += it.second.size();

				}

				if (len != len_l) {

					this->values.clear();

					return ParseResult::ParseUnknownError;

				}

				this->parsed = true;

				return ParseResult::ParseSuccessful;

			}

			/* returns the parsed values as a const unordered_map reference */
			inline const std::unordered_map<std::string, std::unordered_map<std::string, std::string>>& getParsedValues() const {

				return this->values;

			}
			/* returns the value of the key if it exists */
			inline 	const std::string& getValue(std::string key) const {

				for (auto& it : this->values) {

					if (it.second.find(key) != it.second.end()) {

						return it.second.at(key);

					}

				}

				throw std::runtime_error("Key doesn't exist.");

			}
			/* returns a whole section as a const unordered_map reference */
			inline const std::unordered_map<std::string, std::string>& getSection(std::string section) const {

				return this->values.at(section);

			}

			/* returns if the given key is parsed from the file */
			inline bool hasKey(std::string key, std::string section = "") const {

				if (section.length() == 0) {

					for (auto& it : this->values) {

						if (it.second.find(key) != it.second.end()) {

							return true;

						}

					}

					return false;

				} else {

					if (!this->hasSection(section)) {

						return false;

					}

					return this->values.at(section).find(key) != this->values.at(section).end();

				}

			}
			/* returns if the given section is parsed from the file */
			inline bool hasSection(std::string section) const {

				return this->values.find(section) != this->values.end();

			}

	};

}

#define EOUL_TOSTRING_CASE(parse) case parse: os << #parse; return os;

inline std::ostream& operator<<(std::ostream& os, const EOUL::Parser::ParseResult& result) {

	using namespace EOUL::Parser;

	switch (result) {

		EOUL_TOSTRING_CASE(ParseResult::ParseUnknownError)
		EOUL_TOSTRING_CASE(ParseResult::ParseFileStreamNotOpen)
		EOUL_TOSTRING_CASE(ParseResult::ParseSyntaxError)
		EOUL_TOSTRING_CASE(ParseResult::ParseSuccessful)
		EOUL_TOSTRING_CASE(ParseResult::ParseKeyDuplicate)

		default:

			return os;

	}

}

#undef EOUL_TOSTRING_CASE