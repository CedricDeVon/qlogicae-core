use crate::v1::abstract_manager_configurations::AbstractManagerConfigurations;

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct ErrorManagerConfigurations {
    pub base: AbstractManagerConfigurations,

    pub is_output_enabled: bool,

    pub is_output_override_enabled: bool,

    pub is_asynchronous_output_enabled: bool,

    pub is_asynchronous_output_override_enabled: bool,

    pub is_console_output_enabled: bool,

    pub is_runtime_throw_output_enabled: bool,

    pub title: String,

    pub message: String,

    pub title_message_separator: String,
}

impl Default for ErrorManagerConfigurations {
    fn default() -> Self {
        Self {
            base: AbstractManagerConfigurations::default(),

            is_output_enabled: true,

            is_output_override_enabled: false,

            is_asynchronous_output_enabled: true,

            is_asynchronous_output_override_enabled: false,

            is_console_output_enabled: true,

            is_runtime_throw_output_enabled: false,

            title: String::from("error at 'qlogicae-cor'"),

            message: String::from("something went wrong here"),

            title_message_separator: String::from(" - "),
        }
    }
}

impl ErrorManagerConfigurations {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn is_enabled_for_runtime_throw_output(&self) -> bool {
        if self.is_output_override_enabled {
            self.is_output_enabled
        } else {
            self.is_runtime_throw_output_enabled
        }
    }

    pub fn is_enabled_for_console_output(&self) -> bool {
        if self.is_output_override_enabled {
            self.is_output_enabled
        } else {
            self.is_console_output_enabled
        }
    }
}
