#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cstdlib>
using namespace std;

struct ContactBook {
    short identifierOfContact = 0;
    short userIdentiefier = 0;
    string firstName;
    string lastName;
    string phoneNumber;
    string email;
    string adress;
};

struct UserBook {
    short identiefierUser = 0;
    string login;
    string password;
};

vector<UserBook> registration ( vector<UserBook> user ) {

    UserBook newUser;
    short numberOfElementsInContainer = user.size();
    short identiefierUser = 0;
    string loginEntered, passwordEntered;

    fstream fileUsers;
    fileUsers.open( "Uzytkownicy.txt", ios::out | ios::app );

    if ( user.size() == 0 ) identiefierUser = 0;
    else identiefierUser = user[numberOfElementsInContainer - 1].identiefierUser;

    cout << "Wpisz login nowego uzytkownika: ";
    cin >> loginEntered;

    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        while ( user[i].login == loginEntered ) {
            cout << "Login jest juz zarezerwowany. Wpisz inny login: ";
            cin >> loginEntered;
        }
    }
    cout << "Wpisz haslo nowego uzytkownika: ";
    cin >> passwordEntered;

    newUser.identiefierUser = identiefierUser + 1;
    newUser.login = loginEntered;
    newUser.password = passwordEntered;
    user.push_back(newUser);

    fileUsers << newUser.identiefierUser << '|';
    fileUsers << newUser.login << '|';
    fileUsers << newUser.password << '|' << endl;

    fileUsers.close();
    cout << "Uzytkownik zarejestrowany ! \n";
    Sleep(1000);
    system("pause");

    return user;
}

short countContacts () {

    short quantityOfContacts = 0;
    fstream fileToCount;
    fileToCount.open( "ContactBook.txt", ios::in );
    string line;
    cin.sync();
    while ( getline( fileToCount, line ) )
        quantityOfContacts++;
    fileToCount.close();
    return quantityOfContacts;
}


vector<ContactBook> loadAllContacts( ) {

    ContactBook newContact;
    vector<ContactBook> contact;
    char sign = '|';
    string element;
    short elementNumber = 0;
    fstream file;
    file.open( "ContactBook.txt", ios::in );

    if ( file.good() ) {
        while( getline( file, element, sign ) ) {
            switch( elementNumber ) {
            case 0:
                newContact.identifierOfContact = atoi( element.c_str() );
                break;
            case 1:
                newContact.userIdentiefier = atoi( element.c_str() );
                break;
            case 2:
                newContact.firstName = element;
                break;
            case 3:
                newContact.lastName = element;
                break;
            case 4:
                newContact.phoneNumber = element;
                break;
            case 5:
                newContact.email = element;
                break;
            case 6:
                newContact.adress = element;
                break;
            }
            if ( elementNumber >= 6 ) {
                elementNumber = 0;
                contact.push_back( newContact );
            } else elementNumber++;
        }
    }
    file.close();

    return contact;
}

vector<ContactBook> loadAllContactsOfLoggedUser( short idOfLoggedUser ) {

    ContactBook newContact;
    vector<ContactBook> contact;
    vector<ContactBook> contactTemp;
    char sign = '|';
    string element;
    short elementNumber = 0;
    fstream file;
    file.open( "ContactBook.txt", ios::in );

    if ( file.good() ) {
        while( getline( file, element, sign ) ) {
            switch( elementNumber ) {
            case 0:
                newContact.identifierOfContact = atoi( element.c_str() );
                break;
            case 1:
                newContact.userIdentiefier = atoi( element.c_str() );
                break;
            case 2:
                newContact.firstName = element;
                break;
            case 3:
                newContact.lastName = element;
                break;
            case 4:
                newContact.phoneNumber = element;
                break;
            case 5:
                newContact.email = element;
                break;
            case 6:
                newContact.adress = element;
                break;
            }
            if ( elementNumber >= 6 ) {
                elementNumber = 0;
                contact.push_back( newContact );

            } else elementNumber++;
        }
    }
    file.close();

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].userIdentiefier == idOfLoggedUser )
             contactTemp.push_back( contact[i] );
    }
    return contactTemp;
}

void cleaningScreen() {

    HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo( console, & csbi );
    DWORD tmp;
    COORD start = { 0, 0 };
    FillConsoleOutputCharacterA( console, ' ', csbi.dwSize.X * csbi.dwSize.Y, start, & tmp );
    FillConsoleOutputAttribute( console, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, start, & tmp );
    SetConsoleCursorPosition( console, start );
}

void initLoginMenu() {

    cleaningScreen();
    cout << "KSIAZKA KONTAKTOW: \n";
    cout << "1. Logowanie \n";
    cout << "2. Rejestracja \n";
    cout << "9. Zamknij program" << endl;
}

void initMenuBox() {

    cleaningScreen();
    cout << "Ksiazka kontaktow: \n";;
    cout << "1. Wpisz kontakt \n";
    cout << "2. Wyszukaj kontakt po imieniu \n";
    cout << "3. Wyszukaj kontakt po nazwisku \n";
    cout << "4. Wyswietl wszystkie kontakty \n";
    cout << "5. Usun kontakt \n";
    cout << "6. Edytuj kontakt \n";
    cout << "7. Zmien haslo \n";
    cout << "8. Wyloguj sie \n";
    cout << "9. Zamknij program" << endl;

}

void menuEdition() {

    cleaningScreen();
    cout << "\n PODMENU EDYCYJNE \n\n";
    cout << "1 - Imie \n";
    cout << "2 - Nazwisko \n";
    cout << "3 - Numer telefonu \n";
    cout << "4 - Email \n";
    cout << "5 - Adres \n";
    cout << "0 - Powrot do menu" << endl;
}

vector<ContactBook> addContact( vector<ContactBook> contact, short idOfLoggedUser ) {

    string firstName, lastName, phoneNumber, email, adress;
    short quantityOfContacts = countContacts ();
    ContactBook newContact;
    fstream file;
    file.open( "ContactBook.txt", ios::out | ios::app );
    cout << "Podaj imie: ";
    cin.sync();
    getline( cin,  newContact.firstName );
    cout << "Podaj nazwisko: ";
    cin.sync();
    getline( cin,  newContact.lastName );
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline( cin,  newContact.phoneNumber );
    cout << "Podaj email: ";
    cin >>  newContact.email;
    cout << "Podaj adres: ";
    cin.sync();
    getline( cin,  newContact.adress );

    newContact.identifierOfContact = quantityOfContacts + 1;
    newContact.userIdentiefier = idOfLoggedUser;
    contact.push_back( newContact );

    file << newContact.identifierOfContact << '|';
    file << newContact.userIdentiefier << '|';
    file << newContact.firstName << '|';
    file << newContact.lastName << '|';
    file << newContact.phoneNumber << '|';
    file << newContact.email << '|';
    file << newContact.adress << '|' << endl;

    file.close();

    cout << "Kontakt wpisany! \n";
    Sleep(1000);
    system("pause");

    return contact;
}

void searchFirstName( vector<ContactBook> contact, short idOfLoggedUser ) {

    string searchedFirstName;
    cout << "Wyszukaj po imieniu \n";
    cout << "Wpisz imie: " << endl;
    cin >> searchedFirstName;

    short numberOfElementsInContainer = contact.size();

    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( idOfLoggedUser == contact[i].userIdentiefier ) {
            if( contact[i].firstName == searchedFirstName ) {

                cout << contact[i].identifierOfContact << '|';
                cout << contact[i].userIdentiefier << '|';
                cout << contact[i].firstName << '|';
                cout << contact[i].lastName << '|';
                cout << contact[i].phoneNumber << '|';
                cout << contact[i].email << '|';
                cout << contact[i].adress << '|' << endl;
            }
        }
    }
    system("pause");
}

void searchLastName( vector<ContactBook> contact, short idOfLoggedUser ) {

    string searchedLastName;
    cout << "Wyszukaj po nazwisku \n";
    cout << "Wpisz nazwisko: " << endl;
    cin >> searchedLastName;

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( idOfLoggedUser == contact[i].userIdentiefier ) {
            if( contact[i].lastName == searchedLastName ) {

                cout << contact[i].identifierOfContact << '|';
                cout << contact[i].userIdentiefier << '|';
                cout << contact[i].firstName << '|';
                cout << contact[i].lastName << '|';
                cout << contact[i].phoneNumber << '|';
                cout << contact[i].email << '|';
                cout << contact[i].adress << '|' << endl;
            }
        }
    }
    system("pause");
}

void displayContacts( vector<ContactBook> contact, short idOfLoggedUser ) {

    short numberOfElementsInContainer = contact.size();
    cout << "\n TWOJE KONTAKTY \n\n";
    for ( short i = 0; i < numberOfElementsInContainer; ++i ) {
        if ( idOfLoggedUser == contact[i].userIdentiefier ) {

            cout << contact[i].identifierOfContact << '|';
            cout << contact[i].userIdentiefier << '|';
            cout << contact[i].firstName << '|';
            cout << contact[i].lastName << '|';
            cout << contact[i].phoneNumber << '|';
            cout << contact[i].email << '|';
            cout << contact[i].adress << '|' << endl;

        }
    }
    system("pause");
}

void displayContactsBeforeRemove( vector<ContactBook> contact, short idOfLoggedUser ) {

    short numberOfElementsInContainer = contact.size();
    cout << "\n TWOJE KONTAKTY \n\n";
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( idOfLoggedUser == contact[i].userIdentiefier ) {

            cout << contact[i].identifierOfContact << '|';
            cout << contact[i].userIdentiefier << '|';
            cout << contact[i].firstName << '|';
            cout << contact[i].lastName << '|';
            cout << contact[i].phoneNumber << '|';
            cout << contact[i].email << '|';
            cout << contact[i].adress << '|' << endl;

        }
    }
}

void updateTextFile ( vector<ContactBook> contact, short sentIdentifierOfContact ) {

    vector<ContactBook> allContacts = loadAllContacts( );
    fstream fileOrginal, fileTemporary;
    fileOrginal.open( "ContactBook.txt", ios::in );
    fileTemporary.open( "ContactBookTemporary.txt", ios::out | ios::app );

    short numberOfElementsInContainer = allContacts.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {

        if ( allContacts[i].identifierOfContact != sentIdentifierOfContact ) {

            fileTemporary << allContacts[i].identifierOfContact << '|';
            fileTemporary << allContacts[i].userIdentiefier << '|';
            fileTemporary << allContacts[i].firstName << '|';
            fileTemporary << allContacts[i].lastName << '|';
            fileTemporary << allContacts[i].phoneNumber << '|';
            fileTemporary << allContacts[i].email << '|';
            fileTemporary << allContacts[i].adress << '|' << endl;
        } else {
            short numberOfElementsInContactVector = contact.size();
            for ( short j = 0; j < numberOfElementsInContactVector; j++ ) {

                if ( contact[j].identifierOfContact == sentIdentifierOfContact ) {

                    fileTemporary << contact[j].identifierOfContact << '|';
                    fileTemporary << contact[j].userIdentiefier << '|';
                    fileTemporary << contact[j].firstName << '|';
                    fileTemporary << contact[j].lastName << '|';
                    fileTemporary << contact[j].phoneNumber << '|';
                    fileTemporary << contact[j].email << '|';
                    fileTemporary << contact[j].adress << '|' << endl;
                }
            }
        }
    }
    fileOrginal.close();
    fileTemporary.close();
    remove( "ContactBook.txt" );
    rename( "ContactBookTemporary.txt", "ContactBook.txt" );
}

vector<ContactBook> removeContact( vector<ContactBook> contact, short idOfLoggedUser ) {

    char sign;
    short contactIdentiefierToBeDeleted = 0;
    displayContactsBeforeRemove( contact, idOfLoggedUser );

    cout << "\n Wpisz identyfikator kontaktu, ktory ma zostac usuniety z ksiazki kontaktow: ";
    cin >> contactIdentiefierToBeDeleted;

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifierOfContact == contactIdentiefierToBeDeleted ) {

            cout << "Czy na pewno usunac: ";
            cout << contact[i].identifierOfContact << '|';
            cout << contact[i].userIdentiefier << '|';
            cout << contact[i].firstName << '|';
            cout << contact[i].lastName << '|';
            cout << contact[i].email << '|';
            cout << contact[i].phoneNumber << '|';
            cout << contact[i].adress << '|' << endl;
            cout << "Jesli TAK -  wpisz 't' ";

            cin >> sign;
            if ( sign == 't' ) {
                for ( short j = i; j < numberOfElementsInContainer - 1; j++ ) {
                    contact[j].identifierOfContact = contact[j+1].identifierOfContact;
                    contact[j].userIdentiefier = contact[j+1].userIdentiefier;
                    contact[j].firstName = contact[j+1].firstName;
                    contact[j].lastName = contact[j+1].lastName;
                    contact[j].email = contact[j+1].email;
                    contact[j].phoneNumber = contact[j+1].phoneNumber;
                    contact[j].adress = contact[j+1].adress;
                }
                contact.pop_back();
                updateTextFile ( contact, contactIdentiefierToBeDeleted  );
                cout << "Kontakt usunieto pomyslnie i zaktualizowano ksiazke kontaktow \n";

            } else return contact;
        }
    }
    system("pause");

    return contact;
}

vector<ContactBook> editContactFirstName( vector<ContactBook> contact, short identifierOfEditedContact  ) {

    string editedFirstName;

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifierOfContact == identifierOfEditedContact ) {
            cout << "Wpisz nowe imie: ";
            cin >> editedFirstName;
            contact[i].firstName = editedFirstName;
            updateTextFile(contact, identifierOfEditedContact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}

vector<ContactBook> editContactLastName( vector<ContactBook> contact, short identifierOfEditedContact  ) {

    string editedLastName;

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifierOfContact == identifierOfEditedContact ) {
            cout << "Wpisz nowe nazwisko: ";
            cin >> editedLastName;
            contact[i].lastName = editedLastName;
            updateTextFile(contact, identifierOfEditedContact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}


vector<ContactBook> editContactPhoneNumber( vector<ContactBook> contact, short identifierOfEditedContact  ) {

    string editedPhoneNumber;

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifierOfContact == identifierOfEditedContact ) {

            cout << "Wpisz nowy numer telefonu: ";
            cin >> editedPhoneNumber;
            contact[i].phoneNumber = editedPhoneNumber;
            updateTextFile(contact, identifierOfEditedContact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}

vector<ContactBook> editContactEmail( vector<ContactBook> contact, short identifierOfEditedContact  ) {

    string editedEmail;

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifierOfContact == identifierOfEditedContact ) {
            cout << "Wpisz nowy email: ";
            cin >> editedEmail;
            contact[i].email = editedEmail;
            updateTextFile(contact, identifierOfEditedContact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}

vector<ContactBook> editContactAdress( vector<ContactBook> contact, short identifierOfEditedContact  ) {

    string editedAdress;

    short numberOfElementsInContainer = contact.size();
    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( contact[i].identifierOfContact == identifierOfEditedContact ) {
            cout << "Wpisz nowy adres: ";
            cin >> editedAdress;
            contact[i].adress = editedAdress;
            updateTextFile(contact, identifierOfEditedContact );
        }
    }
    cout << "Aktualizacja kontaktu przeprowadzona \n";
    system("pause");

    return contact;
}

vector<UserBook> changePassword ( vector<UserBook> user, short idOfLoggedUser ) {

    string newPassword;
    fstream fileUsers;
    fileUsers.open ( "Uzytkownicy.txt", ios::in | ios::out );

    cout << "Wpisz nowe haslo: ";
    cin >> newPassword;

    short numberOfElementsInContainer = user.size();

    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if ( user[i].identiefierUser == idOfLoggedUser ) {
            user[i].password = newPassword;
        }
    }

    if (fileUsers.good()) {
        for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
            fileUsers << user[i].identiefierUser << '|';
            fileUsers << user[i].login << '|';
            fileUsers << user[i].password << '|' << endl;
        }
    }

    fileUsers.close();
    cout << "Aktualizacja uzytkownika przeprowadzona \n";
    system("pause");

    return user;
}

void exit() {
    exit(0);
}

int loginUser( vector<UserBook> user ) {

    cleaningScreen();

    cout << "\n MENU LOGOWANIA \n";
    cout << "\n Wpisz Twoj login: ";

    string loginEntered, passwordEntered;
    short ilosc = 0;
    short numberOfElementsInContainer = user.size();
    cin >>  loginEntered;

    for ( short i = 0; i < numberOfElementsInContainer; i++ ) {
        if( user[i].login == loginEntered ) {
            do {
                ilosc++;
                cout << "\n Wpisz haslo: ";
                cin >> passwordEntered;
                if( user[i].password == passwordEntered ) {
                    cout << "Zalogowano poprawnie.";
                    return user[i].identiefierUser;
                } else cout << "Nieprawidlowe haslo. \n ";

            } while(user[i].password == passwordEntered || ilosc < 3 );
        }
    }
    Sleep(1000);
    return 0;
}

vector<UserBook> loadAllUsers(vector<UserBook> user) {

    UserBook newUser;
    char sign = '|';
    string element;
    short elementNumber = 0;
    fstream fileUsers;
    fileUsers.open( "Uzytkownicy.txt", ios::in );

    if ( fileUsers.good() ) {
        while( getline( fileUsers, element, sign ) ) {
            switch( elementNumber ) {
            case 0:
                newUser.identiefierUser = atoi( element.c_str() );
                break;
            case 1:
                newUser.login = element;
                break;
            case 2:
                newUser.password = element;
                break;
            }
            if ( elementNumber >= 2 ) {
                elementNumber = 0;
                user.push_back( newUser );
            } else elementNumber++;
        }
    }
    fileUsers.close();

    return user;
}

short logOutUser( vector<ContactBook> contact, short idOfLoggedUser ) {
    contact.clear();
    idOfLoggedUser = 0;

    return idOfLoggedUser;
}

int main() {

    vector<ContactBook> contact;
    vector<UserBook> user;
    short idOfLoggedUser = 0;
    short turnOnSwitch = 0;
    char choice;
    user = loadAllUsers(user);

    while(1) {
        if( turnOnSwitch == 0 ) {
            initLoginMenu();
            cin >> choice;
            if ( choice == '1' ) {
                idOfLoggedUser = loginUser(user);
                contact = loadAllContactsOfLoggedUser( idOfLoggedUser );
                turnOnSwitch = 1;
            } else if ( choice == '2' ) user = registration(user);
            else if ( choice == '9' ) exit();
        } else if( turnOnSwitch == 1 ) {
            initMenuBox();
            cin >> choice;
            if ( choice == '1') {
                contact = addContact( contact, idOfLoggedUser );
            } else if ( choice == '2' ) searchFirstName( contact, idOfLoggedUser );
            else if ( choice == '3' ) searchLastName( contact, idOfLoggedUser );
            else if ( choice == '4' ) displayContacts( contact, idOfLoggedUser );
            else if ( choice == '5' ) removeContact( contact, idOfLoggedUser  );
            else if ( choice == '6' ) turnOnSwitch += 1;
            else if ( choice == '7' ) user = changePassword( user, idOfLoggedUser );
            else if ( choice == '8' ) {
                idOfLoggedUser = logOutUser( contact, idOfLoggedUser);
                turnOnSwitch = 0;
            } else if ( choice == '9' ) exit();
        } else if ( turnOnSwitch == 2 ) {
            short identifierOfEditedContact = 0;
            menuEdition();

            cout << "\n Ktore dane chcesz zmienic (od 1 do 5) lub wcisnij 0 - powrot do menu: ";
            cin >> choice;
            cout << "Wpisz identyfikator kontaktu do edycji: ";
            cin.sync();
            cin >> identifierOfEditedContact;
            if (choice == '1')
                contact = editContactFirstName( contact, identifierOfEditedContact );
            else if (choice == '2')
                contact = editContactLastName( contact, identifierOfEditedContact  );
            else if (choice == '3')
                contact = editContactPhoneNumber( contact, identifierOfEditedContact  );
            else if (choice == '4')
                contact = editContactEmail( contact, identifierOfEditedContact  );
            else if (choice == '5')
                contact = editContactAdress( contact, identifierOfEditedContact  );
            else if (choice == '0')
                turnOnSwitch = 1;
        }
    }
    return 0;
}
