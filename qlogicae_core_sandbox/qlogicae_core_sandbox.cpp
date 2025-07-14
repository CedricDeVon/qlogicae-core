#pragma once

#include "pch.h"

#include "gmail_mailer.hpp"

int main()
{
    const std::string sender_address = "vaughncedriclipardoaraneta@gmail.com";

    const std::function<std::string()> password_provider =
        []() -> std::string
        {
            return "ysmu wrvx biro oyek";
        };

    std::vector<std::string> to_recipients = {
        "vaughncedriclipardoaraneta@gmail.com"
    };

    QLogicaeCore::GmailMailer mailer(
        sender_address,
        password_provider,
        to_recipients);

    mailer.set_subject("Test Email");
    mailer.set_plain_body("Hello, this is a test email sent using GmailMailer.");

    std::string error_message;

    if (!mailer.send_email(error_message))
    {
        std::cerr << "Failed to send email: "
            << error_message << std::endl;
        return 1;
    }

    std::cout << "Email sent successfully." << std::endl;
    return 0;
}