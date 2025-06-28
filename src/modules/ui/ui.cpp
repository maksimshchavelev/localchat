/**
 * @file ui.cpp
 * @brief User interface module
 * @license MIT LICENSE, Copyright (c) 2025, maksimshchavelev
 */


#include "ui.hpp"



/* public ctor */
UI::UI() {}




/* public method */
void UI::print_incoming_message(const std::string& sender, const std::string& time, const std::string& msg)
{
    using namespace ftxui;


    std::lock_guard<std::mutex> lock(IO_mutex_);
    messages_.push_back(
        hbox({
            window(hbox({
                   text(sender + " ") | color(Color::RGB(255, 88, 88)),
                   text(time) | color(Color::RGB(88, 255, 145))
               }), paragraph(msg)),
            filler()
        }));

    screen_->PostEvent(ftxui::Event::Custom);
}




/* public method */
void UI::print_outcoming_message(const std::string &msg)
{
    using namespace ftxui;


    std::ostringstream oss;


    auto utc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto local_tm = std::localtime(&utc);
    oss << std::put_time(local_tm, "%H:%M");


    std::lock_guard<std::mutex> lock(IO_mutex_);
    messages_.push_back(
        window(hbox({
                text("You ") | color(Color::RGB(125, 210, 255)),
                text(oss.str()) | color(Color::RGB(88, 255, 145))
               }), paragraph(msg)) | align_right);
}


