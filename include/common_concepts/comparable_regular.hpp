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

#ifndef COMMON_CONCEPTS_COMPARABLE_REGULAR_HPP
#define COMMON_CONCEPTS_COMPARABLE_REGULAR_HPP

#include <compare>
#include <concepts>

namespace common_concepts {
    /**
     * Three-Way-Comparable and Regular type concept.
     *
     * @tparam T A regular type with a three-way comparator.
     *
     * @version 1.0.0
     * @since 1.0.0
     * @authors Xyphenore
     *
     * @see std::three_way_comparable
     * @see std::regular
     */
    template <typename T>
    concept ComparableRegular = std::three_way_comparable<T> && std::regular<T>;

} // namespace common_concepts

#endif // COMMON_CONCEPTS_COMPARABLE_REGULAR_HPP
