#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		GmailApiManager \
	)

#include "../includes/gmail_api_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	TEST_F(
		GmailApiManagerTest,
		Should_ConstructSuccessfully_When_ValidConfigurations)
	{
		EXPECT_TRUE(manager.construct());
	}

	TEST_F(
		GmailApiManagerTest,
		Should_DestructSuccessfully_When_Constructed)
	{
		manager.construct();
		EXPECT_TRUE(manager.destruct());
	}

	TEST_F(
		GmailApiManagerTest,
		Should_ReturnBadResponse_When_ConfigurationsInvalid)
	{
		manager.configurations.full_smtp_server_address = "";
		manager.configurations.sender_email_address = "";
		manager.configurations.to_recipients.clear();
		manager.configurations.password_provider = []() { return ""; };

		GmailApiManagerResponse
			response =
				manager.send_email();

		EXPECT_EQ(
			response.status,
			ResultsStatus::BAD
		);
	}

	TEST_P(
		GmailApiManagerParameterizedInvalidTest,
		Should_ReturnBadResponse_When_InvalidRecipientProvided)
	{
		manager.configurations.full_smtp_server_address =
			"smtp://localhost:25";
		manager.configurations.sender_email_address =
			"sender@example.com";
		manager.configurations.to_recipients.clear();
		manager.configurations.to_recipients.push_back(
			GetParam()
		);
		manager.configurations.password_provider =
			[]() { return "password"; };

		GmailApiManagerResponse
			response =
				manager.send_email();

		EXPECT_EQ(
			response.status,
			ResultsStatus::BAD
		);
	}

	INSTANTIATE_TEST_CASE_P(
		GmailApiManagerInvalidRecipientsTests,
		GmailApiManagerParameterizedInvalidTest,
		::testing::Values(
			"",
			"invalid-email",
			"@example.com"
		)
	);

	TEST_F(
		GmailApiManagerTest,
		Should_ReturnBadResponse_When_StringPrivateKeyEmpty)
	{
		manager.configurations.full_smtp_server_address =
			"smtp://localhost:25";
		manager.configurations.sender_email_address =
			"";
		manager.configurations.to_recipients.push_back(
			"recipient@example.com"
		);
		manager.configurations.password_provider =
			[]() { return "password"; };

		GmailApiManagerResponse
			response =
				manager.send_email();

		EXPECT_EQ(
			response.status,
			ResultsStatus::BAD
		);
	}

	TEST_F(
		GmailApiManagerTest,
		Should_ReturnFalse_When_StringPublicKeyEmpty)
	{
		manager.configurations.full_smtp_server_address =
			"";
		manager.configurations.sender_email_address =
			"sender@example.com";
		manager.configurations.to_recipients.push_back(
			"recipient@example.com"
		);
		manager.configurations.password_provider =
			[]() { return ""; };

		GmailApiManagerResponse
			response =
				manager.send_email();

		EXPECT_EQ(
			response.status,
			ResultsStatus::BAD
		);
	}

	TEST_F(
		GmailApiManagerTest,
		Should_HandleAsyncVerify_When_MultipleFuturesExecute)
	{
		manager.configurations.full_smtp_server_address =
			"smtp://localhost:25";
		manager.configurations.sender_email_address =
			"sender@example.com";
		manager.configurations.to_recipients.push_back(
			"recipient@example.com"
		);
		manager.configurations.password_provider =
			[]() { return ""; };

		auto
			future_one =
				std::async(
					std::launch::async,
					[&]() -> GmailApiManagerResponse
					{
						return manager.send_email();
					}
				);

		auto
			future_two =
				std::async(
					std::launch::async,
					[&]() -> GmailApiManagerResponse
					{
						return manager.send_email();
					}
				);

		EXPECT_EQ(future_one.get().status, ResultsStatus::BAD);
		EXPECT_EQ(future_two.get().status, ResultsStatus::BAD);
	}

	TEST_F(
		GmailApiManagerTest,
		Should_HandleAsyncConcurrentSendingAcrossThreads)
	{
		manager.configurations.full_smtp_server_address =
			"smtp://localhost:25";
		manager.configurations.sender_email_address =
			"";
		manager.configurations.to_recipients.push_back(
			"recipient@example.com"
		);
		manager.configurations.password_provider =
			[]() { return ""; };

		std::vector<std::thread>
			threads;

		for (size_t index = 0; index < 4; ++index)
		{
			threads.push_back(
				std::thread(
					[&]()
					{
						GmailApiManagerResponse
							response =
								manager.send_email();
						EXPECT_EQ(
							response.status,
							ResultsStatus::BAD
						);
					}
				)
			);
		}

		for (auto& thread : threads)
		{
			thread.join();
		}
	}

	TEST_F(
		GmailApiManagerTest,
		Should_HandleStressLoad_When_RepeatedVerify)
	{
		manager.configurations.full_smtp_server_address =
			"";
		manager.configurations.sender_email_address =
			"";
		manager.configurations.to_recipients.clear();
		manager.configurations.password_provider =
			[]() { return ""; };

		for (size_t iteration = 0; iteration < 50; ++iteration)
		{
			GmailApiManagerResponse
				response =
					manager.send_email();

			EXPECT_EQ(
				response.status,
				ResultsStatus::BAD
			);
		}
	}

	TEST_F(
		GmailApiManagerTest,
		Should_NotModifyResponseBufferDuringSend)
	{
		manager.configurations.full_smtp_server_address =
			"";
		manager.configurations.sender_email_address =
			"";
		manager.configurations.to_recipients.clear();
		manager.configurations.password_provider =
			[]() { return ""; };

		GmailApiManagerResponse
			response =
				manager.send_email();

		GmailApiManagerResponse
			copy_response =
				response;

		manager.send_email();

		EXPECT_EQ(
			copy_response.status,
			response.status
		);
	}

	TEST_F(
		GmailApiManagerTest,
		Should_HandleEmptyConfigurations_When_AllFieldsEmpty)
	{
		manager.configurations.full_smtp_server_address = "";
		manager.configurations.sender_email_address = "";
		manager.configurations.to_recipients.clear();
		manager.configurations.cc_recipients.clear();
		manager.configurations.bcc_recipients.clear();
		manager.configurations.attached_files.clear();
		manager.configurations.password_provider = []() { return ""; };
		manager.configurations.custom_headers.clear();

		GmailApiManagerResponse
			response =
				manager.send_email();

		EXPECT_EQ(
			response.status,
			ResultsStatus::BAD
		);
	}
}

#endif
