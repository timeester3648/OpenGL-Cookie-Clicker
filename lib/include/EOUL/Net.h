#pragma once

#include <string>
#include <Windows.h>

namespace EOUL {

	namespace Net {

		/* downloads a file from the given url to the given path */
		HRESULT download(std::string url, std::string path);

		/* returns if the current pc has a internet connection */
		bool hasInternet();

		/* performes a https get request */
		std::string httpsGetRequest(std::string url);
		/* performes a http get request */
		std::string httpGetRequest(std::string url);

	}

}