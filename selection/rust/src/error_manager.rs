use std::fmt::Display;

use crate::error_manager_configurations::ErrorManagerConfigurations;

#[derive(Debug, Default, Clone)]
pub struct ErrorManager {
    pub configurations: ErrorManagerConfigurations,
}

impl ErrorManager {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn setup(&mut self, configurations: ErrorManagerConfigurations) -> bool {
        if self.configurations.base.is_disabled_for_handling(false) {
            return false;
        }

        self.configurations = configurations;

        true
    }

    pub fn reset(&mut self) -> bool {
        if self.configurations.base.is_disabled_for_handling(false) {
            return false;
        }

        self.configurations = ErrorManagerConfigurations::default();

        true
    }

    pub fn transform_to_error_log<T>(&self, message: T) -> String
    where
        T: Display,
    {
        format!(
            "{}{}{}",
            self.configurations.title, self.configurations.title_message_separator, message,
        )
    }

    pub fn transform_to_error_log_with_title<TTitle, TMessage>(
        &self,
        title: TTitle,
        message: TMessage,
    ) -> String
    where
        TTitle: Display,
        TMessage: Display,
    {
        format!(
            "{}{}{}",
            title, self.configurations.title_message_separator, message,
        )
    }

    pub fn handle_error_output_conditions(&self, error_log: &str) -> Result<(), String> {
        if !self
            .configurations
            .base
            .is_enabled_for_runtime_execution_handling()
        {
            return Ok(());
        }

        if self.configurations.is_enabled_for_console_output() {
            println!("{error_log}");
        }

        if self.configurations.is_enabled_for_runtime_throw_output() {
            return Err(error_log.to_owned());
        }

        Ok(())
    }

    pub fn handle<T>(&self, message: T) -> Result<(), String>
    where
        T: Display,
    {
        let error_log = self.transform_to_error_log(message);

        self.handle_error_output_conditions(&error_log)
    }

    pub fn handle_with_title<TTitle, TMessage>(
        &self,
        title: TTitle,
        message: TMessage,
    ) -> Result<(), String>
    where
        TTitle: Display,
        TMessage: Display,
    {
        let error_log = self.transform_to_error_log_with_title(title, message);

        self.handle_error_output_conditions(&error_log)
    }
}
