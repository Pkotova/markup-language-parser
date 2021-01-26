#include "IMLManagementView.h"
#include<fstream>
#include<iostream>


/*
*   @ "Magical-constants" helps the developer to call any message; it is better practice
*/
std::string unknown = "Unknown key! ";
std::string thanku = "Thanks for choosing IML parser! ";
std::string welcome = "You choose to use IML parser as interpretator, please write your code here!\n Keep writing while input ^";
std::string askForNewFile = "Would you like to save the program? Y/N";
std::string filename = "Chose file name: ";

/*
*   @Prints in the console the menu, read from menu.txt
*/
void IMLManagementView::menu()
{
    std:: string menu;
    std::ifstream dataFile("menu.txt");
    while (std::getline(dataFile, menu)) {
        std::cout << menu << std::endl;
    }
}

/*
*   @Run menu
*/
void IMLManagementView::run()
{
    menu();
    char choice; 
    std::cout << "   >> ";
    std::cin >> choice;
    system("cls");
    switch (choice)
    {
    case '1': filesystem(); break;
    case '2': inlineCode(); break;
    case '3':std::cout << "\033[90m" << thanku << "\033[0m" << std::endl; exit(100);

    default: std::cout << "\033[32m" << unknown << "\033[0m" << std::endl;
        break;
    }
}

/*
*   @Use the app with the given filesystem
*/
void IMLManagementView::filesystem()
{
    Tree* tree = nullptr;
    ExceptionRepository er;
    std::string scr = er.cleanScript();
    tree->generateTree(tree, scr, 0, "");
    tree->treeReversion(tree);
    ResultRepository r;
    std::vector<double>result = tree->treeResult(tree, tree, scr);
    std::string res = toString(result);
    std::cout << std::endl;
    r.setResult(res);
    r.save();
    tree->~Tree();
}

/*
*   @Use the app as interpreter
*/
void IMLManagementView::inlineCode()
{
    std::cout << "\033[90m" << welcome << "\033[0m" << std::endl;

    Tree* tree = nullptr;
    std::string input;
    std::string line;
    int i = 1;
    while (std::getline(std::cin, line))
    {
        std::cout << i << '\t';
        if (line == "^")
            break;

        input += line;
        i++;
    }

    ExceptionRepository* er = new ExceptionRepository(input);
    std::string scr = er->cleanScript();

    tree->generateTree(tree, scr, 0, "");
    tree->treeReversion(tree);
    result(tree->treeResult(tree, tree, scr));
    ResultRepository r;
    std::vector<double>result = tree->treeResult(tree, tree, scr);
    std::string res = toString(result);
    std::cout << std::endl;
    r.setResult(res);
    r.save();

    if (askForSaveAs())
    {
        saveas(input);
    }
    else
    {
        std::cout << thanku << std::endl;
    }
    tree->~Tree();
    //delete er;
}

/*
*   @Save the written code
*/
bool IMLManagementView::askForSaveAs()
{
    std::cout << "\033[94m" << askForNewFile << "\033[0m" << std::endl;
    char answer;
    std::cout << "   >> ";
    std::cin >> answer;
    return (toupper(answer) == 'Y') ? true : false;
}

/*
*   @Save as 
*/
void IMLManagementView::saveas(std::string data)
{
    std::cout << "\033[33m" << "filename: ""\033[0m";
    std::string file; 
    std::cin >> file;
    if (isTxt(file))
    {
        std::ofstream file(file);
        file << data;
        std::cout << "\033[32m" << "Result successfully saved in file " << "\033[0m" << std::endl;
        file.close();
    }
    else
    {
        std::cout << "\033[31m" << "Unsupported file format! Saving failed!" << "\033[0m" << std::endl;
    }
}

/*
*   @Check the file type if its txt 
*/
bool IMLManagementView::isTxt(std::string filename)
{
    std::regex rx(".*.txt$");
    bool found = std::regex_match(filename, rx);
    return found;
}