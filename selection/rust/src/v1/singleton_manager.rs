use std::any::{Any, TypeId};
use std::collections::HashMap;
use std::sync::{Arc, LazyLock, Mutex};

use crate::v1::singleton_manager_configurations::SingletonManagerConfigurations;

type SharedSingleton = Arc<dyn Any + Send + Sync>;

type SingletonRegistry = HashMap<TypeId, SharedSingleton>;

type SingletonPool = Vec<SharedSingleton>;

type SingletonPoolRegistry = HashMap<TypeId, SingletonPool>;

#[derive(Debug, Default)]
pub struct SingletonManager;

static CONFIGURATIONS: LazyLock<Mutex<SingletonManagerConfigurations>> =
    LazyLock::new(|| Mutex::new(SingletonManagerConfigurations::default()));

static SINGLETONS: LazyLock<Mutex<SingletonRegistry>> =
    LazyLock::new(|| Mutex::new(HashMap::new()));

static SINGLETON_POOLS: LazyLock<Mutex<SingletonPoolRegistry>> =
    LazyLock::new(|| Mutex::new(HashMap::new()));

impl SingletonManager {
    pub fn setup(configurations: SingletonManagerConfigurations) -> bool {
        let mut current = CONFIGURATIONS
            .lock()
            .unwrap_or_else(|error| error.into_inner());

        *current = configurations;

        true
    }

    pub fn reset() -> bool {
        *CONFIGURATIONS
            .lock()
            .unwrap_or_else(|error| error.into_inner()) = SingletonManagerConfigurations::default();

        SINGLETONS
            .lock()
            .unwrap_or_else(|error| error.into_inner())
            .clear();

        SINGLETON_POOLS
            .lock()
            .unwrap_or_else(|error| error.into_inner())
            .clear();

        true
    }

    pub fn get_singleton<T>() -> Arc<T>
    where
        T: Default + Send + Sync + 'static,
    {
        let mut singletons = SINGLETONS.lock().unwrap_or_else(|error| error.into_inner());

        let type_id = TypeId::of::<T>();

        if let Some(instance) = singletons.get(&type_id) {
            return instance
                .clone()
                .downcast::<T>()
                .expect("singleton has incorrect type");
        }

        let instance = Arc::new(T::default());

        singletons.insert(type_id, instance.clone());

        instance
    }

    pub fn get_singleton_from_pool<T>(instance_count: usize, index: usize) -> Arc<T>
    where
        T: Default + Send + Sync + 'static,
    {
        assert!(instance_count > 0);

        let mut pools = SINGLETON_POOLS
            .lock()
            .unwrap_or_else(|error| error.into_inner());

        let type_id = TypeId::of::<T>();

        let pool = pools.entry(type_id).or_insert_with(|| {
            (0..instance_count)
                .map(|_| Arc::new(T::default()) as SharedSingleton)
                .collect()
        });

        let pool_size = pool.len();

        pool[index % pool_size]
            .clone()
            .downcast::<T>()
            .expect("singleton has incorrect type")
    }
}
