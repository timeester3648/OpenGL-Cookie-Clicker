#pragma once

#include <filesystem>
#include <Windows.h>

namespace EOUL::Process {

	struct ExecuteProperties {

		bool showCommandPrompt = false;
		bool waitBlockThread = false;

		unsigned int waitTime = INFINITE;

	};

	/* executes a program */
	inline void execute(const std::filesystem::path& program, const std::string& parameters = "", bool waitBlockThread = false) {

		SHELLEXECUTEINFOA info = {};

		info.cbSize = sizeof(SHELLEXECUTEINFO);
		info.fMask = SEE_MASK_NOCLOSEPROCESS | (waitBlockThread ? SEE_MASK_NOASYNC : 0);
		info.hwnd = NULL;
		info.lpVerb = NULL;
		info.lpFile = program.u8string().c_str();
		info.lpParameters = parameters.c_str();
		info.lpDirectory = NULL;
		info.nShow = SW_HIDE;
		info.hInstApp = NULL;

		ShellExecuteExA(&info);

		WaitForSingleObject(info.hProcess, INFINITE);
		CloseHandle(info.hProcess);

	}
	/* executes a program */
	inline void execute(const std::filesystem::path& program, const std::string& parameters, const ExecuteProperties& properties) {

		SHELLEXECUTEINFOA info = {};

		info.cbSize = sizeof(SHELLEXECUTEINFO);
		info.fMask = SEE_MASK_NOCLOSEPROCESS | (properties.waitBlockThread ? SEE_MASK_NOASYNC : 0);
		info.hwnd = NULL;
		info.lpVerb = NULL;
		info.lpFile = program.u8string().c_str();
		info.lpParameters = parameters.c_str();
		info.lpDirectory = NULL;
		info.nShow = (properties.showCommandPrompt ? SW_SHOW : SW_HIDE);
		info.hInstApp = NULL;

		ShellExecuteExA(&info);

		WaitForSingleObject(info.hProcess, INFINITE);
		CloseHandle(info.hProcess);

	}
	/* executes a program */
	inline void execute(SHELLEXECUTEINFO properties) {

		ShellExecuteEx(&properties);

		WaitForSingleObject(properties.hProcess, INFINITE);
		CloseHandle(properties.hProcess);

	}

}