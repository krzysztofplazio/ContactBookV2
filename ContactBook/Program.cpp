#include "Program.h"
#include <iostream>
#include "Contact.h"
#include <conio.h>
#include <mysql.h>
#include "helpers.h"

void Program::mainMenu(MYSQL mysql, User* user)
{
	Contact contact{};
	system("cls");
	cout << "Witaj w swojej prywatnej ksiazce konatkow " << user->getFirstName() << "!\nCo chcialbys teraz zrobic ? \n";
	cout << "1. Wszystkie kontakty.\n";
	cout << "2. Wyszukaj kontakt.\n";
	cout << "3. Dodaj nowy kontakt.\n";
	cout << "4. Edytuj instejacy kontakt.\n";
	cout << "5. Zakoncz dzialanie programu.\n";
	cout << "\nWybierz numer: ";
	auto choose = _getch();
	switch (choose)
	{
	case '1':
	{
		auto contacts = contact.getAllContactsByUserId(mysql, user->getId());
		if (contacts.begin()->second == 0)
		{
			cout << "Brak kontaktow w twojej liscie.\nNacisnij dowolny przycisk aby kontynuowac...";
			auto ch = _getch();
			mainMenu(mysql, user);
		}

		system("cls");
		contact.showContacts(contacts.begin()->first, contacts.begin()->second);
	}
	break;
	case '2':
	{
		string name;
		system("cls");
		cout << "Podaj imie szukanego kontaktu: ";
		cin >> name;
		cout << endl;
		auto contacts = contact.getContactsByFirstNameAndUserId(mysql, name, user->getId());
		if (contacts.begin()->second == 0)
		{
			cout << "Brak kontaktow w twojej liscie.\nNacisnij dowolny przycisk aby kontynuowac...";
			auto ch = _getch();
			mainMenu(mysql, user);
		}

		system("cls");
		cout << "Wyniki dla \'" << name << "';:\n";
		contact.showContacts(contacts.begin()->first, contacts.begin()->second);
	}
	break;
	case '3':
	{
		// createNewContact();
	}
	break;
	case '4':
	{
		// editContact();
	}
	break;
	case '5':
	{
		printf("\nZegnaj! Do zobaczenia!");
		exit(1);
	}
	break;
	default:
		mainMenu(mysql, user);
		break;
	}
}

void Program::loginUser(MYSQL mysql)
{
	User* user{};
	string login, password;
	cout << "Login: ";
	cin >> login;
	cout << "Haslo: ";
	SetStdinEcho(false);
	cin >> password;
	SetStdinEcho(true);

	User* userFromDb = user->getUserByLogin(mysql, login);
	if (userFromDb == NULL)
	{
		cout << "\nNiepoprawny login lub haslo. Sprobuj ponownie.\n";
		loginUser(mysql);
	}

	if (userFromDb != NULL && !user->isPasswordCorrect(mysql, userFromDb->getId(), password))
	{
		cout << "\nNiepoprawny login lub haslo. Sprobuj ponownie.\n";
		loginUser(mysql);
	}

	mainMenu(mysql, userFromDb);
}