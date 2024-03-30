#include <modmaid/core/signatures.hh>
#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

const char* gSignatureToFind = "SimpleStringEasyToFind";

TEST_CASE("Simple signatures", "[signatures]")
{
    auto numericPointerToVariable = reinterpret_cast<std::uintptr_t>(gSignatureToFind);

    REQUIRE(modmaid::signature::FindInRange(
        reinterpret_cast<void*>(numericPointerToVariable - 1000),
        2000,
        "  53 69 6d 70 ??  65 53 74  " // Should have all spaces removed
    ) == gSignatureToFind);

    REQUIRE(modmaid::signature::FindInModule("kernel32.dll", "47 65 74 4D 6F 64 75") != nullptr);
}