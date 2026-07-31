#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		NetworkPingManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
    struct NetworkPingManagerTestParam
    {
        std::string host_address;
    };

    class NetworkPingManagerTest: public ::testing::Test
    {
    public:
        NetworkPingManager manager;

        void SetUp() override
        {
            manager.construct();
        }

        void TearDown() override
        {
            manager.destruct();
        }
    };

    class NetworkPingManagerParameterizedTest: public NetworkPingManagerTest,
        public ::testing::WithParamInterface<NetworkPingManagerTestParam> {
    };

    struct NetworkPingManagerAsyncTest: public NetworkPingManagerTest {};

    struct NetworkPingManagerInvalidHostTest: public NetworkPingManagerTest,
        public ::testing::WithParamInterface<NetworkPingManagerTestParam> {
    };

    struct NetworkPingManagerTimeoutTest: public NetworkPingManagerTest {};

    struct NetworkPingManagerTimeScaleUnitTest: public NetworkPingManagerTest {};
}

#endif
