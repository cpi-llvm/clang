// RUN: %clang -fno-safe-stack -### %s 2>&1 | FileCheck %s -check-prefix=NOSP
// NOSP-NOT: "-stack-protector" "4"

// RUN: %clang -fsafe-stack -### %s 2>&1 | FileCheck %s -check-prefix=SP
// SP: "-stack-protector" "4"

// RUN: %clang     -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// RUN: %clang -O1 -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// RUN: %clang -O2 -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// RUN: %clang -O3 -target i386-unknown-unknown -fsafe-stack %s -S -emit-llvm -o - | FileCheck %s
// RUN: %clang     -target i386-unknown-unknown -fno-safe-stack %s -S -emit-llvm -o - | FileCheck %s -check-prefix=NOSP2
// RUN: %clang -O1 -target i386-unknown-unknown -fno-safe-stack %s -S -emit-llvm -o - | FileCheck %s -check-prefix=NOSP2

// RUN: %clang -O2 -target i386-unknown-unknown -fno-safe-stack %s -S -emit-llvm -o - | FileCheck %s -check-prefix=NOSP2

// RUN: %clang -O3 -target i386-unknown-unknown -fno-safe-stack %s -S -emit-llvm -o - | FileCheck %s -check-prefix=NOSP2

// Verify that -fno-safe-stack invokes safestack instrumentation.

int foo(int *a) { return *a; }
// CHECK: attributes{{.*}}safestack
// NOSP2-NOT: attributes{{.*}}safestack
