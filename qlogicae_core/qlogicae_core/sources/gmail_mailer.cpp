#include "pch.hpp"

#include "../includes/gmail_mailer.hpp"

namespace QLogicaeCore
{
    GmailMailer::GmailMailer()
    {

    }

    GmailMailer::GmailMailer(
        const std::string& sender_address,
        const std::function<std::string()>& password_provider,
        const std::vector<std::string>& to_recipients,
        const std::vector<std::string>& cc_recipients,
        const std::vector<std::string>& bcc_recipients,
        const std::string& smtp_server
    )
        : _curl(nullptr),
        _mime_mixed(nullptr),
        _mime_related(nullptr),
        _html_part(nullptr),
        _plain_part(nullptr),
        _sender_address(sender_address),
        _password_provider(password_provider),
        _smtp_server(smtp_server),
        _recipients(nullptr),
        _headers(nullptr),
        _to_recipients(to_recipients),
        _cc_recipients(cc_recipients),
        _bcc_recipients(bcc_recipients)
    {
        if (sender_address.empty() || !password_provider)
        {
            throw std::runtime_error(
                "Exception at GmailMailer::GmailMailer(): Sender and password provider required"
            );
        }
        if (to_recipients.empty())
        {
            throw std::runtime_error(
                "Exception at GmailMailer::GmailMailer(): At least one recipient required"
            );
        }

        curl_global_init(CURL_GLOBAL_DEFAULT);
        setup();
    }

    GmailMailer::~GmailMailer()
    {
        cleanup();
        curl_global_cleanup();        
    }

    void GmailMailer::setup()
    {
        try
        {
            _curl = curl_easy_init();
            if (_curl == nullptr)
            {
                throw std::runtime_error(
                    "Exception at GmailMailer::setup(): CURL initialization failed"
                );
            }

            configure_smtp();
            prepare_recipients();
            _mime_mixed = curl_mime_init(_curl);
            _mime_related = curl_mime_init(_curl);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(std::string() + "Exception at GmailMailer::setup(): " + exception.what());
        }
    }

    void GmailMailer::configure_smtp()
    {
        try
        {
            std::string full_url = "smtps://" + _smtp_server;
            curl_easy_setopt(_curl, CURLOPT_URL, full_url.c_str());
            curl_easy_setopt(_curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
            curl_easy_setopt(_curl, CURLOPT_USERNAME, _sender_address.c_str());
            std::string password = _password_provider();
            curl_easy_setopt(_curl, CURLOPT_PASSWORD, password.c_str());
            curl_easy_setopt(_curl, CURLOPT_MAIL_FROM,
                ("<" + _sender_address + ">").c_str());
            curl_easy_setopt(_curl, CURLOPT_VERBOSE, 0L);
            curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 1L);
            curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYHOST, 2L);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::configure_smtp(): " + exception.what()
            );
        }
    }

    void GmailMailer::prepare_recipients()
    {
        try
        {
            auto append = [this](const std::vector<std::string>& list)
                {
                    for (const std::string& item : list)
                    {
                        _recipients = curl_slist_append(
                            _recipients,
                            ("<" + item + ">").c_str());
                    }
                };
            append(_to_recipients);
            append(_cc_recipients);
            append(_bcc_recipients);
            curl_easy_setopt(_curl, CURLOPT_MAIL_RCPT, _recipients);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::prepare_recipients(): " + exception.what()
            );
        }
    }

    void GmailMailer::prepare_headers()
    {
        try
        {
            _headers = curl_slist_append(
                _headers,
                ("Subject: " + _subject).c_str());
            _headers = curl_slist_append(
                _headers,
                ("From: <" + _sender_address + ">").c_str());

            for (const std::string& recipient : _to_recipients)
            {
                _headers = curl_slist_append(
                    _headers,
                    ("To: <" + recipient + ">").c_str());
            }
            for (const std::string& cc : _cc_recipients)
            {
                _headers = curl_slist_append(
                    _headers,
                    ("Cc: <" + cc + ">").c_str());
            }
            for (const auto& pair : _custom_headers)
            {
                _headers = curl_slist_append(
                    _headers,
                    (pair.first + ": " + pair.second).c_str());
            }
            curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, _headers);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::prepare_headers(): " + exception.what()
            );
        }
    }

    void GmailMailer::finalize_body()
    {
        try
        {
            if (!_plain_body.empty())
            {
                _plain_part = curl_mime_addpart(_mime_related);
                curl_mime_data(_plain_part, _plain_body.c_str(), CURL_ZERO_TERMINATED);
                curl_mime_type(_plain_part, "text/plain");
            }
            if (!_html_body.empty())
            {
                _html_part = curl_mime_addpart(_mime_related);
                curl_mime_data(_html_part, _html_body.c_str(), CURL_ZERO_TERMINATED);
                curl_mime_type(_html_part, "text/html");
            }
            curl_mimepart* part = curl_mime_addpart(_mime_mixed);
            curl_mime_subparts(part, _mime_related);
            curl_mime_type(part, "multipart/alternative");
            curl_easy_setopt(_curl, CURLOPT_MIMEPOST, _mime_mixed);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::finalize_body(): " + exception.what()
            );
        }
    }

    bool GmailMailer::send_email(std::string& error_message)
    {
        try
        {
            std::scoped_lock lock(_access_mutex);
            reset_mime();
            prepare_headers();
            finalize_body();
            CURLcode result = curl_easy_perform(_curl);
            if (result != CURLE_OK)
            {
                error_message = curl_easy_strerror(result);
                return false;
            }
            return true;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::send_email(): " + exception.what()
            );
        }
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
        try
        {
            if (_mime_mixed)
            {
                curl_mime_free(_mime_mixed);
                _mime_mixed = curl_mime_init(_curl);
            }
            if (_mime_related)
            {
                curl_mime_free(_mime_related);
                _mime_related = curl_mime_init(_curl);
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::reset_mime(): " + exception.what()
            );
        }
    }

    void GmailMailer::cleanup()
    {
        try
        {
            if (_headers)
            {
                curl_slist_free_all(_headers);
                _headers = nullptr;
            }

            if (_recipients)
            {
                curl_slist_free_all(_recipients);
                _recipients = nullptr;
            }

            if (_curl)
            {
                curl_easy_cleanup(_curl);
                _curl = nullptr;
            }

            _mime_mixed = nullptr;
            _mime_related = nullptr;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::cleanup(): " + exception.what()
            );
        }
    }

    void GmailMailer::set_subject(const std::string& subject)
    {
        try
        {
            std::scoped_lock lock(_access_mutex);

            this->_subject = subject;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::set_subject(): " + exception.what()
            );
        }
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
        try
        {
            std::scoped_lock lock(_access_mutex);

            _html_body = html;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::set_html_body(): " + exception.what()
            );
        }
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
        try
        {
            std::scoped_lock lock(_access_mutex);

            _plain_body = plain;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::set_plain_body(): " + exception.what()
            );
        }
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
        try
        {
            std::scoped_lock lock(_access_mutex);
            _custom_headers[key] = value;
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::set_header(): " + exception.what()
            );
        }
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
        try
        {
            std::scoped_lock lock(_access_mutex);

            if (!std::filesystem::exists(file_path))
            {
                throw std::runtime_error(
                    "Exception at GmailMailer::attach_inline_image(): Inline image file not found: " + file_path
                );
            }

            curl_mimepart* part = curl_mime_addpart(_mime_related);
            curl_mime_filedata(part, file_path.c_str());
            curl_mime_type(part, mime_type.c_str());
            curl_mime_encoder(part, "base64");
            curl_mime_filename(part, file_path.c_str());

            std::string header = "Content-ID: <" + content_id + ">";
            struct curl_slist* header_list = curl_slist_append(nullptr, header.c_str());
            curl_mime_headers(part, header_list, 1);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::attach_inline_image(): " + exception.what()
            );
        }
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
        try
        {
            std::scoped_lock lock(_access_mutex);

            if (!std::filesystem::exists(file_path))
            {
                throw std::runtime_error(
                    "Exception at GmailMailer::attach_file(): Attachment file not found: " + file_path
                );
            }

            curl_mimepart* part = curl_mime_addpart(_mime_mixed);
            curl_mime_filedata(part, file_path.c_str());
            curl_mime_type(part, mime_type.c_str());
            curl_mime_encoder(part, "base64");
            curl_mime_filename(part, filename.c_str());

            std::string header =
                "Content-Disposition: attachment; filename=\"" + filename + "\"";
            struct curl_slist* header_list = curl_slist_append(nullptr, header.c_str());
            curl_mime_headers(part, header_list, 1);
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string() + "Exception at GmailMailer::attach_file(): " + exception.what()
            );
        }
    }

    std::future<void> GmailMailer::attach_file_async(
        const std::string& file_path,
        const std::string& mime_type,
        const std::string& filename
    )
    {
        return std::async(
            std::launch::async,
            [this, file_path, mime_type, filename]()
            {
                attach_file(file_path, mime_type, filename);
            }
        );
    }

    void GmailMailer::setup(
        Result<void>& result,
        const std::string& sender_address,
        const std::function<std::string()>& password_provider,
        const std::vector<std::string>& to_recipients,
        const std::vector<std::string>& cc_recipients,
        const std::vector<std::string>& bcc_recipients,
        const std::string& smtp_server
    )
    {
        _curl = nullptr;
        _mime_mixed = nullptr;
        _mime_related = nullptr;
        _html_part = nullptr;
        _plain_part = nullptr;
        _sender_address = sender_address;
        _password_provider = password_provider;
        _smtp_server = smtp_server;
        _recipients = nullptr;
        _headers = nullptr;
        _to_recipients = to_recipients;
        _cc_recipients = cc_recipients;
        _bcc_recipients = bcc_recipients;
        
        if (sender_address.empty() || !password_provider)
        {
            return result.set_to_bad_status_without_value(
                "Sender address is empty or pasword provider is null"
            );
        }
        if (to_recipients.empty())
        {
            return result.set_to_bad_status_without_value(
                "No recipients"
            );
        }

        curl_global_init(CURL_GLOBAL_DEFAULT);
        setup();

        result.set_to_good_status_without_value();
    }

    void GmailMailer::set_subject(
        Result<void>& result,
        const std::string& subject
    )
    {
        std::scoped_lock lock(_access_mutex);

        this->_subject = subject;

        result.set_to_good_status_without_value();
    }

    void GmailMailer::set_subject_async(
        Result<std::future<void>>& result,
        const std::string& subject
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this, subject]()
            {
                Result<void> result;

                set_subject(result, subject);
            })
        );
    }

    void GmailMailer::set_html_body(
        Result<void>& result,
        const std::string& html
    )
    {
        std::scoped_lock lock(_access_mutex);

        _html_body = html;

        result.set_to_good_status_without_value();
    }

    void GmailMailer::set_html_body_async(
        Result<std::future<void>>& result,
        const std::string& html
    )
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async, [this, html]()
            {
                Result<void> result;

                set_html_body(
                    result,
                    html
                );
            })
        );
    }

    void GmailMailer::set_plain_body(
        Result<void>& result,
        const std::string& plain
    )
    {
        std::scoped_lock lock(_access_mutex);

        _plain_body = plain;

        result.set_to_good_status_without_value();
    }

    void GmailMailer::set_plain_body_async(
        Result<std::future<void>>& result,
        const std::string& plain
    )
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this, plain]()
            {
                Result<void> result;

                set_plain_body(
                    result,
                    plain
                );
            })
        );
    }

    void GmailMailer::set_header(
        Result<void>& result,
        const std::string& key,
        const std::string& value)
    {
        std::scoped_lock lock(_access_mutex);

        _custom_headers[key] = value;

        result.set_to_good_status_without_value();
    }

    void GmailMailer::set_header_async(
        Result<std::future<void>>& result,
        const std::string& key,
        const std::string& value)
    {
        result.set_to_good_status_with_value(
            std::async(
                std::launch::async,
                [this, key, value]()
            {
                Result<void> result;

                set_header(result, key, value);
            })
        );
    }

    void GmailMailer::attach_inline_image(
        Result<void>& result,
        const std::string& file_path,
        const std::string& content_id,
        const std::string& mime_type)
    {
        std::scoped_lock lock(_access_mutex);

        if (!std::filesystem::exists(file_path))
        {
            return result.set_to_bad_status_without_value(
                "File does not exist"
            );
        }

        curl_mimepart* part = curl_mime_addpart(_mime_related);
        curl_mime_filedata(part, file_path.c_str());
        curl_mime_type(part, mime_type.c_str());
        curl_mime_encoder(part, "base64");
        curl_mime_filename(part, file_path.c_str());

        std::string header = "Content-ID: <" + content_id + ">";
        struct curl_slist* header_list =
            curl_slist_append(
                nullptr,
                header.c_str()
            );
        curl_mime_headers(part, header_list, 1);

        result.set_to_good_status_without_value();
    }

    void GmailMailer::attach_inline_image_async(
        Result<std::future<void>>& result,
        const std::string& file_path,
        const std::string& content_id,
        const std::string& mime_type)
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, file_path, content_id, mime_type]()
            {
                Result<void> result;

                attach_inline_image(
                    result,
                    file_path,
                    content_id,
                    mime_type
                );
            })
        );
    }

    void GmailMailer::attach_file(
        Result<void>& result,
        const std::string& file_path,
        const std::string& mime_type,
        const std::string& filename)
    {
        std::scoped_lock lock(_access_mutex);

        if (!std::filesystem::exists(file_path))
        {
            return result.set_to_bad_status_without_value(
                "File does not exist"
            );
        }

        curl_mimepart* part = curl_mime_addpart(_mime_mixed);
        curl_mime_filedata(part, file_path.c_str());
        curl_mime_type(part, mime_type.c_str());
        curl_mime_encoder(part, "base64");
        curl_mime_filename(part, filename.c_str());

        std::string header =
            "Content-Disposition: attachment; filename=\"" + filename + "\"";
        struct curl_slist* header_list = curl_slist_append(nullptr, header.c_str());
        curl_mime_headers(part, header_list, 1);

        result.set_to_good_status_without_value();
    }

    void GmailMailer::attach_file_async(
        Result<std::future<void>>& result,
        const std::string& file_path,
        const std::string& mime_type,
        const std::string& filename)
    {
        result.set_to_good_status_with_value(
            std::async(std::launch::async,
                [this, file_path, mime_type, filename]()
            {
                Result<void> result;

                attach_file(
                    result,
                    file_path,
                    mime_type,
                    filename
                );
            })
        );
    }
}
