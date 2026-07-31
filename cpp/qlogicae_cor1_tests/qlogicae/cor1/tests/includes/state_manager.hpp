#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		StateManager \
	)

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_TESTS_NAMESPACE_NAME
{
	class
        StateManagerTest :
            public ::testing::Test
    {
    public:
        StateManager
            state_manager;

        StateManagerItem
            create_item(
                const std::string&
                    key,
                const std::any&
                    initial_value
            )
        {
            StateManagerItem
                item;

            item.key =
                key;

            item.initial_value =
                initial_value;

            item.current_value =
                initial_value;

            return
                item;
        }
    };
	
    class
        StateManagerParameterizedTest :
            public ::testing::TestWithParam<int>
    {
    public:
        StateManager
            state_manager;
    };
}

#endif
