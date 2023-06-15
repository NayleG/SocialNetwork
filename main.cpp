#include "SocialNetwork.h"

//constants
const char THEME_TITLE_FILE[] = "ThemeTitles.txt";
const char THEMES_FILE[] = "Themes.txt";
const char USER_FILE[] = "UserFile.txt";

//printing menus
void printFirstMenu()
{
    std:: cout << std:: endl;
    std:: cout << "Choose operation:" << std:: endl;
    std:: cout << "Signup" << std:: endl;
    std:: cout << "Login" << std:: endl;
    std:: cout << "Exit" << std:: endl;
    std:: cout << std:: endl;
}

void printSecondMenu()
{
    std:: cout << std:: endl;
    std:: cout << "Choose operation:" << std:: endl;
    std:: cout << "Create" << std:: endl;
    std:: cout << "Search <text>" << std:: endl;
    std:: cout << "Open_Title" << std:: endl;
    std:: cout << "Open_ID" << std:: endl;
    std:: cout << "About <id>" << std:: endl;
    std:: cout << "Whoami" << std:: endl;
    std:: cout << "Logout" << std:: endl;
    std:: cout << "Exit" << std:: endl;
    std:: cout << std:: endl;
}

void printThirdMenu()
{
    std:: cout << std:: endl;
    std:: cout << "Choose operation:" << std:: endl;
    std:: cout << "Post" << std:: endl;
    std:: cout << "P_openTitle" << std:: endl;
    std:: cout << "P_openID" << std:: endl;
    std:: cout << "List" << std:: endl;
    std:: cout << "Quid" << std:: endl;
    std:: cout << "Exit" << std:: endl;
    std:: cout << std:: endl;
}

void printFourthMenu()
{
    std:: cout << std:: endl;
    std:: cout << "Choose operation:" << std:: endl;
    std:: cout << "Comment" << std:: endl;
    std:: cout << "Comments" << std:: endl;
    std:: cout << "Reply <id>" << std:: endl;
    std:: cout << "Upvote <id>" << std:: endl;
    std:: cout << "Downvote <id>" << std:: endl;
    std:: cout << "P_close" << std:: endl;
    std:: cout << "Exit" << std:: endl;
    std:: cout << std:: endl;
}

//useful functions
void readWholeLine(MyString& mystr)
{
    char* buff = new char[1024];
    std::cin.getline(buff, 1024);
    mystr = buff;
    delete[] buff;
}

unsigned getCharCountFromFile(std::ifstream& ifs, char ch)
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

unsigned getLinesCount(const char* fileName)
{
    std::ifstream myFile(fileName);

    if (!myFile.is_open())
        return 0;

    return getCharCountFromFile(myFile, '\n');
}

//functions for class SocialNetwork
void SocialNetwork:: free()
{
    delete[] themes;
    delete[] users;
    numOfThemes = 0;
    numOfUsers = 0;
    capacityThemes = 0;
    capacityUsers = 0;
    indexUser = 0;
    indexTheme = 0;
    indexPost = 0;
}

void SocialNetwork:: copyFrom(const SocialNetwork& other)
{
    themes = new Theme[other.numOfThemes];
    numOfThemes = other.numOfThemes;
    capacityThemes = other.capacityThemes;

    for (size_t i = 0; i < numOfThemes; i++)
        themes[i] = other.themes[i];
    
    users = new Users[other.numOfUsers];
    numOfUsers = other.numOfUsers;
    capacityUsers = other.capacityUsers;

    for (size_t i = 0; i < numOfUsers; i++)
        users[i] = other.users[i];
    
    indexUser = other.indexUser;
    indexTheme = other.indexTheme;
    indexPost = other.indexPost;
}

void SocialNetwork:: moveFrom(SocialNetwork&& other)
{
    themes = other.themes;
    other.themes = nullptr;
    users = other.users;
    other.users = nullptr;
    numOfThemes = other.numOfThemes;
    numOfUsers = other.numOfUsers;
    capacityThemes = other.capacityThemes;
    capacityUsers = other.capacityUsers;
    indexUser = other.indexUser;
    indexTheme = other.indexTheme;
    indexPost = other.indexPost;
    other.numOfThemes = other.numOfUsers = other.capacityThemes = other.capacityUsers = other.indexUser = other.indexTheme = other.indexPost = 0;
}

void SocialNetwork::resizeThemes()
{
    Theme* temp = themes;
    themes = new Theme[capacityThemes*2];

    for (size_t i = 0; i < numOfThemes; i++)
        themes[i] = temp[i];
    
    capacityThemes *= 2;
    delete[] temp;
}

void SocialNetwork::resizeUsers()
{
    Users* temp = users;
    users = new Users[capacityUsers*2];

    for (size_t i = 0; i < numOfUsers; i++)
        users[i] = temp[i];
    
    capacityUsers *= 2;
    delete[] temp;
}

SocialNetwork::SocialNetwork(const SocialNetwork& other)
{
    copyFrom(other);
}

SocialNetwork& SocialNetwork::operator=(const SocialNetwork& other)
{
    if (this != &other)
        {
            free();
            copyFrom(other);
        }
        return *this;
}

SocialNetwork:: ~SocialNetwork()
{
    free();
}

SocialNetwork:: SocialNetwork(SocialNetwork&& other) noexcept
{
    moveFrom(std::move(other));
}

SocialNetwork& SocialNetwork::operator=(SocialNetwork&& other) noexcept
{
    if (this != &other)
        {
            free();
            moveFrom(std::move(other));
        }
        return *this;
}

SocialNetwork:: SocialNetwork()
{
    numOfThemes = getLinesCount(THEME_TITLE_FILE);
    themes = new Theme[numOfThemes];
    std:: ifstream ifs(THEMES_FILE);
    if(!ifs.is_open())
        throw std::logic_error("No file found!");
    
    for(int i = 0; i < numOfThemes; i++)
        themes[i].readFromFile(ifs);
    
    ifs.close();
    
    //saving all users from the file in Users* users
    numOfUsers = getLinesCount(USER_FILE);
    users = new Users[numOfUsers];
    std:: ifstream ifsU(USER_FILE);
    if(!ifsU.is_open())
        throw std::logic_error("No file found!");
    
    for(int i = 0; i < numOfUsers; i++)
        users[i].readFromFile(ifsU);
        
    
    ifsU.close();
    
    capacityThemes = numOfThemes;
    capacityUsers = numOfUsers;
    indexUser = indexTheme = indexPost = 0;
}

void SocialNetwork:: signup() // addUser
{
    std:: cout << "First name: ";
    MyString firstName;
    std:: cin >> firstName;
    
    std:: cout << "Last name: ";
    MyString lastName;
    std:: cin >> lastName;
    
    std:: cout << "Password: ";
    MyString password;
    std:: cin >> password;
    
    Users myUser(firstName, lastName, password, numOfUsers);
    if (numOfUsers == capacityUsers)
            resizeUsers();
    
    users[numOfUsers] = myUser;
    numOfUsers++;
    
    std:: cout << "Success!" << std:: endl;
}

bool SocialNetwork:: login() // set indexUser
{
    std:: cout << "First name: ";
    MyString firstName;
    std:: cin >> firstName;
    
    std:: cout << "Password: ";
    MyString password;
    std:: cin >> password;
    
    int i = 0;
    while(i < numOfUsers)
    {
        if(firstName == users[i].getFirstName() && password == users[i].getPassword())
        {
            indexUser = i;
            break;
        }
        i++;
    }
    
    if(i >= numOfUsers)
    {
        std:: cout << "Invalid information!" << std:: endl;
        indexUser = 0;
        return false;
    }
    
    else
    std::cout << std:: endl << "You are in! \n Welcome back, " << users[indexUser].getFirstName() << " " << users[indexUser].getLastName() << "!" << std:: endl;
    return true;
}

void SocialNetwork:: logout()// set indexUser = 0;
{
    std:: cout << std:: endl << "Goodbye, " << users[indexUser].getFirstName() << " " << users[indexUser].getLastName() << "!" << std:: endl;
    indexUser = 0;
}

void SocialNetwork:: create() // addTheme
{
    std:: cout << "Title: ";
    MyString title;
    std:: cin.ignore();
    readWholeLine(title);
    
    std:: cout << "Description: ";
    MyString description;
    readWholeLine(description);
    
    if (numOfThemes == capacityThemes)
            resizeThemes();
    themes[numOfThemes].setTheme(title, description, users[indexUser], numOfThemes);
    numOfThemes++;
    
    std:: cout << "Success!" << std:: endl;
}

void SocialNetwork:: search(const MyString& text) // searching text
{
    int br = 0;
    for(int i = 0; i<numOfThemes; i++)
    {
        if(themes[i].getTitle().contains(text))
        {
            br++;
            themes[i].printTitle();
        }
    }
    if(br == 0)
        std:: cout << "Sorry! No theme found!" << std:: endl;
}

bool SocialNetwork:: open_theme(const size_t id) //set indexTheme = id; return if opened
{
    if(id < numOfThemes)
    {
        indexTheme = id;
        std:: cout << std:: endl << "Welcome to \"" << themes[indexTheme].getTitle() << "\"!" << std:: endl;
        return true;
    }
    else
        std:: cout <<  "There is no such theme!" << std:: endl;
    return false;
}

bool SocialNetwork:: open_theme(const MyString& title) //set indexTheme, return if opened
{
    int i = 0;
    while(i<numOfThemes)
    {
        if(themes[i].getTitle() == title)
        {
            indexTheme = i;
            break;
        }
        i++;
    }
    
    if(i < numOfThemes)
    {
        std:: cout << std:: endl << "Welcome to \"" << themes[indexTheme].getTitle() << "\"!" << std:: endl;
        return true;
    }
    else
        std:: cout <<  "There is no such theme!" << std:: endl;
    return false;
    
}

void SocialNetwork:: post(const MyString& newQuestion) // add question na indextheme
{
    themes[indexTheme].addQuestion(newQuestion);
    std:: cout << "Posted!" << std:: endl;
}

bool SocialNetwork:: p_open(const size_t id)// set indexPost = id; return if opened
{
    indexPost = id;
    if(id >= themes[indexTheme].getNumOfQuestions())
    {
        std:: cout << "There is no such post!" << std:: endl;
        return false;
    }
    
    else
    {
        indexPost = id;
        std:: cout << std:: endl << "Q:" << themes[indexTheme].getQuestions()[indexPost].getTitle() << std:: endl;
        return true;
    }
}

bool SocialNetwork:: p_open(const MyString& title) // set indexPost; return if there is such theme
{
    int i = 0;
    while(i < themes[indexTheme].getNumOfQuestions())
    {
        if(title == themes[indexTheme].getQuestions()[i].getTitle())
        {
            indexPost = i;
            break;
        }
        i++;
    }
    
    if(i < themes[indexTheme].getNumOfQuestions())
    {
        std:: cout << std:: endl << "Q:" << themes[indexTheme].getQuestions()[indexPost].getTitle() << std:: endl;
        return true;
    }
    else
        std:: cout <<  "There is no such post!" << std:: endl;
    return false;
}

void SocialNetwork:: comment(const MyString& newComment) // addcomment
{
    themes[indexTheme].getQuestions()[indexPost].addComment(newComment, users[indexUser]);
    users[indexUser].setPoints(users[indexUser].getPoints() + 1);
    std:: cout << std:: endl << "Posted!" << std:: endl;
}

void SocialNetwork:: comments() const // print comments in the questions of themes[indextheme]
{
    if(themes[indexTheme].getQuestions()[indexPost].getNumOfComments() != 0)
        themes[indexTheme].getQuestions()[indexPost].printComments();
    
    else
        std:: cout << "No comments!" << std:: endl;
}

void SocialNetwork:: reply(const size_t id) // addreply in the comment id
{
    if(id >= (themes[indexTheme].getQuestions()[indexPost].getNumOfComments()))
        std:: cout << "Invalid id!" << std:: endl;
    else
    {
        std:: cout << "Say something: ";
        MyString newRep;
        std:: cin.ignore();
        readWholeLine(newRep);

        themes[indexTheme].getQuestions()[indexPost].getComments()[id].addReply(newRep);
        std:: cout << std:: endl << "Posted!" << std:: endl;
    }
}

void SocialNetwork:: upvote(const size_t id) // addUpvote
{
    if(id >= themes[indexTheme].getQuestions()[indexPost].getNumOfComments())
        std:: cout << "Invalid id!" << std:: endl;
    else
    {
        themes[indexTheme].getQuestions()[indexPost].getComments()[id].upvote(users[indexUser]);
        std:: cout << std:: endl << "Done!" << std:: endl;
    }
}

void SocialNetwork:: downvote(const size_t id) // addDownvote
{
    if(id >= themes[indexTheme].getQuestions()[indexPost].getNumOfComments())
        std:: cout <<  "Invalid id!" << std:: endl;
    else
    {
        themes[indexTheme].getQuestions()[indexPost].getComments()[id].downvote(users[indexUser]);
        std:: cout << std:: endl << "Done!" << std:: endl;
        
    }
}

void SocialNetwork:: p_close() // set indexPost = 0;
{
    std:: cout << std:: endl << "You just left: \"" << themes[indexTheme].getQuestions()[indexPost].getTitle() << "\"!"<< std:: endl;
    indexPost = 0;
}

void SocialNetwork:: quit() // set indexTheme = 0;
{
    std:: cout << std:: endl << "You just left: \"" << themes[indexTheme].getTitle() << "\"!"<< std:: endl;
    indexTheme = 0;
}

void SocialNetwork:: exit() // save users and themes into files
{
    //saving themes in file
    std:: ofstream ofs(THEMES_FILE, std:: ios:: out);
    std:: ofstream ofsTitle(THEME_TITLE_FILE, std:: ios:: out);
    if(!ofs.is_open() || !ofsTitle.is_open())
        throw std::logic_error("No file found!\n");
    for(int i = 0; i < numOfThemes; i++)
        themes[i].saveInFile(ofs, ofsTitle);
    
    ofs.close();
    ofsTitle.close();
    
    //saving users in file
    std:: ofstream ofsU(USER_FILE, std:: ios:: out);
    if(!ofsU.is_open())
        throw std::logic_error("No file found!\n");
    
    for(int i = 0; i < numOfUsers; i++)
    {
        users[i].saveInFile(ofsU);
    }
    ofsU.close();
}

void SocialNetwork::list() // print all questions
{
    if(themes[indexTheme].getNumOfQuestions() != 0)
        themes[indexTheme].printQuestions();
    
    else
        std:: cout << "No questions!" << std:: endl;
}

void SocialNetwork:: whoami() const// return info for users[indexUser]
{
    users[indexUser].print();
}

void SocialNetwork:: about(const size_t id) const // return info for themes[indexTheme]
{
    if(id >= numOfThemes)
        std:: cout << "Invalid id!" << std:: endl;
    else
        themes[id].print();
}


int main()
{
    bool exit = true;
    SocialNetwork myNetwork;

    while(exit)
    {
        printFirstMenu();
        
        MyString decision;
        std::cin >> decision;
        
        if(decision == "Signup")
            myNetwork.signup();
        
        else if(decision == "Login")
        {
            bool loged = false;
            loged = myNetwork.login();
            
            while(exit && loged)
            {
                printSecondMenu();
                
                MyString secondDecision;
                std::cin >> secondDecision;
                
                if(secondDecision == "Create")
                    myNetwork.create();
                
                else if(secondDecision == "Search")
                {
                    MyString text;
                    std:: cin >> text;
                    myNetwork.search(text);
                }
                
                else if(secondDecision == "Open_Title" || secondDecision == "Open_ID")
                {
                    bool open = false;
                    if(secondDecision == "Open_Title")
                    {
                        std:: cout << "Title: ";
                        MyString theme;
                        std:: cin.ignore();
                        readWholeLine(theme);
                        
                        open = myNetwork.open_theme(theme);
                    }
                    
                    else
                    {
                        std:: cout << "ID: ";
                        size_t id;
                        std:: cin >> id;
                        
                        open = myNetwork.open_theme(id);
                    }
                    
                    while(exit && open)
                    {
                        printThirdMenu();
                        
                        MyString thirdDecision;
                        std::cin >> thirdDecision;
                        
                        if(thirdDecision == "Post")
                        {
                            std:: cout << "Question: ";
                            MyString newQuestion;
                            std:: cin.ignore();
                            readWholeLine(newQuestion);
                            
                            myNetwork.post(newQuestion);
                            
                        }
                        else if(thirdDecision == "P_openTitle" || thirdDecision == "P_openID")
                        {
                            bool pOpen = false;
                            
                            if(thirdDecision == "P_openTitle")
                            {
                                std:: cout << "Title: ";
                                MyString post;
                                std:: cin.ignore();
                                readWholeLine(post);
                                
                                pOpen = myNetwork.p_open(post);
                            }
                            
                            else
                            {
                                std:: cout << "ID: ";
                                size_t id;
                                std:: cin >> id;
                                
                                pOpen = myNetwork.p_open(id);
                            }
                            while(exit && pOpen)
                            {
                                printFourthMenu();
                                
                                MyString fourthDecision;
                                std::cin >> fourthDecision;
                                
                                if(fourthDecision == "Comment")
                                {
                                    std:: cout << "Say something: ";
                                    MyString newCom;
                                    std:: cin.ignore();
                                    readWholeLine(newCom);
                                    
                                    myNetwork.comment(newCom);
                                }
                                
                                else if(fourthDecision == "Comments")
                                    myNetwork.comments();
                                
                                else if(fourthDecision == "Reply")
                                {
                                    size_t index;
                                    std:: cin >> index;
                                    myNetwork.reply(index);
                                }
                                
                                else if(fourthDecision == "Upvote")
                                {
                                    size_t index;
                                    std:: cin >> index;
                                    myNetwork.upvote(index);
                                }
                                
                                else if(fourthDecision == "Downvote")
                                {
                                    size_t index;
                                    std:: cin >> index;
                                    myNetwork.downvote(index);
                                }
                                
                                else if(fourthDecision == "P_close")
                                {
                                    myNetwork.p_close();
                                    pOpen = false;
                                }
                                
                                else if (fourthDecision == "Exit")
                                {
                                    myNetwork.exit();
                                    exit = false;
                                }
                                
                                else
                                    std:: cout << "Invalid comand!" << std:: endl;
                                
                            }
                        }
                        else if (thirdDecision == "List")
                        {
                            myNetwork.list();
                        }
                        else if (thirdDecision == "Quid")
                        {
                            myNetwork.quit();
                            open = false;
                        }
                        else if (thirdDecision == "Exit")
                        {
                            myNetwork.exit();
                            exit = false;
                        }
                        else
                            std:: cout << "Invalid comand!" << std:: endl;
                    }
                    
                }
                else if(secondDecision == "About")
                {
                    size_t id;
                    std:: cin >> id;
                    myNetwork.about(id);
                }
                else if(secondDecision == "Whoami")
                    myNetwork.whoami();
                else if(secondDecision == "Logout")
                {
                    myNetwork.logout();
                    loged = false;
                }
                else if(secondDecision == "Exit")
                {
                    myNetwork.exit();
                    exit = false;
                }
                else
                    std:: cout <<  "Invalid comand!" << std:: endl;
                 
            }
            
        }
        
        else if(decision == "Exit")
        {
            myNetwork.exit();
            exit = false;
        }
        
        else
            std:: cout << "Invalid comand!" << std:: endl;
    }
        
}
