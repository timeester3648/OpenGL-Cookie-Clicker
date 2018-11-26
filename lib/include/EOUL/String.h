#pragma once

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

namespace EOUL {

	namespace Util {

		/* returns if the given string starts with the given prefix */
		bool startsWith(const std::string& str, const std::string& prefix);
		/* returns if the given string ens with the given suffix */
		bool endsWith(const std::string& str, const std::string& suffix);
		/* returns if the given string contains a string */
		bool contains(const std::string& str, const std::string& part);

		/* returns a vector of strings splitted by the delimiter */
		std::vector<std::string> split_string(const std::string& str, char delim = ' ');

		/* fills a container with strings of the splitted string parts, based on the delimiter */
		template <class Container>
		void split_string(const std::string& str, Container& cont, char delim = ' ') {

			std::stringstream ss(str);
			std::string token;

			while (std::getline(ss, token, delim)) {

				cont.push_back(token);

			}

		}

	}

}