/*
 *  Copyright (C) 2023 Callum Gran
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* MAGIC MACROS JUST DON'T LOOK */

#define EVAL0(...) __VA_ARGS__
#define EVAL1(...) EVAL0(EVAL0(EVAL0(__VA_ARGS__)))
#define EVAL2(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL3(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL4(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL(...) EVAL4(__VA_ARGS__)

#define NOP

#define MAP_POP_ONE_ARG0(F, X, ...) F(X) __VA_OPT__(MAP_POP_ONE_ARG1 NOP(F, __VA_ARGS__))
#define MAP_POP_ONE_ARG1(F, X, ...) F(X) __VA_OPT__(MAP_POP_ONE_ARG0 NOP(F, __VA_ARGS__))

#define MAP_ONE_ARG(F, ...) __VA_OPT__(EVAL(MAP_POP_ONE_ARG0(F, __VA_ARGS__)))

#define MAP_POP_TWO_ARGS0(F, X, Y, ...) F(X, Y) __VA_OPT__(MAP_POP_TWO_ARGS1 NOP(F, __VA_ARGS__))
#define MAP_POP_TWO_ARGS1(F, X, Y, ...) F(X, Y) __VA_OPT__(MAP_POP_TWO_ARGS0 NOP(F, __VA_ARGS__))

#define MAP_TWO_ARGS(F, ...) __VA_OPT__(EVAL(MAP_POP_TWO_ARGS0(F, __VA_ARGS__)))

#define MAP_POP_THREE_ARGS0(F, X, Y, Z, ...) \
	F(X, Y, Z) __VA_OPT__(MAP_POP_THREE_ARGS1 NOP(F, __VA_ARGS__))
#define MAP_POP_THREE_ARGS1(F, X, Y, Z, ...) \
	F(X, Y, Z) __VA_OPT__(MAP_POP_THREE_ARGS0 NOP(F, __VA_ARGS__))

#define MAP_THREE_ARGS(F, ...) __VA_OPT__(EVAL(MAP_POP_THREE_ARGS0(F, __VA_ARGS__)))

#endif // COMMON_H