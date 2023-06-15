#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "User.h"
#include "Theme.h"

class SocialNetwork
{
    Theme* themes;
    Users* users;
    size_t numOfThemes;
    size_t numOfUsers;
    size_t capacityThemes;
    size_t capacityUsers;
    size_t indexUser;
    size_t indexTheme;
    size_t indexPost;
    
    void free();
    void copyFrom(const SocialNetwork& other);
    void moveFrom(SocialNetwork&& other);
    
    void resizeThemes();
    void resizeUsers();
    
public:
    SocialNetwork();
    SocialNetwork(const SocialNetwork& other);
    SocialNetwork& operator=(const SocialNetwork& other);
    ~SocialNetwork();
    
    SocialNetwork(SocialNetwork&& other) noexcept;
    SocialNetwork& operator=(SocialNetwork&& other) noexcept;
    
    void signup(); // addUser
    bool login(); // set indexUser = index
    void logout(); // set indexUser = 0;
    void create(); // addTheme
    void search(const MyString& text);
    bool open_theme(const size_t id); //set indexTheme = id
    bool open_theme(const MyString& title);
    void post(const MyString& newQuestion); // add question na indextheme
    bool p_open(const size_t id);// set indexPost = id
    bool p_open(const MyString& title);
    void comment(const MyString& newComment); // addcomment
    void comments() const; // print comments
    void reply(const size_t id); // addreply
    void upvote(const size_t id); // addupvote
    void downvote(const size_t id); // addDownvote
    void p_close(); // set indexPost = 0;
    void quit(); // set indexTheme = 0;
    void exit(); // save users and themes into files
    void list(); // print questions
    void whoami() const;// return info for users[indexUser]
    void about(const size_t id) const; // return info for themes[indexTheme]

};

