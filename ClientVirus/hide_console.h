#pragma once
#include<windows.h>


#include"abstract_hide_console.h"
class HideConsole : public AbstractHideConsole{
public:
	bool Hide() {
		auto hConsole = GetConsoleWindow();
		return ShowWindow(hConsole, SW_HIDE);
	}
};

