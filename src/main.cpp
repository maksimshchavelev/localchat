/* MIT LICENSE, Copyright (c) 2025, maksimshchavelev */


#include <signal.h>
#include "modules/app/app.hpp"


void exit_signal(int sig) { app().exit(); }


int main(int argc, char** argv)
{
    signal(SIGINT, exit_signal);

    app().run();

    return 0;
}
