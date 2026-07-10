use qlogicae_cor::v1::error_manager::ErrorManager;
use qlogicae_cor::v1::error_manager_configurations::ErrorManagerConfigurations;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn default_constructor_creates_default_configuration() {
        let manager = ErrorManager::new();

        assert_eq!(
            manager.configurations,
            ErrorManagerConfigurations::default(),
        );
    }

    #[test]
    fn default_trait_creates_default_configuration() {
        let manager = ErrorManager::default();

        assert_eq!(
            manager.configurations,
            ErrorManagerConfigurations::default(),
        );
    }

    #[test]
    fn setup_returns_true() {
        let mut manager = ErrorManager::default();

        let configuration = ErrorManagerConfigurations::default();

        assert!(manager.setup(configuration,),);
    }

    #[test]
    fn setup_replaces_configuration() {
        let mut manager = ErrorManager::default();

        let configuration = ErrorManagerConfigurations {
            title: String::from("new title"),
            message: String::from("new message"),
            is_console_output_enabled: false,
            ..Default::default()
        };

        assert!(manager.setup(configuration.clone(),),);

        assert_eq!(manager.configurations, configuration,);
    }

    #[test]
    fn setup_returns_false_when_runtime_execution_is_disabled() {
        let mut manager = ErrorManager::default();

        manager
            .configurations
            .base
            .is_runtime_execution_handling_enabled = false;

        let configuration = ErrorManagerConfigurations::default();

        assert!(!manager.setup(configuration,),);
    }

    #[test]
    fn reset_returns_true() {
        let mut manager = ErrorManager::default();

        assert!(manager.reset(),);
    }

    #[test]
    fn reset_restores_default_configuration() {
        let mut manager = ErrorManager::default();

        manager.configurations.title = String::from("modified");

        manager.configurations.is_console_output_enabled = false;

        assert!(manager.reset(),);

        assert_eq!(
            manager.configurations,
            ErrorManagerConfigurations::default(),
        );
    }

    #[test]
    fn reset_returns_false_when_runtime_execution_is_disabled() {
        let mut manager = ErrorManager::default();

        manager
            .configurations
            .base
            .is_runtime_execution_handling_enabled = false;

        assert!(!manager.reset(),);
    }

    #[test]
    fn transform_to_error_log_uses_default_title() {
        let manager = ErrorManager::default();

        let log = manager.transform_to_error_log("message");

        assert_eq!(
            log,
            format!(
                "{}{}{}",
                manager.configurations.title,
                manager.configurations.title_message_separator,
                "message",
            ),
        );
    }

    #[test]
    fn transform_to_error_log_accepts_integer() {
        let manager = ErrorManager::default();

        let log = manager.transform_to_error_log(123);

        assert_eq!(
            log,
            format!(
                "{}{}123",
                manager.configurations.title, manager.configurations.title_message_separator,
            ),
        );
    }

    #[test]
    fn transform_to_error_log_with_title() {
        let manager = ErrorManager::default();

        let log = manager.transform_to_error_log_with_title("title", "message");

        assert_eq!(log, String::from("title - message",),);
    }

    #[test]
    fn transform_to_error_log_with_numeric_title() {
        let manager = ErrorManager::default();

        let log = manager.transform_to_error_log_with_title(1, 2);

        assert_eq!(log, String::from("1 - 2",),);
    }

    #[test]
    fn handle_error_output_conditions_returns_ok() {
        let manager = ErrorManager::default();

        assert!(manager.handle_error_output_conditions("error",).is_ok(),);
    }

    #[test]
    fn handle_error_output_conditions_returns_ok_when_runtime_execution_disabled() {
        let mut manager = ErrorManager::default();

        manager
            .configurations
            .base
            .is_runtime_execution_handling_enabled = false;

        assert!(manager.handle_error_output_conditions("error",).is_ok(),);
    }

    #[test]
    fn handle_error_output_conditions_returns_error_when_throw_enabled() {
        let mut manager = ErrorManager::default();

        manager.configurations.is_runtime_throw_output_enabled = true;

        let result = manager.handle_error_output_conditions("error");

        assert!(result.is_err(),);

        assert_eq!(result.unwrap_err(), String::from("error",),);
    }

    #[test]
    fn handle_returns_ok() {
        let manager = ErrorManager::default();

        assert!(manager.handle("message",).is_ok(),);
    }

    #[test]
    fn handle_returns_error() {
        let mut manager = ErrorManager::default();

        manager.configurations.is_runtime_throw_output_enabled = true;

        let result = manager.handle("message");

        assert!(result.is_err(),);

        assert_eq!(
            result.unwrap_err(),
            manager.transform_to_error_log("message",),
        );
    }

    #[test]
    fn handle_with_title_returns_ok() {
        let manager = ErrorManager::default();

        assert!(manager.handle_with_title("title", "message",).is_ok(),);
    }

    #[test]
    fn handle_with_title_returns_error() {
        let mut manager = ErrorManager::default();

        manager.configurations.is_runtime_throw_output_enabled = true;

        let expected = manager.transform_to_error_log_with_title("title", "message");

        let result = manager.handle_with_title("title", "message");

        assert!(result.is_err(),);

        assert_eq!(result.unwrap_err(), expected,);
    }

    #[test]
    fn repeated_setup_and_reset() {
        let mut manager = ErrorManager::default();

        for index in 0..100 {
            let configuration = ErrorManagerConfigurations {
                title: format!("title {}", index),
                ..Default::default()
            };

            assert!(manager.setup(configuration,),);

            assert!(manager.reset(),);
        }
    }

    #[test]
    fn repeated_handle_calls() {
        let manager = ErrorManager::default();

        for _ in 0..1000 {
            assert!(manager.handle("message",).is_ok(),);
        }
    }

    #[test]
    fn repeated_handle_with_title_calls() {
        let manager = ErrorManager::default();

        for _ in 0..1000 {
            assert!(manager.handle_with_title("title", "message",).is_ok(),);
        }
    }

    #[test]
    fn setup_replaces_previous_configuration() {
        let mut manager = ErrorManager::default();

        let first = ErrorManagerConfigurations {
            title: String::from("first"),
            ..Default::default()
        };

        assert!(manager.setup(first,),);

        let second = ErrorManagerConfigurations {
            title: String::from("second"),
            is_console_output_enabled: false,
            ..Default::default()
        };

        assert!(manager.setup(second.clone(),),);

        assert_eq!(manager.configurations, second,);
    }

    #[test]
    fn clone_preserves_configuration() {
        let mut manager = ErrorManager::default();

        manager.configurations.title = String::from("clone");

        let clone = manager.clone();

        assert_eq!(manager.configurations, clone.configurations,);
    }

    #[test]
    fn transform_to_error_log_empty_message() {
        let manager = ErrorManager::default();

        assert_eq!(
            manager.transform_to_error_log("",),
            format!(
                "{}{}",
                manager.configurations.title, manager.configurations.title_message_separator,
            ),
        );
    }

    #[test]
    fn transform_to_error_log_unicode() {
        let manager = ErrorManager::default();

        assert_eq!(
            manager.transform_to_error_log("こんにちは",),
            format!(
                "{}{}こんにちは",
                manager.configurations.title, manager.configurations.title_message_separator,
            ),
        );
    }

    #[test]
    fn transform_to_error_log_long_message() {
        let manager = ErrorManager::default();

        let message = "a".repeat(100_000);

        let log = manager.transform_to_error_log(&message);

        assert!(log.ends_with(&message,),);
    }

    #[test]
    fn transform_to_error_log_custom_separator() {
        let mut manager = ErrorManager::default();

        manager.configurations.title_message_separator = String::from("::");

        assert_eq!(
            manager.transform_to_error_log("message",),
            String::from("error at 'qlogicae-cor'::message",),
        );
    }

    #[test]
    fn transform_to_error_log_empty_separator() {
        let mut manager = ErrorManager::default();

        manager.configurations.title_message_separator.clear();

        assert_eq!(
            manager.transform_to_error_log("message",),
            String::from("error at 'qlogicae-cor'message",),
        );
    }

    #[test]
    fn runtime_throw_override_enabled() {
        let mut manager = ErrorManager::default();

        manager.configurations.is_output_override_enabled = true;

        manager.configurations.is_output_enabled = true;

        manager.configurations.is_runtime_throw_output_enabled = false;

        assert!(manager.handle("message",).is_err(),);
    }

    #[test]
    fn runtime_throw_override_disabled() {
        let mut manager = ErrorManager::default();

        manager.configurations.is_output_override_enabled = true;

        manager.configurations.is_output_enabled = false;

        manager.configurations.is_runtime_throw_output_enabled = true;

        assert!(manager.handle("message",).is_ok(),);
    }

    #[test]
    fn console_override_enabled() {
        let configuration = ErrorManagerConfigurations {
            is_output_override_enabled: true,
            is_output_enabled: true,
            is_console_output_enabled: false,
            ..Default::default()
        };

        assert!(configuration.is_enabled_for_console_output(),);
    }

    #[test]
    fn console_override_disabled() {
        let configuration = ErrorManagerConfigurations {
            is_output_override_enabled: true,
            is_output_enabled: false,
            is_console_output_enabled: true,
            ..Default::default()
        };

        assert!(!configuration.is_enabled_for_console_output(),);
    }

    #[test]
    fn runtime_execution_override() {
        let mut manager = ErrorManager::default();

        manager.configurations.base.is_override_enabled = true;

        manager.configurations.base.is_enabled = false;

        assert!(manager.handle("message",).is_ok(),);
    }

    #[test]
    fn custom_display_type() {
        struct Custom;

        impl std::fmt::Display for Custom {
            fn fmt(&self, formatter: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
                write!(formatter, "custom",)
            }
        }

        let manager = ErrorManager::default();

        let log = manager.transform_to_error_log(Custom);

        assert!(log.ends_with("custom",),);
    }

    #[test]
    fn runtime_execution_override_enabled_allows_handling() {
        let mut manager = ErrorManager::default();

        manager.configurations.base.is_override_enabled = true;

        manager.configurations.base.is_enabled = true;

        manager
            .configurations
            .base
            .is_runtime_execution_handling_enabled = false;

        assert!(manager.handle("message").is_ok(),);
    }

    #[test]
    fn runtime_execution_override_disabled_prevents_throw() {
        let mut manager = ErrorManager::default();

        manager.configurations.base.is_override_enabled = true;

        manager.configurations.base.is_enabled = false;

        manager.configurations.is_runtime_throw_output_enabled = true;

        assert!(manager.handle("message").is_ok(),);
    }

    #[test]
    fn output_override_enables_console_and_throw() {
        let mut manager = ErrorManager::default();

        manager.configurations.is_output_override_enabled = true;

        manager.configurations.is_output_enabled = true;

        manager.configurations.is_console_output_enabled = false;

        manager.configurations.is_runtime_throw_output_enabled = false;

        let result = manager.handle("message");

        assert!(result.is_err(),);
    }

    #[test]
    fn output_override_disables_console_and_throw() {
        let mut manager = ErrorManager::default();

        manager.configurations.is_output_override_enabled = true;

        manager.configurations.is_output_enabled = false;

        manager.configurations.is_console_output_enabled = true;

        manager.configurations.is_runtime_throw_output_enabled = true;

        assert!(manager.handle("message").is_ok(),);
    }

    #[test]
    fn repeated_setup_after_reset_restores_expected_configuration() {
        let mut manager = ErrorManager::default();

        let configuration = ErrorManagerConfigurations {
            title: String::from("custom"),
            ..Default::default()
        };

        assert!(manager.setup(configuration.clone(),),);

        assert!(manager.reset(),);

        assert_eq!(
            manager.configurations,
            ErrorManagerConfigurations::default(),
        );

        assert!(manager.setup(configuration.clone(),),);

        assert_eq!(manager.configurations, configuration,);
    }

    #[test]
    fn clone_after_multiple_mutations_preserves_state() {
        let mut manager = ErrorManager::default();

        manager.configurations.title = String::from("title");

        manager.configurations.message = String::from("message");

        manager.configurations.title_message_separator = String::from("::");

        manager.configurations.is_console_output_enabled = false;

        manager.configurations.is_runtime_throw_output_enabled = true;

        let clone = manager.clone();

        assert_eq!(clone.configurations, manager.configurations,);
    }
}
