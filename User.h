#pragma once
#include <iostream>
#include "MyString.h"
#include <fstream>

class Users
 {
     MyString firstName = " ";
     MyString lastName = " ";
     MyString password = " ";
     size_t id = 0;
     size_t points = 0;
 
 public:
     Users();
     Users(const MyString& newFirstName, const MyString& newLastName, const MyString& newPassword, const size_t num);
     void readUser(const MyString& newFirstName, const MyString& newLastName, const MyString& newPassword, const size_t newId, const size_t newPoints);
     const void print() const;
     const void printInTheme() const;
     const void saveInFile(std::ofstream& ofs) const;
     void readFromFile(std::ifstream& ifs);
     
     const bool isSameAs(const Users& other) const;
     const MyString& getFirstName() const;
     const MyString& getLastName() const;
     const MyString& getPassword() const;
     const size_t getPoints() const;
     void setPoints(const size_t newPoints);
     const size_t getId() const;
     
 };

