/* MIT LICENSE, Copyright (c) 2025, maksimshchavelev */


#include "modules/discovery/discovery.hpp"
#include "modules/transport/jsontransport/jsontransport.hpp"


int main(int argc, char** argv)
{
    Discovery& disc = Discovery::get_instance();

    JsonProtocol protocol;
    JsonTransport jsontransport(protocol);

    jsontransport.run_server_async([](Message msg){
        std::cout << from_byteVector<std::string>(msg.data) << std::endl;
        std::cout << from_byteVector<std::string>(msg.sender) << std::endl;
        std::cout << msg.send_time << std::endl << std::endl;
    });

    drogon::app().run();

    return 0;
}
