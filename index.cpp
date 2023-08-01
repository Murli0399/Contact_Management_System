#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Contact
{
public:
  string name;
  string phone;

  Contact(const string &name, const string &phone)
      : name(name), phone(phone) {}
};

class ContactManagementSystem
{
private:
  vector<Contact> contacts;
  string fileName;

public:
  ContactManagementSystem(const string &fileName)
      : fileName(fileName) {}

  void loadContactsFromFile()
  {
    ifstream inputFile(fileName);
    if (!inputFile)
    {
      cerr << "Error: Could not open the file for reading.\n";
      return;
    }

    string name, phone;
    while (inputFile >> name >> phone)
    {
      contacts.emplace_back(name, phone);
    }
    inputFile.close();
  }

  void saveContactsToFile()
  {
    ofstream outputFile(fileName);
    if (!outputFile)
    {
      cerr << "Error: Could not open the file for writing.\n";
      return;
    }

    for (const auto &contact : contacts)
    {
      outputFile << contact.name << " " << contact.phone << "\n";
    }
    outputFile.close();
  }

  void addContact(const Contact &contact)
  {
    contacts.push_back(contact);
  }

  void viewContacts()
  {
    for (const auto &contact : contacts)
    {
      cout << "Name: " << contact.name << ", Phone: " << contact.phone << "\n";
    }
  }

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

int main()
{
  const string fileName = "contacts.txt";
  ContactManagementSystem cms(fileName);
  cms.loadContactsFromFile();

  int choice;
  string name;
  string phone;

  while (true)
  {
    cout << "\n==== Contact Management System ====\n";
    cout << "1. Add Contact\n";
    cout << "2. View Contacts\n";
    cout << "3. Search Contact\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";

    cin >> choice; // Remove duplicate declaration

    try
    {
      switch (choice)
      {
      case 1:
      {
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
        cms.viewContacts();
        break;
      case 3:
      {
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
        cout << "Exiting the program...\n";
        return 0;
      default:
        cout << "Invalid choice. Please try again.\n";
        break;
      }
    }
    catch (const exception &e)
    {
      cerr << "Error: " << e.what() << "\n";
    }
  }

  return 0;
}
