// RUN: %clang -fno-safe-stack -### %s 2>&1 | FileCheck %s -check-prefix=NOSP
// NOSP-NOT: "-stack-protector" "4"

// RUN: %clang -fsafe-stack -### %s 2>&1 | FileCheck %s -check-prefix=SP
// RUN: %clang -fsanatizer=address -fsafe-stack -### %s 2>&1 | FileCheck %s -check-prefix=SP
// RUN: %clang -fstack-protector -fsafe-stack -### %s 2>&1 | FileCheck %s -check-prefix=SP
// RUN: %clang -fsafe-stack -fstack-protector-all -### %s 2>&1 | FileCheck %s -check-prefix=SP
// SP: "-stack-protector" "4"
