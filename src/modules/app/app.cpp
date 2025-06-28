/**
 * @file app.cpp
 * @brief Main application module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include "app.hpp"




/* external friend function */
App& app()
{
    static App app_;
    return app_;
}





/* private ctor */
App::App() : exit_request_(false), json_protocol_(),
    json_transport_(json_protocol_),
    discovery_(Discovery::get_instance()), ui_()
{
    ui_.run_async([this](const std::string& msg){
        _outcoming_message_handler(msg);
    });
}





/* public method */
void App::run()
{
    std::thread runner([this]()
    {
        json_transport_.run_receiving_messages_async(std::bind(&App::_incoming_message_handler, this, std::placeholders::_1));


        /* wait for exit request */
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this](){ return exit_request_; });
    });

    runner.join();

    exit_request_ = false;
}





/* public method */
void App::exit()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        exit_request_ = true;
    }

    cv_.notify_all();
}





/* public method */
void App::_incoming_message_handler(Message msg)
{

}




/* public method */
void App::_outcoming_message_handler(const std::string &msg)
{
    Message _msg
    {
        .sender = to_byteVector(std::string("...")),
        .data = to_byteVector(msg),
        .send_time = std::chrono::system_clock::now()
    };

    _send_msg_to_everyone(_msg);
}




/* public method */
void App::_send_msg_to_everyone(const Message &msg)
{
    std::cout << discovery_.get_clients_ip_adresses().size();

    /* iterate over all clients */
    for(const auto& ip : discovery_.get_clients_ip_adresses())
    {
        std::cout << ip << std::endl;
        json_transport_.send_message(ip, msg);
    }
}





