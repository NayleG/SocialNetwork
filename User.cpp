#include "User.h"

static unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
{
    size_t currentPosition = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    if (!ifs.is_open())
        return 0;

    unsigned int count = 0;

    while (true)
    {
        char current = ifs.get();
        if (ifs.eof())
            break;

        if (current == ch)
            count++;
    }

    ifs.clear();
    ifs.seekg(currentPosition);
    return count;
}

static unsigned getLinesCount(const char* fileName)
{
    std::ifstream myFile(fileName);

    if (!myFile.is_open())
        return 0;

    return getCharCountFromFile(myFile, '\n')+1;
}

Users:: Users()
{
    MyString firstName = " ";
    MyString lastName = " ";
    MyString password = " ";
    size_t id = 0;
    size_t points = 0;
}

Users:: Users(const MyString& newFirstName, const MyString& newLastName, const MyString& newPassword, const size_t num): firstName(newFirstName), lastName(newLastName), password(newPassword), id(num)
{}

void Users:: readUser(const MyString& newFirstName, const MyString& newLastName, const MyString& newPassword, const size_t newId, const size_t newPoints)
{
    firstName = newFirstName;
    lastName = newLastName;
    password = newPassword;
    id = newId;
    points = newPoints;
}

const void Users:: print() const
{
    std:: cout << firstName << " " << lastName << ", having " << points << " points." << std:: endl;
}

const void Users:: printInTheme() const
{
    std:: cout << firstName << " " << lastName << " {id:" << id << "}" << std:: endl;
}

const void Users:: saveInFile(std::ofstream& ofs) const
{
    ofs << firstName << " " << lastName << " " << password << " " << id << " " << points << std::endl;
}
void Users:: readFromFile(std::ifstream& ifs)
{
    ifs >> firstName >> lastName >> password >> id >> points;
}

const bool Users::isSameAs(const Users& other) const
{
    if(id == other.id)
        return true;
    
    return false;
}

const MyString& Users:: getFirstName() const
{
    return firstName;
}
const MyString& Users:: getLastName() const
{
    return lastName;
}
const MyString& Users:: getPassword() const
{
    return password;
}
const size_t Users:: getPoints() const
{
    return points;
}
void Users:: setPoints(const size_t newPoints)
{
    points = newPoints;
}
const size_t Users::getId() const
{
    return id;
}

