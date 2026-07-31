#include "pch.hpp"

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		NetworkPingManager \
	)

#include "../includes/network_ping_manager.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    TEST_F(NetworkPingManagerTest, Should_ReturnZero_When_RuntimeDisabled)
    {
        manager.configurations.is_feature_runtime_execution_handling_enabled = false;

        auto icmp_result = manager.get_icmp_ping("1.1.1.1");
        auto tcp_result = manager.get_tcp_ping("1.1.1.1");

        EXPECT_EQ(icmp_result.roundtrip_duration, 0);
        EXPECT_EQ(tcp_result.roundtrip_duration, 0);

        manager.configurations.is_feature_runtime_execution_handling_enabled = false;
    }

    TEST_F(NetworkPingManagerTest, Should_ReturnZero_When_HostEmptyAndEdgeCaseEnabled)
    {
        manager.configurations.is_feature_edge_case_handling_enabled = true;

        auto icmp_result = manager.get_icmp_ping("");
        auto tcp_result = manager.get_tcp_ping("");

        EXPECT_EQ(icmp_result.roundtrip_duration, 0);
        EXPECT_EQ(tcp_result.roundtrip_duration, 0);

        manager.configurations.is_feature_edge_case_handling_enabled = false;
    }

    TEST_F(NetworkPingManagerTest, Should_RespectTimeout_ForTcpPing)
    {
        manager.configurations.timeout = std::chrono::milliseconds { 1000 };
        auto start = std::chrono::steady_clock::now();
        auto tcp_result = manager.get_tcp_ping("1.1.1.1");
        auto end = std::chrono::steady_clock::now();
        auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        EXPECT_LE(duration_ms, 1000);
        EXPECT_GE(tcp_result.roundtrip_duration, 0);
        manager.configurations.timeout = std::chrono::milliseconds { 2000 };
    }

    TEST_F(NetworkPingManagerTest, Should_ScaleDurations_Correctly)
    {
        auto nanos = std::chrono::nanoseconds { 1000000 };
        double ms = manager.scale_duration(nanos, TimeScaleUnit::MILLISECONDS);
        double us = manager.scale_duration(nanos, TimeScaleUnit::MICROSECONDS);
        double ns = manager.scale_duration(nanos, TimeScaleUnit::NANOSECONDS);

        EXPECT_DOUBLE_EQ(ms, 1.0);
        EXPECT_DOUBLE_EQ(us, 1000.0);
        EXPECT_DOUBLE_EQ(ns, 1000000.0);
    }

    TEST_F(NetworkPingManagerTest, Should_HandleTcpPing_WithDefaultHost)
    {
        auto result = manager.get_tcp_ping();
        EXPECT_GE(result.roundtrip_duration, 0);
    }

    TEST_F(NetworkPingManagerTest, Should_HandleIcmpPing_WithDefaultHost)
    {
        auto result = manager.get_icmp_ping();
        EXPECT_GE(result.roundtrip_duration, 0);
    }

    INSTANTIATE_TEST_CASE_P(
        HostVariations,
        NetworkPingManagerParameterizedTest,
        ::testing::Values(
            NetworkPingManagerTestParam{ "8.8.8.8" },
            NetworkPingManagerTestParam{ "1.1.1.1" },
            NetworkPingManagerTestParam{ "127.0.0.1" }
        )
    );

    TEST_P(NetworkPingManagerParameterizedTest, Should_HandleMultipleHostsCorrectly)
    {
        auto param = GetParam();
        auto icmp_result = manager.get_icmp_ping(param.host_address);
        auto tcp_result = manager.get_tcp_ping(param.host_address);

        EXPECT_GE(icmp_result.roundtrip_duration, 0);
        EXPECT_GE(tcp_result.roundtrip_duration, 0);
    }

    TEST_F(NetworkPingManagerTest, Should_BeThreadSafe)
    {
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

        std::vector<std::thread> threads;
        std::atomic<int> completed { 0 };

        for (int i = 0; i < 4; i++)
        {
            threads.emplace_back([&]()
            {
                auto res = manager.get_tcp_ping("1.1.1.1");
                if (res.roundtrip_duration >= 0) completed++;
            });
        }

        for (auto& t : threads) t.join();
        EXPECT_EQ(completed.load(), 4);
    }

    TEST_F(NetworkPingManagerTest, Should_HandleStressTest)
    {
        for (int i = 0; i < 4; i++)
        {
            auto tcp_result = manager.get_tcp_ping("1.1.1.1");
            auto icmp_result = manager.get_icmp_ping("1.1.1.1");
            EXPECT_GE(tcp_result.roundtrip_duration, 0);
            EXPECT_GE(icmp_result.roundtrip_duration, 0);
        }
    }

	TEST_F(NetworkPingManagerAsyncTest, Should_HandleTcpPingAsync)
	{
		manager.configurations.is_feature_thread_safety_handling_enabled = true;

		auto future_ping = std::async(std::launch::async, [&]()
			{
				return manager.get_tcp_ping("1.1.1.1");
		});

		auto result = future_ping.get();
		EXPECT_GT(result.roundtrip_duration, 0);
	}

	INSTANTIATE_TEST_CASE_P(
		InvalidHosts,
		NetworkPingManagerInvalidHostTest,
		::testing::Values(
			NetworkPingManagerTestParam{ "nonexistent.example.com" },
			NetworkPingManagerTestParam{ "256.256.256.256" },
			NetworkPingManagerTestParam{ "" }
		)
	);

	TEST_P(NetworkPingManagerInvalidHostTest, Should_ReturnZeroOnInvalidHost_Icmp)
	{
		auto result = manager.get_icmp_ping(GetParam().host_address);
		EXPECT_EQ(result.roundtrip_duration, 0);
		EXPECT_EQ(result.sent_duration, 0);
		EXPECT_EQ(result.receive_duration, 0);
	}

	TEST_P(NetworkPingManagerInvalidHostTest, Should_ReturnZeroOnInvalidHost_Tcp)
	{
		auto result = manager.get_tcp_ping(GetParam().host_address);
		EXPECT_EQ(result.roundtrip_duration, 0);
		EXPECT_EQ(result.sent_duration, 0);
		EXPECT_EQ(result.receive_duration, 0);
	}

	TEST_F(NetworkPingManagerTimeoutTest, Should_HandleTcpPingTimeout)
	{
		manager.configurations.timeout = std::chrono::milliseconds {1};
		auto result = manager.get_tcp_ping("8.8.8.8");
		EXPECT_EQ(result.roundtrip_duration, 0);
		EXPECT_EQ(result.sent_duration, 0);
		EXPECT_EQ(result.receive_duration, 0);
	}

	TEST_F(NetworkPingManagerTimeScaleUnitTest, Should_ScaleDurations_AllUnits)
	{
		boost::asio::io_context io;
		auto start = std::chrono::steady_clock::now();
		auto end = start + std::chrono::milliseconds {1234};
		std::chrono::nanoseconds ns_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		manager.configurations.time_scale_unit = TimeScaleUnit::NANOSECONDS;
		EXPECT_DOUBLE_EQ(manager.scale_duration(ns_duration, manager.configurations.time_scale_unit), 1234000000);

		manager.configurations.time_scale_unit = TimeScaleUnit::MICROSECONDS;
		EXPECT_DOUBLE_EQ(manager.scale_duration(ns_duration, manager.configurations.time_scale_unit), 1234000);

		manager.configurations.time_scale_unit = TimeScaleUnit::MILLISECONDS;
		EXPECT_DOUBLE_EQ(manager.scale_duration(ns_duration, manager.configurations.time_scale_unit), 1234);

		manager.configurations.time_scale_unit = TimeScaleUnit::SECONDS;
		EXPECT_DOUBLE_EQ(manager.scale_duration(ns_duration, manager.configurations.time_scale_unit), 1.234);

		manager.configurations.time_scale_unit = TimeScaleUnit::MINUTES;
		EXPECT_DOUBLE_EQ(manager.scale_duration(ns_duration, manager.configurations.time_scale_unit), 0.020566666666666667);

		manager.configurations.time_scale_unit = TimeScaleUnit::HOURS;
		EXPECT_DOUBLE_EQ(manager.scale_duration(ns_duration, manager.configurations.time_scale_unit), 0.0003427777777777778);

		manager.configurations.time_scale_unit = TimeScaleUnit::DAYS;
		EXPECT_DOUBLE_EQ(manager.scale_duration(ns_duration, manager.configurations.time_scale_unit), 1.428240740740741e-05);
	}
}

#endif
