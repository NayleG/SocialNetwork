#include "Question.h"

void Question:: copyFrom(const Question& other)
{
    title = other.title;
    id = other.id;
    numOfComments = other.numOfComments;
    comments = new Comment[numOfComments];
    for(int i = 0; i < numOfComments; i++)
    {
        comments[i] = other.comments[i];
    }
}
void Question:: free()
{
    numOfComments = 0;
    delete[] comments;
    
}
void Question:: moveFrom(Question&& other)
{
    title = other.title;
    id = other.id;
    numOfComments = other.numOfComments;
    comments = other.comments;
    other.comments = nullptr;
}

Question:: Question() = default;
Question:: Question(const Question& other)
{
    copyFrom(other);
}
Question& Question:: operator=(const Question& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}
Question:: ~Question()
{
    free();
}
Question:: Question(Question&& other) noexcept
{
    moveFrom(std::move(other));
}
Question& Question:: operator=(Question&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void Question:: readFromFile(std::ifstream& ifs)
{
    char* buffTit = new char[BUFF_SIZE];
    ifs.getline(buffTit, BUFF_SIZE);
    title = buffTit;
    delete[] buffTit;
    
    ifs >> id;
    ifs.ignore();
    ifs >> numOfComments;
    ifs.ignore();
    if(numOfComments != 0)
    {
        comments = new Comment[numOfComments];
        for(int i = 0; i < numOfComments; i++)
        {
            comments[i].readFromFile(ifs);
            
        }
        
    }
    
}

const void  Question:: saveInFile(std:: ofstream& ofs) const
{
    ofs << title << std:: endl;
    ofs << id << std:: endl;
    ofs << numOfComments << std:: endl;
    for(int i = 0; i<numOfComments; i++)
        comments[i].saveInFile(ofs);
}

const void  Question::print() const
{
    std:: cout << title << " {id:" << id << "}" << std::endl;
}
const void  Question::printComments() const
{
    for(int i = 0; i<numOfComments; i++)
    {
        comments[i].print();
    }
}

void Question:: addComment(const MyString& newCom, const Users& newAuthor)
{
    Comment newComment;
    newComment.setComment(newAuthor.getFirstName() + " " + newAuthor.getLastName(), newCom, numOfComments);
    Comment* temp = comments;
    comments = new Comment[numOfComments+1];
    for(int i = 0; i < numOfComments; i++)
        comments[i] = temp[i];
    comments[numOfComments] = newComment;
    numOfComments++;
    delete[] temp;
    //std:: cout << "here" << std:: endl;
    //comments[numOfComments-1].print();
}

void Question::setQuestion(const MyString& newTitle, const size_t newId)
{
    title = newTitle;
    id = newId;
    numOfComments = 0;
    Comment* comments = nullptr;
}

Comment* Question:: getComments()
{
    return comments;
}

const size_t Question:: getNumOfComments() const
{
    return numOfComments;
}

const MyString& Question:: getTitle() const
{
    return title;
}
