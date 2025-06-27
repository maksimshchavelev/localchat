/* MIT LICENSE, Copyright (c) 2025, maksimshchavelev */


#include "modules/discovery/discovery.hpp"


int main(int argc, char** argv)
{
    Discovery& disc = Discovery::get_instance();

    drogon::app()
        .addListener("0.0.0.0", 14570);
    drogon::app().run();

    return 0;
}
