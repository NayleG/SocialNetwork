#pragma once
#include <iostream>
#include "User.h"
#include "Reply.h"

class Comment
{
    MyString author;
    MyString text;
    size_t id;
    size_t numOfUpvotes = 0;
    MyString* upvotes = nullptr;
    size_t numOfDownvotes = 0;
    MyString* downvotes = nullptr;
    size_t numOfReplies = 0;
    Reply* replies = nullptr;
    

    void copyFrom(const Comment& other);
    void free();
    void moveFrom(Comment&& other);
    
    void removeVote(const Users& myUser);

public:
    Comment();
    void setComment(const MyString& newAuthor, const MyString& newText, const size_t newId);
    Comment(const Comment& other);
    Comment& operator=(const Comment& other);
    ~Comment();
    Comment(Comment&& other) noexcept;
    Comment& operator=(Comment&& other) noexcept;
    
    void readFromFile(std::ifstream& ifs);
    const void saveInFile(std:: ofstream& ofs) const;
    const void print() const;
    
    void addReply(const MyString& newRep);
    
    const bool hasVoted(const Users& myUser) const;
    const bool hasUpvoted(const Users& myUser) const;
    const bool hasDownvoted(const Users& myUser) const;
    void upvote(const Users& myUser);
    void downvote(const Users& myUser);
};
