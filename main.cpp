#include <iostream>
#include <vector>

using namespace std;

int ID = 100, operation_num, member_ID = 1673;
string title;

void add_book();

inline void main_menu();

inline void book_menu();

inline void member_menu();

inline void mini_menu(int menu_number = 1);

void display_all_books();

int search_for_book(string &name);

void display_book(int index);

void update_book();

void add_member();

void display_all_members();

int search_member(int search_by);

int search_menu();

void display_member(int index);

void update_member_name(int index);

void delete_member();

void borrow_book();

void return_book();

struct book {
    string book_title;
    string author;
    int pub_year;
    int book_ID;
    bool available{true};
};

vector<book> book_records;

struct member {
    string member_name;
    int member_ID;
    vector<string> borrowed_books{};
};

vector<member> member_records;

int main() {
    main_menu();
}

void add_book() {
    string book_title, author;
    int pub_year;

    system("cls");
    cout << "Enter book details:\n\n";
    cin.ignore();

    cout << "Title: ";
    getline(cin, book_title);

    cout << "Author: ";
    getline(cin, author);

    cout << "Publication year: ";
    cin >> pub_year;

    book new_book = {book_title, author, pub_year, ID, true};
    book_records.push_back(new_book);
    ID++;

    cout << "\nBook added successfully!\n";
    mini_menu();
}

inline void main_menu() {
    system("cls");
    cout << "Welcome!\n\n";
    cout << "[1] Book options\n[2] Member options\n[3] Exit\nChoose operation: ";

    input:
    cin >> operation_num;

    switch (operation_num) {
        case 1:
            book_menu();
            break;
        case 2:
            member_menu();
            break;
        case 3:
            exit(0);
        default:
            cout << "\nChoose a valid operation: ";
            goto input;
    }
}

inline void book_menu() {
    int index;

    system("cls");
    cout << "[1] Add new book record\n[2] View all book records\n"
            "[3] Search for a book\n[4] Update a book record\n[5] Delete a book record\n"
            "[6] Return to main menu\n[7] Exit\n";
    input:
    cin >> operation_num;

    switch (operation_num) {
        case 1:
            add_book();
            break;
        case 2:
            display_all_books();
            break;
        case 3:
            if (!book_records.empty()) {
                cin.ignore();
                system("cls");
                cout << "Enter book tile: ";
                getline(cin, title);

                cout << "\nSearching...\n";
                index = search_for_book(title);

                if (index != -1) display_book(index);
                else
                    cout << "Book was not found!\n";
            } else {
                system("cls");
                cout << "No books available!\n";
            }
            mini_menu();
            break;
        case 4:
            update_book();
            break;
        case 5://delete
            if (!book_records.empty()) {
                char yesNO;
                system("cls");

                cin.ignore();
                cout << "Enter book tile: ";
                getline(cin, title);

                cout << "\nSearching...\n";
                index = search_for_book(title);

                if (index != -1) {
                    cout << "\nAre you sure you want to delete this book?[Y/N]";
                    cin >> yesNO;
                    
                    if (yesNO == 'y' || yesNO == 'Y') {
                        book_records.erase(book_records.begin() + index);
                        cout << "\nBook deleted successfully!\n";
                    } else {
                        cout << "\nDeletion was cancelled!\n";
                        mini_menu();
                    }
                } else {
                    cout << "Book was not found!\n";
                }
                mini_menu();
            } else {
                system("cls");
                cout << "No books available!\n";
                mini_menu();
            }
            break;
        case 6:
            main_menu();
            break;
        case 7:
            exit(0);
        default:
            cout << "\nChoose a valid operation: ";
            goto input;
    }
}

inline void member_menu() {
    int index;
    system("cls");
    cout << "[1] Add new member record\n[2] View all member records\n[3] Search for a member\n"
            "[4] Update a member record\n[5] Delete a member record\n"
            "[6] Borrow a book\n[7] Return a book\n[8] Return to main menu\n[9] Exit\n";
    input:
    cin >> operation_num;

    switch (operation_num) {
        case 1:
            add_member();
            break;
        case 2:
            display_all_members();
            break;
        case 3:
            index = search_menu();
            if (index != -1) display_member(index);
            else {
                cout << "Member not found!\n";
                mini_menu(2);
            }
            break;
        case 4:
            index = search_menu();
            if (index != -1) update_member_name(index);
            else {
                cout << "Member not found!\n";
                mini_menu(2);
            }
            break;
        case 5:
            delete_member();
            break;
        case 6:
            borrow_book();
            break;
        case 7:
            return_book();
            break;
        case 8:
            main_menu();
            break;
        case 9:
            exit(0);
        default:
            cout << "Choose valid operation: ";
            goto input;
    }
}

inline void mini_menu(int menu_number) {
    cout << "\n[1] Return to " << (menu_number != 1 ? "member" : "book") << " options\n"
            "[2] Return to main menu\n[3] Exit\n";
    input:
    cin >> operation_num;
    switch (operation_num) {
        case 1:
            menu_number != 1 ? member_menu() : book_menu();
            break;
        case 2:
            main_menu();
            break;
        case 3:
            exit(0);
        default:
            cout << "\nChoose a valid operation: ";
            goto input;
    }
}

void display_all_books() {
    system("cls");
    if (book_records.empty()) cout << "No books available!\n";
    else {
        for (auto &book: book_records) {
            cout << "========================\n";
            cout << "Book title: " << book.book_title << "\n";
            cout << "Book author: " << book.author << "\n";
            cout << "Publication year: " << book.pub_year << "\n";
            cout << "Availability: " << (book.available ? "available" : "unavailable") << "\n";
            cout << "ID: " << book.book_ID << "\n";
        }
        cout << "========================\n";
    }
    mini_menu();
}

int search_for_book(string &name) {
    for (int i = 0; i < book_records.size(); ++i)
        if (book_records[i].book_title == name) return i;
    return -1;
}

void display_book(int index) {
    system("cls");
    cout << "========================\n";
    cout << "Book title: " << book_records[index].book_title << "\n";
    cout << "Book author: " << book_records[index].author << "\n";
    cout << "Publication year: " << book_records[index].pub_year << "\n";
    cout << "Availability: " << (book_records[index].available ? "available" : "unavailable") << "\n";
    cout << "ID: " << book_records[index].book_ID << "\n";
    cout << "========================\n";
    mini_menu();
}

void update_book() {
    if (!book_records.empty()) {
        int choice_to_update, pub_year;
        string author;

        cin.ignore();
        system("cls");
        cout << "Enter book tile: ";
        getline(cin, title);

        cout << "\nSearching...\n";
        int index = search_for_book(title);

        if (index != -1) {
            cout << "choose what to update:\n";
            cout << "\n[1] Title\n[2] Author\n[3] Publication year\n";
            input:
            cin >> choice_to_update;
            cin.ignore();
            system("cls");
            switch (choice_to_update) {
                case 1:
                    cout << "Enter new title: ";
                    getline(cin, title);

                    book_records[index].book_title = title;
                    cout << "\nTitle updated successfully!\n";
                    break;
                case 2:
                    cout << "Enter new author: ";
                    getline(cin, author);

                    book_records[index].author = author;
                    cout << "\nAuthor updated successfully!\n";
                    break;
                case 3:
                    cout << "Enter new publication year: ";
                    cin >> pub_year;

                    book_records[index].pub_year = pub_year;
                    cout << "\nPublication year updated successfully!\n";
                    break;
                default:
                    cout << "\nChoose valid operation: ";
                    goto input;
            }
        } else
            cout << "Book was not found!\n";
        mini_menu();
    } else {
        system("cls");
        cout << "No books available!\n";
        mini_menu();
    }
}

void add_member() {
    system("cls");
    string name;
    cout << "Enter member details:\n";
    cin.ignore();

    cout << "Name: ";
    getline(cin, name);

    name[0] = (char) toupper(name[0]);
    cout << "\nMember added successfully!\n\n";

    cout << "Your member ID: " << member_ID << '\n';
    member newMember = {name, (int) member_ID};//why cast to int?

    member_records.push_back(newMember);
    member_ID++;
    mini_menu(2);
}

void display_all_members() {
    system("cls");
    if (member_records.empty()) cout << "No member records available!\n";
    else {
        for (auto &member: member_records) {
            cout << "========================\n";
            cout << "Member name: " << member.member_name << '\n';
            cout << "Member ID: " << member.member_ID << '\n';
            cout << "Borrowed books: ";
            if (member.borrowed_books.empty()) cout << "none\n";
            else {
                for (int i = 0; i < member.borrowed_books.size() - 1; i++)
                    cout << member.borrowed_books[i] << " ,";

                if (!member.borrowed_books.empty())
                    cout << member.borrowed_books[member.borrowed_books.size() - 1] << '\n';
            }
            cout << "========================\n";
        }
    }
    mini_menu(2);
}

int search_menu() {
    int index;
    if (!member_records.empty()) {
        system("cls");
        cout << "[1] Search by member name\n[2] Search by member ID\n";
        cin >> operation_num;

        index = (operation_num == 1 ? search_member(1) : search_member(2));
        return index;
    } else {
        system("cls");
        cout << "No member records available!\n";

        mini_menu(2);
        return -1;
    }
}

int search_member(int search_by) {//1=name 2=id
    string name;
    int id;
    cin.ignore();
    system("cls");
    if (search_by == 1) {
        cout << "Enter member name: ";
        getline(cin, name);

        name[0] = (char) toupper(name[0]);
        cout << "\nSearching...\n";

        for (int i = 0; i < member_records.size(); i++)
            if (member_records[i].member_name == name) return i;
        return -1;
    } else {
        cout << "Enter member ID: ";
        cin >> id;

        cout << "\nSearching...\n";
        cin.ignore();

        for (int i = 0; i < member_records.size(); i++)
            if (member_records[i].member_ID == id) return i;
        return -1;
    }
}

void display_member(int index) {
    system("cls");
    cout << "========================\n";
    cout << "Member name: " << member_records[index].member_name << '\n';
    cout << "Member ID: " << member_records[index].member_ID << '\n';
    cout << "Borrowed books: ";
    if (member_records[index].borrowed_books.empty()) cout << "none\n";
    else {
        for (int i = 0; i < member_records[index].borrowed_books.size() - 1; i++)
            cout << member_records[index].borrowed_books[i] << ", ";

        if (!member_records[index].borrowed_books.empty())
            cout << member_records[index].borrowed_books[member_records[index].borrowed_books.size() - 1] << '\n';
    }
    cout << "========================\n";
    mini_menu(2);
}

void update_member_name(int index) {
    string name;
    system("cls");
    cout << "Enter new member name: ";
    getline(cin, name);

    name[0] = (char) toupper(name[0]);
    member_records[index].member_name = name;

    cout << "\nName updated successfully!\n";
    mini_menu(2);
}

void delete_member() {
    int index = search_menu();
    char yesNO;
    if (index != -1) {
        cout << "\nMember found!\n";
        cout << "\nAre you sure you want to delete this member?[Y/N]";
        cin >> yesNO;
        if (yesNO == 'y' || yesNO == 'Y') {
            for (auto book: member_records[index].borrowed_books)
                book_records[search_for_book(book)].available = true;

            member_records.erase(member_records.begin() + index);

            cout << "\nMember deleted successfully!\n";
            mini_menu(2);
        } else {
            cout << "\nDeletion was cancelled!\n";
            mini_menu(2);
        }
    } else {
        system("cls");
        cout << "\nMember not found!\n";
        mini_menu(2);
    }
}

void borrow_book() {
    if (!book_records.empty()) {
        int index_m = search_menu();
        if (index_m != -1) {
            system("cls");
            cout << "Enter book tile: ";
            getline(cin, title);
            cout << "\nSearching...\n";

            int index = search_for_book(title);

            if (index != -1) {
                if (book_records[index].available) {
                    cout << "\nBook was found!\n";

                    book_records[index].available = false;

                    cout << '\n' << member_records[index_m].member_name << " borrowed the book "
                         << book_records[index].book_title << ".\n";

                    member_records[index_m].borrowed_books.push_back(title);
                    mini_menu(2);
                } else {
                    cout << "\nBook is not available!\n";
                    mini_menu(2);
                }
            } else {
                cout << "\nBook was not found!\n";
                mini_menu(2);
            }
        } else {
            cout << "\nMember was not found!\n";
            mini_menu(2);
        }
    } else {
        system("cls");
        cout << "No books available!\n";
        mini_menu(2);
    }
}

void return_book() {
    if (!book_records.empty()) {
        int index_m = search_menu();
        if (index_m != -1) {
            system("cls");
            cout << "Enter book tile: ";
            getline(cin, title);

            cout << "\nSearching...\n";
            int index = search_for_book(title);

            if (index != -1) {
                if (!book_records[index].available) {
                    cout << "\nBook was found!\n";
                    book_records[index].available = true;

                    member_records[index_m].borrowed_books.erase(
                                                member_records[index_m].borrowed_books.begin() + index);

                    cout << '\n' << member_records[index_m].member_name << " returned the book "
                         << book_records[index].book_title << ".\n";

                    mini_menu(2);
                } else {
                    cout << "\nBook is not borrowed!\n";
                    mini_menu(2);
                }
            } else {
                cout << "\nBook was not found!\n";
                mini_menu(2);
            }
        } else {
            cout << "\nMember was not found!\n";
            mini_menu(2);
        }
    } else {
        system("cls");
        cout << "No books available!\n";
        mini_menu(2);
    }
}
