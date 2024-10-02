/* emptyMain.cpp
===Coding Convention===

 - Indenting block: Visual Studio Code default size

 - Opening braces on a line by themselves

 - '=' must be surrounded by spaces.

 - There must be a space after commas and colons

 - Must write module name at the top of module.h file.

 - Function name starts with a capitalized letter and capitalizes for each words
    ScenarioControl()

 - A variable name should start with a lowercase letter and capitalizes for words except for the first word
    customer

 - For both header and implementation file, code version history is written latest first
    REVISION HISTORY:
    Rev. 2 - 24/07/04 Updated function by member2
    Rev. 1 - 24/07/03 Original by member1

 - Each major section of a listing is separated by a dividing comment line with '-'
    //---------------------

 - On the header file only, describe the module and explain the cohesion and encapsulation that the module offers
    right after the code version history, separated by the dividing comment

 - Function prototype format
/*
    // Function Description 
    // ------------------------------------------------------------------
    // int ScenarioControl(
    //     int choice,     // in: Indicates the choice made in the main menu
    //     int subchoice   // in: Indicates the choice made in a sub menu
    // );
    // 
*/