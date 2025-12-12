#include "pch.hpp"

#include "qlogicae_cpp_core/includes/validation_manager.hpp"

namespace QLogicaeCppCoreTest
{
	class ValidatorsTest : public ::testing::TestWithParam<std::string>
	{
	protected:
		QLogicaeCppCore::ValidationManager& validators = QLogicaeCppCore::VALIDATION_MANAGER;
		QLogicaeCppCore::Result<bool> result;
	};

    std::string generate_invalid_port()
    {
        static std::vector<std::string> values =
        {
            "-1", "70000", "abc", "", "65536", " "
        };
        return values[std::rand() % values.size()];
    }

    std::string generate_random_date()
    {
        static std::vector<std::string> values =
        {
            "2020/12/12",
            "12-31-2020",
            "20201301",
            "2020-00-01",
            "bad-date"
        };
        return values[std::rand() % values.size()];
    }

    std::string generate_unicode_junk(const size_t len)
    {
        std::string result;
        while (result.size() < len)
        {
            result += "\xF0\x9F\x98\x8A";
        }
        return result;
    }

	INSTANTIATE_TEST_CASE_P(
		ValidatorsTestCases,
		ValidatorsTest,
		::testing::Values(
			"", "abc", "ABC", "123", "aBc123", " ", "@!#",
			"slug-case-example", "user@example.com",
			"deadbeef", "1234abcd5678efgh",
			"550e8400-e29b-41d4-a716-446655440000",
			"2020-02-29", "2099-12-31", "0000-00-00", "1970-01-01",
			"ThisIsALongInputStringToTestMaximumLimitOf128Characters12345678901234567890123456789012345678901234567890123456789012"
		)
	);

	TEST_P(ValidatorsTest, Should_ReturnFalse_When_Empty)
	{
		std::string_view input = GetParam();
		validators.is_not_empty(result, input);
		if (input.empty())
		{
			ASSERT_FALSE(result.get_value());
		}
		else
		{
			ASSERT_TRUE(result.get_value());
		}
	}

	TEST_P(ValidatorsTest, Should_ReturnTrue_When_Empty)
	{
		std::string_view input = GetParam();
		validators.is_empty(result, input);
		ASSERT_EQ(result.get_value(), input.empty());
	}


	TEST_P(ValidatorsTest, Should_ReturnTrue_When_AllLowercase)
	{
		std::string_view input = GetParam();
		bool expected = !input.empty() && std::ranges::all_of(input, [](char c) {return std::islower(static_cast<unsigned char>(c)); });
		validators.is_lowercase(result, input);
		ASSERT_EQ(result.get_value(), expected);
	}


	TEST_P(ValidatorsTest, Should_ReturnTrue_When_AllUppercase)
	{
		std::string_view input = GetParam();
		bool expected = !input.empty() && std::ranges::all_of(input, [](char c) {return std::isupper(static_cast<unsigned char>(c)); });
		validators.is_uppercase(result, input);
		ASSERT_EQ(result.get_value(), expected);
	}


	TEST_P(ValidatorsTest, Should_Identify_FirstLetterUppercase)
	{
		std::string_view input = GetParam();
		bool expected = !input.empty() && std::isupper(static_cast<unsigned char>(input.front()));
		validators.is_first_letter_uppercase(result, input);
		ASSERT_EQ(result.get_value(), expected);
	}

	TEST_P(ValidatorsTest, Should_Validate_PrefixAndSuffix)
	{
		std::string_view input = GetParam();
		validators.is_prefix_found(result, input, "a");
		ASSERT_EQ(result.get_value(), input.starts_with("a"));
		validators.is_suffix_found(result, input, "z");
		ASSERT_EQ(result.get_value(), input.ends_with("z"));
	}


	TEST_P(ValidatorsTest, Should_Identify_Substring)
	{
		std::string_view input = GetParam();
		validators.is_substring_found(result, input, "a");
		ASSERT_EQ(result.get_value(), input.find("a") != std::string::npos);
	}

	TEST_P(ValidatorsTest, Should_Validate_PortInRange)
	{
		validators.is_port_in_range(result, static_cast<uint32_t>(80));
		ASSERT_TRUE(result.get_value());
		validators.is_port_in_range(result, static_cast<uint32_t>(0));
		ASSERT_FALSE(result.get_value());
		validators.is_port_in_range(result, std::string_view("443"));
		ASSERT_TRUE(result.get_value());
		validators.is_port_in_range(result, std::string_view("notaport"));
		ASSERT_FALSE(result.get_value());
	}


	TEST_P(ValidatorsTest, Should_Validate_Alphanumeric)
	{
		std::string_view input = GetParam();
		bool expected = !input.empty() && std::ranges::all_of(input, [](char c) {return std::isalnum(static_cast<unsigned char>(c)); });
		validators.is_alpanumeric(result, input);
		ASSERT_EQ(result.get_value(), expected);
	}


	TEST_P(ValidatorsTest, Should_Validate_Decimal)
	{
		std::string_view input = GetParam();
		bool valid = true;
		bool seen = false;
		for (char c : input)
		{
			if (c == '.')
			{
				if (seen)
				{
					valid = false;
					break;
				}
				seen = true;
			}
			else if (!std::isdigit(static_cast<unsigned char>(c)))
			{
				valid = false;
				break;
			}
		}
		valid = valid && !input.empty();
		validators.is_decimal(result, input);
		ASSERT_EQ(result.get_value(), valid);
	}


	TEST_F(ValidatorsTest, Should_Validate_UTFEncodings)
    {
        validators.is_utf8(result, "abc");
        ASSERT_TRUE(result.get_value());
        validators.is_utf8(result, "\xC0");
        ASSERT_FALSE(result.get_value());
        validators.is_utf16(result, "\xFF\xFEtext");
        ASSERT_TRUE(result.get_value());
        validators.is_utf16(result, "x");
        ASSERT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_LeapYearText)
    {
        validators.is_leap_year(result, "2020");
        ASSERT_TRUE(result.get_value());
        validators.is_leap_year(result, "1900");
        ASSERT_FALSE(result.get_value());
        validators.is_leap_year(result, static_cast<int64_t>(2000));
        ASSERT_TRUE(result.get_value());
        validators.is_leap_year(result, static_cast<int64_t>(2023));
        ASSERT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, Should_Fuzz_RegexValidatorsUnderConcurrency)
    {
        const std::vector<std::string> fuzz_inputs = {
            "c29tZXRleHQ=", "slug-case-example", "deadbeef",
            "550e8400-e29b-41d4-a716-446655440000", "<root></root>",
            "invalid_slug", "not_xml", "not_base64", "baduuid"
        };

        std::atomic<int> success_count = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 16; ++i)
        {
            threads.emplace_back([&]()
                {
                    QLogicaeCppCore::ValidationManager& local = validators;
                    QLogicaeCppCore::Result<bool> r;

                    for (const auto& input : fuzz_inputs)
                    {
                        local.is_base64(r, input);
                        if (r.get_value()) ++success_count;

                        local.is_slug(r, input);
                        if (r.get_value()) ++success_count;

                        local.is_hex(r, input);
                        if (r.get_value()) ++success_count;

                        local.is_uuid4(r, input);
                        if (r.get_value()) ++success_count;
                    }
                });
        }

        for (auto& t : threads) t.join();

        ASSERT_GT(success_count.load(), 0);
    }

    TEST_F(ValidatorsTest, Should_Reject_Malicious_Inputs)
    {
        std::vector<std::string> malicious_inputs = {
            "\x00", "\x1B[31m", "DROP TABLE users;", "<script>alert(1)</script>",
            "\"unclosed", "name,age\njohn,\"doe", "<tag><unclosed>",
            "user@@domain..com", "http:::/wrong", "some slug!", "   ", "\xFF\xFE\x00\x00"
        };

        QLogicaeCppCore::Result<bool> r;

        for (const auto& input : malicious_inputs)
        {
            validators.is_email(r, input);
            ASSERT_FALSE(r.get_value());

            validators.is_slug(r, input);
            ASSERT_FALSE(r.get_value());

            validators.is_uri(r, input);
            ASSERT_FALSE(r.get_value());
        }
    }

    TEST_F(ValidatorsTest, Should_Fuzz_DateTimeAndISOFormats)
    {
        std::vector<std::string> edge_dates = {
            "0000-01-01", "1900-02-28", "2000-02-29", "2023-12-31",
            "9999-12-31", "1970-01-01", "2038-01-19",
            "not-a-date", "31/12/2020", "2020-13-01", "2020-00-10"
        };

        QLogicaeCppCore::Result<bool> r;

        for (const auto& date : edge_dates)
        {
            ASSERT_NO_THROW(validators.is_date(r, date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_datetime(r, date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_past_date(r, date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_future_date(r, date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_iso8601(r, date));
        }
    }

    TEST_F(ValidatorsTest, Should_RandomFuzz_UTF8_Email_JSON)
    {
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> len_dist(1, 512);

        auto random_string = [&](int max_len)
            {
                size_t len = len_dist(rng);
                std::string str;
                for (size_t i = 0; i < len; ++i)
                    str += chars[rng() % chars.size()];
                return str;
            };

        QLogicaeCppCore::Result<bool> r;

        for (int i = 0; i < 1000; ++i)
        {
            std::string fuzz = random_string(512);

            ASSERT_NO_THROW(validators.is_utf8(r, fuzz));
            ASSERT_NO_THROW(validators.is_email(r, fuzz));
        }
    }

    TEST_F(ValidatorsTest, Should_Handle_Malformed_Corpus_Inputs)
    {
        std::vector<std::string> malformed_base64 = {
            "!!invalid!!", "abcd===", "12345", "@@@", "", "c29tZXRleHQ"
        };
        std::vector<std::string> malformed_emails = {
            "user@@domain", "userdomain.com", "@nouser.com", "user@", "", "user@.com"
        };

        QLogicaeCppCore::Result<bool> r;

        for (const auto& input : malformed_base64)
            ASSERT_NO_THROW(validators.is_base64(r, input));

        for (const auto& input : malformed_emails)
            ASSERT_NO_THROW(validators.is_email(r, input));
    }

    TEST_F(ValidatorsTest, Should_Stress_Benchmark_EmailSlugJson)
    {
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_@.:{}[],\" ";
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> len_dist(10, 256);

        auto random_string = [&](size_t len)
            {
                std::string out;
                for (size_t i = 0; i < len; ++i)
                    out += chars[rng() % chars.size()];
                return out;
            };

        QLogicaeCppCore::Result<bool> r;

        for (int i = 0; i < 10000; ++i)
        {
            std::string fuzz = random_string(len_dist(rng));
            validators.is_email(r, fuzz);
            validators.is_slug(r, fuzz);
        }

        SUCCEED();
    }

    TEST_F(ValidatorsTest, Should_Not_Leak_Under_Regex_Stress)
    {
        const std::string input = "c29tZXRleHQ=";
        QLogicaeCppCore::Result<bool> r;

        for (int i = 0; i < 10000; ++i)
        {
            validators.is_base64(r, input);
            validators.is_ipv6(r, "::1");
            validators.is_mac_address(r, "00:1A:2B:3C:4D:5E");
        }
    }

    TEST(ValidatorsABIStability, Should_Preserve_Signature_Compatibility)
    {
        using FuncType = void(QLogicaeCppCore::ValidationManager::*)(QLogicaeCppCore::Result<bool>&, const std::string_view&);
        FuncType f = &QLogicaeCppCore::ValidationManager::is_email;
        ASSERT_NE(f, nullptr);
    }

    TEST_F(ValidatorsTest, Should_Validate_EmptyVector)
    {
        std::vector<int> input;
        QLogicaeCppCore::Result<bool> r;
        validators.is_empty(r, input);
        ASSERT_TRUE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_SortedVector)
    {
        std::vector<int> sorted_values{ 1,2,3,4 };
        std::vector<int> unsorted_values{ 4,2,1,3 };

        QLogicaeCppCore::Result<bool> r;
        validators.is_sorted(r, sorted_values);
        ASSERT_TRUE(r.get_value());
        validators.is_sorted(r, unsorted_values);
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_UniqueValues)
    {
        std::vector<int> unique_values{ 1,2,3 };
        std::vector<int> duplicate_values{ 1,2,2,3 };

        QLogicaeCppCore::Result<bool> r;
        validators.is_unique(r, unique_values);
        ASSERT_TRUE(r.get_value());
        validators.is_unique(r, duplicate_values);
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_EnumValue)
    {
        int allowed[] = { 10,20,30 };
        QLogicaeCppCore::Result<bool> r;

        validators.is_enum_value(r, 20, std::span<const int>(allowed));
        ASSERT_TRUE(r.get_value());
        validators.is_enum_value(r, 40, std::span<const int>(allowed));
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Find_MatchingPredicate)
    {
        std::vector<int> input{ 1,2,3,4 };
        std::function<bool(const int&)> predicate = [](const int& v) {return v == 3; };
        QLogicaeCppCore::Result<bool> r;

        validators.is_found(r, input, predicate);
        ASSERT_TRUE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_AllMatchPredicate)
    {
        std::vector<int> input{ 2,4,6 };
        auto is_even = [](int v) {return v % 2 == 0; };
        QLogicaeCppCore::Result<bool> r;

        validators.is_valid_range(r, input, is_even);
        ASSERT_TRUE(r.get_value());
        input.push_back(3);
        validators.is_valid_range(r, input, is_even);
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Fail_EnumValue_When_Empty)
    {
        std::span<const int> empty_span;
        QLogicaeCppCore::Result<bool> r;
        validators.is_enum_value(r, 10, empty_span);
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_Sorted_When_SingleOrEqual)
    {
        std::vector<int> single_value{ 1 };
        std::vector<int> equal_values{ 2,2,2 };
        QLogicaeCppCore::Result<bool> r;

        validators.is_sorted(r, single_value);
        ASSERT_TRUE(r.get_value());
        validators.is_sorted(r, equal_values);
        ASSERT_TRUE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Fail_AllMatchPredicate_When_AllFail)
    {
        std::vector<int> input{ 1,2,3 };
        auto always_false = [](int) {return false; };
        QLogicaeCppCore::Result<bool> r;

        validators.is_valid_range(r, input, always_false);
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_Unique_With_EdgeValues)
    {
        std::vector<int64_t> values{
            std::numeric_limits<int64_t>::min(),
            std::numeric_limits<int64_t>::max()
        };
        QLogicaeCppCore::Result<bool> r;

        validators.is_unique(r, values);
        ASSERT_TRUE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Fuzz_RegexAndUtfValidators)
    {
        std::vector<std::string> fuzz_inputs = {
            "", "a", "!!@@", "123", "abcdEFGH", "this_is_slug", "bad slug",
            "aGVsbG8gd29ybGQ=", "c29tZVRleHQ=", "not_base64==", "uuid",
            "550e8400-e29b-41d4-a716-446655440000",
            "\xFF\xFE\x00a", "\xC3\x28", "\xE2\x82\xAC", "\xF0\x9F\x98\x81"
        };

        QLogicaeCppCore::Result<bool> r;

        for (const auto& input : fuzz_inputs)
        {
            validators.is_base64(r, input);
            validators.is_slug(r, input);
            validators.is_hex(r, input);
            validators.is_uuid4(r, input);
            validators.is_uuid6(r, input);
            validators.is_utf8(r, input);
            validators.is_utf16(r, input);
        }
    }

    TEST_F(ValidatorsTest, Should_Validate_DateTimePatterns)
    {
        QLogicaeCppCore::Result<bool> r;

        validators.is_date(r, "2020-12-31", "%Y-%m-%d");
        ASSERT_TRUE(r.get_value());
        validators.is_date(r, "12/31/2020", "%Y-%m-%d");
        ASSERT_FALSE(r.get_value());

        validators.is_past_date(r, "2000-01-01", "%Y-%m-%d");
        ASSERT_TRUE(r.get_value());
        validators.is_past_date(r, "3000-01-01", "%Y-%m-%d");
        ASSERT_FALSE(r.get_value());

        validators.is_unix(r, "1618033988");
        ASSERT_TRUE(r.get_value());
        validators.is_unix(r, "NaN");
        ASSERT_FALSE(r.get_value());

        validators.is_iso8601(r, "2020-12-31T23:59:59Z");
        ASSERT_TRUE(r.get_value());
        validators.is_iso8601(r, "not-date");
        ASSERT_FALSE(r.get_value());

        validators.is_utc(r, "2020-12-31T23:59:59Z");
        ASSERT_TRUE(r.get_value());
        validators.is_utc(r, "2020-12-31T23:59:59");
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Fuzz_UnicodeHeavyStrings)
    {
        std::string long_utf8_valid = "\u3053\u3093\u306B\u3061\u306F";
        long_utf8_valid += std::string(1024, 'x');

        std::string long_utf8_invalid = std::string(2048, '\xFF');
        std::string long_slug = std::string(1000, 'a') + "-valid-slug";
        std::string long_email = std::string(100, 'a') + "@example.com";

        QLogicaeCppCore::Result<bool> r;

        validators.is_utf8(r, long_utf8_valid);
        ASSERT_TRUE(r.get_value());
        validators.is_utf8(r, long_utf8_invalid);
        ASSERT_TRUE(r.get_value());
        validators.is_slug(r, long_slug);
        ASSERT_TRUE(r.get_value());
        validators.is_email(r, long_email);
        ASSERT_TRUE(r.get_value());
    }

    TEST_F(ValidatorsTest, Benchmark_HotValidators)
    {
        const std::string input = R"({"key":"value"})";
        const std::string email = "user@example.com";
        const std::string slug = "valid-slug-123";
        const std::string url = "https://example.com";
        const std::string uuid = "550e8400-e29b-41d4-a716-446655440000";

        QLogicaeCppCore::Result<bool> r;

        const int iterations = 100000;
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; ++i)
        {
            validators.is_email(r, email);
            validators.is_slug(r, slug);
            validators.is_url(r, url);
            validators.is_uuid4(r, uuid);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << ms << std::endl;
    }

    TEST_F(ValidatorsTest, Should_Find_When_AllMatch)
    {
        std::vector<int> input{ 10,20,30 };
        std::function<bool(const int&)> predicate = [](const int& v) {return v % 10 == 0; };
        QLogicaeCppCore::Result<bool> r;

        validators.is_found(r, input, predicate);
        ASSERT_TRUE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_FilePatterns)
    {
        QLogicaeCppCore::Result<bool> r;

        validators.is_file_path(r, "/usr/local/bin");
        ASSERT_TRUE(r.get_value());
        validators.is_file_path(r, "not/a/path//");
        ASSERT_FALSE(r.get_value());

        validators.is_file_name(r, "file.txt");
        ASSERT_TRUE(r.get_value());
        validators.is_file_name(r, "bad|name?.txt");
        ASSERT_FALSE(r.get_value());

        validators.is_file_extension(r, "txt");
        ASSERT_TRUE(r.get_value());
        validators.is_file_extension(r, ".txt");
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_EmailAndPassword)
    {
        QLogicaeCppCore::Result<bool> r;

        validators.is_email(r, "user@example.com");
        ASSERT_TRUE(r.get_value());
        validators.is_email(r, "user@@example..com");
        ASSERT_FALSE(r.get_value());

        QLogicaeCppCore::ValidationManagerPasswordRules rules;
        rules.minimum_length = 8;
        rules.maximum_length = 16;
        rules.require_uppercase_characters = true;
        rules.require_lowercase_characters = true;
        rules.require_alpha_numerics = true;
        rules.require_special_characters = true;
        rules.require_unique_characters = true;

        validators.is_strong_password(r, "Abc123$%", rules);
        ASSERT_TRUE(r.get_value());
        validators.is_strong_password(r, "abc123", rules);
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_PhoneNumbers)
    {
        QLogicaeCppCore::Result<bool> r;

        validators.is_phone_number(r, "+1 (800) 123-4567");
        ASSERT_TRUE(r.get_value());
        validators.is_phone_number(r, "abc800123");
        ASSERT_FALSE(r.get_value());

        validators.is_e164_phone_number(r, "+18001234567");
        ASSERT_TRUE(r.get_value());
        validators.is_e164_phone_number(r, "18001234567");
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Reject_PropertyGeneratedInvalids)
    {
        QLogicaeCppCore::Result<bool> r;

        for (int i = 0; i < 100; ++i)
        {
            std::string bad_port = generate_invalid_port();
            validators.is_port_in_range(r, bad_port);
            ASSERT_FALSE(r.get_value());

            std::string bad_date = generate_random_date();
            validators.is_date(r, bad_date, "%Y-%m-%d");
            ASSERT_FALSE(r.get_value());

            std::string junk = generate_unicode_junk(32);
            validators.is_utf8(r, junk + '\xC0');
            ASSERT_FALSE(r.get_value());
        }
    }

    TEST_F(ValidatorsTest, Should_Stress_Validators_Under_Thread_Concurrency)
    {
        const std::string url = "https://example.com/path?query=value";
        const std::string slug = "valid-slug-case";

        std::atomic<int> success = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 20; ++i)
        {
            threads.emplace_back([&]()
                {
                    QLogicaeCppCore::Result<bool> r;

                    for (int j = 0; j < 1000; ++j)
                    {
                        validators.is_url(r, url);
                        if (r.get_value()) ++success;

                        validators.is_slug(r, slug);
                        if (r.get_value()) ++success;
                    }
                });
        }

        for (auto& thread : threads)
            thread.join();

        ASSERT_EQ(success.load(), 20 * 2 * 1000);
    }

    TEST_F(ValidatorsTest, Should_Validate_AddressAndNameParts)
    {
        QLogicaeCppCore::Result<bool> r;

        validators.is_address_line(r, "123 Main Street");
        ASSERT_TRUE(r.get_value());
        validators.is_address_line(r, "a");
        ASSERT_FALSE(r.get_value());

        validators.is_full_name(r, "John Doe");
        ASSERT_TRUE(r.get_value());
        validators.is_first_name(r, "John");
        ASSERT_TRUE(r.get_value());
        validators.is_middle_name(r, "Edward");
        ASSERT_TRUE(r.get_value());
        validators.is_middle_initial(r, "E");
        ASSERT_TRUE(r.get_value());
        validators.is_middle_initial(r, "Ed");
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Match_RegexPatterns)
    {
        QLogicaeCppCore::Result<bool> r;

        validators.is_base64(r, "c29tZXRleHQ=");
        ASSERT_TRUE(r.get_value());
        validators.is_base64(r, "not_base64!!");
        ASSERT_FALSE(r.get_value());

        validators.is_slug(r, "valid-slug-example");
        ASSERT_TRUE(r.get_value());
        validators.is_slug(r, "Invalid Slug");
        ASSERT_FALSE(r.get_value());

        validators.is_hex(r, "deadbeef");
        ASSERT_TRUE(r.get_value());
        validators.is_hex(r, "nothex");
        ASSERT_FALSE(r.get_value());

        validators.is_uuid4(r, "550e8400-e29b-41d4-a716-446655440000");
        ASSERT_TRUE(r.get_value());
        validators.is_uuid4(r, "invalid-uuid");
        ASSERT_FALSE(r.get_value());

        validators.is_uuid6(r, "1e0b46e2-4b5e-6f00-8000-0026bb7655df");
        ASSERT_TRUE(r.get_value());
        validators.is_uuid6(r, "some-invalid-string");
        ASSERT_FALSE(r.get_value());

        validators.is_ipv4(r, "192.168.1.1");
        ASSERT_TRUE(r.get_value());
        validators.is_ipv4(r, "999.999.999.999");
        ASSERT_FALSE(r.get_value());

        validators.is_ipv6(r, "2001:0db8:85a3:0000:0000:8a2e:0370:7334");
        ASSERT_TRUE(r.get_value());
        validators.is_ipv6(r, "invalid_ipv6");
        ASSERT_FALSE(r.get_value());

        validators.is_url(r, "https://example.com");
        ASSERT_TRUE(r.get_value());
        validators.is_url(r, "example dot com");
        ASSERT_FALSE(r.get_value());
    }

    TEST_F(ValidatorsTest, Should_Validate_MimeBase64DataUri)
    {
        QLogicaeCppCore::Result<bool> r;

        validators.is_mime_type(r, "image/png");
        ASSERT_TRUE(r.get_value());
        validators.is_mime_type(r, "fake/type");
        ASSERT_FALSE(r.get_value());

        validators.is_base64_image(r, "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAA");
        ASSERT_TRUE(r.get_value());
        validators.is_base64_image(r, "plain text");
        ASSERT_FALSE(r.get_value());

        validators.is_data_uri(r, "data:text/plain;base64,SGVsbG8gd29ybGQ=");
        ASSERT_TRUE(r.get_value());
        validators.is_data_uri(r, "notdatauri");
        ASSERT_FALSE(r.get_value());
    }


    TEST_F(ValidatorsTest, IsPrimeTests)
    {
        validators.is_prime(result, int64_t(0));
        EXPECT_FALSE(result.get_value());

        validators.is_prime(result, int64_t(2));
        EXPECT_TRUE(result.get_value());

        validators.is_prime(result, int64_t(97));
        EXPECT_TRUE(result.get_value());

        validators.is_prime(result, "-1");
        EXPECT_FALSE(result.get_value());

        validators.is_prime(result, "abc");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, IsDivisibleByTests)
    {
        validators.is_divisible_by(result, int64_t(10), int64_t(2));
        EXPECT_TRUE(result.get_value());

        validators.is_divisible_by(result, int64_t(10), int64_t(0));
        EXPECT_FALSE(result.get_value());

        validators.is_divisible_by(result, "10", "2");
        EXPECT_TRUE(result.get_value());

        validators.is_divisible_by(result, "10", "0");
        EXPECT_FALSE(result.get_value());

        validators.is_divisible_by(result, "abc", "2");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, PercentageTests)
    {
        validators.is_percentage(result, 0.0);
        EXPECT_TRUE(result.get_value());

        validators.is_percentage(result, 100.0);
        EXPECT_TRUE(result.get_value());

        validators.is_percentage(result, -1.0);
        EXPECT_FALSE(result.get_value());

        validators.is_percentage(result, 101.0);
        EXPECT_FALSE(result.get_value());

        validators.is_percentage(result, "50.5");
        EXPECT_TRUE(result.get_value());

        validators.is_percentage(result, "abc");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, LatitudeLongitudeTests)
    {
        validators.is_latitude(result, -90.0);
        EXPECT_TRUE(result.get_value());

        validators.is_latitude(result, 91.0);
        EXPECT_FALSE(result.get_value());

        validators.is_longitude(result, -180.0);
        EXPECT_TRUE(result.get_value());

        validators.is_longitude(result, 181.0);
        EXPECT_FALSE(result.get_value());

        validators.is_coordinate(result, "45.0", "90.0");
        EXPECT_TRUE(result.get_value());

        validators.is_coordinate(result, "-100.0", "0.0");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, CountryCurrencyLanguageCodes)
    {
        validators.is_country_code(result, "US");
        EXPECT_TRUE(result.get_value());

        validators.is_country_code(result, "USA");
        EXPECT_FALSE(result.get_value());

        validators.is_currency_code(result, "USD");
        EXPECT_TRUE(result.get_value());

        validators.is_currency_code(result, "US");
        EXPECT_FALSE(result.get_value());

        validators.is_language_code(result, "en");
        EXPECT_TRUE(result.get_value());

        validators.is_language_code(result, "eng");
        EXPECT_TRUE(result.get_value());

        validators.is_language_code(result, "english");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, RGBAndRGBAColors)
    {
        validators.is_rgb_color(result, uint8_t(255), uint8_t(0), uint8_t(128));
        EXPECT_TRUE(result.get_value());

        validators.is_rgba_color(result, uint8_t(255), uint8_t(0), uint8_t(128), uint8_t(255));
        EXPECT_TRUE(result.get_value());

        validators.is_rgb_color(result, "rgb(255,0,128)");
        EXPECT_TRUE(result.get_value());

        validators.is_rgba_color(result, "rgba(255,0,128,0.5)");
        EXPECT_TRUE(result.get_value());

        validators.is_hex_color(result, "#FF00FF");
        EXPECT_TRUE(result.get_value());

        validators.is_hex_color(result, "#GG00FF");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, FileValidationTests)
    {
        validators.is_file_path(result, "C:\\Users\\Test\\file.txt");
        EXPECT_TRUE(result.get_value());

        validators.is_file_name(result, "file.txt");
        EXPECT_TRUE(result.get_value());

        validators.is_file_extension(result, "txt");
        EXPECT_TRUE(result.get_value());

        std::set<std::string> allowed_extensions{ "txt", "csv" };
        validators.is_file_extension_allowed(result, "txt", allowed_extensions);
        EXPECT_TRUE(result.get_value());

        validators.is_file_extension_allowed(result, "exe", allowed_extensions);
        EXPECT_FALSE(result.get_value());

        validators.is_file_size_allowed(result, 512, 1024);
        EXPECT_TRUE(result.get_value());

        validators.is_file_size_allowed(result, 2048, 1024);
        EXPECT_FALSE(result.get_value());

        std::set<std::string> allowed_types{ "text", "image" };
        validators.is_file_type_allowed(result, "text", allowed_types);
        EXPECT_TRUE(result.get_value());

        validators.is_file_type_allowed(result, "video", allowed_types);
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, AgeAndGenderTests)
    {
        validators.is_age(result, uint8_t(0));
        EXPECT_TRUE(result.get_value());

        validators.is_age(result, uint8_t(130));
        EXPECT_TRUE(result.get_value());

        validators.is_age(result, uint8_t(131));
        EXPECT_FALSE(result.get_value());

        validators.is_adult(result, uint8_t(18));
        EXPECT_TRUE(result.get_value());

        validators.is_adult(result, uint8_t(17), uint8_t(16));
        EXPECT_TRUE(result.get_value());

        validators.is_juvenile(result, uint8_t(13));
        EXPECT_TRUE(result.get_value());

        validators.is_child(result, uint8_t(12));
        EXPECT_TRUE(result.get_value());

        validators.is_gender(result, "M");
        EXPECT_TRUE(result.get_value());

        validators.is_gender(result, "female");
        EXPECT_TRUE(result.get_value());

        validators.is_gender(result, "nonbinary");
        EXPECT_TRUE(result.get_value());

        validators.is_gender(result, "X");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, PersonalNamesTests)
    {
        validators.is_first_name(result, "John");
        EXPECT_TRUE(result.get_value());

        validators.is_middle_name(result, "Paul");
        EXPECT_TRUE(result.get_value());

        validators.is_middle_initial(result, "A");
        EXPECT_TRUE(result.get_value());

        validators.is_middle_initial(result, "AB");
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, StrongPasswordTests)
    {
        QLogicaeCppCore::ValidationManagerPasswordRules rules;
        rules.minimum_length = 8;
        rules.maximum_length = 16;
        rules.require_uppercase_characters = true;
        rules.require_lowercase_characters = true;
        rules.require_alpha_numerics = true;
        rules.require_special_characters = true;
        rules.require_unique_characters = true;

        validators.is_strong_password(result, "Abc123!@#", rules);
        EXPECT_TRUE(result.get_value());

        validators.is_strong_password(result, "abc123", rules);
        EXPECT_FALSE(result.get_value());

        validators.is_strong_password(result, "AAbbCC11!!", rules);
        EXPECT_FALSE(result.get_value());
    }

    TEST_F(ValidatorsTest, CharacterRepeatedAndBlacklistTests)
    {
        validators.is_character_repeated(result, "aaab", 2);
        EXPECT_TRUE(result.get_value());

        validators.is_character_repeated(result, "abc", 1);
        EXPECT_FALSE(result.get_value());

        std::vector<std::string> blacklist{ "bad", "evil" };
        validators.is_blacklisted_word_found(result, "this is bad", blacklist);
        EXPECT_TRUE(result.get_value());

        validators.is_blacklisted_word_found(result, "all good", blacklist);
        EXPECT_FALSE(result.get_value());
    }

    /*
    TEST_P(ValidatorsTest, Base64Validation)
    {
        validators.is_base64(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(Base64Valid, ValidatorsTest, ::testing::Values(
        "SGVsbG8gd29ybGQ=",
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQ="
    ));

    TEST_P(ValidatorsTest, SlugValidation)
    {
        validators.is_slug(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(SlugValid, ValidatorsTest, ::testing::Values(
        "my-slug",
        "test123-slug"
    ));

    TEST_P(ValidatorsTest, HexValidation)
    {
        validators.is_hex(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(HexValid, ValidatorsTest, ::testing::Values(
        "0x1a2b3c",
        "FFAA00"
    ));

    TEST_P(ValidatorsTest, UUID4Validation)
    {
        validators.is_uuid4(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(UUID4Valid, ValidatorsTest, ::testing::Values(
        "550e8400-e29b-41d4-a716-446655440000"
    ));

    TEST_P(ValidatorsTest, UUID6Validation)
    {
        validators.is_uuid6(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(UUID6Valid, ValidatorsTest, ::testing::Values(
        "550e8400-e29b-61d4-a716-446655440000"
    ));

    TEST_P(ValidatorsTest, IPv4Validation)
    {
        validators.is_ipv4(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(IPv4Valid, ValidatorsTest, ::testing::Values(
        "192.168.0.1",
        "8.8.8.8"
    ));

    TEST_P(ValidatorsTest, IPv6Validation)
    {
        validators.is_ipv6(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(IPv6Valid, ValidatorsTest, ::testing::Values(
        "2001:0db8:85a3:0000:0000:8a2e:0370:7334"
    ));

    TEST_P(ValidatorsTest, URLValidation)
    {
        validators.is_url(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(URLValid, ValidatorsTest, ::testing::Values(
        "https://www.example.com",
        "http://localhost:8080/path"
    ));

    TEST_P(ValidatorsTest, URIValidation)
    {
        validators.is_uri(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(URIValid, ValidatorsTest, ::testing::Values(
        "https://example.com/resource",
        "ftp://user:pass@host:21/file"
    ));

    TEST_P(ValidatorsTest, MACAddressValidation)
    {
        validators.is_mac_address(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(MACValid, ValidatorsTest, ::testing::Values(
        "00:1A:2B:3C:4D:5E",
        "AA-BB-CC-DD-EE-FF"
    ));

    TEST_P(ValidatorsTest, HostnameValidation)
    {
        validators.is_hostname(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(HostnameValid, ValidatorsTest, ::testing::Values(
        "example.com",
        "sub.domain.local"
    ));

    TEST_P(ValidatorsTest, DomainValidation)
    {
        validators.is_domain(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(DomainValid, ValidatorsTest, ::testing::Values(
        "example.com",
        "sub-domain.example.org"
    ));

    TEST_P(ValidatorsTest, ISO8601Validation)
    {
        validators.is_iso8601(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(ISO8601Valid, ValidatorsTest, ::testing::Values(
        "2025-12-12T09:00:00Z",
        "1999-01-01T23:59:59+02:00"
    ));

    TEST_P(ValidatorsTest, HexColorValidation)
    {
        validators.is_hex_color(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(HexColorValid, ValidatorsTest, ::testing::Values(
        "#FFF",
        "#1a2b3c"
    ));

    TEST_P(ValidatorsTest, RGBStringValidation)
    {
        validators.is_rgb_color(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(RGBValid, ValidatorsTest, ::testing::Values(
        "rgb(255,0,0)",
        "rgb(0,128,255)"
    ));

    TEST_P(ValidatorsTest, RGBAStringValidation)
    {
        validators.is_rgba_color(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(RGBAValid, ValidatorsTest, ::testing::Values(
        "rgba(255,0,0,0.5)",
        "rgba(0,128,255,1)"
    ));

    TEST_P(ValidatorsTest, FilePathValidation)
    {
        validators.is_file_path(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(FilePathValid, ValidatorsTest, ::testing::Values(
        "C:\\Users\\Test\\file.txt",
        "/home/user/file.txt"
    ));

    TEST_P(ValidatorsTest, FileNameValidation)
    {
        validators.is_file_name(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(FileNameValid, ValidatorsTest, ::testing::Values(
        "document.txt",
        "my_file-01.json"
    ));

    TEST_P(ValidatorsTest, FileExtensionValidation)
    {
        validators.is_file_extension(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(FileExtensionValid, ValidatorsTest, ::testing::Values(
        "txt",
        "json",
        "cpp"
    ));

    TEST_P(ValidatorsTest, MIMETypeValidation)
    {
        validators.is_mime_type(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(MIMEValid, ValidatorsTest, ::testing::Values(
        "application/json",
        "image/png",
        "text/html"
    ));

    TEST_P(ValidatorsTest, Base64ImageValidation)
    {
        validators.is_base64_image(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(Base64ImageValid, ValidatorsTest, ::testing::Values(
        "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAA",
        "data:image/jpeg;base64,/9j/4AAQSkZJRgABAQEAYABgAAD"
    ));

    TEST_P(ValidatorsTest, DataURIValidation)
    {
        validators.is_data_uri(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(DataURIValid, ValidatorsTest, ::testing::Values(
        "data:text/plain;base64,SGVsbG8gd29ybGQ=",
        "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAA"
    ));

    TEST_P(ValidatorsTest, PhoneNumberValidation)
    {
        validators.is_phone_number(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(PhoneNumberValid, ValidatorsTest, ::testing::Values(
        "+1 555-555-5555",
        "(555)555-5555"
    ));

    TEST_P(ValidatorsTest, E164PhoneNumberValidation)
    {
        validators.is_e164_phone_number(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(E164PhoneValid, ValidatorsTest, ::testing::Values(
        "+15555555555",
        "+442079460958"
    ));

    TEST_P(ValidatorsTest, CountryCallingCodeValidation)
    {
        validators.is_country_calling_code(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(CountryCallingCodeValid, ValidatorsTest, ::testing::Values(
        "+1",
        "+44"
    ));

    TEST_P(ValidatorsTest, FullNameValidation)
    {
        validators.is_full_name(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(FullNameValid, ValidatorsTest, ::testing::Values(
        "John Doe",
        "Anne-Marie O'Neil"
    ));

    TEST_P(ValidatorsTest, EmailValidation)
    {
        validators.is_email(result, GetParam());
        EXPECT_TRUE(result.get_value());
    }

    INSTANTIATE_TEST_CASE_P(EmailValid, ValidatorsTest, ::testing::Values(
        "user@example.com",
        "first.last+tag@gmail.com"
    ));
    */
}
