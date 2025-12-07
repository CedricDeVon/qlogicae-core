#include "pch.hpp"

#include "../includes/entity_activation_manager.hpp"

namespace QLogicaeCppCore
{
    EntityActivationManager::EntityActivationManager()
    {

    }

    EntityActivationManager::~EntityActivationManager()
    {

    }

    void EntityActivationManager::get_entity_collection_copy(
        Result<std::unordered_map<std::string_view, EntityActivationStatus>>& result
    )
    {
        std::unordered_map<std::string_view, EntityActivationStatus> copy_data;

        for (const auto& [name, value] : _data)
        {
            copy_data[name] = value;
        }

        result.set_to_good_status_with_value(
            copy_data
        );
    }

    void EntityActivationManager::get_entity_status(
        Result<EntityActivationStatus>& result,
        std::string_view& name
    )
    {
        result.set_to_good_status_with_value(
            _data[name.data()]
        );
    }

    void EntityActivationManager::set_entity_status(
        Result<bool>& result,
        std::string_view& name,
        EntityActivationStatus& status
    )
    {
        _data[name.data()] = status;

        result.set_to_good_status_with_value(
            true
        );
    }

    void EntityActivationManager::set_entity_status_to_active(
        Result<bool>& result,
        std::string_view& name
    )
    {
        _data[name.data()] = EntityActivationStatus::ACTIVE;

        result.set_to_good_status_with_value(
            true
        );
    }

    void EntityActivationManager::set_entity_status_to_inactive(
        Result<bool>& result,
        std::string_view& name
    )
    {
        _data[name.data()] = EntityActivationStatus::INACTIVE;

        result.set_to_good_status_with_value(
            true
        );
    }

    void EntityActivationManager::set_entity_status_to_pending(
        Result<bool>& result,
        std::string_view& name
    )
    {
        _data[name.data()] = EntityActivationStatus::PENDING;

        result.set_to_good_status_with_value(
            true
        );
    }

    void EntityActivationManager::is_entity_name_found(
        Result<bool>& result,
        std::string_view& name
    )
    {
        result.set_to_good_status_with_value(
            _data.contains(name.data())
        );
    }

    void EntityActivationManager::is_entity_status_active(
        Result<bool>& result,
        std::string_view& name
    )
    {
        result.set_to_good_status_with_value(
            _data[name.data()] == EntityActivationStatus::ACTIVE
        );
    }

    void EntityActivationManager::is_entity_status_inactive(
        Result<bool>& result,
        std::string_view& name
    )
    {
        result.set_to_good_status_with_value(
            _data[name.data()] == EntityActivationStatus::INACTIVE
        );
    }

    void EntityActivationManager::is_entity_status_pending(
        Result<bool>& result,
        std::string_view& name
    )
    {
        result.set_to_good_status_with_value(
            _data[name.data()] == EntityActivationStatus::PENDING
        );
    }

    void EntityActivationManager::remove_entity(
        Result<bool>& result,
        std::string_view& name
    )
    {
        result.set_to_good_status_with_value(
            _data.erase(name)
        );
    }
    
    void EntityActivationManager::remove_all_entities(
        Result<bool>& result
    )
    {
        _data.clear();

        result.set_to_good_status_with_value(
            true
        );
    }
}
