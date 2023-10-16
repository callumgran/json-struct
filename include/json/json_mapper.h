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

#ifndef JSON_MAPPER_H
#define JSON_MAPPER_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "json.h"

void map_json_to_JsonStr_internal(JsonValue *val, JsonStr *dest);

void map_json_to_JsonNum_internal(JsonValue *val, JsonNum *dest);

void map_json_to_JsonBool_internal(JsonValue *val, JsonBool *dest);

void map_json_to_JsonStrArray_internal(JsonValue *val, JsonStrArray *dest);

void map_json_to_JsonNumArray_internal(JsonValue *val, JsonNumArray *dest);

void map_json_to_JsonBoolArray_internal(JsonValue *val, JsonBoolArray *dest);

JsonValue *map_JsonStr_to_json_internal(JsonStr *src);

JsonValue *map_JsonNum_to_json_internal(JsonNum *src);

JsonValue *map_JsonBool_to_json_internal(JsonBool *src);

JsonValue *map_JsonStrArray_to_json_internal(JsonStrArray *src);

JsonValue *map_JsonNumArray_to_json_internal(JsonNumArray *src);

JsonValue *map_JsonBoolArray_to_json_internal(JsonBoolArray *src);

#define MAP_JSON_ELEMENT_TO_STRUCT(struct_member_type, struct_member)                   \
	for (size_t i = 0; i < json_object->length; i++) {                                  \
		if (strcmp(json_object->elements[i].key, #struct_member) == 0) {                \
			map_json_to_##struct_member_type##_internal(json_object->elements[i].value, \
														&dest_struct->struct_member);   \
		}                                                                               \
	}

#define STRUCT_LINE(type, val) type val;

#define MAP_JSON_TO_STRUCT(struct_type, ...)                        \
	struct_type *map_json_to_##struct_type(JsonObject *json_object) \
	{                                                               \
		struct_type *dest_struct = malloc(sizeof(struct_type));     \
		MAP_TWO_ARGS(MAP_JSON_ELEMENT_TO_STRUCT, __VA_ARGS__)       \
		return dest_struct;                                         \
	}

#define MAP_JSON_TO_STRUCT_INTERNAL(struct_type, ...)                                        \
	void map_json_to_##struct_type##_internal(JsonValue *json_val, struct_type *dest_struct) \
	{                                                                                        \
		JsonObject *json_object = json_val->value.object;                                    \
		MAP_TWO_ARGS(MAP_JSON_ELEMENT_TO_STRUCT, __VA_ARGS__)                                \
	}

#define MAP_STRUCT_ELEMENT_TO_JSON(struct_member_type, struct_member)                    \
	json_object->elements =                                                              \
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1)); \
	json_object->elements[json_object->length].key = malloc(strlen(#struct_member) + 1); \
	strncpy(json_object->elements[json_object->length].key, #struct_member,              \
			strlen(#struct_member) + 1);                                                 \
	json_object->elements[json_object->length].value =                                   \
		map_##struct_member_type##_to_json_internal(&src_struct->struct_member);         \
	json_object->length++;

#define MAP_STRUCT_TO_JSON(struct_type, ...)                         \
	JsonObject *map_##struct_type##_to_json(struct_type *src_struct) \
	{                                                                \
		JsonObject *json_object = malloc(sizeof(JsonObject));        \
		json_object->length = 0;                                     \
		json_object->elements = malloc(1);                           \
		MAP_TWO_ARGS(MAP_STRUCT_ELEMENT_TO_JSON, __VA_ARGS__)        \
		return json_object;                                          \
	}

#define MAP_STRUCT_TO_JSON_INTERNAL(struct_type, ...)                        \
	JsonValue *map_##struct_type##_to_json_internal(struct_type *src_struct) \
	{                                                                        \
		JsonValue *json_val = malloc(sizeof(JsonValue));                     \
		JsonObject *json_object = malloc(sizeof(JsonObject));                \
		json_object->length = 0;                                             \
		json_object->elements = malloc(1);                                   \
		json_val->type = JSON_TYPE_OBJECT;                                   \
		json_val->value.object = json_object;                                \
		MAP_TWO_ARGS(MAP_STRUCT_ELEMENT_TO_JSON, __VA_ARGS__)                \
		return json_val;                                                     \
	}

#define MAP_STRUCT_ARRAY_TO_JSON_INTERNAL(struct_type, ...)                                      \
	JsonValue *map_##struct_type##Array_to_json_internal(struct_type##Array *src)                \
	{                                                                                            \
		JsonValue *dest = malloc(sizeof(JsonValue));                                             \
		dest->type = JSON_TYPE_ARRAY;                                                            \
		dest->value.array = malloc(sizeof(JsonArray));                                           \
		dest->value.array->length = src->length;                                                 \
		dest->value.array->values = malloc(sizeof(JsonValue *) * dest->value.array->length);     \
		for (size_t i = 0; i < dest->value.array->length; i++) {                                 \
			dest->value.array->values[i] = map_##struct_type##_to_json_internal(src->array + i); \
		}                                                                                        \
		return dest;                                                                             \
	}

#define MAP_JSON_ARRAY_TO_STRUCT_INTERNAL(struct_type, ...)                                     \
	void map_json_to_##struct_type##Array_internal(JsonValue *val, struct_type##Array *dest)    \
	{                                                                                           \
		dest->length = val->value.array->length;                                                \
		dest->array = malloc(sizeof(struct_type) * val->value.array->length);                   \
		for (size_t i = 0; i < val->value.array->length; i++) {                                 \
			map_json_to_##struct_type##_internal(val->value.array->values[i], dest->array + i); \
		}                                                                                       \
	}

#define JSON_STRUCT_INIT(struct_type, ...)                      \
	typedef struct {                                            \
		MAP_TWO_ARGS(STRUCT_LINE, __VA_ARGS__)                  \
	} struct_type;                                              \
	typedef struct {                                            \
		size_t length;                                          \
		struct_type *array;                                     \
	} struct_type##Array;                                       \
	MAP_JSON_TO_STRUCT(struct_type, __VA_ARGS__)                \
	MAP_STRUCT_TO_JSON(struct_type, __VA_ARGS__)                \
	MAP_JSON_TO_STRUCT_INTERNAL(struct_type, __VA_ARGS__)       \
	MAP_STRUCT_TO_JSON_INTERNAL(struct_type, __VA_ARGS__)       \
	MAP_STRUCT_ARRAY_TO_JSON_INTERNAL(struct_type, __VA_ARGS__) \
	MAP_JSON_ARRAY_TO_STRUCT_INTERNAL(struct_type, __VA_ARGS__)


#endif // JSON_MAPPER_H