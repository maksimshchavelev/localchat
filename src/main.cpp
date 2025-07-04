/* MIT LICENSE, Copyright (c) 2025, maksimshchavelev */


#include <signal.h>
#include <iostream>
#include "modules/app/app.hpp"


static std::atomic_bool g_exit_request{false};


void exit_signal(int) {
    g_exit_request.store(true);
    app().exit();
}


std::string safe_getline() {
    std::string line;
    char c;

    while (true)
    {
        size_t n = read(STDIN_FILENO, &c, 1);
        if (n == 1)
        {
            if (c == '\n') break;
            line.push_back(c);
        }
        else if (n == 0)
            break; /* EOF */

        else /* n < 0 */
        {
            if (errno == EINTR)
            {
                if (g_exit_request.load()) {
                    /* Is ctrl + c pressed */
                    return {};
                }
                continue; /* continue reading */
            }
            /* other error */
            perror("read");
            std::exit(1);
        }
    }

    return line;
}

int main() {
    struct sigaction sa{};
    sa.sa_handler = exit_signal;
    sa.sa_flags   = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, nullptr);


    std::cout << "Type username >>> " << std::flush;
    auto username = safe_getline();

    if (username.empty() && g_exit_request.load())
    {
        return 0;
    }

    if(username.empty())
    {
        std::cout << "Got empty username. Exiting" << std::endl;
        return 0;
    }

    app().set_username(username);
    app().run();

    return 0;
}
