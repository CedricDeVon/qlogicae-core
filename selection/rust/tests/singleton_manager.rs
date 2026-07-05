use qlogicae_cor::singleton_manager::SingletonManager;
use qlogicae_cor::singleton_manager_configurations::SingletonManagerConfigurations;

#[cfg(test)]
mod tests {
    use std::sync::Arc;
    use std::thread;

    use super::*;

    #[derive(Debug, Default, PartialEq, Eq)]
    struct Foo {
        value: usize,
    }

    #[derive(Debug, Default, PartialEq, Eq)]
    struct Bar {
        value: usize,
    }

    #[test]
    fn setup_returns_true() {
        SingletonManager::reset();

        let configuration = SingletonManagerConfigurations::default();

        assert!(SingletonManager::setup(configuration));
    }

    #[test]
    fn reset_returns_true() {
        assert!(SingletonManager::reset());
    }

    #[test]
    fn singleton_returns_same_instance() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton::<Foo>();

        let second = SingletonManager::get_singleton::<Foo>();

        assert!(Arc::ptr_eq(&first, &second,));
    }

    #[test]
    fn singleton_returns_different_types() {
        SingletonManager::reset();

        let foo = SingletonManager::get_singleton::<Foo>();

        let bar = SingletonManager::get_singleton::<Bar>();

        assert_ne!(
            Arc::as_ptr(&foo) as *const (),
            Arc::as_ptr(&bar) as *const (),
        );
    }

    #[test]
    fn reset_creates_new_singleton() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton::<Foo>();

        SingletonManager::reset();

        let second = SingletonManager::get_singleton::<Foo>();

        assert!(!Arc::ptr_eq(&first, &second,));
    }

    #[test]
    fn pool_returns_same_instance_for_same_index() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton_from_pool::<Foo>(4, 2);

        let second = SingletonManager::get_singleton_from_pool::<Foo>(4, 2);

        assert!(Arc::ptr_eq(&first, &second,));
    }

    #[test]
    fn pool_returns_different_instances() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton_from_pool::<Foo>(4, 0);

        let second = SingletonManager::get_singleton_from_pool::<Foo>(4, 1);

        assert!(!Arc::ptr_eq(&first, &second,));
    }

    #[test]
    fn pool_wraps_indices() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton_from_pool::<Foo>(3, 1);

        let second = SingletonManager::get_singleton_from_pool::<Foo>(3, 4);

        assert!(Arc::ptr_eq(&first, &second,));
    }

    #[test]
    fn pool_is_independent_per_type() {
        SingletonManager::reset();

        let foo = SingletonManager::get_singleton_from_pool::<Foo>(2, 0);

        let bar = SingletonManager::get_singleton_from_pool::<Bar>(2, 0);

        assert_ne!(
            Arc::as_ptr(&foo) as *const (),
            Arc::as_ptr(&bar) as *const (),
        );
    }

    #[test]
    #[should_panic]
    fn pool_zero_size_panics() {
        SingletonManager::reset();

        SingletonManager::get_singleton_from_pool::<Foo>(0, 0);
    }

    #[test]
    fn concurrent_singleton_access() {
        SingletonManager::reset();

        let mut handles = Vec::new();

        for _ in 0..32 {
            handles.push(thread::spawn(|| SingletonManager::get_singleton::<Foo>()));
        }

        let instances: Vec<_> = handles
            .into_iter()
            .map(|handle| handle.join().unwrap())
            .collect();

        for instance in &instances {
            assert!(Arc::ptr_eq(instance, &instances[0],));
        }
    }

    #[test]
    fn concurrent_pool_access() {
        SingletonManager::reset();

        let mut handles = Vec::new();

        for _ in 0..32 {
            handles.push(thread::spawn(|| {
                SingletonManager::get_singleton_from_pool::<Foo>(8, 5)
            }));
        }

        let instances: Vec<_> = handles
            .into_iter()
            .map(|handle| handle.join().unwrap())
            .collect();

        for instance in &instances {
            assert!(Arc::ptr_eq(instance, &instances[0],));
        }
    }

    #[test]
    fn multiple_resets_remain_valid() {
        for _ in 0..10 {
            assert!(SingletonManager::reset());

            let instance = SingletonManager::get_singleton::<Foo>();

            assert_eq!(instance.value, 0,);
        }
    }

    #[test]
    fn singleton_survives_multiple_requests() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton::<Foo>();

        for _ in 0..1000 {
            let current = SingletonManager::get_singleton::<Foo>();

            assert!(Arc::ptr_eq(&first, &current,));
        }
    }

    #[test]
    fn pool_survives_multiple_requests() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton_from_pool::<Foo>(16, 7);

        for _ in 0..1000 {
            let current = SingletonManager::get_singleton_from_pool::<Foo>(16, 7);

            assert!(Arc::ptr_eq(&first, &current,));
        }
    }

    #[derive(Debug, Default, PartialEq, Eq)]
    struct Baz {
        value: usize,
    }

    #[test]
    fn pool_size_one_always_returns_same_instance() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton_from_pool::<Foo>(1, 0);

        let second = SingletonManager::get_singleton_from_pool::<Foo>(1, 1);

        let third = SingletonManager::get_singleton_from_pool::<Foo>(1, usize::MAX);

        assert!(Arc::ptr_eq(&first, &second,));

        assert!(Arc::ptr_eq(&first, &third,));
    }

    #[test]
    fn very_large_index_wraps_correctly() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton_from_pool::<Foo>(8, usize::MAX);

        let second = SingletonManager::get_singleton_from_pool::<Foo>(8, usize::MAX % 8);

        assert!(Arc::ptr_eq(&first, &second,));
    }

    #[test]
    fn concurrent_first_initialization() {
        SingletonManager::reset();

        let mut handles = Vec::new();

        for _ in 0..128 {
            handles.push(thread::spawn(|| SingletonManager::get_singleton::<Baz>()));
        }

        let instances: Vec<_> = handles
            .into_iter()
            .map(|handle| handle.join().unwrap())
            .collect();

        for instance in &instances {
            assert!(Arc::ptr_eq(instance, &instances[0],));
        }
    }

    #[test]
    fn concurrent_first_pool_initialization() {
        SingletonManager::reset();

        let mut handles = Vec::new();

        for _ in 0..128 {
            handles.push(thread::spawn(|| {
                SingletonManager::get_singleton_from_pool::<Baz>(16, 9)
            }));
        }

        let instances: Vec<_> = handles
            .into_iter()
            .map(|handle| handle.join().unwrap())
            .collect();

        for instance in &instances {
            assert!(Arc::ptr_eq(instance, &instances[0],));
        }
    }

    #[test]
    fn repeated_setup_and_reset() {
        for index in 0..100 {
            let mut configuration = SingletonManagerConfigurations::default();

            configuration.base.is_enabled = index % 2 == 0;

            assert!(SingletonManager::setup(configuration,));

            assert!(SingletonManager::reset());
        }
    }

    #[test]
    fn default_manager_can_be_constructed() {
        let _ = SingletonManager::default();
    }

    #[test]
    fn singleton_reference_count_is_correct() {
        SingletonManager::reset();

        let first = SingletonManager::get_singleton::<Foo>();

        assert_eq!(Arc::strong_count(&first), 2,);

        let second = first.clone();

        assert_eq!(Arc::strong_count(&first), 3,);

        drop(second);

        assert_eq!(Arc::strong_count(&first), 2,);
    }
}
