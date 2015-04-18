// RUN: %clang_cc1 -triple x86_64-linux-unknown -emit-llvm -o - %s -stack-protector 4 | FileCheck -check-prefix=SP %s

int foo(unsigned x) { char buffer[x + 1] __attribute__((no_safe_stack)); return buffer[x]; }

// SP: !no_safe_stack
