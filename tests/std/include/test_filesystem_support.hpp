// Copyright (c) Microsoft Corporation.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <algorithm>
#include <experimental/filesystem>
#include <filesystem>
#include <iterator>
#include <random>
#include <string>

template <class T>
std::string get_test_directory_subname(const T& testName) {
    using namespace std;
    random_device rd;
    uniform_int_distribution<> dist(0, 15);
    string subName(testName);
    subName.push_back('_');
    generate_n(back_inserter(subName), 32, [&] { return "0123456789ABCDEF"[dist(rd)]; });
    return subName;
}

inline std::experimental::filesystem::path get_experimental_test_directory(const char* const testName) {
    return std::experimental::filesystem::temp_directory_path() / get_test_directory_subname(testName);
}

#if _HAS_CXX17
#include <string_view>

inline std::filesystem::path get_test_directory(std::string_view testName) {
    return std::filesystem::temp_directory_path() / get_test_directory_subname(testName);
}
#endif // _HAS_CXX17
