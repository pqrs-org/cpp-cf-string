#include <iostream>
#include <pqrs/cf_string.hpp>

int main(void) {
  if (auto string = pqrs::make_string(CFSTR("example"))) {
    std::cout << *string << std::endl;
  }

  auto string = CFStringCreateWithCString(kCFAllocatorDefault,
                                          "example ★ example",
                                          kCFStringEncodingUTF8);

  if (auto s = pqrs::make_string(string)) {
    std::cout << *s << std::endl;
  }

  return 0;
}
