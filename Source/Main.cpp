
// System Includes
//
#include <stdexcept>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <direct.h>
#include <stdio.h>

// SFML Includes
//

// Game Includes
//
#include "Book/Application.hpp"

void printpath()
{
    char* buffer;
    size_t maxsize = 256;
    if ((buffer = _getcwd(NULL, 0)) == NULL)
    {
        perror("_getcwd error");
    }
    else
    {
        printf("%s\n", buffer, strnlen(buffer, maxsize));
        free(buffer);
    }

}


int main()
{
    printpath();

    try
    {
        Application app;
        app.run();
    }
    catch (std::exception& e)
    {
        std::cout << "\nEXCEPTION: " << e.what() << std::endl;
    }
}