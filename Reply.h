#pragma once
#include <iostream>
#include <fstream>
#include "MyString.h"

const size_t BUFF_SIZE = 1024;
class Reply
{
    MyString text;
    size_t id;
    
public:
    void setReply(const MyString& txt, const size_t num);
    void readFromFile(std::ifstream& ifs);
    const void saveInFile(std:: ofstream& ofs) const;
    const void print() const;
};
