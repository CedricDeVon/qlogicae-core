#pragma once

#include "result.hpp"
#include "utilities.hpp"

#include <curl/curl.h>

#include <string>
#include <vector>
#include <future>
#include <optional>

namespace QLogicaeCore
{
    class GmailMailer
    {
    public:
        GmailMailer();
        
        GmailMailer(
            const std::string& sender_address,
            const std::function<std::string()>& password_provider,
            const std::vector<std::string>& to_recipients,
            const std::vector<std::string>& cc_recipients = {},
            const std::vector<std::string>& bcc_recipients = {},
            const std::string& smtp_server =
                UTILITIES.DEFAULT_GMAIL_MAILER_SMTP_SERVER
        );

        ~GmailMailer();

        GmailMailer(const GmailMailer& gmail_mailer) = delete;

        GmailMailer(GmailMailer&& gmail_mailer) = delete;

        GmailMailer& operator=(const GmailMailer& gmail_mailer) = delete;

        GmailMailer& operator=(GmailMailer&& gmail_mailer) = delete;

        void set_subject(const std::string& subject);

        std::future<void> set_subject_async(const std::string& subject);

        void set_html_body(const std::string& html);

        std::future<void> set_html_body_async(const std::string& html);

        void set_plain_body(const std::string& plain);

        std::future<void> set_plain_body_async(const std::string& plain);

        void set_header(
            const std::string& key,
            const std::string& value
        );

        std::future<void> set_header_async(
            const std::string& key,
            const std::string& value
        );

        void attach_inline_image(
            const std::string& file_path,
            const std::string& content_id,
            const std::string& mime_type
        );

        std::future<void> attach_inline_image_async(
            const std::string& file_path,
            const std::string& content_id,
            const std::string& mime_type
        );

        void attach_file(
            const std::string& file_path,
            const std::string& mime_type,
            const std::string& filename
        );

        std::future<void> attach_file_async(
            const std::string& file_path,
            const std::string& mime_type,
            const std::string& filename
        );

        bool send_email(
            std::string& error_message
        );

        std::future<bool> send_email_async();

        void setup(
            Result<void>& result,
            const std::string& sender_address,
            const std::function<std::string()>& password_provider,
            const std::vector<std::string>& to_recipients,
            const std::vector<std::string>& cc_recipients = {},
            const std::vector<std::string>& bcc_recipients = {},
            const std::string& smtp_server =
            UTILITIES.DEFAULT_GMAIL_MAILER_SMTP_SERVER
        );

        void set_subject(
            Result<void>& result,
            const std::string& subject
        );

        void set_subject_async(
            Result<std::future<void>>& result,
            const std::string& subject
        );

        void set_html_body(
            Result<void>& result,
            const std::string& html
        );

        void set_html_body_async(
            Result<std::future<void>>& result,
            const std::string& html
        );

        void set_plain_body(
            Result<void>& result,
            const std::string& plain
        );

        void set_plain_body_async(
            Result<std::future<void>>& result,
            const std::string& plain
        );

        void set_header(
            Result<void>& result,             
            const std::string& key,
            const std::string& value
        );

        void set_header_async(
            Result<std::future<void>>& result,
            const std::string& key,
            const std::string& value
        );

        void attach_inline_image(
            Result<void>& result, 
            const std::string& file_path,
            const std::string& content_id,
            const std::string& mime_type
        );

        void attach_inline_image_async(
            Result<std::future<void>>& result,
            const std::string& file_path,
            const std::string& content_id,
            const std::string& mime_type
        );

        void attach_file(
            Result<void>& result, 
            const std::string& file_path,
            const std::string& mime_type,
            const std::string& filename
        );

        void attach_file_async(
            Result<std::future<void>>& result,
            const std::string& file_path,
            const std::string& mime_type,
            const std::string& filename
        );

        void send_email(
            Result<bool>& result,
            std::string& error_message
        );

        void send_email_async(
            Result<std::future<bool>>& result
        );

    protected:
        CURL* _curl;

        std::string _subject;

        curl_mime* _mime_mixed;

        std::string _html_body;

        std::string _plain_body;

        std::string _smtp_server;

        std::mutex _access_mutex;

        curl_mime* _mime_related;

        curl_mimepart* _html_part;

        curl_mimepart* _plain_part;

        std::string _sender_address;

        struct curl_slist* _headers;

        struct curl_slist* _recipients;

        std::vector<std::string> _to_recipients;

        std::vector<std::string> _cc_recipients;

        std::vector<std::string> _bcc_recipients;

        std::function<std::string()> _password_provider;

        std::map<std::string, std::string> _custom_headers;

        void cleanup();

        void reset_mime();

        void setup();

        void finalize_body();

        void configure_smtp();

        void prepare_headers();

        void prepare_recipients();
    };
}

