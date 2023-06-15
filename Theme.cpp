#include "Theme.h"

void Theme:: copyFrom(const Theme& other)
{
    title = other.title;
    author = other.author;
    description = other.description;
    id = other.id;
    numOfQuestions = other.numOfQuestions;
    questions = new Question[numOfQuestions];
    for(int i = 0; i < numOfQuestions; i++)
    {
        questions[i] = other.questions[i];
    }
}
void Theme:: free()
{
    delete[] questions;
    questions = nullptr;
}
void Theme:: moveFrom(Theme&& other)
{
    title = other.title;
    author = other.author;
    description = other.description;
    id = other.id;
    numOfQuestions = other.numOfQuestions;
    questions = other.questions;
    other.questions = nullptr;
}

Theme:: Theme() = default;
Theme:: Theme(const Theme& other)
{
    copyFrom(other);
}
Theme& Theme:: operator=(const Theme& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Theme:: ~Theme()
{
    free();
}
Theme:: Theme(Theme&& other) noexcept
{
    moveFrom(std::move(other));
}
Theme& Theme:: operator=(Theme&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void Theme::setTheme(const MyString& tit, const MyString& desc, const Users& myUser, const size_t num)
{
    title = tit;
    author = myUser;
    description = desc;
    id = num;
    numOfQuestions = 0;
    questions = nullptr;
}

void Theme::readFromFile(std::ifstream& ifs)
{
    char* buffTit = new char[BUFF_SIZE];
    ifs.getline(buffTit, BUFF_SIZE);
    title = buffTit;
    delete[] buffTit;
    
    author.readFromFile(ifs);
    ifs.ignore();
    
    char* buffDes = new char[BUFF_SIZE];
    ifs.getline(buffDes, BUFF_SIZE);
    description = buffDes;
    delete[] buffDes;
    
    ifs >> id;
    ifs.ignore();
    ifs >> numOfQuestions;
    ifs.ignore();
    if(numOfQuestions != 0)
    {
        questions = new Question[numOfQuestions];
        for(int i = 0; i < numOfQuestions; i++)
            questions[i].readFromFile(ifs);
    }
}

const void Theme::saveInFile(std:: ofstream& ofs, std:: ofstream& ofsTitle) const
{
    ofsTitle << title << std:: endl;
    ofs << title << std:: endl;
    author.saveInFile(ofs);
    ofs << description << std:: endl;
    ofs << id << std:: endl;
    ofs << numOfQuestions << std:: endl;
    for(int i = 0; i < numOfQuestions; i++)
        questions[i].saveInFile(ofs);
}

const void Theme:: print() const
{
    std:: cout << "Name: " << title << std:: endl;
    std:: cout << "Description: " << description << std:: endl;
    std:: cout << "Created by: "; author.printInTheme();
    std:: cout << "Question asked: " << numOfQuestions << std:: endl;
}

const void Theme:: printTitle() const
{
    std:: cout << title << " {id:" << id << "}" << std:: endl;
}

const void Theme:: printQuestions() const
{
    for(int i = 0; i<numOfQuestions; i++)
        questions[i].print();
}

void Theme:: addQuestion(const MyString& newTitle)
{
    Question newQuestion;
    newQuestion.setQuestion(newTitle, numOfQuestions);
    Question* temp = questions;
    questions = new Question[numOfQuestions+1];
    for(int i = 0; i < numOfQuestions; i++)
        questions[i] = temp[i];
    questions[numOfQuestions] = newQuestion;
    numOfQuestions++;
    delete[] temp;
}

Question* Theme:: getQuestions()
{
    return questions;
}

const size_t Theme:: getNumOfQuestions() const
{
    return numOfQuestions;
}
const MyString& Theme:: getTitle() const
{
    return title;
}
