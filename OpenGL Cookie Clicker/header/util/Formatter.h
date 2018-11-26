#pragma once

#include <string>
#include <vector>

class Formatter {

	private:

		struct Abbreviation {

			std::string short_name, long_name;

		};

	private:

		static std::vector<Abbreviation> abbreviations;
		static std::vector<std::string> longPrefixes, longSuffixes, shortPrefixes, shortSuffixes;

	private:

		static std::string beautify(std::string num);

	public:

		static std::string formatCookies(long double cookies, int max_after_comma = 3);

		static void init();

};