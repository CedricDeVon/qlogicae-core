#pragma once

#include "result.hpp"
#include "instance_manager.hpp"
#include "entity_activation_status.hpp"

#include <string_view>
#include <unordered_map>

namespace QLogicaeCppCore
{
    class EntityActivationManager
    {
    public:
        EntityActivationManager();

        ~EntityActivationManager();

        EntityActivationManager(
            const EntityActivationManager& instance
        ) = delete;

        EntityActivationManager(
            EntityActivationManager&& instance
        ) noexcept = delete;

        EntityActivationManager& operator = (
            EntityActivationManager&& instance
        ) = delete;

        EntityActivationManager& operator = (
            const EntityActivationManager& instance
        ) = delete;

        void get_entity_collection_copy(
            Result<std::unordered_map<std::string_view, EntityActivationStatus>>& result
        );

        void get_entity_status(
            Result<EntityActivationStatus>& result,
            std::string_view& name
        );

        void set_entity_status(
            Result<bool>& result,
            std::string_view& name,
            EntityActivationStatus& status
        );

        void set_entity_status_to_active(
            Result<bool>& result,
            std::string_view& name
        );

        void set_entity_status_to_inactive(
            Result<bool>& result,
            std::string_view& name
        );

        void set_entity_status_to_pending(
            Result<bool>& result,
            std::string_view& name
        );

        void is_entity_name_found(
            Result<bool>& result,
            std::string_view& name
        );

        void is_entity_status_active(
            Result<bool>& result,
            std::string_view& name
        );

        void is_entity_status_inactive(
            Result<bool>& result,
            std::string_view& name
        );

        void is_entity_status_pending(
            Result<bool>& result,
            std::string_view& name
        );

        void remove_entity(
            Result<bool>& result,
            std::string_view& name
        );
        
        void remove_all_entities(
            Result<bool>& result
        );

    protected:
        std::unordered_map<std::string_view, EntityActivationStatus> _data;
    };

    inline static EntityActivationManager& ENTITY_ACTIVATION_MANAGER =
        INSTANCE_MANAGER.get_instance<EntityActivationManager>();
}
