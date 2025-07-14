#pragma once

#include "pch.h"

namespace QLogicaeCore
{
    class GmailMailer
    {
    public:
        GmailMailer(
            const std::string& sender_address,
            const std::function<std::string()>& password_provider,
            const std::vector<std::string>& to_recipients,
            const std::vector<std::string>& cc_recipients = {},
            const std::vector<std::string>& bcc_recipients = {},
            const std::string& smtp_server = "smtp.gmail.com:465");

        ~GmailMailer();

        GmailMailer(const GmailMailer&) = delete;
        GmailMailer(GmailMailer&&) = delete;
        GmailMailer& operator=(const GmailMailer&) = delete;
        GmailMailer& operator=(GmailMailer&&) = delete;

        void set_subject(const std::string& subject);
        std::future<void> set_subject_async(const std::string& subject);

        void set_html_body(const std::string& html);
        std::future<void> set_html_body_async(const std::string& html);

        void set_plain_body(const std::string& plain);
        std::future<void> set_plain_body_async(const std::string& plain);

        void set_header(
            const std::string& key,
            const std::string& value);
        std::future<void> set_header_async(
            const std::string& key,
            const std::string& value);

        void attach_inline_image(
            const std::string& file_path,
            const std::string& content_id,
            const std::string& mime_type);
        std::future<void> attach_inline_image_async(
            const std::string& file_path,
            const std::string& content_id,
            const std::string& mime_type);

        void attach_file(
            const std::string& file_path,
            const std::string& mime_type,
            const std::string& filename);
        std::future<void> attach_file_async(
            const std::string& file_path,
            const std::string& mime_type,
            const std::string& filename);

        bool send_email(std::string& error_message);
        std::future<bool> send_email_async();

    protected:
        CURL* curl;
        curl_mime* mime_mixed;
        curl_mime* mime_related;
        curl_mimepart* html_part;
        curl_mimepart* plain_part;

        std::string sender_address;
        std::function<std::string()> password_provider;
        std::string subject;
        std::string html_body;
        std::string plain_body;
        std::string smtp_server;

        struct curl_slist* recipients;
        struct curl_slist* headers;

        std::vector<std::string> to_recipients;
        std::vector<std::string> cc_recipients;
        std::vector<std::string> bcc_recipients;

        std::map<std::string, std::string> custom_headers;
        std::mutex access_mutex;

        void initialize();
        void cleanup();
        void reset_mime();
        void finalize_body();
        void configure_smtp();
        void prepare_recipients();
        void prepare_headers();
    };
}
