#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;
//Structs - Prestorted data - Global variables(Mohamed Mostafa Taher)
//Ui Functions(windows.h library) - Search- integration(Mohamed Fadl)
//Sign up--Log in(Mohamed Mostafa Komy)
//Add mood-Delete mood-Validation(Date-Mood-Level)-integration(Mohamed Maher)
//Save && load file--log out(Karim Haggag)
//update mood--display all moods(Mohamed Ali)
//Statistics -- Main menu (Ame Wael)

//Noted: While tasks were divided among team members,
// cllaboration was maintained throughout the project.
// each member contributed to multiple parts beyond their orimary task.




void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printHeader(string title) {
    setColor(11);
    cout << "\n  =================================== \n";
    cout << "    " << title;
    int spaces = 38 - title.length();
    for (int i = 0; i < spaces; i++) cout << " ";
    cout << "\n";
    cout << "  ===================================\n";
    setColor(7);
}

void printLine() {
    setColor(8);
    cout << "  ----------------------------------------\n";
    setColor(7);
}

void printSuccess(string msg) {
    setColor(10);
    cout << "  + " << msg << "\n";
    setColor(7);
}

void printError(string msg) {
    setColor(12);
    cout << "  x " << msg << "\n";
    setColor(7);
}

void printOption(int num, string text) {
    setColor(14);
    cout << "  [" << num << "] ";
    setColor(7);
    cout << text << "\n";
}

struct MoodEntry {
    int day = 0, month = 0, year = 0;
    string moodType = "";
    int moodLevel = 0;
    string note = "";
    string userid;
};

struct UserAccount {
    string username;
    string password;
};

struct MoodStatistics {
    int sumlvls = 0;
    int totalEntries = 0;
    float averageMood = 0.0;
    int happyCount = 0;
    int sadCount = 0;
    int calmCount = 0;
    int angryCount = 0;
    int stressedCount = 0;
};

const int MAX_MOODS = 100;
const int MAX_USERS = 10;

MoodEntry moods[MAX_MOODS] = {
    {1,  4, 2026, "happy",    5, "Great day!",       "user1"},
    {2,  4, 2026, "sad",      2, "Not feeling well", "user1"},
    {3,  4, 2026, "stressed", 5, "New project!",     "user1"},
    {4,  4, 2026, "angry",    3, "Long day",         "user1"},
    {5,  4, 2026, "calm",     4, "Chilling",         "user1"},
    {6,  4, 2026, "angry",    1, "Bad mood",         "user2"},
    {7,  4, 2026, "happy",    5, "Awesome!",         "user2"},
    {8,  4, 2026, "sad",      2, "Missed something", "user2"},
    {9,  4, 2026, "stressed", 4, "Good news",        "user2"},
    {10, 4, 2026, "calm",     3, "Calm day",         "user2"}
};

int moodSize = 10;

UserAccount users[MAX_USERS] = {
    {"user1", "12345678"},
    {"user2", "abcdefgh"}
};

int userCount = 2;
int currentUser = -1;

MoodStatistics stats[12];
//Mohamed Fadl and Mohamed Ali participated in the printmood function because it's related to update function
void printMoodColored(int i) {
    printLine();
    setColor(9);  cout << "  Date  : "; setColor(7);
    cout << moods[i].day << "/" << moods[i].month << "/" << moods[i].year << "\n";

    setColor(9); cout << "  Mood  : ";
    if (moods[i].moodType == "happy" || moods[i].moodType == "Happy")    setColor(10);
    else if (moods[i].moodType == "sad" || moods[i].moodType == "Sad")      setColor(12);
    else if (moods[i].moodType == "angry" || moods[i].moodType == "Angry")    setColor(12);
    else if (moods[i].moodType == "stressed" || moods[i].moodType == "Stressed") setColor(14);
    else if (moods[i].moodType == "calm" || moods[i].moodType == "Calm")     setColor(11);
    cout << moods[i].moodType << "\n";

    setColor(9); cout << "  Level : ";
    for (int s = 0; s < moods[i].moodLevel; s++) { setColor(14); cout << "*"; }
    for (int s = moods[i].moodLevel; s < 5; s++) { setColor(8);  cout << "-"; }
    setColor(7); cout << " (" << moods[i].moodLevel << "/5)\n";

    setColor(9); cout << "  Note  : "; setColor(7);
    cout << moods[i].note << "\n";
    setColor(7);
}

bool isValidMooddate(int dy, int moth, int yr) {
    if (yr < 2000 || yr > 2026) return false;
    if (moth < 1 || moth > 12)  return false;
    if (moth == 1 || moth == 3 || moth == 5 || moth == 7 ||
        moth == 8 || moth == 10 || moth == 12)
        return (dy >= 1 && dy <= 31);
    else if (moth == 4 || moth == 6 || moth == 9 || moth == 11)
        return (dy >= 1 && dy <= 30);
    else if (moth == 2) {
        if (yr % 4 == 0) return (dy >= 1 && dy <= 29);
        else             return (dy >= 1 && dy <= 28);
    }
    return false;
}

bool isValidMoodType(string type) {
    return (type == "happy" || type == "Happy" ||
        type == "sad" || type == "Sad" ||
        type == "angry" || type == "Angry" ||
        type == "stressed" || type == "Stressed" ||
        type == "calm" || type == "Calm");
}

bool isValidMoodLevel(int level) {
    return (level >= 1 && level <= 5);
}

void saveUsers() {
    ofstream file("users.txt");
    if (!file.is_open()) return;
    file << userCount << "\n";
    for (int i = 0; i < userCount; i++)
        file << users[i].username << "\n" << users[i].password << "\n";
    file.close();
}

void saveMoods() {
    ofstream file("moods.txt");
    if (!file.is_open()) return;
    file << moodSize << "\n";
    for (int i = 0; i < moodSize; i++) {
        file << moods[i].day << "\n"
            << moods[i].month << "\n"
            << moods[i].year << "\n"
            << moods[i].moodType << "\n"
            << moods[i].moodLevel << "\n"
            << moods[i].note << "\n"
            << moods[i].userid << "\n";
    }
    file.close();
}

void loadUsers() {
    ifstream file("users.txt");
    if (!file.is_open()) return;
    file >> userCount;
    file.ignore();
    for (int i = 0; i < userCount; i++) {
        getline(file, users[i].username);
        getline(file, users[i].password);
    }
    file.close();
}

void loadMoods() {
    ifstream file("moods.txt");
    if (!file.is_open()) return;
    file >> moodSize;
    file.ignore();
    for (int i = 0; i < moodSize; i++) {
        file >> moods[i].day >> moods[i].month >> moods[i].year;
        file.ignore();
        getline(file, moods[i].moodType);
        file >> moods[i].moodLevel;
        file.ignore();
        getline(file, moods[i].note);
        getline(file, moods[i].userid);
    }
    file.close();
}

bool logout() {
    char choice;
    setColor(14); cout << "\n  Are you sure you want to logout? (y/n): ";
    setColor(7);  cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        saveUsers();
        saveMoods();
        currentUser = -1;
        printSuccess("Data saved. Logged out successfully!");
        return true;
    }

    printError("Logout cancelled.");
    return false;
} 

void signUp() {
    printHeader("        Create New Account        ");

    if (userCount >= 10) {
        printError("User limit reached! (Max 10)");
        return;
    }

    UserAccount x;
    setColor(14); cout << "  Enter username: "; setColor(7);
    cin >> x.username;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == x.username) {
            printError("Username already exists!");
            return;
        }
    }

    setColor(14); cout << "  Enter password: "; setColor(7);
    cin >> x.password;

    if (x.password.length() < 8) {
        printError("Password must be at least 8 characters!");
        return;
    }

    users[userCount].username = x.username;
    users[userCount].password = x.password;
    userCount++;
    printSuccess("Account created successfully!");
}

bool login() {
    printHeader("              Login               ");

    UserAccount x;
    setColor(14); cout << "  Enter username: "; setColor(7);
    cin >> x.username;
    setColor(14); cout << "  Enter password: "; setColor(7);
    cin >> x.password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == x.username &&
            users[i].password == x.password) {
            currentUser = i;
            printSuccess("Welcome back, " + x.username + "!");
            return true;
        }
    }

    printError("Invalid username or password!");
    return false;
}

void addMood() {
    printHeader("           Add New Mood           ");

    if (moodSize >= 100) {
        printError("Memory full! Cannot add more moods.");
        return;
    }

    MoodEntry m;

    setColor(14); cout << "  Enter Day   : "; setColor(7); cin >> m.day;
    setColor(14); cout << "  Enter Month : "; setColor(7); cin >> m.month;
    setColor(14); cout << "  Enter Year  : "; setColor(7); cin >> m.year;

    if (!isValidMooddate(m.day, m.month, m.year)) {
        printError("Invalid date!");
        return;
    }

    setColor(14); cout << "  Enter mood (happy/sad/angry/stressed/calm): ";
    setColor(7);  cin >> m.moodType;

    if (!isValidMoodType(m.moodType)) {
        printError("Invalid mood type!");
        return;
    }

    setColor(14); cout << "  Enter level (1-5): ";
    setColor(7);  cin >> m.moodLevel;

    if (!isValidMoodLevel(m.moodLevel)) {
        printError("Invalid level!");
        return;
    }

    setColor(14); cout << "  Enter note: ";
    setColor(7);  cin.ignore();
    getline(cin, m.note);

    m.userid = users[currentUser].username;
    moods[moodSize] = m;
    moodSize++;
    printSuccess("Mood added successfully!");
}

void displayAllMoods() {
    printHeader("          All Mood Entries        ");

    if (moodSize == 0) {
        printError("No moods found!");
        return;
    }

    int count = 0;
    for (int i = 0; i < moodSize; i++) {
        if (moods[i].userid == users[currentUser].username) {
            count++;
            setColor(13); cout << "  Entry #" << count << "\n"; setColor(7);
            printMoodColored(i);
            printLine();
        }
    }

    if (count == 0)
        printError("No moods found for your account!");
}

void deleteMood() {
    printHeader("           Delete Mood            ");

    if (moodSize == 0) {
        printError("No moods to delete!");
        return;
    }
    displayAllMoods();

    int idx;
    setColor(14); cout << "\n  Enter entry number to delete: ";
    setColor(7);  cin >> idx;

    int userEntries[MAX_MOODS];
    int userCount2 = 0;
    for (int i = 0; i < moodSize; i++) {
        if (moods[i].userid == users[currentUser].username)
            userEntries[userCount2++] = i;
    }

    if (idx < 1 || idx > userCount2) {
        printError("Invalid entry number!");
        return;
    }

    int p = userEntries[idx - 1];

    for (int i = p; i < moodSize - 1; i++)
        moods[i] = moods[i + 1];

    moodSize--;
    printSuccess("Mood deleted successfully!");
}

void updateMood() {
    printHeader("           Update Mood            ");

    if (moodSize == 0) {
        printError("No moods to update!");
        return;
    }

    displayAllMoods();

    int idx;
    setColor(14); cout << "\n  Enter entry number to update: ";
    setColor(7);  cin >> idx;

    int userEntries[MAX_MOODS];
    int userCount2 = 0;
    for (int i = 0; i < moodSize; i++) {
        if (moods[i].userid == users[currentUser].username)
            userEntries[userCount2++] = i;
    }

    if (idx < 1 || idx > userCount2) {
        printError("Invalid entry number!");
        return;
    }

    int realIdx = userEntries[idx - 1];
    MoodEntry& m = moods[realIdx];

    setColor(14); cout << "  New Day   : "; setColor(7); cin >> m.day;
    setColor(14); cout << "  New Month : "; setColor(7); cin >> m.month;
    setColor(14); cout << "  New Year  : "; setColor(7); cin >> m.year;

    if (!isValidMooddate(m.day, m.month, m.year)) {
        printError("Invalid date!");
        return;
    }

    setColor(14); cout << "  New mood (happy/sad/angry/stressed/calm): ";
    setColor(7);  cin >> m.moodType;

    if (!isValidMoodType(m.moodType)) {
        printError("Invalid mood type!");
        return;
    }

    setColor(14); cout << "  New level (1-5): ";
    setColor(7);  cin >> m.moodLevel;

    if (!isValidMoodLevel(m.moodLevel)) {
        printError("Invalid level!");
        return;
    }

    setColor(14); cout << "  New note: ";
    setColor(7);  cin.ignore();
    getline(cin, m.note);

    printSuccess("Mood updated successfully!");
}

void searchByDate() {
    printHeader("          Search by Date          ");
    int d, m, y;

    setColor(14); cout << "  Enter Day   : "; setColor(7); cin >> d;
    setColor(14); cout << "  Enter Month : "; setColor(7); cin >> m;
    setColor(14); cout << "  Enter Year  : "; setColor(7); cin >> y;

    bool found = false;
    for (int i = 0; i < moodSize; i++) {
        if (moods[i].day == d && moods[i].month == m && moods[i].year == y
            && moods[i].userid == users[currentUser].username) {
            printMoodColored(i);
            found = true;
        }
    }

    if (!found) printError("No mood entries found for this date.");
    printLine();
}

void searchByType() {
    printHeader("        Search by Mood Type       ");
    string type;

    setColor(14); cout << "  Enter Type (happy/sad/angry/stressed/calm): ";
    setColor(7);  cin >> type;

    if (!isValidMoodType(type)) {
        printError("Invalid mood type!");
        return;
    }

    bool found = false;
    int  count = 0;

    for (int i = 0; i < moodSize; i++) {
        if (moods[i].moodType == type
            && moods[i].userid == users[currentUser].username) {
            printMoodColored(i);
            found = true;
            count++;
        }
    }

    if (!found)
        printError("No mood entries found for this type.");
    else {
        printLine();
        setColor(10); cout << "  Total found: " << count << " entries.\n"; setColor(7);
    }
}

void searchMenu() {
    int choice;
    do {
        printHeader("            Search Menu           ");
        printOption(1, "Search by Date");
        printOption(2, "Search by Mood Type");
        printOption(0, "Back to Main Menu");
        setColor(14); cout << "\n  Choose: "; setColor(7);
        cin >> choice;

        switch (choice) {
        case 1: searchByDate(); break;
        case 2: searchByType(); break;
        case 0: break;
        default: printError("Invalid choice!");
        }
    } while (choice != 0);
}
//Statistics - Main menu(Amr wael)
void calculateStatistics() {
    if (moodSize == 0) return;
    for (int i = 0; i < 12; i++) stats[i] = MoodStatistics();

    for (int i = 0; i < moodSize; i++) {
        if (moods[i].userid != users[currentUser].username) continue;

        int mt = moods[i].month - 1;
        if (mt < 0 || mt > 11) continue;

        stats[mt].sumlvls += moods[i].moodLevel;
        stats[mt].totalEntries++;

        if (moods[i].moodType == "happy" || moods[i].moodType == "Happy")    stats[mt].happyCount++;
        else if (moods[i].moodType == "sad" || moods[i].moodType == "Sad")      stats[mt].sadCount++;
        else if (moods[i].moodType == "angry" || moods[i].moodType == "Angry")    stats[mt].angryCount++;
        else if (moods[i].moodType == "calm" || moods[i].moodType == "Calm")     stats[mt].calmCount++;
        else if (moods[i].moodType == "stressed" || moods[i].moodType == "Stressed") stats[mt].stressedCount++;
    }

    for (int i = 0; i < 12; i++) {
        if (stats[i].totalEntries > 0)
            stats[i].averageMood = (float)stats[i].sumlvls / stats[i].totalEntries;
    }
}

void showStatistics() {
    calculateStatistics();
    int choice, mt;

    printHeader("          Mood Statistics         ");
    setColor(9); cout << "  1. All Statistics (Overall)\n  2. Statistics for a Month\n";
    setColor(14); cout << "  Choice: "; setColor(7);
    cin >> choice;

    if (choice == 1) {
        MoodStatistics overall;
        int overallSumLvls = 0;

        for (int i = 0; i < 12; i++) {
            overall.totalEntries += stats[i].totalEntries;
            overall.happyCount += stats[i].happyCount;
            overall.sadCount += stats[i].sadCount;
            overall.angryCount += stats[i].angryCount;
            overall.stressedCount += stats[i].stressedCount;
            overall.calmCount += stats[i].calmCount;
            overallSumLvls += stats[i].sumlvls;
        }

        if (overall.totalEntries > 0)
            overall.averageMood = (float)overallSumLvls / overall.totalEntries;

        cout << "\n>>> All Statistics:\n";
        setColor(11); cout << "  Total Entries : "; setColor(7); cout << overall.totalEntries << "\n";
        setColor(11); cout << "  Average Level : "; setColor(7); cout << overall.averageMood << "/5\n";
        printLine();
        setColor(10); cout << "  Happy    : " << overall.happyCount << "\n";
        setColor(12); cout << "  Sad      : " << overall.sadCount << "\n";
        setColor(12); cout << "  Angry    : " << overall.angryCount << "\n";
        setColor(14); cout << "  Stressed : " << overall.stressedCount << "\n";
        setColor(11); cout << "  Calm     : " << overall.calmCount << "\n";
        setColor(7);
        printLine();
    }
    //Bouns
    else if (choice == 2) {
        setColor(9); cout << "  Enter month (1-12): "; setColor(7);
        cin >> mt;

        if (mt >= 1 && mt <= 12) {
            int idx = mt - 1;
            if (stats[idx].totalEntries > 0) {
                cout << "\n>>> Report for Month " << mt << ":\n";
                setColor(11); cout << "  Total Entries : "; setColor(7); cout << stats[idx].totalEntries << "\n";
                setColor(11); cout << "  Average Level : "; setColor(7); cout << stats[idx].averageMood << "/5\n";
                printLine();
                setColor(10); cout << "  Happy    : " << stats[idx].happyCount << "\n";
                setColor(12); cout << "  Sad      : " << stats[idx].sadCount << "\n";
                setColor(12); cout << "  Angry    : " << stats[idx].angryCount << "\n";
                setColor(14); cout << "  Stressed : " << stats[idx].stressedCount << "\n";
                setColor(11); cout << "  Calm     : " << stats[idx].calmCount << "\n";
                setColor(7);
                printLine();
            }
            else {
                printError("No entries found for this month.");
            }
        }
        else {
            printError("Invalid month number!");
        }
    }
    else {
        printError("Invalid choice!");
    }
}

bool mainMenu() {
    int stch, choice;
    bool log = true;

    system("cls");
    setColor(11);
    cout << "\n\n";
    cout << "   ====================================== \n";
    cout << "  |                                      |\n";
    cout << "  |    Digital Mood Tracker System       |\n";
    cout << "  |                                      |\n";
    cout << "   ====================================== \n\n";
    setColor(7);

    while (log) {
        printHeader("             Welcome              ");
        printOption(1, "Sign Up");
        printOption(2, "Login");
        printOption(3, "Exit");
        setColor(14); cout << "\n  Choose: "; setColor(7);
        cin >> stch;

        if (stch == 1) signUp();
        else if (stch == 2) { if (login()) log = false; }
        else if (stch == 3) return false;
        else    printError("Invalid choice!");
    }

    do {
        printHeader("            Main Menu             ");
        printOption(1, "Add Mood");
        printOption(2, "Update Mood");
        printOption(3, "Delete Mood");
        printOption(4, "Show All Moods");
        printOption(5, "Show Statistics");
        printOption(6, "Search Mood");
        printOption(7, "Logout");
        setColor(14); cout << "\n  Choose: "; setColor(7);
        cin >> choice;

        switch (choice) {
        case 1: addMood();         break;
        case 2: updateMood();      break;
        case 3: deleteMood();      break;
        case 4: displayAllMoods(); break;
        case 5: showStatistics();  break;
        case 6: searchMenu();      break;
        case 7:
            if (logout()) break;
            else { choice = 0; continue; }
        default: printError("Invalid choice!");
        }

    } while (choice != 7);

    return true;
}

int main() {
    loadUsers();
    loadMoods();

    while (mainMenu()) {}
    return 0;
}