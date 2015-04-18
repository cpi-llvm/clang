// RUN: %clang_cc1 -triple x86_64-linux-unknown -emit-llvm -o - %s -stack-protector 4 | FileCheck -check-prefix=SP %s

class C {
public:
    int var;
} __attribute__((no_safe_stack));

int foo() { C c; return c.var; }

// SP: !no_safe_stack
