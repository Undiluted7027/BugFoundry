/* ErrorMessages.cpp
REVISION HISTORY:
Rev. 1 - 24/07/13 Original by Jason Lee 
--------------------------------------------------------------------*/
#include "../include/ErrorMessages.hpp"

int YesNoError(char msg)
{
    if (msg != 'Y' || msg != 'N')
    {
        cout << "Error: Your input is neither Y nor N. Canceled the action" << endl;
        return 1;
    }
    return 0;
}

/*
Checks if the provided msg is neither 'Y' or 'N'.
--------------------------------------------------------------------*/
int NameError(char *msg)
{
    if (strlen(msg) == 0)
    {
        cout << "Error: Your name cannot exceed 30 characters" << endl;
        return 1;
    } 
    return 0;
}

/*
Checks if the provided msg is empty.
--------------------------------------------------------------------*/
int EmailError(char *msg)
{
    if (strlen(msg) == 0)
    {
        cout << "Error: Email input has to contain '@' and cannot exceed 24 maximum characters" << endl;
        return 1;
    } 
    for (int i = 0; i < int(strlen(msg)); i++)
    {
        if (msg[i] == '@') return 0;
    }
    cout << "Error: Email input has to contain '@' and cannot exceed 24 maximum characters" << endl;
    return 1;
}

/*
Checks if the provided msg is empty or does not contain the '@' chracter.
--------------------------------------------------------------------*/
int PhoneError(char *msg)
{
    if (strlen(msg) > 11) 
    {
        cout << "Phone number input must follow format [1]DDDDDDDDDD where D is a digit" << endl;
        return 1;
    }
    for (int i = 0; i < int(strlen(msg)); i++)
    {
        if (msg[i] > '9' || msg[i] < '0')
        {
            cout << "Phone number input must follow format [1]DDDDDDDDDD where D is a digit" << endl;
            return 1;
        }
    }
    return 0;
}

/*
Checks if the provided msg exceeds 11 characters or contains non-digit characters.
--------------------------------------------------------------------*/
int DeptError(char msg)
{
    if (msg != 'S' || msg != 'M' || msg != ' ')
    {
        cout << "Error: Please enter nothing for the customer, S for the software engineer, or M for the marketer" << endl;
        return 1;
    }
    return 0;
}

/*
Checks if the provided msg is not 'S' or 'M' or ' '.
--------------------------------------------------------------------*/
int DescError(char *msg)
{
    if (strlen(msg) == 0)
    {
        cout << "Error: Description cannot exceed 30 characters" << endl;
        return 1;
    }
    return 0;
}

/*
Checks if the provided msg is empty for Description.
--------------------------------------------------------------------*/
int ProductError(char *msg)
{
    if (strlen(msg) == 0)
    {
        cout << "Error: Product name must be max 10 characters" << endl;
        return 1;
    }
    return 0;
}

/*
Checks if the provided msg is empty for Product name.
--------------------------------------------------------------------*/
int DateError(char *msg)
{
    for (int i = 0; i < 4; i++)
    {
        if (msg[i] < '0' && msg[i] > '9')
        {
            cout << "Error: The date must be in the format of YYYY-MM-DD" << endl;
            return 1;
        }
    }
    if (msg[4] != '-' && msg[7] != '-')
    {
        cout << "Error: The date must be in the format of YYYY-MM-DD" << endl;
        return 1;
    }
    if (msg[5] == '1')
    {
        if (msg[6] > '2' || msg[6] < 0)
        {
            cout << "Error: The date must be in the format of YYYY-MM-DD" << endl;
            return 1;
        }
    }
    if (msg[5] == '0')
    {
        if (msg[6] < '0' && msg[6] > '9')
        {
            cout << "Error: The date must be in the format of YYYY-MM-DD" << endl;
            return 1;
        }
    }
    if (msg[8] < '0' && msg[8] > '3')
    {
        cout << "Error: The date must be in the format of YYYY-MM-DD" << endl;
        return 1;
    }
    if (msg[9] < '0' && msg[9] > '9')
    {
        cout << "Error: The date must be in the format of YYYY-MM-DD" << endl;
        return 1;
    }
    return 0;
}

/*
Validates if msg correctly follows 'YYYY-MM-DD' format, checking each charater's position and range to verify its correctness.
--------------------------------------------------------------------*/
int ReleaseIDError(char *msg)
{
    if (strlen(msg) == 0)
    {
        cout << "Error: releaseID must be max 8 characters" << endl;
        return 1;
    }
    return 0;
}

/*
Checks if the provided msg is empty for releaseID.
--------------------------------------------------------------------*/
int ChangeIDError(char *msg)
{
    if (strlen(msg) == 0)
    {
        cout << "Error: releaseID must be max 6 digits" << endl;
        return 1;
    }
    for (unsigned int i = 0; i < strlen(msg); i++)
    {
        if (msg[i] > '9' && msg[i] < '0')
        {
            cout << "Error: releaseID must be max 6 digits" << endl;
            return 1;
        }
    }
    return 0;
}

/*
Checks if the provided msg is empty or contains non-digit characters for releaseID.
--------------------------------------------------------------------*/
int StateError(char state)
{
    if (state != 'X' || state != 'P' || state != 'O')
    {
        cout << "Error: Status must be CANCELED, INPROGRESS, or DONE" << endl;
        return 1;
    }
    return 0;
}

/*
Validates the msg matches one of the valid states ("CANCELED", "INPROGRESS", or "DONE").
--------------------------------------------------------------------*/
int PriorityError(int level)
{
    if (level > 5 || level < 1)
    {
        cout << "Error: Priority level must be a number in the range of 1 and 5 being the highest" << endl;
        return 1;
    }
    return 0;
}

/*
Checks if the provided level falls within the range of 1-5.
--------------------------------------------------------------------*/
int DisplayPageError(int choice)
{
    if (choice != 0 && choice != 1)
    {
        cout << "Error: Please type 1 to go to the next page, or 0 to quit" << endl;
        return -1;
    }
    return choice;
}

/*
Validates if the provided integer choice is either 0 or 1.
--------------------------------------------------------------------*/
int SearchPageError(int choice, int lowest, int highest)
{
    if (choice != 0 && choice != 1 && (choice > highest || choice < lowest))
    {
        cout << "Please type the number of a shown item, or 1 to go to the next page, or 0 to quit" << endl;
        return -1;
    }
    return choice;
}

/*
Checks if choice is either 0 or 1 and choice falls within the range of what is defined from 'highest' to 'lowest'.
--------------------------------------------------------------------*/