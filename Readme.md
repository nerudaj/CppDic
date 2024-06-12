# CppDic

Dependency injection container with compile-time validation of registered services.

---

This project was built as a challenge to see whether it is possible to create an equivalent of C#'s ServiceProvider with compile-time checking whether each service can be constructed based on the services already registered in the container.

This project doesn't care about lifetimes (everything is `std::shared_ptr`) and prevents construction of circular dependencies by design. Project is not meant for production use.

## API usage

Considering following two classes:

```cpp
struct A {};

struct B
{
	B(std::shared_ptr<A>) {}
};
```

One can instantiate them in the provider like this:

```cpp
#include <cppdic/ServiceProviderBuilder.hpp>

auto&& provider = dic::ServiceProviderBuilder()
	.addService<A>()
	.addService<B>()
	.build();
```

Services can also implement interfaces:

```cpp
struct I
{
	virtual ~I() = default;
};

struct Impl : public I {};

auto&& provider = dic::ServiceProviderBuilder()
	.addService<I, Impl>();
```

Services can be mocked:

```cpp
auto&& mock = std::shared_ptr<MockOfI>();
auto&& provider = dic::ServiceProviderBuilder()
	.addService<I>(mock)
	.build();
```

And services can be overriden in the builder:

```cpp
auto&& mock = std::shared_ptr<MockOfI>();
auto&& provider = dic::ServiceProviderBuilder()
	.addService<I, Impl>()
	.addService<I>(mock) // replaces <I, Impl>
	.build();
```

Instantiated services can be easily retrieved from the final provider:

```cpp
provider->get<I>()->doSomething();
```

## Documentation

This repo was published as a complement to my Medium article about this project. The article is available here: [link]() (no premium account required)
