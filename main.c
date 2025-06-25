#include "contact.h"
#include <stdlib.h>
#include <stdio_ext.h> 

void savecontact(AddressBook *addressBook);
int main() 
{          
    AddressBook addressBook;
    int option;
    //all function calls should be inside the main 
    // initialise address book
    initialize(&addressBook);  
    // give the user options to add edit search delete and exit
    while(1)
    {  
        printf("\n");
        printf("----------------------Operation to be performed---------------------------\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List Contact\n");
        printf("6. Save Contact\n");
        printf("7. Exit\n");

        // read the options from user to perform operation
        printf("Enter the option from 1 - 7 : ");
        scanf("%d",&option);
        // clear input buffer
        __fpurge(stdin);
        switch(option)
        {
            case 1:
                    createContact(&addressBook);
                    break;
            case 2:
                    searchContact(&addressBook);
                    break;
            case 3: 
                    editContact(&addressBook);
                    break;
            case 4:
                    deleteContact(&addressBook);
                    break;
            case 5:
                    listContacts(&addressBook);
                    break;
            case 6:
                    savecontact(&addressBook);
                    break;
            case 7:
                    exit(0);
            default:
                    printf("Inavlid option! \n");
                    printf("Please enter the option in range between (1 - 7) \n");        
        }
    }
    return 0;
}

