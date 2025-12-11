#include "pch.hpp"

#include "../includes/entity_activation_manager.hpp"

namespace QLogicaeCppCore
{
    EntityActivationManager::EntityActivationManager()
    {
        Result<bool> result;

        construct(result);
    }

    EntityActivationManager::~EntityActivationManager()
    {
        Result<bool> result;

        destruct(result);
    }

    void EntityActivationManager::construct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void EntityActivationManager::destruct(
        Result<bool>& result
    )
    {
        result.set_to_good_status_with_value(
            true
        );
    }

    void EntityActivationManager::get_entity_collection_copy(
        Result<std::unordered_map<std::string, EntityActivationStatus>>& result
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        result.set_to_good_status_with_value(_data);
    }

    void EntityActivationManager::get_entity_status(
        Result<EntityActivationStatus>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        const std::string key(name);
        auto it = _data.find(key);

        if (it == _data.end())
        {
            result.set_to_bad_status_with_value(
                EntityActivationStatus::NONE
            );

            return;
        }

        result.set_to_good_status_with_value(
            it->second
        );
    }

    void EntityActivationManager::set_entity_status(
        Result<bool>& result,
        const std::string_view& name,
        EntityActivationStatus& status
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _data[std::string(name)] = status;

        result.set_to_good_status_with_value(true);
    }

    void EntityActivationManager::set_entity_status_to_active(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _data[std::string(name)] = EntityActivationStatus::ACTIVE;

        result.set_to_good_status_with_value(true);
    }

    void EntityActivationManager::set_entity_status_to_inactive(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _data[std::string(name)] = EntityActivationStatus::INACTIVE;

        result.set_to_good_status_with_value(true);
    }

    void EntityActivationManager::set_entity_status_to_pending(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _data[std::string(name)] = EntityActivationStatus::PENDING;

        result.set_to_good_status_with_value(true);
    }

    void EntityActivationManager::is_entity_name_found(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        const std::string key(name);

        result.set_to_good_status_with_value(
            _data.contains(key)
        );
    }

    void EntityActivationManager::is_entity_status_active(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        const std::string key(name);
        auto it = _data.find(key);

        if (it == _data.end())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(
            it->second == EntityActivationStatus::ACTIVE
        );
    }

    void EntityActivationManager::is_entity_status_inactive(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        const std::string key(name);
        auto it = _data.find(key);

        if (it == _data.end())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(
            it->second == EntityActivationStatus::INACTIVE
        );
    }

    void EntityActivationManager::is_entity_status_pending(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        const std::string key(name);
        auto it = _data.find(key);

        if (it == _data.end())
        {
            result.set_to_good_status_with_value(false);
            return;
        }

        result.set_to_good_status_with_value(
            it->second == EntityActivationStatus::PENDING
        );
    }

    void EntityActivationManager::remove_entity(
        Result<bool>& result,
        const std::string_view& name
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        const std::string key(name);

        result.set_to_good_status_with_value(
            _data.erase(key)
        );
    }

    void EntityActivationManager::remove_all_entities(
        Result<bool>& result
    )
    {
        std::lock_guard<std::mutex> lock(_mutex);

        _data.clear();

        result.set_to_good_status_with_value(true);
    }

}
