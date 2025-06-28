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
App::App() : exit_request_(false), json_protocol_(), json_transport_(json_protocol_), ui_()
{
    ui_.run_async([this](const std::string& msg){
        std::cout << "Got msg " << msg;
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





