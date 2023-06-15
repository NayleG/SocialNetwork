#pragma once
#include <iostream>
#include "Question.h"

class Theme
{
    MyString title;
    Users author;
    MyString description;
    size_t id;
    size_t numOfQuestions = 0;
    Question* questions = nullptr;
    
    void copyFrom(const Theme& other);
    void free();
    void moveFrom(Theme&& other);

    public:
    Theme();
    Theme(const Theme& other);
    Theme& operator=(const Theme& other);
    ~Theme();
    Theme(Theme&& other) noexcept;
    Theme& operator=(Theme&& other) noexcept;
    
    void setTheme(const MyString& tit, const MyString& desc, const Users& myUser, const size_t num);
    
    void readFromFile(std::ifstream& ifs);
    const void saveInFile(std:: ofstream& ofs, std:: ofstream& ofsTitle) const;
    const void print() const;
    const void printTitle() const;
    const void printQuestions() const;
    
    void addQuestion(const MyString& newTitle);
    Question* getQuestions();
    const size_t getNumOfQuestions() const;
    const MyString& getTitle() const;

};
