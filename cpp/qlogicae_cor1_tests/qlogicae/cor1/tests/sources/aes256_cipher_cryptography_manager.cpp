#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		Aes256CipherCryptographyManager \
	)

#include "../includes/aes256_cipher_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(Aes256CipherCryptographyManagerTest, Should_Construct_WithoutThrow_When_Called)
	{
		ASSERT_NO_THROW(Aes256CipherCryptographyManager manager_instance);
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_Destruct_WithoutThrow_When_Called)
	{
		ASSERT_NO_THROW({
			Aes256CipherCryptographyManager manager_instance;
		});
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_EncryptAndDecrypt_Correctly_When_ValidInputs)
	{
		const std::string text = "TestString123";
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');

		std::string encrypted = manager.encrypt_text(text, key, nonce);
		ASSERT_FALSE(encrypted.empty());

		std::string decrypted = manager.decrypt_text(encrypted, key, nonce);
		ASSERT_EQ(decrypted, text);
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_ReturnNotEmptyString_When_TextIsEmpty)
	{
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');

		std::string encrypted = manager.encrypt_text("", key, nonce);
		ASSERT_TRUE(encrypted.empty());

		std::string decrypted = manager.decrypt_text(encrypted, key, nonce);
		ASSERT_TRUE(decrypted.empty());
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_ReturnNotEmptyString_When_PrivateKeyIsEmpty)
	{
		const std::string text = "SampleText";
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');

		std::string encrypted = manager.encrypt_text(text, "", nonce);
		ASSERT_FALSE(encrypted.empty());
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_ReturnNotEmptyString_When_NonceIsEmpty)
	{
		const std::string text = "SampleText";
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');

		std::string encrypted = manager.encrypt_text(text, key, "");
		ASSERT_FALSE(encrypted.empty());
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_ReturnNotEmptyString_When_InvalidBase64Input)
	{
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');

		std::string decrypted = manager.decrypt_text("INVALID_BASE64", key, nonce);
		ASSERT_FALSE(decrypted.empty());
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_HandleConcurrentEncryptionsWithoutRaceConditions)
	{
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');
		const std::string text = "ThreadSafeTest";

		const size_t thread_count = 16;
		std::vector<std::thread> threads;
		std::atomic<size_t> success_count = 0;

		for (size_t i = 0; i < thread_count; ++i)
		{
			threads.emplace_back([&]()
			{
				std::string encrypted = manager.encrypt_text(text, key, nonce);
				if (!encrypted.empty())
					success_count.fetch_add(1);
			});
		}

		for (auto& thread : threads)
			thread.join();

		ASSERT_EQ(success_count, thread_count);
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_HandleConcurrentDecryptionsWithoutRaceConditions)
	{
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');
		const std::string text = "ThreadSafeDecryptTest";
		std::string encrypted = manager.encrypt_text(text, key, nonce);

		const size_t thread_count = 16;
		std::vector<std::thread> threads;
		std::atomic<size_t> success_count = 0;

		for (size_t i = 0; i < thread_count; ++i)
		{
			threads.emplace_back([&]()
			{
				std::string decrypted = manager.decrypt_text(encrypted, key, nonce);
				if (decrypted == text)
					success_count.fetch_add(1);
			});
		}

		for (auto& thread : threads)
			thread.join();

		ASSERT_EQ(success_count, thread_count);
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_EncryptAndDecryptCorrectlyUsingAsync)
	{
		const std::string text = "AsyncTestString";
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');

		auto encrypt_future = std::async(std::launch::async, [&]()
		{
			return manager.encrypt_text(text, key, nonce);
		});

		std::string encrypted = encrypt_future.get();
		ASSERT_FALSE(encrypted.empty());

		auto decrypt_future = std::async(std::launch::async, [&]()
		{
			return manager.decrypt_text(encrypted, key, nonce);
		});

		std::string decrypted = decrypt_future.get();
		ASSERT_EQ(decrypted, text);
	}

	TEST_F(Aes256CipherCryptographyManagerTest, Should_EncryptAndDecryptUnderHighLoad)
	{
		const std::string key(crypto_aead_aes256gcm_KEYBYTES, 'k');
		const std::string nonce(crypto_aead_aes256gcm_NPUBBYTES, 'n');
		const std::string text(1024 * 1024, 'x');

		std::string encrypted = manager.encrypt_text(text, key, nonce);
		std::string decrypted = manager.decrypt_text(encrypted, key, nonce);

		ASSERT_EQ(decrypted, text);
	}

	TEST_P(Aes256CipherCryptographyManagerParameterizedTest, Should_HandleVariousTextKeyNonceCombinations)
	{
		auto [text, key, nonce] = GetParam();
		std::string encrypted = manager.encrypt_text(text, key, nonce);
		if (!text.empty() && !key.empty() && !nonce.empty())
		{
			ASSERT_FALSE(encrypted.empty());
			std::string decrypted = manager.decrypt_text(encrypted, key, nonce);
			ASSERT_EQ(decrypted, text);
		}
		else if (text.empty())
		{
			ASSERT_TRUE(encrypted.empty());
		}
		else
		{
			ASSERT_FALSE(encrypted.empty());
		}
	}

	INSTANTIATE_TEST_CASE_P(
		EncryptDecryptCombinations,
		Aes256CipherCryptographyManagerParameterizedTest,
		::testing::Values(
			std::make_tuple("", std::string(crypto_aead_aes256gcm_KEYBYTES, 'k'), std::string(crypto_aead_aes256gcm_NPUBBYTES, 'n')),
			std::make_tuple("ShortText", std::string(crypto_aead_aes256gcm_KEYBYTES, 'k'), std::string(crypto_aead_aes256gcm_NPUBBYTES, 'n')),
			std::make_tuple(std::string(1024 * 1024, 'x'), std::string(crypto_aead_aes256gcm_KEYBYTES, 'k'), std::string(crypto_aead_aes256gcm_NPUBBYTES, 'n')),
			std::make_tuple("TextWithEmptyKey", "", std::string(crypto_aead_aes256gcm_NPUBBYTES, 'n')),
			std::make_tuple("TextWithEmptyNonce", std::string(crypto_aead_aes256gcm_KEYBYTES, 'k'), "")
		)
	);

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_EncryptText)
	{
		std::string result = manager.encrypt_text("test", "key", "nonce");
		ASSERT_FALSE(result.empty());
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_DecryptText)
	{
		std::string result = manager.decrypt_text("test", "key", "nonce");
		ASSERT_FALSE(result.empty());
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_Construct)
	{
		ASSERT_TRUE(manager.construct());
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_Destruct)
	{
		ASSERT_TRUE(manager.destruct());
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_SingletonAccess)
	{
		ASSERT_NO_THROW(SingletonManager::get_singleton<Aes256CipherCryptographyManager>());
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_MultithreadedEncryption)
	{
		std::atomic<int> success_count{0};
		std::vector<std::thread> threads;
		for (int i = 0; i < 16; ++i)
		{
			threads.emplace_back([&]()
			{
				std::string result = manager.encrypt_text("multithread", "key", "nonce");
				if (!result.empty()) ++success_count;
			});
		}
		for (auto& t : threads) t.join();
		ASSERT_EQ(success_count.load(), 16);
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_MultithreadedDecryption)
	{
		std::atomic<int> success_count{0};
		std::vector<std::thread> threads;
		for (int i = 0; i < 16; ++i)
		{
			threads.emplace_back([&]()
			{
				std::string result = manager.decrypt_text("multithread", "key", "nonce");
				if (!result.empty()) ++success_count;
			});
		}
		for (auto& t : threads) t.join();
		ASSERT_EQ(success_count.load(), 16);
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_AsyncEncryption)
	{
		auto future = std::async(std::launch::async, [&]()
		{
			return manager.encrypt_text("async", "key", "nonce");
		});
		std::string result = future.get();
		ASSERT_FALSE(result.empty());
	}

	TEST_F(Aes256CipherCryptographyManagerExceptionTest, Should_HandleException_When_AsyncDecryption)
	{
		auto future = std::async(std::launch::async, [&]()
		{
			return manager.decrypt_text("async", "key", "nonce");
		});
		std::string result = future.get();
		ASSERT_FALSE(result.empty());
	}
}

#endif
