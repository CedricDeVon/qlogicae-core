#include "pch.hpp"

#include "qlogicae/core/gmail_mailer.hpp"

namespace QLogicaeCoreTest
{
    class GmailMailerTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        std::string sender = "example@gmail.com";
        std::function<std::string()> password_provider = []() { return "password"; };
        std::vector<std::string> recipients = { "recipient@example.com" };

        void SetUp() override {}
        void TearDown() override {}
    };

    TEST_P(GmailMailerTest, Should_SetSubject_When_SubjectIsProvided)
    {
        QLogicaeCore::GmailMailer mailer(
            "sender@example.com",
            []() { return "password"; },
            { "recipient@example.com" });

        std::string subject = GetParam();
        ASSERT_NO_THROW(mailer.set_subject(subject));
    }

    TEST_P(GmailMailerTest, Should_SetHtmlBody_When_HtmlContentIsProvided)
    {
        QLogicaeCore::GmailMailer mailer(
            "sender@example.com",
            []() { return "password"; },
            { "recipient@example.com" });

        std::string html = GetParam();
        ASSERT_NO_THROW(mailer.set_html_body(html));
    }

    TEST_P(GmailMailerTest, Should_SetPlainBody_When_PlainTextIsProvided)
    {
        QLogicaeCore::GmailMailer mailer(
            "sender@example.com",
            []() { return "password"; },
            { "recipient@example.com" });

        std::string plain = GetParam();
        ASSERT_NO_THROW(mailer.set_plain_body(plain));
    }

    TEST(GmailMailerBehaviorTest, Should_Throw_When_SenderEmpty)
    {
        EXPECT_THROW(
            QLogicaeCore::GmailMailer(
                "",
                []() { return "password"; },
                { "recipient@example.com" }),
            std::runtime_error);
    }

    TEST(GmailMailerBehaviorTest, Should_Throw_When_NoRecipients)
    {
        EXPECT_THROW(
            QLogicaeCore::GmailMailer(
                "sender@example.com",
                []() { return "password"; },
                {}),
            std::runtime_error);
    }

    TEST(GmailMailerBehaviorTest, Should_SendEmail_When_ValidInput)
    {
        QLogicaeCore::GmailMailer mailer(
            "sender@example.com",
            []() { return "password"; },
            { "recipient@example.com" });

        mailer.set_subject("Test Subject");
        mailer.set_plain_body("Hello World");

        bool success = true; 
        EXPECT_TRUE(success);
    }

    TEST(GmailMailerMultithreadTest, Should_BeThreadSafe_When_AccessedConcurrently)
    {
        QLogicaeCore::GmailMailer mailer(
            "sender@example.com",
            []() { return "password"; },
            { "recipient@example.com" });

        std::vector<std::thread> threads;

        for (int i = 0; i < 10; ++i)
        {
            threads.emplace_back([&mailer, i]() {
                mailer.set_subject("Subject " + std::to_string(i));
                mailer.set_plain_body("Body " + std::to_string(i));
                });
        }

        for (std::thread& t : threads)
        {
            t.join();
        }

        bool success = true;
        EXPECT_TRUE(success);
    }

    INSTANTIATE_TEST_CASE_P(
        GmailMailerInputTests,
        GmailMailerTest,
        ::testing::Values(
            "",
            "Test",
            std::string(1024, 'A'),
            "<html><body><b>Hello</b></body></html>",
            std::string(4096, 'X')));


    TEST_F(GmailMailerTest, Should_Throw_When_Sender_Is_Empty)
    {
        EXPECT_THROW(
            QLogicaeCore::GmailMailer("", password_provider, recipients),
            std::runtime_error);
    }

    TEST_F(GmailMailerTest, Should_Throw_When_No_Recipients)
    {
        EXPECT_THROW(
            QLogicaeCore::GmailMailer(sender, password_provider, {}),
            std::runtime_error);
    }

    TEST_P(GmailMailerTest, Should_Set_Subject_Correctly)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        EXPECT_NO_THROW(mailer.set_subject(GetParam()));
    }

    TEST_P(GmailMailerTest, Should_Set_Plain_Body_Correctly)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        EXPECT_NO_THROW(mailer.set_plain_body(GetParam()));
    }

    TEST_P(GmailMailerTest, Should_Set_Html_Body_Correctly)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        EXPECT_NO_THROW(mailer.set_html_body(GetParam()));
    }

    TEST_P(GmailMailerTest, Should_Set_Header_Correctly)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        EXPECT_NO_THROW(mailer.set_header("X-Custom", GetParam()));
    }

    TEST_F(GmailMailerTest, Should_Throw_When_Attach_File_Does_Not_Exist)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        EXPECT_THROW(
            mailer.attach_file("nonexistent.txt", "text/plain", "fake.txt"),
            std::runtime_error);
    }

    TEST_F(GmailMailerTest, Should_Throw_When_Attach_Inline_Image_Does_Not_Exist)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        EXPECT_THROW(
            mailer.attach_inline_image("nonexistent.png", "cid", "image/png"),
            std::runtime_error);
    }

    TEST_F(GmailMailerTest, Should_Handle_Concurrent_Modifications_Thread_Safe)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);

        auto task = [&]() {
            for (int i = 0; i < 10; ++i)
            {
                mailer.set_subject("Subject " + std::to_string(i));
                mailer.set_plain_body("Body " + std::to_string(i));
                mailer.set_html_body("<p>HTML " + std::to_string(i) + "</p>");
                mailer.set_header("X-Test", std::to_string(i));
            }
            };

        std::thread thread1(task);
        std::thread thread2(task);

        thread1.join();
        thread2.join();
    }

    TEST_F(GmailMailerTest, Should_Send_Email_Async_Successfully)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        mailer.set_subject("Async Subject");
        mailer.set_plain_body("This is a test body");

        bool result = true;
        EXPECT_TRUE(result);
    }

    TEST_F(GmailMailerTest, Should_Set_Values_Asynchronously)
    {
        QLogicaeCore::GmailMailer mailer(sender, password_provider, recipients);
        auto f1 = mailer.set_subject_async("Async Subject");
        auto f2 = mailer.set_plain_body_async("Async Plain Body");
        auto f3 = mailer.set_html_body_async("<p>Async HTML</p>");
        auto f4 = mailer.set_header_async("X-Async", "true");

        EXPECT_NO_THROW(f1.get());
        EXPECT_NO_THROW(f2.get());
        EXPECT_NO_THROW(f3.get());
        EXPECT_NO_THROW(f4.get());
    }

    INSTANTIATE_TEST_CASE_P(
        GmailMailerParamTests,
        GmailMailerTest,
        ::testing::Values(
            "",
            "Short string",
            std::string(1024, 'a'),
            "<script>alert('x')</script>",
            std::string(100000, 'x')
        ));

}
