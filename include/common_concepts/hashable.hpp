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

#ifndef COMMON_CONCEPTS_HASHABLE_HPP
#define COMMON_CONCEPTS_HASHABLE_HPP

#include <concepts>
#include <functional>

/**
 * All generic concepts not in the std::concepts.
 *
 * @version 1.0.0
 * @since 1.0.0
 *
 * @see std::concepts
 */
namespace common_concepts {
    /**
     * Hashable concept.
     *
     * @tparam T A type with an overload function std::hash.
     *
     * @version 1.0.0
     * @since 1.0.0
     * @authors en.cppreference.com
     *
     * @see https://en.cppreference.com/w/cpp/language/constraints
     */
    template <typename T>
    concept Hashable = requires (T t) {
       { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
    };

} // namespace common_concepts

#endif // COMMON_CONCEPTS_HASHABLE_HPP
