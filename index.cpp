// Contact Management System in C++

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Contact class to store name and phone details
class Contact
{
public:
  string name;
  string phone;

  // Constructor to initialize name and phone
  Contact(const string &name, const string &phone)
      : name(name), phone(phone) {}
};

// ContactManagementSystem class to manage contacts
class ContactManagementSystem
{
private:
  vector<Contact> contacts;
  string fileName;

public:
  // Constructor to initialize with file name
  ContactManagementSystem(const string &fileName)
      : fileName(fileName) {}

  // Function to load contacts from file
  void loadContactsFromFile()
  {
    ifstream inputFile(fileName);
    if (!inputFile)
    {
      cerr << "Error: Could not open the file for reading.\n";
      return;
    }

    // Read name and phone from file and add to contacts vector
    string name, phone;
    while (inputFile >> name >> phone)
    {
      contacts.emplace_back(name, phone);
    }
    inputFile.close();
  }

  // Function to save contacts to file
  void saveContactsToFile()
  {
    ofstream outputFile(fileName);
    if (!outputFile)
    {
      cerr << "Error: Could not open the file for writing.\n";
      return;
    }

    // Write contacts' name and phone to file
    for (const auto &contact : contacts)
    {
      outputFile << contact.name << " " << contact.phone << "\n";
    }
    outputFile.close();
  }

  // Function to add a new contact
  void addContact(const Contact &contact)
  {
    contacts.push_back(contact);
  }

  // Function to view all contacts
  void viewContacts()
  {
    for (const auto &contact : contacts)
    {
      cout << "Name: " << contact.name << ", Phone: " << contact.phone << "\n";
    }
  }

  // Function to search for a contact by name
  Contact *searchContact(const string &name)
  {
    for (auto &contact : contacts)
    {
      if (contact.name == name)
      {
        return &contact;
      }
    }
    return nullptr;
  }
};

// Main function
int main()
{
  // File to store contacts
  const string fileName = "contacts.txt";

  // Create ContactManagementSystem object and load contacts from file
  ContactManagementSystem cms(fileName);
  cms.loadContactsFromFile();

  // Variables for user input
  int choice;
  string name;
  string phone;

  // Main loop for user interaction
  while (true)
  {
    cout << "\n==== Contact Management System ====\n";
    cout << "1. Add Contact\n";
    cout << "2. View Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";

    // Get user choice
    cin >> choice;

    try
    {
      switch (choice)
      {
      case 1:
      {
        // Add a new contact
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter phone number: ";
        cin >> phone;

        cms.addContact(Contact(name, phone));
        cms.saveContactsToFile();
        break;
      }
      case 2:
        // View all contacts
        cms.viewContacts();
        break;
      case 3:
      {
        // Search for a contact by name
        cout << "Enter the name to search: ";
        cin.ignore();
        getline(cin, name);

        Contact *result = cms.searchContact(name);
        if (result)
        {
          cout << "Contact found - Name: " << result->name << ", Phone: " << result->phone << "\n";
        }
        else
        {
          cout << "Contact not found.\n";
        }
        break;
      }
      case 4:
        // Exit the program
        cout << "Exiting the program...\n";
        return 0;
      default:
        cout << "Invalid choice. Please try again.\n";
        break;
      }
    }
    catch (const exception &e)
    {
      // Catch and display any exceptions
      cerr << "Error: " << e.what() << "\n";
    }
  }

  return 0;
}
