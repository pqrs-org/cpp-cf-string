#include <boost/ut.hpp>
#include <pqrs/cf/string.hpp>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "make_string"_test = [] {
    {
      std::string expected("example");
      auto actual = pqrs::cf::make_string(CFSTR("example"));
      expect(actual != std::nullopt);
      expect(*actual == expected);
    }

    {
      // With Unicode characters
      std::string expected("example ★★ example");
      auto actual = pqrs::cf::make_string(CFSTR("example ★★ example"));
      expect(actual != std::nullopt);
      expect(*actual == expected);
    }

    expect(pqrs::cf::make_string(static_cast<CFTypeRef>(nullptr)) == std::nullopt);
    expect(pqrs::cf::make_string(static_cast<CFStringRef>(nullptr)) == std::nullopt);

    {
      if (auto dictionary = CFDictionaryCreateMutable(nullptr,
                                                      0,
                                                      &kCFTypeDictionaryKeyCallBacks,
                                                      &kCFTypeDictionaryValueCallBacks)) {
        expect(pqrs::cf::make_string(dictionary) == std::nullopt);

        CFRelease(dictionary);
      } else {
        expect(false);
      }
    }
  };

  "make_cf_string"_test = [] {
    {
      auto expected = CFSTR("example");
      auto actual = pqrs::cf::make_cf_string("example");
      expect(actual);
      expect(CFEqual(*actual, expected));
    }

    {
      // With Unicode characters
      auto expected = CFSTR("example ★★ example");
      auto actual = pqrs::cf::make_cf_string("example ★★ example");
      expect(actual);
      expect(CFEqual(*actual, expected));
    }
  };

  return 0;
}
