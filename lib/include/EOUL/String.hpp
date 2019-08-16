#pragma once

#include <Windows.h>

#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

namespace EOUL::Util {

	/* returns if the given string starts with the given prefix */
	template <typename StringType = std::string>
	inline bool startsWith(const StringType& str, const StringType& prefix) {

		return str.find(prefix) == 0;

	}
	/* returns if the given string ends with the given suffix */
	template <typename StringType = std::string>
	inline bool endsWith(const StringType& str, const StringType& suffix) {

		return str.find(suffix) == str.length() - suffix.length();

	}
	/* returns if the given string contains a string */
	template <typename StringType = std::string>
	inline bool contains(const StringType& str, const StringType& part) {

		return str.find(part) != StringType::npos;

	}

	/* converts a std::string to a std::wstring */
	inline std::wstring toWString(const std::string& str) {

		if (str.empty()) {

			return std::wstring();

		}

		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);

		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);

		return wstrTo;

	}
	/* converts a std::string to a std::wstring */
	inline std::string toString(const std::wstring& str) {

		if (str.empty()) {

			return std::string();

		}

		int size_needed = WideCharToMultiByte(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0, NULL, NULL);
		std::string strTo(size_needed, 0);

		WideCharToMultiByte(CP_UTF8, 0, &str[0], (int)str.size(), &strTo[0], size_needed, NULL, NULL);

		return strTo;

	}

	/* replaces a sequense of characters in a string */
	template <typename StringType = std::string>
	inline void replace(StringType& str, const StringType& toReplace, const StringType& toReplaceWith) {

		size_t pos;

		while ((pos = str.find(toReplace)) != std::string::npos) {

			str.replace(pos, toReplace.length(), toReplaceWith);

		}

	}

	/* returns a vector of strings splitted by the delimiter */
	template <typename StringType = std::string>
	inline std::vector<StringType> splitString(const StringType& str, StringType delimiter = " ") {

		std::vector<StringType> arr;

		splitString(str, arr, delimiter);

		return arr;

	}

	/* fills a container with strings of the splitted string parts, based on the delimiter */
	template <class Container, typename StringType = std::string>
	inline void splitString(Container& cont, const StringType& str, StringType delimiter = " ") {

		size_t startIndex = 0;
		size_t endIndex = 0;

		while ((endIndex = str.find(delimiter, startIndex)) < str.size()) {

			StringType val = str.substr(startIndex, endIndex - startIndex);

			cont.push_back(val);

			startIndex = endIndex + delimiter.size();

		}

		if (startIndex < str.size()) {

			StringType val = str.substr(startIndex);

			cont.push_back(val);

		}

	}

}