/*******************************************************************************
 * Common_Concepts - Concepts not included in the std::concepts.
 * Copyright (C)  2022 Xyphenore
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 ******************************************************************************/

#include "doctest/doctest.h"

#include <common_concepts/hashable.hpp>
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>

namespace {
    template <common_concepts::Hashable T>
    class HashableTest final {
    public:
        constexpr explicit HashableTest(T test) noexcept: value_(std::move(test)) {}

        [[nodiscard("You call the function to get the hash of subvalue.")]] constexpr size_t hash() const noexcept {
            return std::hash<T>{}(value_);
        }

    private:
        T value_;
    };
} // namespace

#define COMMON_CONCEPTS_TEST_STRINGS std::string, std::string_view, const char*
#define COMMON_CONCEPTS_TEST_WSTRINGS std::wstring, std::wstring_view, const wchar_t*
#define COMMON_CONCEPTS_TEST_U8STRINGS std::u8string, std::u8string_view, const char8_t*
#define COMMON_CONCEPTS_TEST_U16STRINGS std::u16string, std::u16string_view, const char16_t*
#define COMMON_CONCEPTS_TEST_U32STRINGS std::u32string, std::u32string_view, const char32_t*

#define COMMON_CONCEPTS_TEST_SIGNED_INTEGERS int8_t, int16_t, int32_t, int64_t
#define COMMON_CONCEPTS_TEST_UNSIGNED_INTEGERS uint8_t, uint16_t, uint32_t, uint64_t, size_t

DOCTEST_TEST_SUITE("Test Hashable concept") {
    DOCTEST_TEST_CASE_TEMPLATE("Test on integers",
                               T,
                               COMMON_CONCEPTS_TEST_SIGNED_INTEGERS,
                               COMMON_CONCEPTS_TEST_UNSIGNED_INTEGERS) {
        constexpr T integer = 15;
        DOCTEST_REQUIRE((std::hash<T>{}(integer) == ::HashableTest(integer).hash()));
    }

    DOCTEST_TEST_CASE_TEMPLATE("Test on string", T, COMMON_CONCEPTS_TEST_STRINGS) {
        const T text("TEST");
        DOCTEST_REQUIRE((std::hash<T>{}(text) == ::HashableTest(text).hash()));
    }

    DOCTEST_TEST_CASE_TEMPLATE("Test on u8 string", T, COMMON_CONCEPTS_TEST_U8STRINGS) {
        const T text(u8"TEST");
        DOCTEST_REQUIRE((std::hash<T>{}(text) == ::HashableTest(text).hash()));
    }

    DOCTEST_TEST_CASE_TEMPLATE("Test on u16 string", T, COMMON_CONCEPTS_TEST_U16STRINGS) {
        const T text(u"TEST");
        DOCTEST_REQUIRE((std::hash<T>{}(text) == ::HashableTest(text).hash()));
    }

    DOCTEST_TEST_CASE_TEMPLATE("Test on u32 string", T, COMMON_CONCEPTS_TEST_U32STRINGS) {
        const T text(U"TEST");
        DOCTEST_REQUIRE((std::hash<T>{}(text) == ::HashableTest(text).hash()));
    }

    DOCTEST_TEST_CASE_TEMPLATE("Test on wstring", T, COMMON_CONCEPTS_TEST_WSTRINGS) {
        const T text(L"TEST");
        DOCTEST_REQUIRE((std::hash<T>{}(text) == ::HashableTest(text).hash()));
    }
}
