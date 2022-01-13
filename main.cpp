#include <iostream>
#include <string>
#include "/usr/include/sqlite3.h"
#include "User.h"

sqlite3* db;

//sections
auto loginWindow() -> int;
auto mainSection() -> int;
auto librarySection() -> int;
auto storeSection() -> int;
auto walletSection() -> int;

//database functions
auto authLogin(std::string login) -> void;
auto authPassword(std::string password) -> void;
auto connectDB() -> void;
auto createTableDB() -> void;
auto createTableDBGame() -> void;
auto getValuesFromTableDB() -> void;
auto getValuesFromTableDBGame() -> void;
auto getValueFromTableDB(std::string value) -> void;
auto getValueFromTableDBGame(std::string value) -> void;
auto removeValuesFromTableDB(User user) -> void;
auto removeValuesFromTableDBGame(Game game) -> void;
auto insertValuesToTableDB(User user) -> void;
auto insertValuesToTableDBGame(Game game) -> void;
auto getDetailsFromLoginDB(std::string login) -> void;
auto getDetailsFromPasswordDB(std::string password) -> void;
auto removeTableDB() -> void;
auto removeTableDBGame() -> void;
auto authStore() -> void;
auto authGamePurchase(std::string query, std::string ownership) -> void;
auto updatePriceInDatabase(std::string username, int value) -> void;
auto authGameLibrary(std::string ownership) -> void;
auto updateOIDInDatabase(std::string username, int value) -> void;
auto updatePriceGameInDatabase(std::string query, int value, std::string ownership) -> void;
auto authGameSell(std::string username, std::string query, std::string ownership, int price) -> void;

//variables
bool loginAuth;
bool passwordAuth;
std::string retrieved;
std::string currentUsername;
std::string currentUserID;
std::string currentOwnershipID;
int CurrentWalletBalance;
std::string valueFromDB;

//user objects
User user1("username", "1234", "admin", "adminp", 0, "101");
User user2("username2", "1235", "user", "lol123", 0, "202");

//implement second user!
//implement username change - functionality of userid!

Game game1("Mario", "Nintendo", 1984, 10, "101");
Game game3("Lol", "xd", 666, 5, "101");
Game game4("Test", "TestDev", 2013, 15, "000");
Game game5("Game", "Dev", 2003, 30, "000");
Game game6("Gaming", "Developer", 2009, 50, "000");
Game game7("abc", "bcd", 2000, 20, "000");
Game game8("bbbb", "aaaaa", 2001, 5, "000");
Game game9("jjj", "dddd", 1999, 4, "000");

//callbacks (for getting info from the database)

auto callback(void* NotUsed, int argc, char** argv, char** ColumnName) {
	for (int i = 0; i < argc; i++)
	{
		std::cout << ColumnName[i] << ": " << argv[i] << std::endl;
	}

	std::cout << std::endl;

	return 0;
}

auto callbackRetrieve(void* NotUsed, int argc, char** argv, char** ColumnName) {
	retrieved.clear();
	for (int i = 0; i < argc; i++)
	{
		retrieved += argv[i];
	}

	return 0;
}

auto callbackModify(void* NotUsed, int argc, char** argv, char** ColumnName) {
	return 0;
}

//function definitions

auto main() -> int {

loginWindow();

return 0;
}

auto loginWindow() -> int {

std::cout << std::endl;
std::cout << "=========================================" << std::endl;
std::cout << "Welcome to the Game Store. Please log in:" << std::endl;
std::cout << "=========================================" << std::endl;
std::cout << std::endl;
std::cout << "Login: " << std::endl;
std::string lg;
std::getline(std::cin, lg);
authLogin(lg);
std::cout << "Password: " << std::endl;
std::string ps;
std::getline(std::cin, ps);
authPassword(ps);

if (loginAuth == true && passwordAuth == true) {
		mainSection();
	}
	else {
		std::cout << "Your login and password details could not be authenticated.";
		exit(0);
	}


return 0;
}

auto mainSection() -> int {

std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "=================================" << std::endl;
	std::cout << "Welcome, " + currentUsername + "!" << std::endl;
	std::cout << "=================================" << std::endl;
    std::cout << "What do you want to do? Type: seeLibrary, seeStore, seeWallet, exit" << std::endl;
    std::string request;
    std::getline(std::cin, request);
    if (request == "seeLibrary") {
       librarySection();
    } else if (request == "seeStore") {
       storeSection();
    } else if (request == "seeWallet") {
       walletSection();
	} else if (request == "exit") {
		exit(0);
    } else {
       std::cout << "Wrong prompt." << std::endl;
       mainSection();
    }

return 0;
}

auto librarySection() -> int {

std::cout << std::endl;
std::cout << "==================" << std::endl;
std::cout << "Your game library:" << std::endl;
std::cout << "==================" << std::endl;
std::cout << std::endl;

authGameLibrary(currentOwnershipID);

std::string rq;

std::cout << "Enter the title of the game you want to sell OR type 'x' to exit to the main section:";
std::getline(std::cin, rq);
if (rq == "x") {
	mainSection();
} else {
	std::string pr;
	std::cout << "Enter the price you want to sell it for: " << std::endl;
	std::getline(std::cin, pr);
	authGameSell(currentUsername, rq, currentOwnershipID, std::stoi(pr));
}

std::string rq1;

std::cout << std::endl;
std::cout << "Type 'main' in order to return to main section: ";
std::getline(std::cin, rq1);
if (rq1 == "main") {
	mainSection();
} else {
	std::cerr << "Wrong prompt." << std::endl;
	storeSection();
}

return 0;

}

auto storeSection() -> int {

std::cout << std::endl;

std::cout << "==============================" << std::endl;
std::cout << "Games available in the store: " << std::endl;
std::cout << "==============================" << std::endl;
std::cout << std::endl;
authStore();
std::cout << std::endl;
std::cout << "==========================" << std::endl;
std::cout << "Your wallet's balance is: " << CurrentWalletBalance << "." << std::endl;
std::cout << "==========================" << std::endl;
std::cout << std::endl;

std::string gameBuyQuery;
std::cout << "Enter the title of the game you want to buy OR type 'x' to exit to the main section:" << std::endl;
std::getline(std::cin, gameBuyQuery);
if (gameBuyQuery == "x") {
	mainSection();
} else {
    authGamePurchase(gameBuyQuery, currentOwnershipID);
}

std::string rq;

std::cout << std::endl;
std::cout << "Type 'main' in order to return to main section: ";
std::getline(std::cin, rq);
if (rq == "main") {
	mainSection();
} else {
	std::cerr << "Wrong prompt." << std::endl;
	storeSection();
}

return 0;
}

auto walletSection() -> int {

std::cout << std::endl;
std::cout << std::endl;

std::cout << "====================================" << std::endl;
std::cout << "Your wallet's balance is currently: " << CurrentWalletBalance << "." << std::endl;
std::cout << "====================================" << std::endl;

std::string rq;

std::cout << "Type 'main' in order to return to main section: ";
std::getline(std::cin, rq);
if (rq == "main") {
	mainSection();
} else {
	std::cerr << "Wrong prompt." << std::endl;
	walletSection();
}

return 0;
}

auto connectDB() -> void {

int connectDBcheck = sqlite3_open("mainDatabase.db", &db);

if (connectDBcheck) {
std::cerr << "The database could not be opened.";
} else {
std::cout << "The database was opened successfully.";
}

}

auto createTableDB() -> void {
	std::string sql = "CREATE TABLE USER(" \
		"USERNAME STRING NOT NULL,"
		"USER_ID INTEGER NOT NULL,"
		"LOGIN STRING NOT NULL,"
        "PASSWORD STRING NOT NULL,"
		"BALANCE INTEGER NOT NULL,"
		"OWNERSHIPIDUSER STRING NOT NULL); ";

	sqlite3_open("mainDatabase.db", &db);
	int openDb;
	char* error;

	openDb = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

	if (openDb != SQLITE_OK) {
		std::cerr << "The table could not be created." << std::endl;
		sqlite3_free(error);
	}
	else {
		std::cout << "The table was created successfully." << std::endl;
	}

	std::cout << std::endl;

	sqlite3_close(db);

}

auto createTableDBGame() -> void {
	std::string sql = "CREATE TABLE GAME(" \
		"TITLE STRING NOT NULL,"
		"DEVELOPER STRING NOT NULL,"
		"YEAROFRELEASE INTEGER NOT NULL,"
		"PRICE INTEGER NOT NULL,"
		"OWNERSHIPID STRING NOT NULL); ";

	sqlite3_open("mainDatabase.db", &db);
	int openDb;
	char* error;

	openDb = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

	if (openDb != SQLITE_OK) {
		std::cerr << "The table could not be created." << std::endl;
		sqlite3_free(error);
	}
	else {
		std::cout << "The table was created successfully." << std::endl;
	}

	std::cout << std::endl;

	sqlite3_close(db);

}

auto removeTableDB() -> void {
std::string sql = "DROP TABLE USER";

sqlite3_open("mainDatabase.db", &db);
	int openDb;
	char* error;

	openDb = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

	if (openDb != SQLITE_OK) {
		std::cerr << "The table could not be deleted." << std::endl;
		sqlite3_free(error);
	}
	else {
		std::cout << "The table was deleted successfully." << std::endl;
	}

	std::cout << std::endl;

	sqlite3_close(db);

}

auto removeTableDBGame() -> void {
std::string sql = "DROP TABLE GAME";

sqlite3_open("mainDatabase.db", &db);
	int openDb;
	char* error;

	openDb = sqlite3_exec(db, sql.c_str(), NULL, 0, &error);

	if (openDb != SQLITE_OK) {
		std::cerr << "The table could not be deleted." << std::endl;
		sqlite3_free(error);
	}
	else {
		std::cout << "The table was deleted successfully." << std::endl;
	}

	std::cout << std::endl;

	sqlite3_close(db);

}

auto insertValuesToTableDB(User user) -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string username = user.getUsername();
    std::string userID = user.getUserID();
    std::string login = user.getLogin();
	std::string password = user.getPassword();
	std::string balance = std::to_string(user.getBalance());
    std::string ownershipIDUser = user.getOwnershipIDUser();
	std::string insert = "INSERT INTO USER ('USERNAME', 'USER_ID', 'LOGIN', 'PASSWORD', 'BALANCE', 'OWNERSHIPIDUSER') VALUES ('" + username +"', '" + userID + "', '" 
		+ login + "', '" + password + "', '" + balance + "', '" + ownershipIDUser + "')";
	char* error;
	sqlite3_exec(db, insert.c_str(), callback, 0, &error);
	sqlite3_close(db);
}

auto insertValuesToTableDBGame(Game game) -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string title = game.getTitle();
    std::string developer = game.getDeveloper();
	int yearOfRelease = game.getYearOfRelease();
	int price = game.getPrice();
	std::string ownershipID = game.getOwnershipID();
	std::string insert = "INSERT INTO GAME ('TITLE', 'DEVELOPER', 'YEAROFRELEASE', 'PRICE', 'OWNERSHIPID') VALUES ('" + title +"', '" + developer + "', '" 
		+ std::to_string(yearOfRelease) + "', '" + std::to_string(price) + "', '" + ownershipID + "')";
	char* error;
	sqlite3_exec(db, insert.c_str(), callback, 0, &error);
	sqlite3_close(db);
}

auto removeValuesFromTableDB(User user) -> void {
	sqlite3_open("mainDatabase.db", &db);
    std::string username = user.getUsername();
    std::string userID = user.getUserID();
	std::string remove = "DELETE FROM USER WHERE USERNAME='" + username + +"' AND USER_ID='" + userID + "'";
	char* error;
	sqlite3_exec(db, remove.c_str(), callback, 0, &error);
	sqlite3_close(db);
}

auto removeValuesFromTableDBGame(Game game) -> void {
	sqlite3_open("mainDatabase.db", &db);
    std::string title = game.getTitle();
	std::string ownershipID = game.getOwnershipID();
	std::string remove = "DELETE FROM GAME WHERE TITLE='" + title + +"' AND OWNERSHIPID='" + ownershipID + "'";
	char* error;
	sqlite3_exec(db, remove.c_str(), callback, 0, &error);
	sqlite3_close(db);
}

auto getValuesFromTableDB() -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string get = "SELECT * FROM USER";
	char* error;
	sqlite3_exec(db, get.c_str(), callback, 0, &error);
	sqlite3_close(db);
}

auto getValuesFromTableDBGame() -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string get = "SELECT * FROM GAME";
	char* error;
	sqlite3_exec(db, get.c_str(), callback, 0, &error);
	sqlite3_close(db);
}

auto getValueFromTableDB(std::string value, std::string query) -> void {

sqlite3_open("mainDatabase.db", &db);
	if (value == "USER_ID" || value == "USERNAME" || value == "LOGIN" || value == "PASSWORD" || value == "OWNERSHIPUSERID" || value == "BALANCE") {
		std::string get = "SELECT " + value + " FROM USER WHERE USERNAME='" + query + "'";
		char* error;
		if (sqlite3_exec(db, get.c_str(), callbackRetrieve, 0, &error)) {
			std::cout << "Failed to retrieve." << std::endl;
		} else {
			valueFromDB = retrieved;
		}
	}
	else {
		std::cerr << "The column name you've input does not exist in the database." << std::endl;
	}

	sqlite3_close(db);

}

auto getValueFromTableDBGame(std::string value, std::string query) -> void {

sqlite3_open("mainDatabase.db", &db);
	if (value == "TITLE" || value == "DEVELOPER" || value == "YEAROFRELEASE" || value == "OWNERSHIPID" || value == "PRICE") {
		std::string get = "SELECT " + value + " FROM GAME WHERE TITLE='" + query + "'";
		char* error;
		if (sqlite3_exec(db, get.c_str(), callbackRetrieve, 0, &error)) {
			std::cout << "Failed to retrieve." << std::endl;
		} else {
			valueFromDB = retrieved;
		}
	}
	else {
		std::cerr << "The column name you've input does not exist in the database." << std::endl;
	}

	sqlite3_close(db);

}


auto getDetailsFromLoginDB(std::string login) -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string getUsername = "SELECT USERNAME FROM USER WHERE LOGIN='" + login + "'";
    std::string getUserID = "SELECT USER_ID FROM USER WHERE LOGIN='" + login + "'";
	std::string getOwnershipID = "SELECT OWNERSHIPIDUSER FROM USER WHERE LOGIN='" + login + "'";
	std::string getBalance = "SELECT BALANCE FROM USER WHERE LOGIN='" + login + "'";
	char* error;
	int gUsername = sqlite3_exec(db, getUsername.c_str(), callbackRetrieve, 0, &error);
	if (gUsername) {
		std::cout << "Failed to retrieve." << std::endl;
	}
	else {
		currentUsername = retrieved;
	}
    int gUserID = sqlite3_exec(db, getUserID.c_str(), callbackRetrieve, 0, &error);
    if (gUserID) {
        std::cout << "Failed to retrieve." << std::endl;
    } else {
        currentUserID = retrieved;
    }
	int gOwnershipIDUser = sqlite3_exec(db, getOwnershipID.c_str(), callbackRetrieve, 0, &error);
	if (gOwnershipIDUser) {
        std::cout << "Failed to retrieve." << std::endl;
    } else {
        currentOwnershipID = retrieved;
    }
	int gBalance = sqlite3_exec(db, getBalance.c_str(), callbackRetrieve, 0, &error);
	if (gBalance) {
		std::cout << "Failed to retrieve." << std::endl;
	} else {
		CurrentWalletBalance = std::stoi(retrieved);
	}

	sqlite3_close(db);
}

auto getDetailsFromPasswordDB(std::string password) -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string getUsername = "SELECT USERNAME FROM USER WHERE PASSWORD='" + password + "'";
    std::string getUserID = "SELECT USER_ID FROM USER WHERE PASSWORD='" + password + "'";
	std::string getOwnershipID = "SELECT OWNERSHIPIDUSER FROM USER WHERE PASSWORD='" + password + "'";
	std::string getBalance = "SELECT BALANCE FROM USER WHERE PASSWORD='" + password + "'";
	char* error;
	int gUsername = sqlite3_exec(db, getUsername.c_str(), callbackRetrieve, 0, &error);
	if (gUsername) {
		std::cout << "Failed to retrieve." << std::endl;
	}
	else {
		currentUsername = retrieved;
	}
    int gUserID = sqlite3_exec(db, getUserID.c_str(), callbackRetrieve, 0, &error);
    if (gUserID) {
        std::cout << "Failed to retrieve." << std::endl;
    } else {
        currentUserID = retrieved;
    }
	int gOwnershipIDUser = sqlite3_exec(db, getOwnershipID.c_str(), callbackRetrieve, 0, &error);
	if (gOwnershipIDUser) {
        std::cout << "Failed to retrieve." << std::endl;
    } else {
        currentOwnershipID = retrieved;
    }
	int gBalance = sqlite3_exec(db, getBalance.c_str(), callbackRetrieve, 0, &error);
	if (gBalance) {
		std::cout << "Failed to retrieve." << std::endl;
	} else {
		CurrentWalletBalance = std::stoi(retrieved);
	}

	sqlite3_close(db);
}

auto authLogin(std::string login) -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string get = "SELECT LOGIN FROM USER WHERE LOGIN='" + login + "'";
	char* error;
	int auth = sqlite3_exec(db, get.c_str(), callbackRetrieve, 0, &error);
	if (login == retrieved) {
		loginAuth = true;
		getDetailsFromLoginDB(login);
	}
	else {
		loginAuth = false;
	}

	sqlite3_close(db);
}


auto authPassword(std::string password) -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string get = "SELECT PASSWORD FROM USER WHERE PASSWORD='" + password + "'";
	char* error;
	int auth = sqlite3_exec(db, get.c_str(), callbackRetrieve, 0, &error);
	if (password == retrieved) {
		passwordAuth = true;
		getDetailsFromPasswordDB(password);
	}
	else {
		passwordAuth = false;
	}

	sqlite3_close(db);
}

auto authGameLibrary(std::string ownership) -> void {
sqlite3_open("mainDatabase.db", &db);
	std::string get = "SELECT TITLE, DEVELOPER, YEAROFRELEASE FROM GAME WHERE OWNERSHIPID='" + ownership + "'";
	char* error;
	sqlite3_exec(db, get.c_str(), callback, 0, &error);
	sqlite3_close(db);
}

auto authStore() -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string get = "SELECT TITLE, DEVELOPER, YEAROFRELEASE, PRICE FROM GAME WHERE OWNERSHIPID='000'";
	char* error;
	if (sqlite3_exec(db, get.c_str(), callback, 0, &error)) {
		std::cout << "Failed to view store." << std::endl;
	} else {
		std::cout << "";
	}
	sqlite3_close(db);
}

auto updatePriceInDatabase(std::string username, int value) -> void {
    sqlite3_open("mainDatabase.db", &db);
	std::string update = "UPDATE USER SET BALANCE='" + std::to_string(value) + "' WHERE USERNAME='" + username + "'";
	char* error;
	if (sqlite3_exec(db, update.c_str(), callbackModify, 0, &error)) {
			std::cerr << "Update failed." << std::endl;
		} else {
			std::cout << "Update successful." << std::endl;
		}

	sqlite3_close(db);

}

auto updatePriceGameInDatabase(std::string query, int value, std::string ownership) -> void {
	sqlite3_open("mainDatabase.db", &db);
	std::string update = "UPDATE GAME SET PRICE='" + std::to_string(value) + "' WHERE TITLE='" + query + "' AND OWNERSHIPID='" + ownership + "'";
	char* error;
	if (sqlite3_exec(db, update.c_str(), callbackModify, 0, &error)) {
			std::cerr << "Update failed." << std::endl;
		} else {
			std::cout << "Update successful." << std::endl;
		}

	sqlite3_close(db);
}

auto updateOIDInDatabase(std::string ow, int value) -> void {
    sqlite3_open("mainDatabase.db", &db);
	std::string update = "UPDATE GAME SET OWNERSHIPID='" + std::to_string(value) + "' WHERE TITLE='" + ow + "'";
	char* error;
	if (sqlite3_exec(db, update.c_str(), callbackModify, 0, &error)) {
			std::cerr << "Failed." << std::endl;
		} else {
			std::cout << "Your update was successful!" << std::endl;
		}

	sqlite3_close(db);

}

auto authGamePurchase(std::string query, std::string ownership) -> void {
	sqlite3_open("mainDatabase.db", &db);	
	getValueFromTableDBGame("TITLE", query);
	if (query == valueFromDB) {
       getValueFromTableDBGame("PRICE", query);
	   if (CurrentWalletBalance >= std::stoi(valueFromDB)) {
		updateOIDInDatabase(query, std::stoi(ownership));
		int updatedBalance = CurrentWalletBalance - std::stoi(valueFromDB);
		CurrentWalletBalance = updatedBalance;
		updatePriceInDatabase(currentUsername, updatedBalance);
	} else {
		std::cerr << "Not enough funds." << std::endl;
	}
	} else {
		std::cerr << "The name you've input does not exist in the database." << std::endl;
	}
	
	
	sqlite3_close(db);
}

auto authGameSell(std::string username, std::string query, std::string ownership, int price) -> void {
	sqlite3_open("mainDatabase.db", &db);
	getValueFromTableDBGame("TITLE", query);
	if (query == valueFromDB) {
		updatePriceGameInDatabase(query, price, ownership);
        int updatedBalance = CurrentWalletBalance + price;
		CurrentWalletBalance = updatedBalance;
		updatePriceInDatabase(currentUsername, updatedBalance);
		updateOIDInDatabase(query, 000);
	} else {
		std::cerr << "The name you've input does not exist in the database." << std::endl;
	}

    sqlite3_close(db);
}
