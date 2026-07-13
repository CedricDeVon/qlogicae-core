use std::fmt::Display;
use std::ops::{Deref, DerefMut};

use crate::v1::abstract_manager_configurations::AbstractManagerConfigurations;
use crate::v1::error_manager::ErrorManager;
use crate::v1::singleton_manager::SingletonManager;

#[derive(Debug, Clone)]
pub struct AbstractManager<T>
where
    T: Deref<Target = AbstractManagerConfigurations> + DerefMut + Default + Clone,
{
    pub configurations: T,
}

impl<T> AbstractManager<T>
where
    T: Deref<Target = AbstractManagerConfigurations> + DerefMut + Default + Clone,
{
    pub fn new(configurations: T) -> Self {
        Self { configurations }
    }

    pub fn setup(&mut self, configurations: T) -> bool {
        if self.configurations.is_disabled_for_handling(false) {
            return false;
        }

        self.configurations = configurations;

        true
    }

    pub fn reset(&mut self) -> bool {
        if self.configurations.is_disabled_for_handling(false) {
            return false;
        }

        self.configurations = T::default();

        true
    }

    pub fn handle_error<TMessage>(&self, message: TMessage) -> bool
    where
        TMessage: Display,
    {
        SingletonManager::get_singleton::<ErrorManager>()
            .handle(message)
            .is_ok()
    }

    pub fn handle_error_with_title<TTitle, TMessage>(
        &self,
        title: TTitle,
        message: TMessage,
    ) -> bool
    where
        TTitle: Display,
        TMessage: Display,
    {
        SingletonManager::get_singleton::<ErrorManager>()
            .handle_with_title(title, message)
            .is_ok()
    }
}
