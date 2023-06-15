#include "Reply.h"

void Reply:: setReply(const MyString& txt, const size_t num)
{
    text = txt;
    id = num;
}

void Reply:: readFromFile(std::ifstream& ifs)
{
    char* buff = new char[BUFF_SIZE];
    ifs.getline(buff, BUFF_SIZE);
    text = buff;
    ifs >> id;
    delete[] buff;
}

const void Reply:: saveInFile(std:: ofstream& ofs) const
{
    ofs << text << std:: endl;
    ofs << id << std:: endl;
}

const void Reply:: print() const
{
    std:: cout << "  >>" << text << " {id:" << id << "}" << std:: endl;
}
