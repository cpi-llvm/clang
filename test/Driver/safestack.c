// RUN: %clang     -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// RUN: %clang -O1 -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// RUN: %clang -O2 -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// RUN: %clang -O3 -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// Verify that -fsafe-stack invokes safestack instrumentation.

int foo(char *s, int n)
{
  int  i;
  char buff[64];
  for (i = 0; i < n; ++i)
    buff[i] = s[i];
  return buff[n];
}
// CHECK: safestack
