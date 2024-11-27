#include <bits/stdc++.h>

using namespace std;

struct RoomInfo {
    int roomNumber;
    char type[30];
    char guestName[50];
    int isBooked; // 0 = Not Booked, 1 = Booked
};

RoomInfo room;
fstream file;

void password();
void headline();
void mainMenu();
void addRoom();
void listRooms();
void bookRoom();
void checkoutRoom();
void searchRoom();
void editRoom();
void deleteRoom();
void help();

int main() {
    password();
    return 0;
}

void headline() {
    cout << "\n\n\t\t ___Hotel Management System___\n\n\t\t";
}

void password() {
    headline();

    string pass1 = "admin";
    string pass2;

    cout << "\n\tEnter password: ";
    cin >> pass2;

    while (true) {
        if (pass1 == pass2) {
            cout << "\n\n\tPassword matched.\n";
            cout << "\tPress any key to continue...";
            cin.ignore();
            cin.get();
            break;
        } else {
            cout << "\n\n\tTry again. Enter password: ";
            cin >> pass2;
        }
    }
    mainMenu();
}

void mainMenu() {
    int choice;

    cout << "\n\n\t ____ Main Menu ____\n";
    cout << "\n\n\t 1. Add Room";
    cout << "\n\n\t 2. List Rooms";
    cout << "\n\n\t 3. Book Room";
    cout << "\n\n\t 4. Checkout Room";
    cout << "\n\n\t 5. Search Room";
    cout << "\n\n\t 6. Edit Room";
    cout << "\n\n\t 7. Delete Room";
    cout << "\n\n\t 8. Help";
    cout << "\n\n\t 9. Exit";
    cout << "\n\t\t---------------";
    cout << "\n\n\tEnter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            addRoom();
            break;
        case 2:
            listRooms();
            break;
        case 3:
            bookRoom();
            break;
        case 4:
            checkoutRoom();
            break;
        case 5:
            searchRoom();
            break;
        case 6:
            editRoom();
            break;
        case 7:
            deleteRoom();
            break;
        case 8:
            help();
            break;
        case 9:
            cout << "\n\n\tExiting...\n";
            exit(0);
        default:
            cout << "\nInvalid choice. Try again.";
            mainMenu();
    }
}

void addRoom() {
    int roomNumber, count = 0;
    cout << "\n\n\t ____ Add Room ____\n\n";
    file.open("rooms.dat", ios::in | ios::out | ios::binary | ios::app);
    cout << "\tEnter Room Number: ";
    cin >> roomNumber;

    file.seekg(0, ios::beg);
    while (file.read(reinterpret_cast<char*>(&room), sizeof(room))) {
        if (roomNumber == room.roomNumber) {
            cout << "\n\n\tThis room already exists!";
            count = 1;
            break;
        }
    }

    if (count == 1) {
        file.close();
        cin.ignore();
        cin.get();
        mainMenu();
        return;
    }

    room.roomNumber = roomNumber;
    cout << "\n\tEnter Room Type (Single/Double/Suite): ";
    cin >> room.type;
    room.isBooked = 0; // Not booked initially
    strcpy(room.guestName, "None");

    file.clear();
    file.write(reinterpret_cast<char*>(&room), sizeof(room));
    file.close();

    cout << "\n\n\tRoom added successfully!";
    cin.ignore();
    cin.get();
    mainMenu();
}

void listRooms() {
    int count = 0;
    cout << "\n\n\t\t ******** Room List *****\n\n";
    cout << setw(10) << "Room No" << setw(20) << "Type" << setw(20) << "Guest Name" << setw(15) << "Status" << "\n\n";

    file.open("rooms.dat", ios::in | ios::binary);
    while (file.read(reinterpret_cast<char*>(&room), sizeof(room))) {
        cout << setw(10) << room.roomNumber
             << setw(20) << room.type
             << setw(20) << (room.isBooked ? room.guestName : "None")
             << setw(15) << (room.isBooked ? "Booked" : "Available") << endl;
        count++;
    }
    file.close();

    if (count == 0) {
        cout << "\nNo rooms available.";
    }

    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get();
    mainMenu();
}

void bookRoom() {
    int roomNumber, count = 0;
    cout << "\n\n\t\t ****** Book Room *****\n\n";
    file.open("rooms.dat", ios::in | ios::out | ios::binary);

    cout << "\tEnter Room Number to Book: ";
    cin >> roomNumber;

    while (file.read(reinterpret_cast<char*>(&room), sizeof(room))) {
        if (room.roomNumber == roomNumber) {
            count = 1;
            if (room.isBooked) {
                cout << "\n\n\tRoom is already booked by: " << room.guestName;
            } else {
                cout << "\n\n\tRoom is available. Enter Guest Name: ";
                cin.ignore();
                cin.getline(room.guestName, 50);
                room.isBooked = 1;

                file.seekp(-static_cast<int>(sizeof(room)), ios::cur);
                file.write(reinterpret_cast<char*>(&room), sizeof(room));
                cout << "\n\n\tRoom booked successfully!";
            }
            break;
        }
    }

    file.close();

    if (count == 0) {
        cout << "\n\n\tRoom not found.";
    }

    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get();
    mainMenu();
}

void checkoutRoom() {
    int roomNumber, count = 0;
    cout << "\n\n\t\t ****** Checkout Room *****\n\n";
    file.open("rooms.dat", ios::in | ios::out | ios::binary);

    cout << "\tEnter Room Number to Checkout: ";
    cin >> roomNumber;

    while (file.read(reinterpret_cast<char*>(&room), sizeof(room))) {
        if (room.roomNumber == roomNumber) {
            count = 1;
            if (!room.isBooked) {
                cout << "\n\n\tRoom is already vacant.";
            } else {
                cout << "\n\n\tChecking out room. Guest: " << room.guestName;
                room.isBooked = 0;
                strcpy(room.guestName, "None");

                file.seekp(-static_cast<int>(sizeof(room)), ios::cur);
                file.write(reinterpret_cast<char*>(&room), sizeof(room));
                cout << "\n\n\tRoom checked out successfully!";
            }
            break;
        }
    }

    file.close();

    if (count == 0) {
        cout << "\n\n\tRoom not found.";
    }

    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get();
    mainMenu();
}

void searchRoom() {
    int roomNumber, count = 0;
    cout << "\n\n\t\t ****** Search Room *****\n\n";
    file.open("rooms.dat", ios::in | ios::binary);

    cout << "\tEnter Room Number to Search: ";
    cin >> roomNumber;

    while (file.read(reinterpret_cast<char*>(&room), sizeof(room))) {
        if (room.roomNumber == roomNumber) {
            count = 1;
            cout << "\n\n\tRoom Found:";
            cout << "\n\tRoom Number: " << room.roomNumber;
            cout << "\n\tType: " << room.type;
            cout << "\n\tGuest Name: " << (room.isBooked ? room.guestName : "None");
            cout << "\n\tStatus: " << (room.isBooked ? "Booked" : "Available");
            break;
        }
    }

    file.close();

    if (count == 0) {
        cout << "\n\n\tRoom not found.";
    }

    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get();
    mainMenu();
}

void editRoom() {
    int roomNumber, count = 0;
    cout << "\n\n\t\t ****** Edit Room Details *****\n\n";
    file.open("rooms.dat", ios::in | ios::out | ios::binary);

    cout << "\tEnter Room Number to Edit: ";
    cin >> roomNumber;

    while (file.read(reinterpret_cast<char*>(&room), sizeof(room))) {
        if (room.roomNumber == roomNumber) {
            count = 1;
            cout << "\n\n\tEditing Room Details:";
            cout << "\n\tCurrent Type: " << room.type;
            cout << "\n\tEnter New Type: ";
            cin >> room.type;

            file.seekp(-static_cast<int>(sizeof(room)), ios::cur);
            file.write(reinterpret_cast<char*>(&room), sizeof(room));
            cout << "\n\n\tRoom details updated successfully!";
            break;
        }
    }

    file.close();

    if (count == 0) {
        cout << "\n\n\tRoom not found.";
    }

    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get();
    mainMenu();
}

void deleteRoom() {
    int roomNumber, count = 0;
    cout << "\n\n\t\t ****** Delete Room *****\n\n";
    file.open("rooms.dat", ios::in | ios::binary);
    fstream tempFile("temp.dat", ios::out | ios::binary);

    cout << "\tEnter Room Number to Delete: ";
    cin >> roomNumber;

    while (file.read(reinterpret_cast<char*>(&room), sizeof(room))) {
        if (room.roomNumber == roomNumber) {
            count = 1;
            cout << "\n\n\tDeleting Room...";
        } else {
            tempFile.write(reinterpret_cast<char*>(&room), sizeof(room));
        }
    }

    file.close();
    tempFile.close();

    if (count == 0) {
        cout << "\n\n\tRoom not found.";
    } else {
        remove("rooms.dat");
        rename("temp.dat", "rooms.dat");
        cout << "\n\n\tRoom deleted successfully!";
    }

    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get();
    mainMenu();
}

void help() {
    cout << "\n\n\t\t ****** Help Section *****\n\n";
    cout << "\n\t1. This is a simple Hotel Management System.";
    cout << "\n\t2. Password is: admin.";
    cout << "\n\t3. You can add rooms, book rooms, and manage them.";
    cout << "\n\t4. Follow the main menu options.";
    cout << "\n\t5. Thank you.\n\n";

    cout << "\n\n\tPress any key to return to the main menu...";
    cin.ignore();
    cin.get();
    mainMenu();
}
