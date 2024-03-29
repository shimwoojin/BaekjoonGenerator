#include "stdafx.h"
#include "ConnectSystem.h"

ConnectSystem::ConnectSystem()
{
	chrome_directory = L"C://Program Files/Google/Chrome/Application/chrome.exe";
}

bool ConnectSystem::ConnectTo(std::string address)
{
	std::wstring converted_address(address.begin(), address.end());

	HINSTANCE handle = ShellExecute(NULL, NULL, chrome_directory.c_str(), converted_address.c_str(), NULL, SW_HIDE);
	
	return true;
}
