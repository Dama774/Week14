#include "../headers/user.h"

User::User(const std::string& name, const std::string& userID) 
    : name(name), userID(userID) {}

std::string User::getName() const { 
    return name; 
}

std::string User::getUserID() const { 
    return userID; 
}
