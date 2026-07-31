#pragma once

#if QLOGICAE_COR1__BASE__HPP_CPP__IS_COMPILATION_CONDITIONS_ENABLED_TEMPLATE( \
		StateManager \
	)

#include "state_manager_item.hpp"
#include "state_manager_configurations.hpp"

namespace
	QLOGICAE_COR1__BASE__HPP_CPP__COR_NAMESPACE_NAME
{
    class
		StateManager :
			public QLOGICAE_COR1__BASE__HPP_CPP__ABSTRACT_CLASS_NAME<StateManagerConfigurations>
    {
    public:		
		std::unordered_map<std::string, StateManagerItem>
			items;

		StateManager();

		bool
			add(
				const std::vector<StateManagerItem>&
					items
			);

		bool
			add(
				const StateManagerItem&
					item
			);

		std::unordered_map<std::string,std::any>
			get(
				const std::vector<std::string>&
					item_keys
			);

		std::any
			get(
				const std::string&
					item_key
			);

		bool
			signal(
				const std::unordered_map<std::string, std::vector<std::string>>&
					target_items
			);

		bool
			signal(
				const std::vector<std::string>&
					item_keys
			);

		bool
			signal(
				const std::string&
					item_key,
				const std::vector<std::string>&
					signal_keys
			);

		bool
			signal(
				const std::string&
					item_key
			);

		bool
			set(
				const std::unordered_map<std::string, std::any>&
					items
			);

		bool
			set(
				const std::string&
					item_key,
				const std::any&
					item_value
			);

		bool
			reset(
				const std::vector<std::string>&
					item_keys
			);

		bool
			reset(
				const std::string&
					item_key
			);

		bool
			remove(
				const std::vector<std::string>&
					item_keys
			);

		bool
			remove(
				const std::string&
					item_key
			);

		bool
			clear();
    };
}

#endif
