/* Main.cpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Sanchit Jain
----------------------------------------------------------------------
This CPP file called Main.cpp handles the startup of the program, calls required functions and passes the control scope to ScenarioControl and activatesUI. It also mentions the coding convention used in this assignment.
--------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
// #include "ScenarioControl.cpp"
#include "UI.cpp"

using namespace std;

//-----------------------------------------------------------------------
int Startup()
{
    return InitControl();
}
/* 
int Startup(const string FILENAMES[]) checks if binary files exist in the DIRECTORY 
to essentially check if the program is being run for the first time. 
If they do, then it returns 0, if they don't then the files are created. 
If files were created successfully, it returns 1 else -1. The function does not fail.
----------------------------------------------------------------------*/
int main()
{
    int startupFlag = Startup();
    switch (startupFlag)
    {
        case 0:
            cerr << "Startup failed" << endl;
            return 1;
        default:
            cout << "Startup successful" << endl;
        Start(); // Calling UI
    }
    return 0;
}