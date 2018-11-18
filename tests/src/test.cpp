#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/cf_string.hpp>

TEST_CASE("make_string") {
  {
    std::string expected("example");
    auto actual = pqrs::make_string(CFSTR("example"));
    REQUIRE(actual != std::nullopt);
    REQUIRE(*actual == expected);
  }
  {
    // With Unicode characters
    std::string expected("example ★★ example");
    auto actual = pqrs::make_string(CFSTR("example ★★ example"));
    REQUIRE(actual != std::nullopt);
    REQUIRE(*actual == expected);
  }
}

TEST_CASE("make_cf_string") {
  {
    auto expected = CFSTR("example");
    auto actual = pqrs::make_cf_string("example");
    REQUIRE(actual);
    REQUIRE(CFEqual(*actual, expected));
  }
  {
    // With Unicode characters
    auto expected = CFSTR("example ★★ example");
    auto actual = pqrs::make_cf_string("example ★★ example");
    REQUIRE(actual);
    REQUIRE(CFEqual(*actual, expected));
  }
}
