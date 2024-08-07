// RUN: %clang -target x86_64-unknown %s -### 2>&1 | FileCheck %s --check-prefix=CHECK-ABSENT
// RUN: %clang -target x86_64-sie-ps5 %s -### 2>&1 | FileCheck %s --check-prefix=CHECK-ABSENT
// RUN: %clang -target x86_64-scei-ps4 -fno-stack-size-section %s -### 2>&1 | FileCheck %s --check-prefix=CHECK-ABSENT
// CHECK-ABSENT-NOT: -fstack-size-section

// RUN: %clang -target x86_64-unknown -fstack-size-section -### 2>&1 | FileCheck %s --check-prefix=CHECK-PRESENT
// RUN: %clang -target x86_64-scei-ps4 %s -### 2>&1 | FileCheck %s --check-prefix=CHECK-ABSENT
// CHECK-PRESENT: -fstack-size-section

// RUN: %clang -target x86_64-unknown -fstack-size-section -fno-stack-size-section %s -### 2>&1 \
// RUN:     | FileCheck %s --check-prefix=CHECK-ABSENT
// RUN: %clang -target x86_64-unknown -fno-stack-size-section -fstack-size-section %s -### 2>&1 \
// RUN:     | FileCheck %s --check-prefix=CHECK-PRESENT

// RUN: %clang -### --target=x86_64-linux-gnu -flto -fstack-size-section %s 2>&1 | FileCheck %s --check-prefix=LTO
// RUN: %clang -### --target=x86_64-linux-gnu -flto -fstack-size-section -fno-stack-size-section %s 2>&1 | FileCheck %s --check-prefix=LTO-NO
// RUN: %clang -### --target=x86_64-sie-ps5 -fstack-size-section %s 2>&1 | FileCheck %s --check-prefix=LTO

// LTO: "-plugin-opt=-stack-size-section"
// LTO-NO-NOT: "-plugin-opt=-stack-size-section"

int foo() { return 42; }
