class User {
private:
std::string username;
std::string user_id;
std::string login;
std::string password;
int balance;
std::string ownershipIDUser;

public:

User(std::string username, std::string user_id, std::string login, std::string password, int balance, std::string ownershipIDUser) {
this->user_id = user_id;
this->username = username;
this->login = login;
this->password = password;
this->balance = balance;
this->ownershipIDUser = ownershipIDUser;
}

auto getUserID() -> std::string {
return user_id;
}

auto getUsername() -> std::string {
return username;
}

auto setUsername(std::string usernameSet) -> void {
username = usernameSet;
}

auto getLogin() -> std::string {
return login;
}

auto getPassword() -> std::string {
return password;
}

auto getBalance() -> int {
    return balance;
}

auto setBalance(int newBalance) -> void {
    balance = newBalance;
}

auto getOwnershipIDUser() -> std::string {
return ownershipIDUser;
}

auto setOwnershipIDUser(std::string ownershipChangeID) -> void {
ownershipIDUser = ownershipChangeID;
}

};

class Game {
private:
std::string title;
std::string developer;
int yearOfRelease;
int price;
std::string ownershipID;

public:
Game(std::string title, std::string developer, int yearOfRelease, int price, std::string ownershipID) {
this->title = title;
this->developer = developer;
this->yearOfRelease = yearOfRelease;
this->price = price;
this->ownershipID = ownershipID;
}

auto getTitle() -> std::string {
return title;
}

auto getDeveloper() -> std::string {
return developer;
}

auto getYearOfRelease() -> int {
return yearOfRelease;
}

auto getPrice() -> int {
    return price;
}

auto getOwnershipID() -> std::string {
return ownershipID;
}

};
