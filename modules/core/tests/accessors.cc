#include <modmaid/core/extern_macros.hh>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

class IBasicInterface
{
public:
    virtual ~IBasicInterface() = default;
    virtual int _add(int a, int b) = 0;
    int _number;
    bool _boolean;
    void* _pointer;
};

class BasicImplementation : public  IBasicInterface
{
    int _add(int a, int b) override
    {
        return a + b;
    }
};

class BasicAccessor
{
public:
    maid_define_property_getter_and_setter(int, Number, offsetof(IBasicInterface, _number));
    maid_define_property_getter_and_setter(bool, Boolean, offsetof(IBasicInterface, _boolean));
    maid_define_property_getter_and_setter(void*, Poitner, offsetof(IBasicInterface, _pointer));

    maid_define_virtual_method(int, Add, 1, (int a, int b), a, b);
};

std::pair<BasicImplementation*, BasicAccessor*> CreateAccessor()
{
    auto impl = new BasicImplementation();
    impl->_boolean = true;
    impl->_number = 1337;
    impl->_pointer = impl;

    return { impl, reinterpret_cast<BasicAccessor*>(impl) };
}

TEST_CASE("Test property getters", "[accessors]")
{
    auto pair = CreateAccessor();
    auto impl = pair.first;
    auto accessor = pair.second;

    REQUIRE(accessor->GetBoolean() == true);
    REQUIRE(accessor->GetNumber() == 1337);
    REQUIRE(accessor->GetPoitner() == impl);

    delete impl;
}

TEST_CASE("Test property setters", "[accessors]")
{
    auto pair = CreateAccessor();
    auto impl = pair.first;
    auto accessor = pair.second;

    accessor->SetBoolean(false);
    REQUIRE(impl->_boolean == false);

    accessor->SetNumber(200);
    REQUIRE(impl->_number == 200);

    accessor->SetPoitner(&CreateAccessor);
    REQUIRE(impl->_pointer == &CreateAccessor);

    delete impl;
}


TEST_CASE("Test methods", "[accessors]")
{
    auto pair = CreateAccessor();
    auto impl = pair.first;
    auto accessor = pair.second;

    REQUIRE(accessor->Add(20, 10) == 30);

    delete impl;
}
