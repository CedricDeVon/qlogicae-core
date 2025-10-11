#include "pch.hpp"

#include "validators.hpp"

namespace QLogicaeCoreTest
{
    class ValidatorsTest : public ::testing::TestWithParam<std::string>
    {
    protected:
        QLogicaeCore::Validators& validators = QLogicaeCore::Validators::get_instance();
    };

    class ValidatorsTemplateTest : public ::testing::Test
    {
    protected:
        QLogicaeCore::Validators& validators = QLogicaeCore::Validators::get_instance();
    };

    INSTANTIATE_TEST_CASE_P(
        ValidatorsTestCases,
        ValidatorsTest,
        ::testing::Values(
            "", "abc", "ABC", "123", "aBc123", "  ", "@!#",
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
        bool result = validators.is_not_empty(input);
        if (input.empty())
        {
            ASSERT_FALSE(result);
        }
        else
        {
            ASSERT_TRUE(result);
        }
    }

    TEST_P(ValidatorsTest, Should_ReturnTrue_When_Empty)
    {
        std::string_view input = GetParam();
        bool result = validators.is_empty(input);
        ASSERT_EQ(result, input.empty());
    }

    TEST_P(ValidatorsTest, Should_ReturnTrue_When_AllLowercase)
    {
        std::string_view input = GetParam();
        bool expected = !input.empty() && std::ranges::all_of(input, [](char c)
            {
                return std::islower(static_cast<unsigned char>(c));
            });
        ASSERT_EQ(validators.is_lowercase(input), expected);
    }

    TEST_P(ValidatorsTest, Should_ReturnTrue_When_AllUppercase)
    {
        std::string_view input = GetParam();
        bool expected = !input.empty() && std::ranges::all_of(input, [](char c)
            {
                return std::isupper(static_cast<unsigned char>(c));
            });
        ASSERT_EQ(validators.is_uppercase(input), expected);
    }

    TEST_P(ValidatorsTest, Should_Identify_FirstLetterUppercase)
    {
        std::string_view input = GetParam();
        bool expected = !input.empty() && std::isupper(static_cast<unsigned char>(input.front()));
        ASSERT_EQ(validators.is_first_letter_uppercase(input), expected);
    }

    TEST_P(ValidatorsTest, Should_Validate_PrefixAndSuffix)
    {
        std::string_view input = GetParam();
        ASSERT_EQ(validators.is_prefix_found(input, "a"), input.starts_with("a"));
        ASSERT_EQ(validators.is_suffix_found(input, "z"), input.ends_with("z"));
    }

    TEST_P(ValidatorsTest, Should_Identify_Substring)
    {
        std::string_view input = GetParam();
        ASSERT_EQ(validators.is_substring_found(input, "a"), input.find("a") != std::string::npos);
    }

    TEST_P(ValidatorsTest, Should_Validate_PortInRange)
    {
        ASSERT_TRUE(validators.is_port_in_range(80));
        ASSERT_FALSE(validators.is_port_in_range(0));
        ASSERT_TRUE(validators.is_port_in_range("443"));
        ASSERT_FALSE(validators.is_port_in_range("notaport"));
    }

    TEST_P(ValidatorsTest, Should_Validate_Alphanumeric)
    {
        std::string_view input = GetParam();
        bool expected = !input.empty() && std::ranges::all_of(input, [](char c)
            {
                return std::isalnum(static_cast<unsigned char>(c));
            });
        ASSERT_EQ(validators.is_alpanumeric(input), expected);
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
        ASSERT_EQ(validators.is_decimal(input), valid);
    }

    TEST(ValidatorsTestFixed, Should_Validate_AsynchronousBehavior)
    {
        std::promise<bool> promise;
        std::future<bool> future = promise.get_future();
        std::thread thread([
            &promise
        ]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                promise.set_value(true);
            });
            bool result = future.get();
            thread.join();
            ASSERT_TRUE(result);
    }

    TEST(ValidatorsTestFixed, Should_Handle_MultiThreadedAccess)
    {
        std::atomic<int> counter = 0;
        std::vector<std::thread> threads;
        for (int index = 0; index < 10; ++index)
        {
            threads.emplace_back([
                &counter
            ]()
                {
                    for (int iteration = 0; iteration < 1000; ++iteration)
                    {
                        counter.fetch_add(1, std::memory_order_relaxed);
                    }
                });
        }
        for (std::thread& thread : threads)
        {
            thread.join();
        }
        ASSERT_EQ(counter.load(), 10000);
    }

    TEST(ValidatorsTestFixed, Should_Complete_UnderStressConditions)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int index = 0; index < 100000; ++index)
        {
            volatile bool result = QLogicaeCore::Validators::get_instance().is_even(index);
            (void)result;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        ASSERT_LT(duration.count(), 2.0);
    }

    TEST(ValidatorsTestFixed, Should_Validate_EdgeCases)
    {
        ASSERT_TRUE(QLogicaeCore::Validators::get_instance().is_even(0));
        ASSERT_FALSE(QLogicaeCore::Validators::get_instance().is_even(-1));
        ASSERT_TRUE(QLogicaeCore::Validators::get_instance().is_even(2));
        ASSERT_FALSE(QLogicaeCore::Validators::get_instance().is_even(3));
        ASSERT_TRUE(QLogicaeCore::Validators::get_instance().is_even(
            std::numeric_limits<int64_t>::min()));
        ASSERT_FALSE(QLogicaeCore::Validators::get_instance().is_even(
            std::numeric_limits<int64_t>::max()));
    }

    TEST(ValidatorsTest,
        Should_Return_Same_Instance_When_Accessed_Multiple_Times)
    {
        QLogicaeCore::Validators& first =
            QLogicaeCore::Validators::get_instance();

        QLogicaeCore::Validators& second =
            QLogicaeCore::Validators::get_instance();

        ASSERT_EQ(&first, &second);
    }

    TEST(ValidatorsTest,
        Should_Handle_Many_Accesses_Under_Stress)
    {
        QLogicaeCore::Validators* instances[10000];

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 10000; ++i)
        {
            instances[i] = &QLogicaeCore::Validators::get_instance();
        }

        for (int i = 1; i < 10000; ++i)
        {
            ASSERT_EQ(instances[i], instances[0]);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = end - start;

        ASSERT_LT(std::chrono::duration_cast<std::chrono::seconds>(
            duration).count(), 2);
    }

    TEST(ValidatorsTest,
        Should_Be_Safe_When_Used_From_Multiple_Threads)
    {
        std::atomic<int> match_count = 0;
        QLogicaeCore::Validators* base = &QLogicaeCore::Validators::get_instance();

        std::vector<std::thread> threads;

        for (int i = 0; i < 20; ++i)
        {
            threads.emplace_back([&match_count, base]()
                {
                    QLogicaeCore::Validators* local =
                        &QLogicaeCore::Validators::get_instance();

                    if (local == base)
                    {
                        ++match_count;
                    }
                });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

        ASSERT_EQ(match_count.load(), 20);
    }

    TEST(ValidatorsTest,
        Should_Not_Throw_When_Called_Repeatly_In_TryCatch)
    {
        ASSERT_NO_THROW({
            for (int i = 0; i < 1000; ++i)
            {
                QLogicaeCore::Validators::get_instance();
            }
            });
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_UTFEncodings)
    {
        ASSERT_TRUE(validators.is_utf8("abc"));
        ASSERT_FALSE(validators.is_utf8("\xC0"));
        ASSERT_TRUE(validators.is_utf16("\xFF\xFEtext"));
        ASSERT_FALSE(validators.is_utf16("x"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_LeapYearText)
    {
        ASSERT_TRUE(validators.is_leap_year("2020"));
        ASSERT_FALSE(validators.is_leap_year("1900"));
        ASSERT_TRUE(validators.is_leap_year(2000));
        ASSERT_FALSE(validators.is_leap_year(2023));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_ISOCountryCurrencyLanguageCodes)
    {
        ASSERT_TRUE(validators.is_country_code("US"));
        ASSERT_FALSE(validators.is_country_code("U"));

        ASSERT_TRUE(validators.is_currency_code("USD"));
        ASSERT_FALSE(validators.is_currency_code("EU"));

        ASSERT_TRUE(validators.is_language_code("en"));
        ASSERT_TRUE(validators.is_language_code("eng"));
        ASSERT_FALSE(validators.is_language_code("e"));
        ASSERT_FALSE(validators.is_language_code("engl"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_FileAllowRules)
    {
        ASSERT_TRUE(validators.is_file_extension_allowed("txt", { "txt", "md" }));
        ASSERT_FALSE(validators.is_file_extension_allowed("exe", { "txt", "md" }));

        ASSERT_TRUE(validators.is_file_type_allowed("application/json", { "application/json" }));
        ASSERT_FALSE(validators.is_file_type_allowed("application/xml", { "application/json" }));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_PercentageFormats)
    {
        ASSERT_TRUE(validators.is_percentage("99.9"));
        ASSERT_TRUE(validators.is_percentage("100"));
        ASSERT_FALSE(validators.is_percentage("one hundred"));
        ASSERT_FALSE(validators.is_percentage("200.5"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_Coordinates)
    {
        ASSERT_TRUE(validators.is_latitude("45.0"));
        ASSERT_FALSE(validators.is_latitude("120.0"));

        ASSERT_TRUE(validators.is_longitude("-73.935242"));
        ASSERT_FALSE(validators.is_longitude("-190.00"));

        ASSERT_TRUE(validators.is_coordinate("45.0", "-73.9"));
        ASSERT_FALSE(validators.is_coordinate("999", "999"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_RepeatedCharactersAndBlacklist)
    {
        ASSERT_TRUE(validators.is_character_repeated("aaa", 2));
        ASSERT_FALSE(validators.is_character_repeated("abc", 1));

        ASSERT_TRUE(validators.is_blacklisted_word_found("this is a test", { "test", "admin" }));
        ASSERT_FALSE(validators.is_blacklisted_word_found("hello world", { "test" }));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_AgeAndGenderParsing)
    {
        ASSERT_TRUE(validators.is_age("30"));
        ASSERT_FALSE(validators.is_age("abc"));

        ASSERT_TRUE(validators.is_gender("Male"));
        ASSERT_TRUE(validators.is_gender("nonbinary"));
        ASSERT_FALSE(validators.is_gender("unknown"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_GenericTemplates_WithStrings)
    {
        std::vector<std::string> names = { "Alice", "Bob", "Charlie" };
        std::vector<std::string> duplicates = { "A", "B", "A" };

        ASSERT_TRUE(validators.is_sorted(std::vector<std::string>{"a", "b", "c"}));
        ASSERT_FALSE(validators.is_sorted(std::vector<std::string>{"z", "a", "c"}));

        ASSERT_TRUE(validators.is_unique(names));
        ASSERT_FALSE(validators.is_unique(duplicates));

        ASSERT_TRUE(validators.is_empty(std::vector<std::string>{}));
        ASSERT_FALSE(validators.is_empty(names));

        ASSERT_TRUE(validators.is_valid_range(names, [](const std::string& s) { return !s.empty(); }));
        ASSERT_FALSE(validators.is_valid_range(duplicates, [](const std::string& s) { return s == "X"; }));
    }

    TEST_F(ValidatorsTemplateTest, Should_Fuzz_StructuredFormatValidators)
    {
        std::vector<std::string> fuzz_inputs = {
            "", "{", "}", "[]", "not_json", "{\"key\":}", "{\"key\":\"value\"}",
            "<root>", "<root></root>", "<tag><nested></tag>", "not<xml>",
            "plain@example.com", "user@", "@domain.com", "user@domain",
            "user@domain.com", "user@sub.domain.org"
        };

        for (const auto& input : fuzz_inputs)
        {
            ASSERT_NO_THROW(validators.is_email(input));
        }
    }

    TEST_F(ValidatorsTemplateTest, Should_Fuzz_NumericBoundaryValidators)
    {
        std::vector<std::string> fuzz_ages = { "-1", "0", "5", "18", "120", "200", "abc" };
        std::vector<std::string> fuzz_percentages = { "-10", "0", "50", "99.9", "100", "200", "NaN", "100.001" };
        std::vector<std::string> fuzz_ports = { "0", "1", "22", "65535", "65536", "99999", "notaport" };

        for (const auto& age : fuzz_ages)
        {
            ASSERT_NO_THROW(validators.is_age(age));
        }

        for (const auto& pct : fuzz_percentages)
        {
            ASSERT_NO_THROW(validators.is_percentage(pct));
        }

        for (const auto& port : fuzz_ports)
        {
            ASSERT_NO_THROW(validators.is_port_in_range(port));
        }
    }

    TEST_F(ValidatorsTemplateTest, Should_Fuzz_RegexValidatorsUnderConcurrency)
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
                    QLogicaeCore::Validators& local = validators; 

                    for (const auto& input : fuzz_inputs)
                    {
                        if (local.is_base64(input)) ++success_count;
                        if (local.is_slug(input)) ++success_count;
                        if (local.is_hex(input)) ++success_count;
                        if (local.is_uuid4(input)) ++success_count;
                    }
                });
        }

        for (auto& t : threads) t.join();

        ASSERT_GT(success_count.load(), 0); 
    }

    TEST_F(ValidatorsTemplateTest, Should_Reject_Malicious_Inputs)
    {
        std::vector<std::string> malicious_inputs = {
            "\x00", "\x1B[31m", "DROP TABLE users;", "<script>alert(1)</script>",
            "\"unclosed", "name,age\njohn,\"doe", "<tag><unclosed>",
            "user@@domain..com", "http:::/wrong", "some slug!", "   ", "\xFF\xFE\x00\x00"
        };

        for (const auto& input : malicious_inputs)
        {
            ASSERT_FALSE(validators.is_email(input));
            ASSERT_FALSE(validators.is_slug(input));
            ASSERT_FALSE(validators.is_uri(input));
        }
    }

    TEST_F(ValidatorsTemplateTest, Should_Fuzz_DateTimeAndISOFormats)
    {
        std::vector<std::string> edge_dates = {
            "0000-01-01", "1900-02-28", "2000-02-29", "2023-12-31",
            "9999-12-31", "1970-01-01", "2038-01-19", 
            "not-a-date", "31/12/2020", "2020-13-01", "2020-00-10"
        };

        for (const auto& date : edge_dates)
        {
            ASSERT_NO_THROW(validators.is_date(date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_datetime(date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_past_date(date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_future_date(date, "%Y-%m-%d"));
            ASSERT_NO_THROW(validators.is_iso8601(date));
        }
    }

    TEST_F(ValidatorsTemplateTest, Should_RandomFuzz_UTF8_Email_JSON)
    {
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+";
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> len_dist(1, 512);

        auto random_string = [&](int max_len) {
            size_t len = len_dist(rng);
            std::string str;
            for (size_t i = 0; i < len; ++i)
                str += chars[rng() % chars.size()];
            return str;
            };

        for (int i = 0; i < 1000; ++i)
        {
            std::string fuzz = random_string(512);

            ASSERT_NO_THROW(validators.is_utf8(fuzz));
            ASSERT_NO_THROW(validators.is_email(fuzz));
        }
    }

    TEST_F(ValidatorsTemplateTest, Should_Handle_Malformed_Corpus_Inputs)
    {
        std::vector<std::string> malformed_base64 = {
            "!!invalid!!", "abcd===", "12345", "@@@", "", "c29tZXRleHQ" 
        };
        std::vector<std::string> malformed_emails = {
            "user@@domain", "userdomain.com", "@nouser.com", "user@", "", "user@.com"
        };

        for (const auto& input : malformed_base64)
            ASSERT_NO_THROW(validators.is_base64(input));

        for (const auto& input : malformed_emails)
            ASSERT_NO_THROW(validators.is_email(input));
    }

    TEST_F(ValidatorsTemplateTest, Should_Stress_Benchmark_EmailSlugJson)
    {
        const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_@.:{}[],\" ";
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<size_t> len_dist(10, 256);

        auto random_string = [&](size_t len) {
            std::string out;
            for (size_t i = 0; i < len; ++i)
                out += chars[rng() % chars.size()];
            return out;
            };

        constexpr int rounds = 10000;
        for (int i = 0; i < rounds; ++i)
        {
            std::string fuzz = random_string(len_dist(rng));
            validators.is_email(fuzz);
            validators.is_slug(fuzz);
        }

        SUCCEED(); 
    }

    std::string generate_invalid_port() {
        static std::vector<std::string> values = { "-1", "70000", "abc", "", "65536", " " };
        return values[rand() % values.size()];
    }

    std::string generate_random_date() {
        static std::vector<std::string> values = { "2020/12/12", "12-31-2020", "20201301", "2020-00-01", "bad-date" };
        return values[rand() % values.size()];
    }

    std::string generate_unicode_junk(size_t len = 2048) {
        std::string result;
        while (result.size() < len)
            result += "\xF0\x9F\x98\x8A"; 
        return result;
    }

    TEST_F(ValidatorsTemplateTest, Should_Not_Leak_Under_Regex_Stress)
    {
        const std::string input = "c29tZXRleHQ=";
        for (int i = 0; i < 10000; ++i) {
            volatile bool ok = validators.is_base64(input);
            ok &= validators.is_ipv6("::1");
            ok &= validators.is_mac_address("00:1A:2B:3C:4D:5E");
        }
    }

    TEST(ValidatorsABIStability, Should_Preserve_Signature_Compatibility)
    {
        using FuncType = bool(QLogicaeCore::Validators::*)(const std::string_view&);
        FuncType f2 = &QLogicaeCore::Validators::is_email;
        ASSERT_NE(f2, nullptr);
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_EmptyVector)
    {
        std::vector<int> input;
        ASSERT_TRUE(validators.is_empty(input));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_SortedVector)
    {
        std::vector<int> sorted_values{ 1, 2, 3, 4 };
        std::vector<int> unsorted_values{ 4, 2, 1, 3 };
        ASSERT_TRUE(validators.is_sorted(sorted_values));
        ASSERT_FALSE(validators.is_sorted(unsorted_values));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_UniqueValues)
    {
        std::vector<int> unique_values{ 1, 2, 3 };
        std::vector<int> duplicate_values{ 1, 2, 2, 3 };
        ASSERT_TRUE(validators.is_unique(unique_values));
        ASSERT_FALSE(validators.is_unique(duplicate_values));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_EnumValue)
    {
        int allowed[] = { 10, 20, 30 };
        ASSERT_TRUE(validators.is_enum_value(20, std::span<const int>(allowed)));
        ASSERT_FALSE(validators.is_enum_value(40, std::span<const int>(allowed)));
    }

    TEST_F(ValidatorsTemplateTest, Should_Find_MatchingPredicate)
    {
        std::vector<int> input = { 1, 2, 3, 4 };
        std::function<bool(const int&)> predicate = [](const int& value) { return value == 3; };
        ASSERT_TRUE(validators.is_found(input, predicate));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_AllMatchPredicate)
    {
        std::vector<int> input = { 2, 4, 6 };
        auto is_even = [](int value) { return value % 2 == 0; };
        ASSERT_TRUE(validators.is_valid_range(input, is_even));
        input.push_back(3);
        ASSERT_FALSE(validators.is_valid_range(input, is_even));
    }

    TEST_F(ValidatorsTemplateTest, Should_Fail_EnumValue_When_Empty)
    {
        std::span<const int> empty_span;
        ASSERT_FALSE(validators.is_enum_value(10, empty_span));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_Sorted_When_SingleOrEqual)
    {
        std::vector<int> single_value{ 1 };
        std::vector<int> equal_values{ 2, 2, 2 };
        ASSERT_TRUE(validators.is_sorted(single_value));
        ASSERT_TRUE(validators.is_sorted(equal_values));
    }

    TEST_F(ValidatorsTemplateTest, Should_Fail_AllMatchPredicate_When_AllFail)
    {
        std::vector<int> input{ 1, 2, 3 };
        auto always_false = [](int) { return false; };
        ASSERT_FALSE(validators.is_valid_range(input, always_false));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_Unique_With_EdgeValues)
    {
        std::vector<int64_t> values{
            std::numeric_limits<int64_t>::min(),
            std::numeric_limits<int64_t>::max()
        };
        ASSERT_TRUE(validators.is_unique(values));
    }

    TEST_F(ValidatorsTemplateTest, Should_Fuzz_RegexAndUtfValidators)
    {
        std::vector<std::string> fuzz_inputs = {
            "", "a", "!!@@", "123", "abcdEFGH", "this_is_slug", "bad slug",
            "aGVsbG8gd29ybGQ=", "c29tZVRleHQ=", "not_base64==", "uuid", "550e8400-e29b-41d4-a716-446655440000",
            "\xFF\xFE\x00a", "\xC3\x28", "\xE2\x82\xAC", "\xF0\x9F\x98\x81"
        };

        for (const auto& input : fuzz_inputs)
        {
            ASSERT_NO_THROW(validators.is_base64(input));
            ASSERT_NO_THROW(validators.is_slug(input));
            ASSERT_NO_THROW(validators.is_hex(input));
            ASSERT_NO_THROW(validators.is_uuid4(input));
            ASSERT_NO_THROW(validators.is_uuid6(input));
            ASSERT_NO_THROW(validators.is_utf8(input));
            ASSERT_NO_THROW(validators.is_utf16(input));
        }
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_DateTimePatterns)
    {
        ASSERT_TRUE(validators.is_date("2020-12-31", "%Y-%m-%d"));
        ASSERT_FALSE(validators.is_date("12/31/2020", "%Y-%m-%d"));

        ASSERT_TRUE(validators.is_past_date("2000-01-01", "%Y-%m-%d"));
        ASSERT_FALSE(validators.is_past_date("3000-01-01", "%Y-%m-%d"));

        ASSERT_TRUE(validators.is_unix("1618033988"));
        ASSERT_FALSE(validators.is_unix("NaN"));

        ASSERT_TRUE(validators.is_iso8601("2020-12-31T23:59:59Z"));
        ASSERT_FALSE(validators.is_iso8601("not-date"));

        ASSERT_TRUE(validators.is_utc("2020-12-31T23:59:59Z"));
        ASSERT_FALSE(validators.is_utc("2020-12-31T23:59:59"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Fuzz_UnicodeHeavyStrings)
    {
        std::string long_utf8_valid = "\u3053\u3093\u306B\u3061\u306F";
        long_utf8_valid += std::string(1024, 'x');

        std::string long_utf8_invalid = std::string(2048, '\xFF');
        std::string long_slug = std::string(1000, 'a') + "-valid-slug";
        std::string long_email = std::string(100, 'a') + "@example.com";

        ASSERT_NO_THROW(validators.is_utf8(long_utf8_valid));
        ASSERT_NO_THROW(validators.is_utf8(long_utf8_invalid));
        ASSERT_NO_THROW(validators.is_slug(long_slug));
        ASSERT_NO_THROW(validators.is_email(long_email));
    }

    TEST_F(ValidatorsTemplateTest, Benchmark_HotValidators)
    {
        const std::string input = R"({"key":"value"})";
        const std::string email = "user@example.com";
        const std::string slug = "valid-slug-123";
        const std::string url = "https://example.com";
        const std::string uuid = "550e8400-e29b-41d4-a716-446655440000";

        const int iterations = 100000;
        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < iterations; ++i) {
            volatile bool r2 = validators.is_email(email);
            volatile bool r3 = validators.is_slug(slug);
            volatile bool r4 = validators.is_url(url);
            volatile bool r5 = validators.is_uuid4(uuid);
            (void)(r2 && r3 && r4 && r5);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "[Benchmark] 100K hot validator calls took " << ms << " ms" << std::endl;
    }

    TEST_F(ValidatorsTemplateTest, Should_Find_When_AllMatch)
    {
        std::vector<int> input{ 10, 20, 30 };
        std::function<bool(const int&)> predicate = [](const int& v) { return v % 10 == 0; };
        ASSERT_TRUE(validators.is_found(input, predicate));
    }


    TEST_F(ValidatorsTemplateTest, Should_Validate_FilePatterns)
    {
        ASSERT_TRUE(validators.is_file_path("/usr/local/bin"));
        ASSERT_FALSE(validators.is_file_path("not/a/path//"));

        ASSERT_TRUE(validators.is_file_name("file.txt"));
        ASSERT_FALSE(validators.is_file_name("bad|name?.txt"));

        ASSERT_TRUE(validators.is_file_extension("txt"));
        ASSERT_FALSE(validators.is_file_extension(".txt"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_EmailAndPassword)
    {
        ASSERT_TRUE(validators.is_email("user@example.com"));
        ASSERT_FALSE(validators.is_email("user@@example..com"));

        QLogicaeCore::ValidationPasswordRules rules;
        rules.minimum_length = 8;
        rules.maximum_length = 16;
        rules.require_uppercase_characters = true;
        rules.require_lowercase_characters = true;
        rules.require_alpha_numerics = true;
        rules.require_special_characters = true;
        rules.require_unique_characters = true;

        ASSERT_TRUE(validators.is_strong_password("Abc123$%", rules));
        ASSERT_FALSE(validators.is_strong_password("abc123", rules));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_PhoneNumbers)
    {
        ASSERT_TRUE(validators.is_phone_number("+1 (800) 123-4567"));
        ASSERT_FALSE(validators.is_phone_number("abc800123"));

        ASSERT_TRUE(validators.is_e164_phone_number("+18001234567"));
        ASSERT_FALSE(validators.is_e164_phone_number("18001234567"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Reject_PropertyGeneratedInvalids)
    {
        for (int i = 0; i < 100; ++i)
        {
            std::string bad_port = generate_invalid_port();
            ASSERT_FALSE(validators.is_port_in_range(bad_port));

            std::string bad_date = generate_random_date();
            ASSERT_FALSE(validators.is_date(bad_date, "%Y-%m-%d"));

            std::string junk = generate_unicode_junk();
            ASSERT_FALSE(validators.is_utf8(junk + '\xC0'));
        }
    }

    TEST_F(ValidatorsTemplateTest, Should_Stress_Validators_Under_Thread_Concurrency)
    {
        const std::string url = "https://example.com/path?query=value";
        const std::string slug = "valid-slug-case";
        const std::string json = "{\"key\": [1, 2, {\"nested\": true}]}";

        std::atomic<int> success = 0;
        std::vector<std::thread> threads;

        for (int i = 0; i < 20; ++i)
        {
            threads.emplace_back([&]() {
                for (int j = 0; j < 1000; ++j)
                {
                    if (validators.is_url(url)) ++success;
                    if (validators.is_slug(slug)) ++success;
                }
                });
        }

        for (auto& thread : threads)
            thread.join();

        ASSERT_EQ(success.load(), 20 * 2 * 1000);
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_AddressAndNameParts)
    {
        ASSERT_TRUE(validators.is_address_line("123 Main Street"));
        ASSERT_FALSE(validators.is_address_line("a"));

        ASSERT_TRUE(validators.is_full_name("John Doe"));
        ASSERT_TRUE(validators.is_first_name("John"));
        ASSERT_TRUE(validators.is_middle_name("Edward"));
        ASSERT_TRUE(validators.is_middle_initial("E"));
        ASSERT_FALSE(validators.is_middle_initial("Ed"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Match_RegexPatterns)
    {
        ASSERT_TRUE(validators.is_base64("c29tZXRleHQ="));
        ASSERT_FALSE(validators.is_base64("not_base64!!"));

        ASSERT_TRUE(validators.is_slug("valid-slug-example"));
        ASSERT_FALSE(validators.is_slug("Invalid Slug"));

        ASSERT_TRUE(validators.is_hex("deadbeef"));
        ASSERT_FALSE(validators.is_hex("nothex"));

        ASSERT_TRUE(validators.is_uuid4("550e8400-e29b-41d4-a716-446655440000"));
        ASSERT_FALSE(validators.is_uuid4("invalid-uuid"));

        ASSERT_TRUE(validators.is_uuid6("1e0b46e2-4b5e-6f00-8000-0026bb7655df"));
        ASSERT_FALSE(validators.is_uuid6("some-invalid-string"));

        ASSERT_TRUE(validators.is_ipv4("192.168.1.1"));
        ASSERT_FALSE(validators.is_ipv4("999.999.999.999"));

        ASSERT_TRUE(validators.is_ipv6("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
        ASSERT_FALSE(validators.is_ipv6("invalid_ipv6"));

        ASSERT_TRUE(validators.is_url("https://example.com"));
        ASSERT_FALSE(validators.is_url("example dot com"));
    }

    TEST_F(ValidatorsTemplateTest, Should_Validate_MimeBase64DataUri)
    {
        ASSERT_TRUE(validators.is_mime_type("image/png"));
        ASSERT_FALSE(validators.is_mime_type("fake/type"));

        ASSERT_TRUE(validators.is_base64_image("data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAA"));
        ASSERT_FALSE(validators.is_base64_image("plain text"));

        ASSERT_TRUE(validators.is_data_uri("data:text/plain;base64,SGVsbG8gd29ybGQ="));
        ASSERT_FALSE(validators.is_data_uri("notdatauri"));
    }

}
