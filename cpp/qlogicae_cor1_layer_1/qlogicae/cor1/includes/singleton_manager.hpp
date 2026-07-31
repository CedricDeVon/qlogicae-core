#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		SingletonManager \
	)

#include "singleton_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		SingletonManager
    {
    public:     
		static SingletonManagerConfigurations
			configurations;

		QLOGICAE_COR1__STATIC__HPP__MUTEX_LAYER_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1
		);

		SingletonManager();

		~SingletonManager();

		static bool
			construct();

		static bool
			destruct();

		static bool
			setup(
				const SingletonManagerConfigurations&
					new_configurations
			);

		static bool
			reset();

		template <typename Type> static Type&
			get_singleton();
	
		template <typename Type, std::size_t InstanceCount> static Type&
			get_singleton();

		static SingletonManager&
			get_this_singleton();		
    };

    template <typename Type> Type&
        SingletonManager
			::get_singleton()
    {			
		QLOGICAE_COR1__BASE__HPP_CPP__THREAD_SAFETY_GUARD_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1
		);
			
        static Type
            singleton;		  

        return
            singleton;
    }    

	template <typename Type, std::size_t InstanceCount> static Type&
		SingletonManager
			::get_singleton()
	{
		static_assert(InstanceCount > 0);

		QLOGICAE_COR1__BASE__HPP_CPP__THREAD_SAFETY_GUARD_TEMPLATE
		(
			QLOGICAE_COR1__BASE__HPP_CPP__MUTEX_LAYER_1
		);

		static std::array<Type, InstanceCount>
			instances{};

		return
			instances
			[
				std::hash<std::thread::id>{}(
					std::this_thread::get_id()
				) % InstanceCount
			];
	}
}

#endif
