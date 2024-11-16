#ifndef ERRORMESSAGES_HPP
#define ERRORMESSAGES_HPP

/* ErrorMessages.hpp
REVISION HISTORY:
Rev. 1 - 24/07/13 Original by Jason Lee 
--------------------------------------------------------------------

------------------------------------------------------------------*/
#include <iostream>
#include <string.h>
using namespace std;
/*--------------------------------------------------------------------
// Exported constants/types/variables
This module does not export any constant/types/variables

--------------------------------------------------------------------*/
// This module does not include any classes

/*
Prints the error message when user failed to interact with yes or no prompt.
--------------------------------------------------------------------*/
int YesNoError(
    char msg        // in: The choice input 
);
/*
Prints the error message when user failed to input their name within standard.
--------------------------------------------------------------------*/
int NameError(
    char *msg       // in: The name input
);
/*
Prints the error message when user failed to input their email within standard.
--------------------------------------------------------------------*/
int EmailError(
    char *msg       // in: The email input
);
/*
Prints the error message when user failed to input their phone within standard.
--------------------------------------------------------------------*/
int PhoneError(
    char *msg       // in: The phone input
);
/*
Prints the error message when user failed to input their department within standard.
--------------------------------------------------------------------*/
int DeptError(
    char msg        // in: The department input
);
/*
Prints the error message when user failed to input their description within standard.
--------------------------------------------------------------------*/
int DescError(
    char *msg       // in: The description input 
);
/*
Prints the error message when user failed to input the product name within standard.
--------------------------------------------------------------------*/
int ProductError(
    char *msg       // in: The product name input
);
/*
Prints the error message when user failed to input the date format correctly.
--------------------------------------------------------------------*/
int DateError(
    char *msg       // in: The date input 
);
/*
Prints the error message when user failed to input the releaseID in correct format.
--------------------------------------------------------------------*/
int ReleaseIDError(
    char *msg       // in: The releaseID input
);
/*
Prints the error message when user failed to input ChangeID in correct format
--------------------------------------------------------------------*/
int ChangeIDError(
    char *msg       // in: The ChangeID input
);
/*
Prints the error message when user failed to input state in correct format
--------------------------------------------------------------------*/
int StateError(
    char *msg       // in: The state input
);
/*
Prints the error message when user failed to input priority level in correct format
--------------------------------------------------------------------*/
int PriorityError(
    int level       // in: The priority input
);
/*
Prints the error message when user failed to input display page in correct format
--------------------------------------------------------------------*/
int DisplayPageError(
    int choice      // in: The display page input
);
/*
Prints the error message when user failed to interact with searching in pages in correct format
--------------------------------------------------------------------*/
int SearchPageError(
    int choice,     // in: The choice in page input
    int lowest,     // in: The lowest possible choice at the page
    int highest     // in: The highest possible choice at the page
);

#endif