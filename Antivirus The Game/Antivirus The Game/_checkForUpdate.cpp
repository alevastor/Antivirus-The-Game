#include "main.h"
#include <wininet.h>
#pragma comment (lib, "wininet.lib")
#include <urlmon.h>
#pragma comment (lib, "urlmon.lib")
#include <sstream>

bool isNewUpdate(bool fromStart)
{
	std::wstring URL, FileName;
	URL = L"http://justfileserver.at.ua/AntivirusGame/GameVersion.txt";
	CreateDirectory("update",NULL);
	FileName = L"update\\gameVersion.txt";
	DeleteUrlCacheEntryW(URL.c_str());
	if(InternetCheckConnectionW(URL.c_str(),FLAG_ICC_FORCE_CONNECTION,0))
	{
		HRESULT hr = URLDownloadToFileW( 0, URL.c_str(), FileName.c_str(), 0, 0);
		if(hr!=S_OK)
		{
			ifstream gameVersionFile;
			string s;
			gameVersionFile.open("update\\gameVersion.txt");
			while(!gameVersionFile.eof())
			{
				getline(gameVersionFile,s);
			}
			if(s!=GAME_VERSION)
				return true;
			else
				return false;
	    }
		else
		{
			if(!fromStart)
			{
				stringstream ss;
				ss << "An error occured : error code = 0x" <<  hex << hr;
				MessageBox(NULL,ss.str().c_str(),"Connection Error",MB_OK | MB_ICONERROR);
			}
			return false;
		}
	}
	else
	{
		if(!fromStart)
		{
			stringstream ss;
			ss << "An error occured : error code = 0x" << GetLastError();
			MessageBox(NULL,ss.str().c_str(),"Connection Error",MB_OK | MB_ICONERROR);
		}
		return false;
	}
}