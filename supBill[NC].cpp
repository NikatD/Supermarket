#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits> // Necessary for input validation

using namespace std;

// Define structure for a product
struct Product {
    int pcode;
    float price;
    float discount;
    string pname;
};

void intro();
void menu();
bool loginAdmin();
void registerAdmin();
void changeAdminPassword();
void administrator();
void buyer();
void add();
void edit();
void rem();
void list();
void receipt();

int main() {

    intro();
    system("cls");
    menu();
    return 0;
}

void intro()
{
    cout << "\n\n   ********************************************************************************************\n";
    cout << "\n\t\tWelcome to QuickCheck - Your Efficient Supermarket Billing Solution!\t\t\n";
    cout << "\n  Our user-friendly interface ensures fast and accurate transactions,allowing you to breeze through ";
    cout << "\n       the checkout with ease and convenient billing process for both customers and staff.";
    cout << "\n\n   ********************************************************************************************\n\n";
    cout << "\tPress any key to get started  ";
    cin.get();
}

void menu() {
    int choice;

    while (true) {
        cout << "|-----------------------------------|\n";
        cout << "|       SUPERMARKET MAIN MENU       |\n";
        cout << "|-----------------------------------|\n";
        cout << "|         1. ADMINISTRATOR          |\n";
        cout << "|         2. BUYER                  |\n";
        cout << "|         3. EXIT                   |\n";
        cout << "|___________________________________|\n";

        cout << "\nSelect Option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int adminChoice;
                cout << " ----------------------------------\n";
                cout << "|       ADMINISTRATOR MENU         |\n";
                cout << "|----------------------------------|\n";
                cout << "|         1. REGISTER              |\n";
                cout << "|         2. LOGIN                 |\n";
                cout << "|         3. CHANGE PASSWORD       |\n"; // Added option to change password
                cout << "|__________________________________|\n";

                cout << "\nSelect Option: ";
                cin >> adminChoice;

                switch (adminChoice) {
                    case 1:
                        // Call function to handle administrator registration
                        registerAdmin();
                        break;

                    case 2:
                        if (loginAdmin()) {
                            administrator();
                        } else {
                            cout << "Invalid Email/Password ! \n";
                        }
                        break;

                    case 3:
                        // Call function to handle changing administrator password
                         changeAdminPassword();
                        break;

                    default:
                        cout << "\nInvalid Choice ! \n";
                        break;
                }
                break;
            }

            case 2:
                // Call function to handle buyer menu
                buyer();
                break;

            case 3:
                exit(0);

            default:
                cout << "Please select from the given Options ! \n";
                break;
        }
    }
}

bool loginAdmin() {
    string email, password;
    cout << "\nEnter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

    ifstream adminFile("admin_passwords.txt");
    if (adminFile.is_open()) {
        string storedEmail, storedPassword;
        while (adminFile >> storedEmail >> storedPassword) {
            if (storedEmail == email && storedPassword == password) {
                cout << "\nLogin Successful!\n";
                adminFile.close();
                return true;
            }
        }
        adminFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }
    return false;
}

void registerAdmin() {
    string email, password;
    cout << "\nEnter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

    ofstream adminFile("admin_passwords.txt", ios::app);
    if (adminFile.is_open()) {
        adminFile << email << " " << password << endl;
        adminFile.close();
        cout << "\nRegistration Successful!\n";
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }
}

void changeAdminPassword() {
    string email, oldPassword, newPassword;
    cout << "\nEnter Email: ";
    cin >> email;
    cout << "Enter Old Password: ";
    cin >> oldPassword;

    ifstream adminFile("admin_passwords.txt");
    ofstream tempFile("temp.txt");

    if (adminFile.is_open() && tempFile.is_open()) {
        string storedEmail, storedPassword;
        while (adminFile >> storedEmail >> storedPassword) {
            if (storedEmail == email && storedPassword == oldPassword) {
                cout << "Enter New Password: ";
                cin >> newPassword;
                tempFile << storedEmail << " " << newPassword << endl;
                cout << "\nPassword Changed Successfully!\n";
            } else {
                tempFile << storedEmail << " " << storedPassword << endl;
            }
        }
        adminFile.close();
        tempFile.close();
        remove("admin_passwords.txt");
        rename("temp.txt", "admin_passwords.txt");
    } else {
        cout << "Error: Unable to open files.\n";
    }
}

void administrator() {
    int choice;
    while (true) {
        cout << "|---------------------------------|\n";
        cout << "|       ADMINISTRATOR MENU        |\n";
        cout << "|_________________________________|\n";
        cout << "|       1. ADD PRODUCT            |\n";
        cout << "|       2. MODIFY PRODUCT         |\n";
        cout << "|       3. DELETE PRODUCT         |\n";
        cout << "|       4. BACK TO MENU           |\n";
        cout << "|_________________________________|\n";

        cout << "\nPlease Enter your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;

            case 2:
                edit();
                break;

            case 3:
                rem();
                break;

            case 4:
                return; // Return to the previous menu

            default:
                cout << "\nInvalid Choice ! \n";
                break;
        }
    }
}

void edit() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n      [ MODIFY THE PRODUCT ]      \n";
    cout << "                                  \n";
    cout << "Product Code: ";
    while (!(cin >> pkey)) {
        cout << "Invalid input. Please enter an integer for the product code: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\nFile doesn't exist! \n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        Product temp;
        data >> temp.pcode >> temp.pname >> temp.price >> temp.discount;
        while (!data.eof()) {
            if (pkey == temp.pcode) {
                cout << "\nProduct new Code: ";
                while (!(cin >> temp.pcode)) {
                    cout << "Invalid input. Please enter an integer for the product code: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Name of the Product: ";
                cin >> temp.pname;

                cout << "Price of the Product: ";
                while (!(cin >> temp.price)) {
                    cout << "Invalid input. Please enter a float for the price: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Discount: ";
                while (!(cin >> temp.discount)) {
                    cout << "Invalid input. Please enter a float for the discount: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                data1 << temp.pcode << " " << temp.pname << " " << temp.price << " " << temp.discount << endl;
                cout << "\nRecord Edited! \n";
                token++;
            } else {
                data1 << temp.pcode << " " << temp.pname << " " << temp.price << " " << temp.discount << endl;
            }
            data >> temp.pcode >> temp.pname >> temp.price >> temp.discount;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\nRecord Not Found! \n";
        }
    }
}

void rem() {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n     [ DELETE PRODUCT ]     \n";
    cout << "                              \n";
    cout << "Product Code: ";
    while (!(cin >> pkey)) {
        cout << "Invalid input. Please enter an integer for the product code: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\nFile doesn't exist! \n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        Product temp;
        data >> temp.pcode >> temp.pname >> temp.price >> temp.discount;
        while (!data.eof()) {
            if (temp.pcode == pkey) {
                cout << "\n\nProduct Deleted Successfully! \n";
                token++;
            } else {
                data1 << temp.pcode << " " << temp.pname << " " << temp.price << " " << temp.discount << endl;
            }
            data >> temp.pcode >> temp.pname >> temp.price >> temp.discount;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\nRecord not Found! \n";
        }
    }
}

void buyer() {
    int choice;
    while (true) {
        cout << " -------------------------------\n";
        cout << "|           BUYER MENU          |\n";
        cout << "|-------------------------------|\n";
        cout << "|       1. BUY PRODUCT          |\n";
        cout << "|       2. BACK TO MENU         |\n";
        cout << "|_______________________________|\n";

        cout << "\nPlease Enter your Choice: ";
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                receipt();
                break;

            case 2:
                return; // Return to the previous menu

            default:
                cout << "\nInvalid Choice ! \n";
                break;
        }
    }
}

void list() {
    fstream data;
    data.open("database.txt", ios::in);

    cout << " ______________________________________\n";
    cout << "|P.No   Name    Price   Discount(in %) | \n";
    cout << "|______________________________________| \n";

    if (!data) {
        cout << "No products available in the store." << endl;
    } else {
        Product temp;
        bool productAvailable = false;

        while (data >> temp.pcode >> temp.pname >> temp.price >> temp.discount) {
            cout << "  " << temp.pcode << "\t" << temp.pname << "\t" << temp.price << "\t" << temp.discount << "\n";
            productAvailable = true;
        }

        if (!productAvailable) {
            cout << "No products available in the store." << endl;
        }
    }

    data.close();
}


void receipt() {
    system("cls");
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n         [ PRODUCT LIST ]       \n";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\nEmpty Database! \n";
        return;
    } else {
        data.close();

        list();
        cout << "\n\nPlease Place the Order!\n";
        do {
            cout << "\n\nEnter Product Code (or enter -1 to exit): ";
            while (!(cin >> arrc[c])) {
                cout << "Invalid input. Please enter an integer for the product code: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (arrc[c] == -1) {
                cout << "\nExiting order placement...\n";
                return;
            }
            cout << "\nEnter the Product Quantity: ";
            while (!(cin >> arrq[c])) {
                cout << "Invalid input. Please enter an integer for the product quantity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            c++;
            cout << "\n\nDo you want to Buy another Product? If Yes, then Press 'y' else 'n' ! \n";
            cin >> choice;
        } while (choice == 'y');

        system("cls");
        cout << "\n\n  __________________________  [ RECEIPT ]  __________________________\n";
        cout << "\nP.No\tName\tQuantity\tPrice\tAmount \t Amount with Discount";

        Product temp;
        for (int i = 0; i < c; i++) {
            data.open("database.txt", ios::in);
            while (data >> temp.pcode >> temp.pname >> temp.price >> temp.discount) {
                if (temp.pcode == arrc[i]) {
                    amount = temp.price * arrq[i];
                    dis = amount - (amount * temp.discount / 100);
                    total += dis;
                    cout << "\n" << temp.pcode << "\t" << temp.pname << " \t " << arrq[i] << " \t\t " << temp.price << " \t " << amount << "  \t  " << dis;
                }
            }
            data.close();
        }
    }

    cout << "\n\n     Total Amount: ETB. " << total << "\n\n";
}

void add() {
    system("cls");
    fstream data;
    Product product;
    int token = 0;

    cout << "\n\n        [ ADD NEW PRODUCT ]        \n";
    cout << "                               \n";

    // Input validation for product code
    cout << "Product Code of the Product: ";
    while (!(cin >> product.pcode)) {
        cout << "Invalid input. Please enter an integer for the product code: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Name of the Product: ";
    cin >> product.pname;

    // Input validation for price
    cout << "Price of the Product: ";
    while (!(cin >> product.price)) {
        cout << "Invalid input. Please enter a float for the price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Input validation for discount
    cout << "Discount on Product (in %): ";
    while (!(cin >> product.discount)) {
        cout << "Invalid input. Please enter a float for the discount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Open the data file in input mode to check for existing records
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "Error: Unable to open file for reading.\n";
        return;
    } else {
        data.close();
    }

    // Reopen the data file in append mode to add the new record
    data.open("database.txt", ios::app);
    if (!data) {
        cout << "Error: Unable to open file for writing.\n";
        return;
    }

    // Write the new record to the file
    data << product.pcode << " " << product.pname << " " << product.price << " " << product.discount << endl;
    data.close();
    cout << "\nRecord Inserted! \n\n";
}
