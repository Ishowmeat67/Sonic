#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


using namespace std;
int role;
string admin_Username, admin_Password, Manager_username, Manager_password, currentPerformance, currentDate, currentTime, paymentMethod, bookingType;
int choice;
int seats_sold, seats_avaliable, seats2_sold, seats2_avaliable = 0;
const int ROWS = 15;
const int COLS = 20;
const int ROWS2 = 15;
const int COLS2 = 20;
char seats[ROWS][COLS];
char seats2[ROWS2][COLS2];
int ROW, COL, ROW2, COL2;
double totalPayment, p1TotalPayment, p2TotalPayment = 0.00;
double showPrice;
bool repeat, menuReturn;
bool e = false;
struct Booking {
    string performance;
    string date;
    string time;
    string payMethod;
    int numSeats = 0;
    double totalPaid = 0.00;
};
vector<pair<int, int>> selectedSeats;
vector<pair<int, int>> selectedSeats2;
vector<Booking> bookingHistory;


int validateInput()

{
    int num;
    while (!(cin >> num))  // keep asking until valid number
    {
        cout << "Invalid number. Please try again" << endl;
        cout << "Enter a number: ";
        cin.clear(); //Reset input errors
        cin.ignore(10000, '\n'); // Remove bad input
        // W3Schools.com. (2025). W3schools.com. https://www.w3schools.com/cpp/cpp_input_validation.asp
    }
    return num;
}
void generateReceipt()
{
    if (currentPerformance == "Performing Arts")
    {
        showPrice = 15.00;
    }
    else if (currentPerformance == "Magic Show")
    {
        showPrice = 25.00;
    }
    cout << "Generating receipt...\n";
    PlaySound(TEXT("receipt.wav"), NULL, SND_FILENAME | SND_SYNC);
    //aJynks. (2012, April 1). PlaySound in C++ Console application? Stack Overflow. https://stackoverflow.com/questions/9961949/playsound-in-c-console-application
    cout << "\n========================================" << endl;
    cout << "           OFFICIAL RECEIPT             " << endl;
    cout << "========================================" << endl;
    cout << " Performance: " << currentPerformance << endl;
    cout << " Date:        " << currentDate << endl;
    cout << " Time:        " << currentTime << endl;
    cout << "----------------------------------------" << endl;
    if (bookingType == "Single Choice")
    {
        for (auto seat : selectedSeats)
        {
            cout << " Seat: Row " << seat.first + 1
                << ", Column " << seat.second + 1 << endl;
        }
    }
    else if (bookingType == "Entire Row")
    {
        cout << " Seats Row: " << ROW << endl;
        cout << " Seat Column: 1 - 20" << endl;
    }
    else if (bookingType == "Entire Column")
    {
        cout << " Seats Row: 1 - 15" << endl;
        cout << " Seats Column: " << COL << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << " BOOKING TYPE: " << bookingType << endl;
    if (bookingType == "Single Choice")
    {
        cout << " Total Seats: " << selectedSeats.size() << endl;
        cout << " Total Paid:  RM " << selectedSeats.size() * showPrice << endl;
    }
    else if (bookingType == "Entire Row")
    {
        cout << " Total Seats: " << 20 << endl;
        cout << " Total Paid:  RM " << 20 * showPrice << endl;
    }
    else if (bookingType == "Entire Column")
    {
        cout << " Total Seats: " << 15 << endl;
        cout << " Total Paid:  RM " << 15 * showPrice << endl;
    }
    cout << "========================================" << endl;
    cout << "Press enter to continue...\n";
    totalPayment += selectedSeats.size() * showPrice;
    cin.ignore();
    cin.get();
}
void paymentSelection()
{
    int paymentChoice;
    cout << "--- SELECT PAYMENT METHOD ---\n";
    cout << "1 = Cash\n";
    cout << "2 = Credit card\n";
    cout << "3 = Touch n Go\n";
    do
    {
        cout << "Enter a number: ";
        paymentChoice = validateInput();

        if (paymentChoice == 1)
        {
            paymentMethod = "Cash";
        }
        else if (paymentChoice == 2)
        {
            paymentMethod = "Credit Card";
        }
        else if (paymentChoice == 3)
        {
            paymentMethod = "Touch n Go";
        }
        else
        {
            cout << "Invalid number! Please try again" << endl;
        }
    } while (!(paymentChoice == 1 || paymentChoice == 2 || paymentChoice == 3));
}
void viewSeats2()
{
    cout << "\nShowing seats for Magic Show" << endl;
    cout << "KEY: @ = Avaliable | * = Waiting for payment | # = Taken\n";
    cout << "COLUMNS  : 1 2 3 4 5 6 7 8 9 10 ---------------- 20" << endl;
    for (int i = 0; i < ROWS2; i++)
    {

        cout << " ROWS " << setw(2) << i + 1 << " : ";
        for (int j = 0; j < COLS2; j++)
        {

            cout << seats2[i][j] << " ";

        }
        cout << endl;
    }
}
void viewSeats()
{
    cout << "\nShowing seats for Performing Arts" << endl;
    cout << "KEY: @ = Avaliable | * = Waiting for payment | # = Taken\n";
    cout << "COLUMNS  : 1 2 3 4 5 6 7 8 9 10 ---------------- 20" << endl;
    for (int i = 0; i < ROWS; i++)
    {

        cout << " ROWS " << setw(2) << i + 1 << " : ";
        for (int j = 0; j < COLS; j++)
        {

            cout << seats[i][j] << " ";

        }
        cout << endl;
    }
}
void bookEntireColumn()
{
    bool success;
    do
    {
        success = true;
        if (currentPerformance == "Performing Arts")
        {
            viewSeats();
        }
        else
        {
            viewSeats2();
        }
        cout << "Enter a column number (1-20) to book the entire column or 0 to cancel: ";
        cin >> COL;
        COL2 = COL;
        if (COL == 0)
        {
            cout << "Cancelled successfully." << endl;
            return;
        }

        if (COL < 1 || COL > COLS)
        {
            cout << "Invalid input! Please try again." << endl;
            success = false;
        }
        else
        {
            if (currentPerformance == "Performing Arts")
            {
                for (int i = 0; i < ROWS; i++)
                    if (seats[i][COL - 1] == '#')
                    {
                        cout << "Sorry. Some seats in this column are already booked." << endl;
                        success = false;
                        break;
                    }
            }
            else
            {
                for (int i = 0; i < ROWS2; i++)
                {
                    if (seats2[i][COL2 - 1] == '#')
                    {
                        cout << "Sorry. Some seats in this column are already booked." << endl;
                        success = false;
                        break;
                    }
                }
                if (seats2[ROW2 - 1][COL2 - 1] == '#')
                {
                    cout << "Sorry. Some seats in this column are already booked." << endl;
                    success = false;
                }
            }
            if (success == true)
            {

                if (currentPerformance == "Performing Arts")
                {
                    for (int i = 0; i < ROWS; i++)
                    {
                        seats[i][COL - 1] = '#';
                    }
                }
                else
                {
                    for (int i = 0; i < ROWS2; i++)
                    {
                        seats2[i][COL2 - 1] = '#';
                    }
                }
                paymentSelection();
                generateReceipt();
                Booking newB;
                newB.performance = currentPerformance;
                newB.date = currentDate;
                newB.time = currentTime;
                newB.payMethod = paymentMethod;
                newB.numSeats = 15;
                newB.totalPaid = 15 * showPrice;
                bookingHistory.push_back(newB);
                menuReturn = true;
                if (currentPerformance == "Performing Arts")
                {
                    p1TotalPayment += 15 * showPrice;
                }
                else
                {
                    p2TotalPayment += 15 * showPrice;
                }
                totalPayment += newB.totalPaid;
            }
        }

    } while (success != true);
}
void bookEntireRow()
{
    bool success;
    do
    {
        success = true;
        if (currentPerformance == "Performing Arts")
        {
            viewSeats();
        }
        else
        {
            viewSeats2();
        }
        cout << "Enter a row number (1-15) to book the entire row or 0 to cancel: ";
        cin >> ROW;
        ROW2 = ROW;
        if (ROW == 0)
        {
            cout << "Cancelled successfully." << endl;
            return;
        }
        if (ROW < 1 || ROW > ROWS)
        {
            cout << "Invalid input! Please try again." << endl;
            success = false;
        }
        else
        {
            if (currentPerformance == "Performing Arts")
            {
                for (int j = 0; j < COLS; j++)
                {
                    if (seats[ROW - 1][j] == '#')
                    {
                        cout << "Sorry. Some seats in this row are already booked." << endl;
                        success = false;
                        break;
                    }
                }
            }
            else
            {
                for (int j = 0; j < COLS2; j++)
                {
                    if (seats2[ROW2 - 1][j] == '#')
                    {
                        cout << "Sorry. Some seats in this row are already booked." << endl;
                        success = false;
                        break;
                    }
                }
            }
            if (success == true)
            {
                if (currentPerformance == "Performing Arts")
                {
                    for (int j = 0; j < COLS; j++)
                    {
                        seats[ROW - 1][j] = '#';
                    }
                }
                else
                {
                    for (int j = 0; j < COLS2; j++)
                    {
                        seats2[ROW2 - 1][j] = '#';
                    }
                }
                paymentSelection();
                generateReceipt();
                menuReturn = true;
                Booking newB;
                newB.performance = currentPerformance;
                newB.date = currentDate;
                newB.time = currentTime;
                newB.payMethod = paymentMethod;
                newB.numSeats = 20;
                newB.totalPaid = 20 * showPrice;
                bookingHistory.push_back(newB);
                if (currentPerformance == "Performing Arts")
                {
                    p1TotalPayment += 20 * showPrice;
                }
                else
                {
                    p2TotalPayment += 20 * showPrice;
                }
                totalPayment += newB.totalPaid;
            }
        }

    } while (success != true);
}
void bookSeats()
{
    do
    {
        do
        {
            if (currentPerformance == "Performing Arts")
            {
                viewSeats();
            }
            else
            {
                viewSeats2();
            }
            cout << "Enter a number (1-15) for row, Type 0 to return to Time selection or -1 to proceed payment\n";
            cout << "Enter a number: ";
            cin >> ROW;
            ROW2 = ROW;
            if (ROW < -1 || ROW > 15)
            {
                cout << "Invalid input! Please try again" << endl;
            }
            else if (ROW == 0 && selectedSeats.size() > 0)
            {
                cout << "You have not pay for the seats yet" << endl;
            }
            else if (ROW == -1 && selectedSeats.size() == 0)
            {
                cout << "You haven't book a seat yet" << endl;
            }
            else if (ROW == 0)
            {
                return;
            }
            else if (ROW == -1 && selectedSeats.size() > 0)
            {
                paymentSelection();
                if (currentPerformance == "Performing Arts")
                {
                    for (auto seat : selectedSeats)
                    {
                        seats[seat.first][seat.second] = '#';
                    }
                }
                else
                {
                    for (auto seat2 : selectedSeats)
                    {
                        seats2[seat2.first][seat2.second] = '#';
                    }
                }
                generateReceipt();
                menuReturn = true;
                Booking newB;
                newB.performance = currentPerformance;
                newB.date = currentDate;
                newB.time = currentTime;
                newB.payMethod = paymentMethod;
                newB.numSeats = selectedSeats.size();
                newB.totalPaid = selectedSeats.size() * showPrice;
                bookingHistory.push_back(newB);
                totalPayment += newB.totalPaid;
                //C++ Structures (struct). (n.d.). Www.w3schools.com. https://www.w3schools.com/cpp/cpp_structs.asp
                if (currentPerformance == "Performing Arts")
                {
                    p1TotalPayment += selectedSeats.size() * showPrice;
                }
                else
                {
                    p2TotalPayment += selectedSeats.size() * showPrice;
                }
                selectedSeats.clear();
                return;
            }
        } while (ROW < 1 || ROW > 15);
        do
        {
            cout << "Enter a number for column: ";
            cin >> COL;
            COL2 = COL;
            if (COL < 1 || COL > 20)
            {
                cout << "Invalid input! Please try again" << endl;
            }
        } while (COL < 1 || COL > 20);
        do
        {
            if (currentPerformance == "Performing Arts")
            {
                if (seats[ROW - 1][COL - 1] == '@')
                {
                    seats[ROW - 1][COL - 1] = '*';
                    selectedSeats.push_back({ ROW - 1, COL - 1 });
                    //GeeksforGeeks. (2024, February 19). How to Create a Vector of Pairs in C++? GeeksforGeeks. 
                    //https://www.geeksforgeeks.org/cpp/how-to-create-vector-of-pairs-in-cpp/
                }
                else
                {
                    cout << "Sorry. This seat is has already been booked. Please choose another seat." << endl;
                }
            }
            else
            {
                if (seats2[ROW2 - 1][COL2 - 1] == '@')
                {
                    seats2[ROW2 - 1][COL2 - 1] = '*';
                    selectedSeats.push_back({ ROW2 - 1, COL2 - 1 });
                }
                else
                {
                    cout << "Sorry. This seat is has already been booked. Please choose another seat." << endl;
                }
            }
            if (menuReturn == true) return;
        } while (repeat != false);
    } while (repeat != true);
}
void bookTypeSeats()
{
    do
    {
        cout << "\nHow would you like to book a seat?\n";
        cout << "1 = Book seats\n";
        cout << "2 = Book an entire row\n";
        cout << "3 = Book an entire column\n";
        cout << "0 = Back to time selection\n";
        cout << "Enter a number: ";
        choice = validateInput();
        switch (choice)
        {
        case 1: bookingType = "Single Choice"; bookSeats(); break;
        case 2: bookingType = "Entire Row"; bookEntireRow(); break;
        case 3: bookingType = "Entire Column"; bookEntireColumn(); break;
        case 0: return;
        default: cout << "Invalid number! Please try again.\n"; continue;
        }
        if (menuReturn == true) return;
    } while (choice != 0);
}
void Performance_Time_Selection() {
    int tChoice;
    do {
        cout << "\n--- SELECT TIME for " << currentPerformance << " ---" << endl;
        cout << "1 = 10.30am - 11.30am" << endl;
        cout << "0 = Back to Date selection" << endl;
        cout << "Enter a number: ";

        tChoice = validateInput();
        if (tChoice == 1) currentTime = "10.30am - 11.30am";
        else if (tChoice == 0) return;
        else { cout << "Invalid number! Please try again.\n"; continue; }

        bookTypeSeats();
        if (menuReturn == true) return;
    } while (tChoice != 0);
}
void Performance_Date_Selection() {
    int dChoice;
    do {
        cout << "\n--- Select DATE for " << currentPerformance << " ---" << endl;
        cout << "1 = 19 May 2026" << endl;
        cout << "0 = Back to performance selection" << endl;
        cout << "Enter a number: ";
        dChoice = validateInput();

        if (dChoice == 1) currentDate = "19 May 2026";
        else if (dChoice == 0) return;
        else { cout << "Invalid number! Please try again.\n";continue; }
        Performance_Time_Selection();
        if (menuReturn == true) return;
    } while (dChoice != 0);
}
void performance_Selection() {
    int pChoice;
    do
    {
        cout << "\n--- Which performance would you like to book? ---" << endl;
        cout << "1 = Performing Arts" << endl;
        cout << "2 = Magic Show" << endl;
        cout << "0 = Back to menu" << endl;
        cout << "Enter a number: ";
        pChoice = validateInput();
        if (pChoice == 1) currentPerformance = "Performing Arts";
        else if (pChoice == 2) currentPerformance = "Magic Show";
        else if (pChoice == 0) return;
        else { cout << "Invalid number! Please try again.\n"; continue; }
        Performance_Date_Selection();
        if (menuReturn == true) return;
    } while (pChoice != 0);
}
void validateAdmin()
{
    do
    {
        cout << "Enter username: ";
        cin >> admin_Username;

        cout << "Enter password: ";
        cin >> admin_Password;

        if (admin_Username == "Jasper" && admin_Password == "admin123")
        {
            cout << "Login successful! Welcome, " << admin_Username << "!" << endl;
        }
        else
        {
            cout << "Invalid login! Try again.\n";
        }
    } while (admin_Username != "Jasper" || admin_Password != "admin123");
}
void validateManager()
{
    do
    {
        cout << "Enter username: ";
        cin >> Manager_username;

        cout << "Enter password: ";
        cin >> Manager_password;

        if (Manager_username == "Irwin" && Manager_password == "manager123")
        {
            cout << "Login successful! Welcome, " << Manager_username << endl;
        }
        else
        {
            cout << "Invalid login! Try again.\n";
        }
    } while (Manager_username != "Irwin" || Manager_password != "manager123");
}
void seatAvailability()
{
    seats_avaliable = 0;
    seats_sold = 0;
    seats2_avaliable = 0;
    seats2_sold = 0;

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (seats[i][j] == '@')
            {
                seats_avaliable++;
            }
            else
            {
                seats_sold++;
            }
        }
    }
    for (int i = 0; i < ROWS2; i++)
    {
        for (int j = 0; j < COLS2; j++)
        {
            if (seats2[i][j] == '@')
            {
                seats2_avaliable++;
            }
            else
            {
                seats2_sold++;
            }
        }
    }
    cout << "\nPerforming Arts" << endl;
    cout << "Number of seats available: " << seats_avaliable << endl;
    cout << "Number of seats sold: " << seats_sold << endl;
    cout << endl;
    cout << "Magic Show" << endl;
    cout << "Number of seats available: " << seats2_avaliable << endl;
    cout << "Number of seats sold: " << seats2_sold << endl;

    cout << "\nPress enter to continue...";
    cin.ignore();
    cin.get();
}
void viewBookingDetails() {
    cout << "\n--- ALL BOOKING DETAILS ---" << endl;
    if (bookingHistory.empty()) {
        cout << "No bookings recorded yet." << endl;
    }
    else {
        for (size_t i = 0; i < bookingHistory.size(); i++) {
            cout << " Booking #" << i + 1 << " | Performance: " << bookingHistory[i].performance
                << "\n  Date: " << bookingHistory[i].date << " | Time: " << bookingHistory[i].time
                << "\n  Seats: " << bookingHistory[i].numSeats
                << " | Total: RM " << fixed << setprecision(2) << bookingHistory[i].totalPaid << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    cout << "\nPress enter to continue...";
    cin.ignore();
    cin.get();
}
void viewPriceList() {
    cout << "\n--- SEAT PRICE LIST ---" << endl;
    cout << "Performing Arts: RM 15.00 each seat" << endl;
    cout << "Magic Show: RM 25.00 each seat" << endl;
    cout << "Fixed price applies to each performances." << endl;
    cout << "--------------------------------" << endl;
    cout << "\nPress enter to continue...";
    cin.ignore();
    cin.get();
}
void viewPaymentDetails() {
    cout << "\n--- PAYMENT HISTORY ---" << endl;
    if (bookingHistory.empty()) {
        cout << "No payments recorded yet." << endl;
    }
    else {
        double grandTotal = 0;

        for (const auto& b : bookingHistory) {
            cout << "Method: " << setw(15) << left << b.payMethod
                << " | Amount: RM " << fixed << setprecision(2) << b.totalPaid << endl;
            grandTotal += b.totalPaid;
        }
        cout << "---------------------------------------" << endl;
        cout << "TOTAL SYSTEM REVENUE: RM " << grandTotal << endl;
    }
    cout << "\nPress enter to continue...";
    cin.ignore();
    cin.get();
}
void adminMenu()
{
    validateAdmin();
    do
    {
        menuReturn = false;
        cout << "\n----- ADMINISTRATOR MENU -----\n";
        cout << "1 = Book seat for customer \n";
        cout << "2 = View price list\n";
        cout << "3 = View booking detials\n";
        cout << "4 = View payment details\n";
        cout << "5 = Logout\n";
        cout << "--------------------------------" << endl;
        cout << "Enter a number: ";
        choice = validateInput();
        switch (choice)
        {
        case 1: performance_Selection(); break;
        case 2: viewPriceList(); break;
        case 3: viewBookingDetails(); break;
        case 4: viewPaymentDetails(); break;
        case 5: cout << "Successfully logout" << endl;
            return;
        default: cout << "Invalid number: Please try again" << endl;
        }
    } while (choice != 5);
}
void managerMenu()
{
    validateManager();
    do
    {
        int choice;
        cout << "\n----- MANAGER MENU -----\n";
        cout << "1 = View total payments" << endl;
        cout << "2 = View number of seats sold" << endl;
        cout << "3 = Logout" << endl;
        cout << "--------------------------------" << endl;
        cout << "Enter a number: " << endl;
        choice = validateInput();
        switch (choice)
        {
        case 1: cout << "Total payment collected for Performing Arts: RM " << p1TotalPayment << endl << 
            "Total payment collected for Magic Show: RM " << p2TotalPayment << endl; break;
        case 2: seatAvailability(); break;
        case 3: cout << "Successfully logout" << endl;
            return;
        default: cout << "Invalid number! Please try again." << endl;
        }
    } while (choice != 3);
}
void initializeSeats()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            seats[i][j] = '@';
        }
    }
    for (int i = 0; i < ROWS2; i++)
    {
        for (int j = 0; j < COLS2; j++)
        {
            seats2[i][j] = '@';
        }
    }
}
int main()
{
    initializeSeats();
    {
        do
        {
            cout << "---------- Main Menu ----------\n";
            cout << "1 = Administrator\n";
            cout << "2 = Manager\n";
            cout << "0 = Exit program\n";
            cout << "--------------------------------\n";
            cout << "Enter a number: " << endl;
            role = validateInput();
            if (role == 1)
            {
                adminMenu();
            }
            else if (role == 2)
            {
                managerMenu();
            }
            else if (role == 0)
            {
                cout << "Exiting program...";
            }
            else
            {
                cout << "Invalid number! Please try again.\n";
                cout << "Enter a number: " << endl;
            }
        } while (!(role == 0));
    }
}
