#ifndef CONTACT_H
#define CONTACT_H 
      
#define MAX_CONTACTS 100
  
#include <stdio.h> 
#include <string.h>
 
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;
 
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void savecontact(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void validate_name(AddressBook *addressBook);
void validate_phone(AddressBook *addressBook);
void validate_email(AddressBook *addressBook);

#endif
