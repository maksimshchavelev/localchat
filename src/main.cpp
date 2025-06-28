/* MIT LICENSE, Copyright (c) 2025, maksimshchavelev */


#include <signal.h>
#include <iostream>
#include "modules/app/app.hpp"


void exit_signal(int sig) { app().exit(); }


int main(int argc, char** argv)
{
    signal(SIGINT, exit_signal);

    std::string username;
    std::cout << "Type username >>> ";

    while(!std::getline(std::cin, username)) { std::cout << "Type username >>> "; }

    app().set_username(username);
    app().run();

    return 0;
}
