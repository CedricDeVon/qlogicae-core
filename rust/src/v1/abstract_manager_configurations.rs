#[derive(Debug, Clone, PartialEq, Eq)]
pub struct AbstractManagerConfigurations {
    pub is_override_enabled: bool,

    pub is_enabled: bool,

    pub is_runtime_execution_handling_enabled: bool,

    pub is_edge_case_handling_enabled: bool,

    pub is_error_handling_enabled: bool,
}

impl Default for AbstractManagerConfigurations {
    fn default() -> Self {
        Self {
            is_override_enabled: false,

            is_enabled: true,

            is_runtime_execution_handling_enabled: true,

            is_edge_case_handling_enabled: true,

            is_error_handling_enabled: true,
        }
    }
}

impl AbstractManagerConfigurations {
    pub fn new() -> Self {
        Self::default()
    }

    pub fn is_disabled_for_handling(&self, conditions: bool) -> bool {
        !self.is_enabled_for_runtime_execution_handling()
            || (self.is_enabled_for_edge_case_handling() && conditions)
    }

    pub fn is_enabled_for_runtime_execution_handling(&self) -> bool {
        if self.is_override_enabled {
            self.is_enabled
        } else {
            self.is_runtime_execution_handling_enabled
        }
    }

    pub fn is_enabled_for_edge_case_handling(&self) -> bool {
        if self.is_override_enabled {
            self.is_enabled
        } else {
            self.is_edge_case_handling_enabled
        }
    }

    pub fn is_enabled_for_error_handling(&self) -> bool {
        if self.is_override_enabled {
            self.is_enabled
        } else {
            self.is_error_handling_enabled
        }
    }
}
