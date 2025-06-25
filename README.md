# Addressbook-Application
Address Book Management System: Developed a console-based application in C language to  manage contact information, including names, phone numbers, and email addresses.  • Core Features: Implemented functionalities to add, edit, search, delete, and list contacts with  robust validation for accurate and unique entries. 

# Features
Add Contacts: Allows users to add new contacts with information like name, phone number, email, and address.
Search Contacts: Enables searching for contacts based on name, phone number, or email.
Update Contacts: Provides the option to update existing contact details.
Delete Contacts: Allows users to delete a contact from the address book.
Data Persistence: Contacts are saved in a file, ensuring data is retained between sessions.
Display Contacts: Displays all saved contacts in a user-friendly format.
Sort Contacts: Users can sort contacts by name, phone number, or email.

# Project Structure
The project is organized into the following key files:

address_book.c: Contains the main functionality for managing contacts (add, update, delete, search, etc.).
contact.h: Header file defining the Contact structure and function prototypes for managing contacts.
file_operations.c: Functions for saving and loading contacts to/from a file.
ui.c: User interface functions for interacting with the user through the terminal.
Makefile: Contains build instructions for compiling the application.

