#include "hide_console.h"
#include "auto_run_add_directory.h"
int main() {
    AbstractHideConsole* hide = new HideConsole();
    hide->Hide();
    AbstractAutoRun* auto_run = new AutoRunAddDirectory();
    auto_run->AutoRun();



    return 0;
}