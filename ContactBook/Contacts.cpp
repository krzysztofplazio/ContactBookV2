#include "Contact.h"

Contacts::Contacts(Contact* contacts, int count)
{
    _contacts = contacts;
    _count = count;
}

Contacts::~Contacts()
{
    delete[] _contacts;
}

Contact* Contacts::getContacts()
{
    return _contacts;
}

int Contacts::getCount()
{
    return _count;
}

void Contacts::setContacts(Contact* contacts)
{
    _contacts = contacts;
}

void Contacts::setCount(int count)
{
    _count = count;
}
