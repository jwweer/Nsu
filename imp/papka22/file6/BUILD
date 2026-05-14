load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "bank_account",
    hdrs = [
        "bank_account.h",
        "debit_account.h",
        "credit_account.h",
    ],
    srcs = [
        "bank_account.c",
        "debit_account.c",
        "credit_account.c",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "bank_account_private",
    hdrs = [
        "bank_account_p.h",
        "debit_account_p.h",
        "credit_account_p.h",
    ],
    visibility = ["//visibility:private"],
)

cc_test(
    name = "bank_account_test",
    size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":bank_account",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)