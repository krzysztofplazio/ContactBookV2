#include "Program.h"

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
			cout << "Brak kontaktow w twojej liscie.";
			backToMainMenu(mysql, user);
		}

		system("cls");
		contact.showContacts(contacts.begin()->first, contacts.begin()->second);

		backToMainMenu(mysql, user);
	}
	break;
	case '2':
	{
		string name;
		system("cls");
		cout << "Podaj imie szukanego kontaktu: ";
		cin >> name;
		cout << endl;

		int c;
		if ((c = getchar()) != '\n' && c != EOF)
			while ((c = getchar()) != '\n' && c != EOF) {}

		auto contacts = contact.getContactsByFirstNameAndUserId(mysql, name, user->getId());
		if (contacts.begin()->second == 0)
		{
			cout << "Brak kontaktow w twojej liscie.";
			backToMainMenu(mysql, user);
		}

		system("cls");
		cout << "Wyniki dla \'" << name << "\':\n";
		contact.showContacts(contacts.begin()->first, contacts.begin()->second);

		backToMainMenu(mysql, user);
	}
	break;
	case '3':
	{
		system("cls");
		cout << "Dodaj swoj nowy kontakt!\n";
		Contact contact;
		int c;
		contact.writeContact(user->getId());
		setNewContact(mysql, user, &contact);
	}
	break;
	case '4':
	{
		editContact(mysql, user);
	}
	break;
	case '5':
	{
		string bye = "\nZegnaj! Do zobaczenia!";
		for (auto i = 0; i < bye.length(); i++)
		{
			cout << bye[i];
			Sleep(50);
		}
		exit(1);
	}
	break;
	default:
		mainMenu(mysql, user);
		break;
	}
}

void Program::backToMainMenu(MYSQL mysql, User* user)
{
	cout << "\nNacisnij dowolny przycisk aby kontynuowac...";
	auto ch = _getch();
	mainMenu(mysql, user);
}

void Program::setNewContact(MYSQL mysql, User* user, Contact* newContact)
{
	char sure;
	cout << "Czy jestes pewny, ze chcesz dodac ten kontakt? [y/N]: ";
	while (true)
	{
		sure = _getch();
		if (sure == 'y' || sure == 'n' || sure == 'N')
		{
			cout << endl;
			switch (sure)
			{
			case 'y':
			{

				if (!newContact->createContact(mysql, newContact))
				{
					cout << "Nie udalo sie dodac kontaktu.";
					backToMainMenu(mysql, user);
				}

				cout << "Dodano nowy kontakt!\n";
				backToMainMenu(mysql, user);
			}
			break;
			case 'n':
			case 'N':
			{
				backToMainMenu(mysql, user);
			}
			break;
			}
		}
	}
}

void Program::editContact(MYSQL mysql, User* user)
{
	system("cls");
	Contact contact;
	string name;
	cout << "Wyszukaj kontakt, ktory chcesz zedytowac: ";
	cin >> name;

	auto contacts = contact.getContactsByFirstNameAndUserId(mysql, name, user->getId());
	if (contacts.begin()->second == 0)
	{
		cout << "Brak szukanego kontaku.";
		backToMainMenu(mysql, user);
	}

	system("cls");
	cout << "Wyniki dla \'" << name << "\':\n";
	contact.showContacts(contacts.begin()->first, contacts.begin()->second);

	if (contacts.begin()->second == 1)
	{
		cout << "Czy na pewno chcesz edytowac ten kontakt? [n|N/*]\n";
		auto pick = _getch();
		if (pick != 'n' && pick != 'N')
		{
			cout << "Anulowano edycje kontaktu.";
			backToMainMenu(mysql, user);
		}

		system("cls");
		contact.showContacts(contacts.begin()->first, 1);
		changeContact(mysql, user, contacts.begin()->first);
	}

	cout << "Wybierz numer indeksu kontaktu, ktory cie interesuje: ";
	int userId;
	cin >> userId;

	int c;
	if ((c = getchar()) != '\n' && c != EOF)
		while ((c = getchar()) != '\n' && c != EOF) {}

	auto pickedContact = contact.getContactById(mysql, userId);
	if (pickedContact == NULL)
	{
		cout << "\nNie ma takiego kontaku. ";
		backToMainMenu(mysql, user);
	}

	system("cls");
	contact.showContacts(pickedContact, 1);
	changeContact(mysql, user, pickedContact);
}

void Program::changeContact(MYSQL mysql, User* user, Contact* contact)
{
	string query;
	cout << "\n\nKtora wartosc chcesz edytowac?\n";
	cout << "1. Imie\n";
	cout << "2. Nazwisko\n";
	cout << "3. Numer telefonu\n";
	cout << "4. Adres\n";
	cout << "5. Email\n";
	cout << "6. Zrezygnuj.\n";

	char pick;
	while (true)
	{
		pick = _getch();
		switch (pick)
		{
		case '1':
		{
			string firstName;
			cout << "Podaj nowe imie: ";
			cin >> firstName;
			contact->setFirstName(firstName);
			goto exit_loop;
		}
		break;
		case '2':
		{
			string lastName;
			cout << "Podaj nowe nazwisko: ";
			cin >> lastName;
			contact->setLastName(lastName);
			goto exit_loop;
		}
		break;
		case '3':
		{
			string phoneNumber;
			cout << "Podaj nowy numer telefonu: ";
			cin >> phoneNumber;
			contact->setPhoneNumber(phoneNumber);
			goto exit_loop;
		}
		break;
		case '4':
		{
			string address;
			cout << "Podaj nowy adres: ";
			cin >> address;
			contact->setAddress(address);
			goto exit_loop;
		}
		break;
		case '5':
		{
			string email;
			cout << "Podaj nowy email: ";
			cin >> email;
			contact->setEmail(email);
			goto exit_loop;
		}
		break;
		case '6':
		{
			int c;
			if ((c = getchar()) != '\n' && c != EOF)
				while ((c = getchar()) != '\n' && c != EOF) {}
			backToMainMenu(mysql, user);
		}
		break;
		default:
		{
			cout << "Wybierz poprawna opcje.\n";
		}
		break;
		}
	}	
exit_loop:;
	int c;
	if ((c = getchar()) != '\n' && c != EOF)
		while ((c = getchar()) != '\n' && c != EOF) {}
	auto isEdited = contact->updateContact(mysql, contact);
	if (!isEdited)
	{
		cout << "Kontakt nie zostal zedytowany. Prosze sprobowac jeszcze raz.\n";
		backToMainMenu(mysql, user);
	}

	cout << "Kontakt zosta³ zedytowany!";
	backToMainMenu(mysql, user);
}

void Program::loginUser(MYSQL mysql)
{
	User* user{};
	string login, password;
	cout << "Login: ";
	cin >> login;
	cout << "Haslo: ";
	CensorePassword(false);
	cin >> password;
	CensorePassword(true);

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

	int c;
	if ((c = getchar()) != '\n' && c != EOF)
		while ((c = getchar()) != '\n' && c != EOF) {}

	mainMenu(mysql, userFromDb);
}