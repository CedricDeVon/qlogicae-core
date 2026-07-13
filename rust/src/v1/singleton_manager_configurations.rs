use crate::v1::abstract_manager_configurations::AbstractManagerConfigurations;

#[derive(Debug, Clone, PartialEq, Eq, Default)]
pub struct SingletonManagerConfigurations {
    pub base: AbstractManagerConfigurations,
}

impl SingletonManagerConfigurations {
    pub fn new() -> Self {
        Self::default()
    }
}
