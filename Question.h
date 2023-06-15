#pragma once
#include <iostream>
#include "Comment.h"

class Question
{
    MyString title;
    size_t id;
    size_t numOfComments = 0;
    Comment* comments = nullptr;

    void copyFrom(const Question& other);
    void free();
    void moveFrom(Question&& other);

    public:
    Question();
    Question(const Question& other);
    Question& operator=(const Question& other);
    ~Question();
    Question(Question&& other) noexcept;
    Question& operator=(Question&& other) noexcept;
    
    void setQuestion(const MyString& newTitle, const size_t newId);
    void readFromFile(std::ifstream& ifs);
    const void saveInFile(std:: ofstream& ofs) const;
    const void print() const;
    const void printComments() const;
    
    void addComment(const MyString& newCom, const Users& newAuthor);
    
    Comment* getComments();
    const size_t getNumOfComments() const;
    const MyString& getTitle() const;

};
