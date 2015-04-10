// RUN: %clang_cc1 -fsyntax-only -verify  %s

#define NO_SAFE_STACK __attribute__((no_safe_stack))

#if !__has_attribute(no_safe_stack)
#error "Should support no_safe_stack"
#endif

void nosp_fun() NO_SAFE_STACK;

void nosp_fun_args() __attribute__((no_safe_stack(1))); // \
  // expected-error {{'no_safe_stack' attribute takes no arguments}}

int nosp_testfn(int y) NO_SAFE_STACK;

int nosp_testfn(int y) {
  int x NO_SAFE_STACK = y; // \
    // expected-error {{'no_safe_stack' attribute only applies to functions}}
  return x;
}

int nosp_test_var NO_SAFE_STACK; // \
  // expected-error {{'no_safe_stack' attribute only applies to functions}}

class NoSPFoo {
 private:
  int test_field NO_SAFE_STACK; // \
    // expected-error {{'no_safe_stack' attribute only applies to functions}}
  void test_method() NO_SAFE_STACK;
};

class NO_SAFE_STACK NoSPTestClass { // \
  // expected-error {{'no_safe_stack' attribute only applies to functions}}
};

void nosp_fun_params(int lvar NO_SAFE_STACK); // \
  // expected-error {{'no_safe_stack' attribute only applies to functions}}
