/**
 * @file ui.tpp
 * @brief Implementation of template methods and functions
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#pragma once


#include "ui.hpp"


/* public method */
template<typename OutcomingMessageFunctor>
void UI::run_async(OutcomingMessageFunctor&& outcoming_msg_callback)
    requires requires { outcoming_msg_callback(std::declval<const std::string&>()); }
{
    static bool running = false;

    if(running)
        throw std::runtime_error("void UI::run_async(...) is already running!");

    running = true;

    std::thread runner([this, callback = std::forward<OutcomingMessageFunctor>(outcoming_msg_callback)]()
    {
        using namespace ftxui;


    #if defined(__unix__)
        std::cout << "\033[2J\033[H"; /* ANSI code for clear screen in Linux */
    #elif defined(_WIN32) or defined(_WIN64)
        std::cout << "\x1B[2J\x1B[H";
    #endif


        screen_ = std::shared_ptr<ftxui::ScreenInteractive>(
            new ftxui::ScreenInteractive(ftxui::ScreenInteractive::TerminalOutput())); /* create screen */

        std::string input_str;
        InputOption input_options;
        input_options.multiline = false;
        input_options.placeholder = "Type message...";

        Component input = Input(&input_str, input_options);

        auto renderer = Renderer(
            input,
            [&](){
                IO_mutex_.lock();
                auto box = vbox(messages_) | border;
                IO_mutex_.unlock();

                return vscroll_indicator(yframe(vbox({
                    box,
                    input->Render() | border
                }))) | flex ;
            }
        );


        auto root = CatchEvent(renderer, [&](Event event){
            /* Handle sengind message in UI */
            if(event == Event::Return && input_str.size() > 0)
            {
                print_outcoming_message(input_str);

                callback(input_str);

                input_str.clear();
                return true;
            }
            return false;
        });

        screen_->TrackMouse(true);
        screen_->Loop(root);
    });

    runner.detach();
}

