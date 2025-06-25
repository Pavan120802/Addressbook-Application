#include "contact.h"
#include <stdio_ext.h>
#include <ctype.h>  
#include <string.h>      
int validate_name(const char *name)
{
    for(int i = 0; name[i] != '\0'; i++)
    {
        if(!isalpha(name[i]) && name[i] != ' ')
        {
            printf("The name should contain only alphabets and space \n");
            return 0; // invalid
        }
    }
    return 1; // valid
}
int validate_phone(const char *phone) 
{
    int len = strlen(phone);
    if(len != 10)
        {
            printf("The phone number should contain only 10 numbers \n");
            return 0; //invalid
        }
    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
        {
            printf("The Phone Number should contain integers only \n");
            return 0; //invalid
        }
    }
    return 1; //valid
}
int validate_email(const char *email)
{
    for(int i = 0; email[i] != '\0'; i++)
    {
        if(strchr(email, '@') == NULL || strstr(email, ".com") == NULL || strstr(email, ".com") < strchr(email, '@'))
        {
            printf("Please enter valid email containing @ and .com\n");
            return 0; //invalid
        }
    }
    return 1; //valid
}

void initialize(AddressBook *addressBook) 
{
    FILE *file = fopen("contact.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char temp[100];
    addressBook->contactCount = 0;

    while (fscanf(file, "%99[^\n]\n", temp) != EOF) 
    {
        char *name = strtok(temp, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");

        if (name && phone && email) {
            strncpy(addressBook->contacts[addressBook->contactCount].name, name, sizeof(addressBook->contacts[addressBook->contactCount].name) - 1);
            strncpy(addressBook->contacts[addressBook->contactCount].phone, phone, sizeof(addressBook->contacts[addressBook->contactCount].phone) - 1);
            strncpy(addressBook->contacts[addressBook->contactCount].email, email, sizeof(addressBook->contacts[addressBook->contactCount].email) - 1);

            addressBook->contactCount++;
        }
    }

    fclose(file);
}

void listContacts(AddressBook *addressBook) 
{ 
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts available!\n");
        return;
    } 
    printf("\nList of Contacts:\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("Sl.no     name       Phone number            email   \n");
    printf("-----------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%d.      %-14s%-17s%s\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("\nPress any key to continue : ");
    char temp;
    scanf("%c", &temp); 
}

void createContact(AddressBook *addressBook) 
{
    char temp_name[100], temp_phone[100], temp_email[100];
    printf("\n");
    __fpurge(stdin);
    printf("Enter the name : ");
    scanf("%99[^\n]",temp_name);
    if(!validate_name(temp_name)) return;
    // if name alredy exists in addressbook exit or return
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcasecmp(addressBook->contacts[i].name, temp_name) == 0)
        {
        printf("The name already exists in the contacts\n");
        return;
        }
    }

    // for phone number
    __fpurge(stdin);
    printf("Enter Phone Number: ");
    scanf("%99[^\n]",temp_phone);
    if(!validate_phone(temp_phone)) return;
    // if phone alredy exists in addressbook exit or return
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, temp_phone) == 0)
        {
        printf("The Phone number already exists in the contacts\n");
        return;
        }
    }
    // for email
     __fpurge(stdin);
    printf("Enter Email: ");
    scanf("%99[^\n]",temp_email);
    if(!validate_email(temp_email)) return;
    // if email alredy exists in addressbook exit or return
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, temp_email) == 0)
        {
        printf("The email already exists in the contacts\n");
        return;
        }
    }

    // if name phone and email are unique add it to the addressbook
    strcpy(addressBook->contacts[addressBook->contactCount].name, temp_name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, temp_phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, temp_email);
    (addressBook->contactCount)++; 
    printf("Contact added successfully\n");
    printf("\n");
    __fpurge(stdin);
    printf("Press any key to continue : ");
    char temp;
    scanf("%c", &temp);
}

void searchContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to search!\n");
        return;
    }

    int search;
    char searchh[100];
    int found = 0;
    int j = 0;
    printf("Search Contact by:\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &search);
    __fpurge(stdin);
    printf("Enter your search: ");
    scanf("%s", searchh);
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        int flag = 0;
        switch (search) 
        {
            case 1:
                if (strcasestr(addressBook->contacts[i].name, searchh)) flag = 1;
                break;
            case 2:
                if (strcasestr(addressBook->contacts[i].phone, searchh)) flag = 1;
                break;
            case 3:
                if (strcasestr(addressBook->contacts[i].email, searchh)) flag = 1;
                break;
            default:
                printf("Invalid option selected.\n");
                return;
        }
        if (flag && found == 0) 
        {
            printf("\n-------------------------------Contact found----------------------------------\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("Sl.no     name       Phone number            email   \n");
            printf("-----------------------------------------------------------------------------\n");
        }
        // Print the matched contact
        if (flag) 
        {
            printf("%d.      %-14s%-17s%s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            found = 1;  // flag == 1 --> contact was found
            j++;
        }
    }
    if (!found) 
    {
        printf("No contact found matching the search query!\n");
    }
    __fpurge(stdin);
    printf("\nPress any key to continue : ");
    char temp;
    scanf("%c", &temp);
}

void editContact(AddressBook *addressBook) 
{
    char edit_phone[100],edit_name[100],edit_email[100];
    char new_phone[100],new_name[100],new_email[100];
    int edit,j = 0;
    printf("\n");
    printf("--------------Edit Contact----------------\n");
    printf("1. Edit contact by Name\n");
    printf("2. Edit contact by Phone\n");
    printf("3. Edit contact by email\n");
    printf("Enter your choise 1 - 3 : ");
    scanf("%d",&edit);
    __fpurge(stdin);
    switch(edit)
    {
        case 1:
                printf("Enter the name to be edited : ");
                scanf("%99[^\n]",edit_name);
                __fpurge(stdin);
                int found_name = 0;
                // chech for matching name in addressbook
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcasecmp(addressBook->contacts[i].name, edit_name) == 0)
                    {
                        found_name = 1;
                        printf("\n-------------------------------Contact found----------------------------------\n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("Sl.no     name       Phone number            email   \n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("%d.      %-14s%-17s%s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        j++;
                        printf("\n");

                        //edit the contact
                        __fpurge(stdin);
                        printf("Enter new name: ");
                        scanf("%99[^\n]",new_name);
                        if(!validate_name(new_name)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].name, new_name) == 0)
                            {
                                printf("The name already exists in the contacts\n");
                            return;
                            }
                        }
                    
                        __fpurge(stdin);
                        printf("Enter new phone: ");
                        scanf("%99[^\n]",new_phone);
                        if(!validate_phone(new_phone)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].phone, new_phone) == 0)
                            {
                                printf("The phone already exists in the contacts\n");
                            return;
                            }
                        }
                        
                        __fpurge(stdin);
                        printf("Enter new email: ");
                        scanf("%99[^\n]",new_email);
                        if(!validate_email(new_email)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].email, new_email) == 0)
                            {
                                printf("The email already exists in the contacts\n");
                            return;
                            }
                        }
                        strcpy(addressBook->contacts[i].name, new_name);
                        strcpy(addressBook->contacts[i].phone, new_phone);
                        strcpy(addressBook->contacts[i].email, new_email);
                        printf("\n");
                        printf("Contact Updated successfully\n");
                        return;
                    }
                }
                if (!found_name) 
                {
                    printf("Entered Contact not found\n");
                }
                break;
        case 2: 
                printf("Enter the phone to be edited : ");
                scanf("%99[^\n]",edit_phone);
                __fpurge(stdin);
                int found_phone = 0;
                // check for matching phone in addressbook
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcasecmp(addressBook->contacts[i].phone, edit_phone) == 0)
                    {
                        found_phone = 1;
                        printf("\n-------------------------------Contact found----------------------------------\n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("Sl.no     name       Phone number            email   \n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("%d.      %-14s%-17s%s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        j++;
                        printf("\n");

                        //edit the contact
                        __fpurge(stdin);
                        printf("Enter new name: ");
                        scanf("%99[^\n]",new_name);
                        if(!validate_name(new_name)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].name, new_name) == 0)
                            {
                                printf("The name already exists in the contacts\n");
                            return;
                            }
                        }
                        
                        __fpurge(stdin);
                        printf("Enter new phone: ");
                        scanf("%99[^\n]",new_phone);
                        if(!validate_phone(new_phone)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].phone, new_phone) == 0)
                            {
                                printf("The phone already exists in the contacts\n");
                            return;
                            }
                        }
                        
                        __fpurge(stdin);
                        printf("Enter new email: ");
                        scanf("%99[^\n]",new_email);
                        if(!validate_email(new_email)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].email, new_email) == 0)
                            {
                                printf("The email already exists in the contacts\n");
                            return;
                            }
                        }
                        strcpy(addressBook->contacts[i].name, new_name);
                        strcpy(addressBook->contacts[i].phone, new_phone);
                        strcpy(addressBook->contacts[i].email, new_email);
                        printf("\n");
                        printf("Contact Updated successfully\n");
                        return;
                    }
                }
                if (!found_phone) 
                {
                    printf("Entered Contact not found\n");
                }
                break;
        case 3: 
                printf("Enter the email to be edited : ");
                scanf("%99[^\n]",edit_email);
                __fpurge(stdin);
                int found_email = 0;
                // chech for matching email in addressbook
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcasecmp(addressBook->contacts[i].email, edit_email) == 0)
                    {
                        found_email = 1;
                        printf("\n-------------------------------Contact found----------------------------------\n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("Sl.no     name       Phone number            email   \n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("%d.      %-14s%-17s%s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        j++;
                        printf("\n");

                        //edit the contact
                        __fpurge(stdin);
                        printf("Enter new name: ");
                        scanf("%99[^\n]",new_name);
                        if(!validate_name(new_name)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].name, new_name) == 0)
                            {
                                printf("The name already exists in the contacts\n");
                            return;
                            }
                        }
                        
                        __fpurge(stdin);
                        printf("Enter new phone: ");
                        scanf("%99[^\n]",new_phone);
                        if(!validate_phone(new_phone)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].phone, new_phone) == 0)
                            {
                                printf("The phone already exists in the contacts\n");
                            return;
                            }
                        }
                        
                        __fpurge(stdin);
                        printf("Enter new email: ");
                        scanf("%99[^\n]",new_email);
                        if(!validate_email(new_email)) return;
                        for(int i = 0; i < addressBook->contactCount; i++)
                        {
                            if(strcasecmp(addressBook->contacts[i].email, new_email) == 0)
                            {
                                printf("The email already exists in the contacts\n");
                            return;
                            }
                        }
                        strcpy(addressBook->contacts[i].name, new_name);
                        strcpy(addressBook->contacts[i].phone, new_phone);
                        strcpy(addressBook->contacts[i].email, new_email);
                        printf("\n");
                        printf("Contact Updated successfully\n");
                        return;
                    }
                }
                if (!found_email) 
                {
                    printf("Entered Contact not found\n");
                }
                break;
        default: 
                printf("Enter valid option\n");
                return;  
    }
}

void deleteContact(AddressBook *addressBook) 
{
    char delete_phone[100],delete_name[100],delete_email[100];
    int delete;
    int found = 0,j = 0;
    char ch;
    printf("\n");
    printf("--------------Delete Contact----------------\n");
    printf("1. Delete contact by Name\n");
    printf("2. Delete contact by Phone\n");
    printf("3. Delete contact by email\n");
    printf("Enter your choise 1 - 3 : ");
    scanf("%d",&delete);
    __fpurge(stdin);
    switch(delete)
    {
        case 1:
                printf("Enter the name to be deleted : ");
                scanf("%99[^\n]",delete_name);
                // chech for matching name in addressbook
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcasecmp(addressBook->contacts[i].name, delete_name) == 0)
                    {
                        found = 1;
                        printf("\n-------------------------------Contact found----------------------------------\n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("Sl.no     name       Phone number            email   \n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("%d.      %-14s%-17s%s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        printf("\n");
                        printf("Press any key to confirm deletion or 'q' to cancel: ");
                    scanf(" %c", &ch);  
                    printf("\n");
                    __fpurge(stdin);

                    if (ch != 'q' && ch != 'Q')
                    {
                        // Delete the contact
                        for(int j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully!\n");
                    }
                    else
                    {
                        printf("Contact deletion cancelled.\n");
                    }
                    return;
                    }
                }
                if (!found) 
                {
                    printf("Entered Contact not found\n");
                }
                break;
        case 2:
                printf("Enter the phone to be deleted : ");
                scanf("%99[^\n]",delete_phone);
                // chech for matching phone in addressbook
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcasecmp(addressBook->contacts[i].phone, delete_phone) == 0)
                    {
                        found = 1;
                        printf("\n-------------------------------Contact found----------------------------------\n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("Sl.no     name       Phone number            email   \n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("%d.      %-14s%-17s%s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        printf("\n");
                        printf("Press any key to confirm deletion or 'q' to cancel: ");
                    scanf(" %c", &ch);  
                    __fpurge(stdin);

                    if (ch != 'q' && ch != 'Q')
                    {
                        // Delete the contact
                        for(int j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully!\n");
                    }
                    else
                    {
                        printf("Contact deletion cancelled.\n");
                    }
                    return;
                    }
                }
                if (!found) 
                {
                    printf("Entered Contact not found\n");
                }
                break;
        case 3:
                printf("Enter the email to be deleted : ");
                scanf("%99[^\n]",delete_email);
                // chech for matching name in addressbook
                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcasecmp(addressBook->contacts[i].email, delete_email) == 0)
                    {
                        found = 1;
                        printf("\n-------------------------------Contact found----------------------------------\n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("Sl.no     name       Phone number            email   \n");
                        printf("-----------------------------------------------------------------------------\n");
                        printf("%d.      %-14s%-17s%s\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        printf("\n");
                        printf("Press any key to confirm deletion or 'q' to cancel: ");
                    scanf(" %c", &ch);  
                    __fpurge(stdin);
                    if (ch != 'q' && ch != 'Q')
                    {
                        // Delete the contact
                        for(int j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("Contact deleted successfully!\n");
                    }
                    else
                    {
                        printf("Contact deletion cancelled.\n");
                    }
                    return;
                    }
                }
                if (!found) 
                {
                    printf("Entered Contact not found\n");
                }
                break;
        default:
                printf("Enter valid option\n");
                return;
    }
}
void savecontact(AddressBook *addressBook)
{
    FILE *file = fopen("contact.txt", "w");
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(file, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved successfully.\n");
}