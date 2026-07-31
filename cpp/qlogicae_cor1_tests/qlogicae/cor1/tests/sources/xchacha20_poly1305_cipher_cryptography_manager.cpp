#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		XChaCha20Poly1305CipherCryptographyManager \
	)

#include "../includes/xchacha20_poly1305_cipher_cryptography_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{	
	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_EncryptAndDecrypt_When_InputIsEmpty)
	{
		const std::string plaintext{};
		const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'A');
		const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'B');

		const std::string ciphertext =
			manager_instance.encrypt_text(plaintext, key, nonce);

		const std::string decrypted =
			manager_instance.decrypt_text(ciphertext, key, nonce);

		EXPECT_EQ(plaintext, decrypted);
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_ReturnEmpty_When_KeyIsInvalid)
	{
		const std::string plaintext{"Test"};
		const std::string invalid_key(10, 'A');
		const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'B');

		const std::string ciphertext =
			manager_instance.encrypt_text(plaintext, invalid_key, nonce);

		EXPECT_FALSE(ciphertext.empty());
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_ReturnEmpty_When_NonceIsInvalid)
	{
		const std::string plaintext{"Test"};
		const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'A');
		const std::string invalid_nonce(5, 'B');

		const std::string ciphertext =
			manager_instance.encrypt_text(plaintext, key, invalid_nonce);

		EXPECT_FALSE(ciphertext.empty());
	}

	TEST_P(XChaCha20Poly1305CipherCryptographyManagerParameterizedTest,
		Should_EncryptAndDecrypt_When_InputIsParameterized)
	{
		const std::string plaintext = GetParam();
		const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'K');
		const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'N');

		const std::string ciphertext =
			manager_instance.encrypt_text(plaintext, key, nonce);

		const std::string decrypted =
			manager_instance.decrypt_text(ciphertext, key, nonce);

		EXPECT_EQ(plaintext, decrypted);
	}

	INSTANTIATE_TEST_CASE_P(
		ValidAndEdgeCases,
		XChaCha20Poly1305CipherCryptographyManagerParameterizedTest,
		::testing::Values(
			"",
			"a",
			"Hello World",
			"1234567890",
			"Ω≈ç√∫˜µ≤≥÷",
			std::string(1024, 'X')
		)
	);

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_HandleAsyncEncryptAndDecrypt_When_CalledInFuture)
	{
		const std::string plaintext{"Async Test"};
		const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'A');
		const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'B');

		auto future_ciphertext = std::async(
			std::launch::async,
			[&]()
			{
				return manager_instance.encrypt_text(plaintext, key, nonce);
			}
		);

		const std::string ciphertext = future_ciphertext.get();

		auto future_decrypted = std::async(
			std::launch::async,
			[&]()
			{
				return manager_instance.decrypt_text(ciphertext, key, nonce);
			}
		);

		EXPECT_EQ(plaintext, future_decrypted.get());
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_HandleMultithreadedEncryptAndDecrypt_When_CalledSimultaneously)
	{
		const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'A');
		const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'B');

		std::atomic<bool> success(true);
		std::vector<std::thread> threads;

		for (size_t i = 0; i < 16; ++i)
		{
			threads.emplace_back([&, i]()
			{
				const std::string plaintext = "Thread Test " + std::to_string(i);
				const std::string ciphertext =
					manager_instance.encrypt_text(plaintext, key, nonce);
				const std::string decrypted =
					manager_instance.decrypt_text(ciphertext, key, nonce);
				if (plaintext != decrypted)
				{
					success = false;
				}
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		EXPECT_TRUE(success);
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_HandleStressEncryptionAndDecryption_When_LargeIterations)
	{
		const std::string plaintext(std::size_t(1024), 'S');
		const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'K');
		const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'N');

		bool success = true;

		for (size_t i = 0; i < 1000; ++i)
		{
			const std::string ciphertext =
				manager_instance.encrypt_text(plaintext, key, nonce);
			const std::string decrypted =
				manager_instance.decrypt_text(ciphertext, key, nonce);
			if (plaintext != decrypted)
			{
				success = false;
				break;
			}
		}

		EXPECT_TRUE(success);
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_HandleExceptionSafety_When_InvalidInputs)
	{
		const std::string invalid_key;
		const std::string invalid_nonce;
		const std::string plaintext{"Exception Test"};

		const std::string ciphertext =
			manager_instance.encrypt_text(plaintext, invalid_key, invalid_nonce);

		const std::string decrypted =
			manager_instance.decrypt_text(ciphertext, invalid_key, invalid_nonce);

		EXPECT_FALSE(ciphertext.empty());
		EXPECT_FALSE(decrypted.empty());
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_ReturnSameSingleton_When_AccessedConcurrently)
	{
		std::vector<XChaCha20Poly1305CipherCryptographyManager*>
			singleton_instances(16, nullptr);

		std::vector<std::thread>
			threads;

		for (size_t i = 0; i < 16; ++i)
		{
			threads.emplace_back([i, &singleton_instances]()
			{
				singleton_instances[i] =
					&SingletonManager::get_singleton<
						XChaCha20Poly1305CipherCryptographyManager>();
			});
		}

		for (auto& thread : threads)
		{
			thread.join();
		}

		XChaCha20Poly1305CipherCryptographyManager*
			expected_instance =
				&SingletonManager::get_singleton<XChaCha20Poly1305CipherCryptographyManager>();

		for (auto* instance : singleton_instances)
		{
			EXPECT_EQ(instance, expected_instance);
		}
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_HandleBinaryInput_When_TextContainsAllByteValues)
	{
		std::string binary_text;
		binary_text.reserve(256);
		for (unsigned char i = 0; i < 255; ++i)
		{
			binary_text.push_back(static_cast<char>(i));
		}

		std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'k');
		std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'n');

		const std::string cipher_text =
			manager_instance.encrypt_text(binary_text, key, nonce);

		EXPECT_FALSE(cipher_text.empty());

		const std::string decrypted_text =
			manager_instance.decrypt_text(cipher_text, key, nonce);

		EXPECT_EQ(binary_text, decrypted_text);
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_RespectThreadSafetyOverride_When_OverrideEnabled)
	{
		auto original_configurations = manager_instance.configurations;
		XChaCha20Poly1305CipherCryptographyManagerConfigurations
			new_configurations = original_configurations;

		new_configurations.is_thread_safety_handling_override_enabled = true;
		new_configurations.is_utility_thread_safety_handling_enabled = false;
		new_configurations.is_feature_thread_safety_handling_enabled = false;
		new_configurations.is_error_thread_safety_handling_enabled = false;

		EXPECT_TRUE(manager_instance.setup(new_configurations));

		EXPECT_TRUE(manager_instance.configurations
			.is_thread_safety_enabled_for_utility_handling());
		EXPECT_TRUE(manager_instance.configurations
			.is_thread_safety_enabled_for_feature_handling());
		EXPECT_TRUE(manager_instance.configurations
			.is_thread_safety_enabled_for_error_handling());

		EXPECT_TRUE(manager_instance.reset());
	}

	TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
		Should_RespectThreadSafetyFlags_When_OverrideDisabled)
	{
		auto original_configurations = manager_instance.configurations;
		XChaCha20Poly1305CipherCryptographyManagerConfigurations
			new_configurations = original_configurations;

		new_configurations.is_thread_safety_handling_override_enabled = false;
		new_configurations.is_utility_thread_safety_handling_enabled = true;
		new_configurations.is_feature_thread_safety_handling_enabled = true;
		new_configurations.is_error_thread_safety_handling_enabled = true;

		EXPECT_TRUE(manager_instance.setup(new_configurations));

		EXPECT_TRUE(manager_instance.configurations
			.is_thread_safety_enabled_for_utility_handling());
		EXPECT_TRUE(manager_instance.configurations
			.is_thread_safety_enabled_for_feature_handling());
		EXPECT_TRUE(manager_instance.configurations
			.is_thread_safety_enabled_for_error_handling());

		EXPECT_TRUE(manager_instance.reset());
	}

    TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
        Should_EncryptAndDecrypt_When_ValidInput)
    {
        const std::string text = "hello world";
        const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'k');
        const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'n');

        const std::string cipher = manager_instance.encrypt_text(text, key, nonce);
        EXPECT_FALSE(cipher.empty());

        const std::string decrypted = manager_instance.decrypt_text(cipher, key, nonce);
        EXPECT_EQ(decrypted, text);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
        Should_HandleEmptyString_When_EncryptAndDecrypt)
    {
        const std::string text;
        const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'k');
        const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'n');

        const std::string cipher = manager_instance.encrypt_text(text, key, nonce);
        EXPECT_TRUE(cipher.empty());

        const std::string decrypted = manager_instance.decrypt_text(cipher, key, nonce);
        EXPECT_EQ(decrypted, text);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
        Should_EncryptAndDecryptAsync_When_UsingFutures)
    {
        const std::string text = "async test string";
        const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'k');
        const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'n');

        auto encrypt_future = std::async(std::launch::async, [&]()
        {
            return manager_instance.encrypt_text(text, key, nonce);
        });

        const std::string cipher = encrypt_future.get();
        EXPECT_FALSE(cipher.empty());

        auto decrypt_future = std::async(std::launch::async, [&]()
        {
            return manager_instance.decrypt_text(cipher, key, nonce);
        });

        const std::string decrypted = decrypt_future.get();
        EXPECT_EQ(decrypted, text);
    }

    TEST_F(XChaCha20Poly1305CipherCryptographyManagerTest,
        Should_HandleMultithreadedEncryption_When_ConcurrentThreads)
    {
        const std::string text = "threaded test";
        const std::string key(crypto_aead_xchacha20poly1305_ietf_KEYBYTES, 'k');
        const std::string nonce(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES, 'n');

        std::vector<std::thread> threads;
        std::atomic<bool> success(true);

        for (int i = 0; i < 16; ++i)
        {
            threads.emplace_back([&]()
            {
                try
                {
                    const std::string cipher = manager_instance.encrypt_text(text, key, nonce);
                    const std::string decrypted = manager_instance.decrypt_text(cipher, key, nonce);
                    if (decrypted != text)
                    {
                        success = false;
                    }
                }
                catch (...)
                {
                    success = false;
                }
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        EXPECT_TRUE(success);
    }
}

#endif
