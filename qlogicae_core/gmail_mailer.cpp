#pragma once

#include "pch.h"

#include "gmail_mailer.hpp"

namespace QLogicaeCore
{
    GmailMailer::GmailMailer(
        const std::string& sender_address,
        const std::function<std::string()>& password_provider,
        const std::vector<std::string>& to_recipients,
        const std::vector<std::string>& cc_recipients,
        const std::vector<std::string>& bcc_recipients,
        const std::string& smtp_server)
        : curl(nullptr),
        mime_mixed(nullptr),
        mime_related(nullptr),
        html_part(nullptr),
        plain_part(nullptr),
        sender_address(sender_address),
        password_provider(password_provider),
        smtp_server(smtp_server),
        recipients(nullptr),
        headers(nullptr),
        to_recipients(to_recipients),
        cc_recipients(cc_recipients),
        bcc_recipients(bcc_recipients)
    {
        if (sender_address.empty() || !password_provider)
        {
            throw std::invalid_argument("Sender and password provider required");
        }
        if (to_recipients.empty())
        {
            throw std::invalid_argument("At least one recipient required");
        }
        curl_global_init(CURL_GLOBAL_DEFAULT);
        initialize();
    }

    GmailMailer::~GmailMailer()
    {
        cleanup();
        curl_global_cleanup();
    }


    void GmailMailer::initialize()
    {
        curl = curl_easy_init();
        if (curl == nullptr)
        {
            throw std::runtime_error("CURL initialization failed");
        }
        configure_smtp();
        prepare_recipients();
        mime_mixed = curl_mime_init(curl);
        mime_related = curl_mime_init(curl);
    }

    void GmailMailer::configure_smtp()
    {
        std::string full_url = "smtps://" + smtp_server;
        curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_USERNAME, sender_address.c_str());
        std::string password = password_provider();
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM,
            ("<" + sender_address + ">").c_str());
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    }

    void GmailMailer::prepare_recipients()
    {
        auto append = [this](const std::vector<std::string>& list)
            {
                for (const std::string& item : list)
                {
                    recipients = curl_slist_append(
                        recipients,
                        ("<" + item + ">").c_str());
                }
            };
        append(to_recipients);
        append(cc_recipients);
        append(bcc_recipients);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    }

    void GmailMailer::prepare_headers()
    {
        headers = curl_slist_append(
            headers,
            ("Subject: " + subject).c_str());
        headers = curl_slist_append(
            headers,
            ("From: <" + sender_address + ">").c_str());

        for (const std::string& recipient : to_recipients)
        {
            headers = curl_slist_append(
                headers,
                ("To: <" + recipient + ">").c_str());
        }
        for (const std::string& cc : cc_recipients)
        {
            headers = curl_slist_append(
                headers,
                ("Cc: <" + cc + ">").c_str());
        }
        for (const auto& pair : custom_headers)
        {
            headers = curl_slist_append(
                headers,
                (pair.first + ": " + pair.second).c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    void GmailMailer::finalize_body()
    {
        if (!plain_body.empty())
        {
            plain_part = curl_mime_addpart(mime_related);
            curl_mime_data(plain_part, plain_body.c_str(), CURL_ZERO_TERMINATED);
            curl_mime_type(plain_part, "text/plain");
        }
        if (!html_body.empty())
        {
            html_part = curl_mime_addpart(mime_related);
            curl_mime_data(html_part, html_body.c_str(), CURL_ZERO_TERMINATED);
            curl_mime_type(html_part, "text/html");
        }
        curl_mimepart* part = curl_mime_addpart(mime_mixed);
        curl_mime_subparts(part, mime_related);
        curl_mime_type(part, "multipart/alternative");
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime_mixed);
    }

    bool GmailMailer::send_email(std::string& error_message)
    {
        std::scoped_lock lock(access_mutex);
        reset_mime();
        prepare_headers();
        finalize_body();
        CURLcode result = curl_easy_perform(curl);
        if (result != CURLE_OK)
        {
            error_message = curl_easy_strerror(result);
            return false;
        }
        return true;
    }

    std::future<bool> GmailMailer::send_email_async()
    {
        return std::async(std::launch::async, [this]() -> bool
            {
                std::string message;
                return send_email(message);
            });
    }

    void GmailMailer::reset_mime()
    {
        if (mime_mixed)
        {
            curl_mime_free(mime_mixed);
            mime_mixed = curl_mime_init(curl);
        }
        if (mime_related)
        {
            curl_mime_free(mime_related);
            mime_related = curl_mime_init(curl);
        }
    }

    void GmailMailer::cleanup()
    {
        if (headers)
        {
            curl_slist_free_all(headers);
            headers = nullptr;
        }

        if (recipients)
        {
            curl_slist_free_all(recipients);
            recipients = nullptr;
        }

        if (curl)
        {
            curl_easy_cleanup(curl);
            curl = nullptr;
        }

        mime_mixed = nullptr;
        mime_related = nullptr;
    }


    void GmailMailer::set_subject(const std::string& subject)
    {
        std::scoped_lock lock(access_mutex);
        this->subject = subject;
    }

    std::future<void> GmailMailer::set_subject_async(
        const std::string& subject)
    {
        return std::async(std::launch::async, [this, subject]() {
            set_subject(subject);
            });
    }

    void GmailMailer::set_html_body(const std::string& html)
    {
        std::scoped_lock lock(access_mutex);
        html_body = html;
    }

    std::future<void> GmailMailer::set_html_body_async(
        const std::string& html)
    {
        return std::async(std::launch::async, [this, html]() {
            set_html_body(html);
            });
    }

    void GmailMailer::set_plain_body(const std::string& plain)
    {
        std::scoped_lock lock(access_mutex);
        plain_body = plain;
    }

    std::future<void> GmailMailer::set_plain_body_async(
        const std::string& plain)
    {
        return std::async(std::launch::async, [this, plain]() {
            set_plain_body(plain);
            });
    }

    void GmailMailer::set_header(
        const std::string& key,
        const std::string& value)
    {
        std::scoped_lock lock(access_mutex);
        custom_headers[key] = value;
    }

    std::future<void> GmailMailer::set_header_async(
        const std::string& key,
        const std::string& value)
    {
        return std::async(std::launch::async, [this, key, value]() {
            set_header(key, value);
            });
    }

    void GmailMailer::attach_inline_image(
        const std::string& file_path,
        const std::string& content_id,
        const std::string& mime_type)
    {
        std::scoped_lock lock(access_mutex);

        if (!std::filesystem::exists(file_path))
        {
            throw std::runtime_error("Inline image file not found: " + file_path);
        }

        curl_mimepart* part = curl_mime_addpart(mime_related);
        curl_mime_filedata(part, file_path.c_str());
        curl_mime_type(part, mime_type.c_str());
        curl_mime_encoder(part, "base64");
        curl_mime_filename(part, file_path.c_str());

        std::string header = "Content-ID: <" + content_id + ">";
        struct curl_slist* header_list = curl_slist_append(nullptr, header.c_str());
        curl_mime_headers(part, header_list, 1);
    }

    std::future<void> GmailMailer::attach_inline_image_async(
        const std::string& file_path,
        const std::string& content_id,
        const std::string& mime_type)
    {
        return std::async(std::launch::async, [this, file_path, content_id, mime_type]() {
            attach_inline_image(file_path, content_id, mime_type);
            });
    }

    void GmailMailer::attach_file(
        const std::string& file_path,
        const std::string& mime_type,
        const std::string& filename)
    {
        std::scoped_lock lock(access_mutex);

        if (!std::filesystem::exists(file_path))
        {
            throw std::runtime_error("Attachment file not found: " + file_path);
        }

        curl_mimepart* part = curl_mime_addpart(mime_mixed);
        curl_mime_filedata(part, file_path.c_str());
        curl_mime_type(part, mime_type.c_str());
        curl_mime_encoder(part, "base64");
        curl_mime_filename(part, filename.c_str());

        std::string header =
            "Content-Disposition: attachment; filename=\"" + filename + "\"";
        struct curl_slist* header_list = curl_slist_append(nullptr, header.c_str());
        curl_mime_headers(part, header_list, 1);
    }

    std::future<void> GmailMailer::attach_file_async(
        const std::string& file_path,
        const std::string& mime_type,
        const std::string& filename)
    {
        return std::async(std::launch::async, [this, file_path, mime_type, filename]() {
            attach_file(file_path, mime_type, filename);
            });
    }
}

