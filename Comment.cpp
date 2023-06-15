#include "Comment.h"

void Comment:: copyFrom(const Comment& other)
{
    author = other.author;
    text = other.text;
    id = other.id;
    
    numOfUpvotes = other.numOfUpvotes;
    upvotes = new MyString[numOfUpvotes];
    for(int i = 0; i < numOfUpvotes; i++)
    {
        upvotes[i] = other.upvotes[i];
    }
    
    numOfDownvotes = other.numOfDownvotes;
    downvotes = new MyString[numOfDownvotes];
    for(int i = 0; i < numOfDownvotes; i++)
    {
        downvotes[i] = other.downvotes[i];
    }
    
    numOfReplies = other.numOfReplies;
    replies = new Reply[numOfReplies];
    for(int i = 0; i < numOfReplies; i++)
    {
        replies[i] = other.replies[i];
    }
}

void Comment:: free()
{
    delete[] upvotes;
    upvotes = nullptr;
    delete[] downvotes;
    downvotes = nullptr;
    delete[] replies;
    replies = nullptr;
}

void Comment:: moveFrom(Comment&& other)
{
    author = other.author;
    text = other.text;
    id = other.id;
    numOfUpvotes = other.numOfUpvotes;
    upvotes = other.upvotes;
    other.upvotes = nullptr;
    numOfDownvotes = other.numOfDownvotes;
    downvotes = other.downvotes;
    other.downvotes = nullptr;
    numOfReplies = other.numOfReplies;
    replies = other.replies;
    other.replies = nullptr;
}

Comment:: Comment() = default;

void Comment:: setComment(const MyString& newAuthor, const MyString& newText, const size_t newId)
{
    author = newAuthor;
    text = newText;
    id = newId;
    numOfUpvotes = 0;
    MyString* upvotes = nullptr;
    numOfDownvotes = 0;
    MyString* downvotes = nullptr;
    numOfReplies = 0;
    Reply* replies = nullptr;
}

Comment:: Comment(const Comment& other)
{
    copyFrom(other);
}

Comment& Comment:: operator=(const Comment& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

Comment:: ~Comment()
{
    free();
}

Comment:: Comment(Comment&& other) noexcept
{
    moveFrom(std::move(other));
}

Comment& Comment:: operator=(Comment&& other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void Comment:: readFromFile(std::ifstream& ifs)
{
    char* buffA = new char[BUFF_SIZE];
    ifs.getline(buffA, BUFF_SIZE);
    author = buffA;
    delete[] buffA;
    
    char* buffC = new char[BUFF_SIZE];
    ifs.getline(buffC, BUFF_SIZE);
    text = buffC;
    delete[] buffC;
    
    ifs >> id;
    ifs.ignore();
    
    ifs >> numOfUpvotes;
    ifs.ignore();
    MyString* upvotes = new MyString[numOfUpvotes];
    for(int i = 0; i < numOfUpvotes; i++)
    {
        char* buff = new char[BUFF_SIZE];
        ifs.getline(buff, BUFF_SIZE);
        upvotes[i] = buff;
        delete[] buff;
        ifs.ignore();
    }
    
    ifs >> numOfDownvotes;
    ifs.ignore();
    MyString* downvotes = new MyString[numOfDownvotes];
    for(int i = 0; i < numOfDownvotes; i++)
    {
        char* buff = new char[BUFF_SIZE];
        ifs.getline(buff, BUFF_SIZE);
        downvotes[i] = buff;
        delete[] buff;
        ifs.ignore();
    }
    
    ifs >> numOfReplies;
    ifs.ignore();
    if(numOfReplies != 0)
    {
        Reply* replies = new Reply[numOfReplies];
        for(int i = 0; i < numOfReplies; i++)
        {
            replies[i].readFromFile(ifs);
            ifs.ignore();
        }
    }
}

const void Comment::saveInFile(std:: ofstream& ofs) const
{
    ofs<< author << std:: endl;
    ofs << text << std:: endl;
    ofs << id << std:: endl;
    ofs << numOfUpvotes << std::endl;
    for(int i = 0; i < numOfUpvotes; i++)
    {
       ofs << upvotes[i] << std:: endl;
    }
    
    ofs << numOfDownvotes << std:: endl;
    for(int i = 0; i < numOfDownvotes; i++)
    {
        ofs << downvotes[i] << std:: endl;
    }
    ofs << numOfReplies << std:: endl;
    for(int i = 0; i < numOfReplies; i++)
    {
        replies[i].saveInFile(ofs);
    }
}
const void Comment:: print() const
{
    std:: cout << " >"  << text << " {id:" << id << "} ";
    if(numOfUpvotes != 0)
        std::cout << "{upvotes: " << numOfUpvotes << "} ";
    if(numOfDownvotes != 0)
        std::cout << "{downvotes: " << numOfDownvotes << "} ";
    std::cout << std:: endl;
    for(int i = 0; i<numOfReplies; i++)
        replies[i].print();
}

void Comment:: addReply(const MyString& newRep)
{
    Reply newReply;
    newReply.setReply(newRep, numOfReplies);
    Reply* temp = replies;
    replies = new Reply[numOfReplies+1];
    for(int i = 0; i < numOfReplies; i++)
        replies[i] = temp[i];
    replies[numOfReplies] = newReply;
    numOfReplies++;
    delete[] temp;
}

const bool Comment:: hasVoted(const Users& myUser) const
{
    if(hasUpvoted(myUser) == false && hasDownvoted(myUser) == false)
        return false;
    
    return true;
}

const bool Comment:: hasUpvoted(const Users& myUser) const
{
    bool upvoted = false;
    
    for(int i = 0; i < numOfUpvotes; i++)
    {
        if(myUser.getFirstName() + " " + myUser.getPassword() == upvotes[i])
        {
            upvoted = true;
            break;
        }
    }
    
    return upvoted;
}

const bool Comment:: hasDownvoted(const Users& myUser) const
{
    bool downvoted = false;
    
    for(int i = 0; i < numOfDownvotes; i++)
    {
        if(myUser.getFirstName() + " " + myUser.getPassword() == downvotes[i])
        {
            downvoted = true;
            break;
        }
    }
    
    return downvoted;
}

void Comment::upvote(const Users& myUser)
{
    if(hasVoted(myUser) == false)
    {
        MyString* temp = upvotes;
        upvotes = new MyString[numOfUpvotes+1];
        for(int i = 0; i < numOfUpvotes; i++)
            upvotes[i] = temp[i];
        upvotes[numOfUpvotes] = myUser.getFirstName() + " " + myUser.getPassword();
        numOfUpvotes++;
        delete[] temp;
    }
    else
        removeVote(myUser);
}

void Comment::downvote(const Users& myUser)
{
    if(hasVoted(myUser) == false)
    {
        MyString* temp = downvotes;
        downvotes = new MyString[numOfDownvotes+1];
        for(int i = 0; i < numOfDownvotes; i++)
            downvotes[i] = temp[i];
        downvotes[numOfDownvotes] = myUser.getFirstName() + " " + myUser.getPassword();
        numOfDownvotes++;
        delete[] temp;
    }
    else
        removeVote(myUser);
}

void Comment:: removeVote(const Users& myUser)
{
    if(hasUpvoted(myUser))
    {
        MyString* temp = upvotes;
        upvotes = new MyString[numOfUpvotes-1];
        for(int i = 0, t = 0; i < numOfUpvotes; i++)
        {
            if(myUser.getFirstName() + " " + myUser.getPassword() != temp[i])
            {
                upvotes[t] = temp[i];
                t++;
            }
        }
        
        numOfUpvotes--;
        delete[] temp;
    }
    
    else
    {
        MyString* temp = downvotes;
        downvotes = new MyString[numOfDownvotes-1];
        for(int i = 0, t = 0; i < numOfDownvotes; i++)
        {
            if(myUser.getFirstName() + " " + myUser.getPassword() != temp[i])
            {
                downvotes[t] = temp[i];
                t++;
            }
        }
        
        numOfDownvotes--;
        delete[] temp;
    }
}
