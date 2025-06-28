/* MIT LICENSE, Copyright (c) 2025, maksimshchavelev */


#include "modules/discovery/discovery.hpp"
#include "modules/transport/jsontransport/jsontransport.hpp"


int main(int argc, char** argv)
{
    Discovery& disc = Discovery::get_instance();

    JsonProtocol protocol;
    JsonTransport jsontransport(protocol);

    jsontransport.run_receiving_messages_async([](Message msg){
        std::cout << from_byteVector<std::string>(msg.data) << std::endl;
        std::cout << from_byteVector<std::string>(msg.sender) << std::endl;

        std::time_t utc = std::chrono::system_clock::to_time_t(msg.send_time);
        std::cout << std::put_time(std::localtime(&utc), "%e.%m.%Y %H.%M") << std::endl << std::endl;
    });

    jsontransport.send_message("192.168.0.100", Message{
        .sender = to_byteVector(std::string("Maksim")),
        .data = to_byteVector(std::string("Проверка связи")),
        .send_time = std::chrono::system_clock::now()
    });

    std::cout << std::chrono::duration_cast<std::chrono::minutes>(std::chrono::system_clock::now().time_since_epoch()).count();

    drogon::app().run();

    return 0;
}
