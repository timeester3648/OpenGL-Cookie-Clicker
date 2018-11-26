#include "../../header/util/Formatter.h"
#include "../../header/game/GameSettings.h"

#include <iostream>

std::vector<Formatter::Abbreviation> Formatter::abbreviations;
std::vector<std::string> Formatter::longPrefixes, Formatter::longSuffixes, Formatter::shortPrefixes, Formatter::shortSuffixes;

void Formatter::init() {

	abbreviations = {

		{"",  ""},
		{"k", "thousand"},
		{"M", "million"},
		{"B", "billion"},
		{"T", "trillion"},
		{"Qa", "quadrillion"},
		{"Qi", "quintillion"},
		{"Sx", "sextillion"},
		{"Sp", "septillion"},
		{"Oc", "octillion"},
		{"No", "nonillion"}

	};

	longPrefixes = { "", "un", "duo", "tre", "quattuor", "quin", "sex", "septen", "octo", "novem" };
	longSuffixes = { "decillion", "vigintillion", "trigintillion", "quadragintillion", "quinquagintillion", "sexagintillion", "septuagintillion", "octogintillion", "nonagintillion" };
	shortPrefixes = { "", "Un", "Do", "Tr", "Qa", "Qi", "Sx", "Sp", "Oc", "No" };
	shortSuffixes = { "D", "V", "T", "Qa", "Qi", "Sx", "Sp", "O", "N" };

	for (size_t i = 0; i < longSuffixes.size(); i++) {

		for (size_t j = 0; j < longPrefixes.size(); j++) {

			abbreviations.push_back({ (shortPrefixes[j] + shortSuffixes[i]), (longPrefixes[j] + longSuffixes[i]) });

		}

	}

	abbreviations[11].short_name = "Dc";

}

std::string Formatter::formatCookies(long double cookies, int max_after_comma) {

	std::string tmp = std::to_string(cookies);

	for (size_t i = tmp.length() - 1; i >= 0 && i != -1; i--) {

		if (tmp.at(i) == '.') {

			if (i + 1 + max_after_comma < tmp.length() && max_after_comma != 0) {

				tmp = tmp.substr(0, i + 1 + max_after_comma);

			} else if (max_after_comma == 0) {

				tmp = tmp.substr(0, i);

			}

			break;

		}

	}

	if (cookies < 1000000 || !GameSettings::short_numbers) {

		return beautify(tmp);

	}

	bool hasDot = tmp.find(".") != std::string::npos;
	std::string temp = tmp;

	if (hasDot) {

		for (size_t i = tmp.length() - 1; i >= 0 && i != -1; i--) {

			if (tmp.at(i) == '.') {

				temp = tmp.substr(0, i);

				break;

			}

		}

	}

	size_t start_len = 0;
	size_t add = 3;
	size_t i = 0;

	for (; i < abbreviations.size(); i++) {

		if (start_len + i * 3 + 1 == temp.length() || start_len + i * 3 + 2 == temp.length() || start_len + i * 3 + 3 == temp.length()) {

			break;

		}

	}

	std::string result = temp.substr(0, temp.length() - (start_len + i * 3));
	std::string end = temp.substr(result.length(), temp.length() - result.length() - 1);

	while (end.length() < 3) {

		end += "0";

	}

	bool went = false;

	if (!(end.at(0) == '0' && end.at(1) == '0' && end.at(2) == '0')) {

		went = true;

		char& f = end.at(0);
		char& s = end.at(1);
		char& t = end.at(2);

		if (end.length() >= 3 && end.at(3) >= '5') {

			if (t < '9') {

				t++;

			} else {

				if (s < '9') {

					t = '0';
					s++;

				} else {

					if (f < '9') {

						t = '0';
						s = '0';
						f++;

					} else {

						t = '0';
						s = '0';
						f = '0';

						bool could = false;
						for (size_t j = result.length() - 1; j >= 0 && j != -1; j--) {

							if (result.at(j) == '9') {

								result.at(j) = '0';

							} else {

								result.at(j)++;
								could = true;

								break;

							}

						}

						if (!could) {

							std::string str = "1";

							for (size_t j = result.length() - 1; j >= 0 && j != -1; j--) {

								str += "0";

							}

							if (str.length() >= 4) {

								i++;

								str = "1";

							}

							return beautify(str) + " " + abbreviations[i].long_name;

						}

					}

				}

			}

		}

		result += "." + end.substr(0, 3);

		while (result.at(result.length() - 1) == '0') {

			result.erase(result.length() - 1);

		}

		if (result.at(result.length() - 1) == '.') {

			result.erase(result.length() - 1);

		}

	}

	if (!went) {

		result = result.substr(0, result.length() - (start_len + i * 3));

	}

	return result + " " + abbreviations[i].long_name;

}

std::string Formatter::beautify(std::string num) {

	bool hasDot = num.find(".") != std::string::npos;
	size_t i = num.length() - 1;

	if (hasDot) {

		for (size_t ii = num.length() - 1; ii >= 0 && ii != -1; ii--) {

			if (num.at(ii) == '.') {

				i = ii - 1;

			}

		}

	}

	size_t j = 0;
	for (; i >= 0 && i != -1; i--) {

		if (j == 3) {

			num.insert(i + 1, ",");

			j = 0;

		}

		j++;

	}

	while (num.at(num.length() - 1) == '0' && hasDot) {

		num.erase(num.length() - 1);

	}

	if (num.at(num.length() - 1) == '.') {

		num.erase(num.length() - 1);

	}

	return num;

}