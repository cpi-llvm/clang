// RUN: %clang_cc1 -triple x86_64-linux-unknown -emit-llvm -o - %s -stack-protector 4 | FileCheck -check-prefix=SP %s

__attribute__((no_safe_stack))
int foo(int *a) {  return *a; }

// SP-NOT: attributes #{{.*}} = { nounwind safestack{{.*}} }
