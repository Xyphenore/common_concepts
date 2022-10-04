/*******************************************************************************
 * Common_Concepts - Safe conversion from a string to integer.
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

#include <cstdint>
#include <string_view>

#include "doctest/doctest.h"

#include <common_concepts/comparable_regular.hpp>

namespace {
    template<common_concepts::ComparableRegular T>
    class ComparableRegularTest final {
    public:
        constexpr explicit ComparableRegularTest( T test ) noexcept
        : value_( std::move(test) ) {}

        // NOLINTNEXTLINE(hicpp-use-nullptr, modernize-use-nullptr)
        constexpr auto operator<=>(const ComparableRegularTest&) const noexcept = default;

        [[nodiscard("You call the function to get the value.")]]
        constexpr T value() const noexcept { return value_; }

    private:
        T value_;
    };
} // namespace

#define COMMON_CONCEPTS_TEST_SIGNED_INTEGERS int8_t, int16_t, int32_t, int64_t
#define COMMON_CONCEPTS_TEST_UNSIGNED_INTEGERS uint8_t, uint16_t, uint32_t, uint64_t, size_t

DOCTEST_TEST_SUITE("Test ComparableRegular concept") {
    DOCTEST_TEST_CASE_TEMPLATE( "Test on an integer", T,
                                COMMON_CONCEPTS_TEST_SIGNED_INTEGERS, COMMON_CONCEPTS_TEST_UNSIGNED_INTEGERS ) {
        constexpr T integer = 15;

        DOCTEST_SUBCASE("Equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(integer) == ::ComparableRegularTest(integer)) );
            DOCTEST_REQUIRE(
                (::ComparableRegularTest(integer) != ::ComparableRegularTest(static_cast<T>(integer + 1)))
            );
        }

        DOCTEST_SUBCASE("Simple operator") {
            DOCTEST_REQUIRE(
                (::ComparableRegularTest(static_cast<T>(integer + 1)) > ::ComparableRegularTest(integer))
            );
            DOCTEST_REQUIRE(
                (::ComparableRegularTest(integer) < ::ComparableRegularTest(static_cast<T>(integer + 1)))
            );
        }

        DOCTEST_SUBCASE("Over equality") {
            DOCTEST_REQUIRE(
                (::ComparableRegularTest(static_cast<T>(integer + 1)) >= ::ComparableRegularTest(integer))
            );
            DOCTEST_REQUIRE( (::ComparableRegularTest(integer) >=::ComparableRegularTest(integer)) );
        }

        DOCTEST_SUBCASE("Under equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(integer) <= ::ComparableRegularTest(integer)) );
            DOCTEST_REQUIRE(
                (::ComparableRegularTest(integer) <= ::ComparableRegularTest(static_cast<T>(integer + 1)))
            );
        }
    }

    DOCTEST_TEST_CASE_TEMPLATE( "Test on an integer value", T,
                                COMMON_CONCEPTS_TEST_SIGNED_INTEGERS, COMMON_CONCEPTS_TEST_UNSIGNED_INTEGERS) {
        constexpr T integer = 15;

        DOCTEST_SUBCASE("Equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(integer).value() == ::ComparableRegularTest(integer).value()) );
            DOCTEST_REQUIRE((
                ::ComparableRegularTest(integer).value() != ::ComparableRegularTest(static_cast<T>(integer + 1)).value()
            ));
        }

        DOCTEST_SUBCASE("Simple operator") {
            DOCTEST_REQUIRE((
                ::ComparableRegularTest(static_cast<T>(integer + 1)).value() > ::ComparableRegularTest(integer).value()
            ));
            DOCTEST_REQUIRE((
                ::ComparableRegularTest(integer).value() < ::ComparableRegularTest(static_cast<T>(integer + 1)).value()
            ));
        }

        DOCTEST_SUBCASE("Over equality") {
            DOCTEST_REQUIRE((
                ::ComparableRegularTest(static_cast<T>(integer + 1)).value()
                >= ::ComparableRegularTest( integer ).value()
            ));
            DOCTEST_REQUIRE( (::ComparableRegularTest(integer).value() >= ::ComparableRegularTest(integer).value()) );
        }

        DOCTEST_SUBCASE("Under equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(integer).value() <= ::ComparableRegularTest(integer).value()) );
            DOCTEST_REQUIRE((
                ::ComparableRegularTest(integer).value() <= ::ComparableRegularTest(static_cast<T>(integer + 1)).value()
            ));
        }
    }

    DOCTEST_TEST_CASE_TEMPLATE( "Test on strings", T, const char* ) {
        const T text = "TEST";
        const T text2 = "text";

        DOCTEST_SUBCASE("Equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) == ::ComparableRegularTest(text)) );
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) != ::ComparableRegularTest(text2)) );
        }
    }

    DOCTEST_TEST_CASE_TEMPLATE( "Test on wstrings", T, const wchar_t* ) {
        const T text = L"TEST";
        const T text2 = L"text";

        DOCTEST_SUBCASE("Equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) == ::ComparableRegularTest(text)) );
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) != ::ComparableRegularTest(text2)) );
        }
    }

    DOCTEST_TEST_CASE_TEMPLATE( "Test on u8strings", T, const char8_t* ) {
        const T text = u8"TEST";
        const T text2 = u8"text";

        DOCTEST_SUBCASE("Equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) == ::ComparableRegularTest(text)) );
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) != ::ComparableRegularTest(text2)) );
        }
    }

    DOCTEST_TEST_CASE_TEMPLATE( "Test on u16strings", T, const char16_t* ) {
        const T text = u"TEST";
        const T text2 = u"text";

        DOCTEST_SUBCASE("Equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) == ::ComparableRegularTest(text)) );
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) != ::ComparableRegularTest(text2)) );
        }
    }

    DOCTEST_TEST_CASE_TEMPLATE( "Test on u32strings", T, const char32_t* ) {
        const T text = U"TEST";
        const T text2 = U"text";

        DOCTEST_SUBCASE("Equality") {
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) == ::ComparableRegularTest(text)) );
            DOCTEST_REQUIRE( (::ComparableRegularTest(text) != ::ComparableRegularTest(text2)) );
        }
    }
}
