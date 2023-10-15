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

#define NORMALIZE_JSON_null JSON_TYPE_NULL
#define NORMALIZE_JSON_NULL JSON_TYPE_NULL
#define NORMALIZE_JSON_boolean JSON_TYPE_BOOLEAN
#define NORMALIZE_JSON_BOOLEAN JSON_TYPE_BOOLEAN
#define NORMALIZE_JSON_number JSON_TYPE_NUMBER
#define NORMALIZE_JSON_NUMBER JSON_TYPE_NUMBER
#define NORMALIZE_JSON_string JSON_TYPE_STRING
#define NORMALIZE_JSON_STRING JSON_TYPE_STRING
#define NORMALIZE_JSON_array JSON_TYPE_ARRAY
#define NORMALIZE_JSON_ARRAY JSON_TYPE_ARRAY
#define NORMALIZE_JSON_object JSON_TYPE_OBJECT
#define NORMALIZE_JSON_OBJECT JSON_TYPE_OBJECT

#define NORMALIZE_JSON_JsonStr JSON_TYPE_STRING

#define NORMALIZE_JSON_JsonNum JSON_TYPE_NUMBER

#define NORMALIZE_JSON_JsonBool JSON_TYPE_BOOLEAN

#define NORMALIZE_JSON_TYPE(X) NORMALIZE(JSON_##X)

void json_set_struct_member(JsonValue *val, void *dest);

void json_set_json_value(void *val, JsonValue *dest);

#define MAP_JSON_ELEMENT_TO_STRUCT(struct_member_type, struct_member)        \
	do {                                                                     \
		for (size_t i = 0; i < json_object->length; i++) {                   \
			if (strcmp(json_object->elements[i].key, #struct_member) == 0) { \
				json_set_struct_member(json_object->elements[i].value,       \
									   &dest_struct->struct_member);         \
			}                                                                \
		}                                                                    \
	} while (0);

#define STRUCT_LINE(type, val) type val;

#define MAP_JSON_TO_STRUCT(struct_type, ...)                                          \
	void map_json_to_##struct_type(JsonObject *json_object, struct_type *dest_struct) \
	{                                                                                 \
		MAP_TWO_ARGS(MAP_JSON_ELEMENT_TO_STRUCT, __VA_ARGS__)                         \
	}

#define MAP_STRUCT_ELEMENT_TO_JSON(struct_member_type, struct_member)                              \
	do {                                                                                           \
		json_object->elements =                                                                    \
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));       \
		json_object->elements[json_object->length].key = malloc(strlen(#struct_member) + 1);       \
		strncpy(json_object->elements[json_object->length].key, #struct_member,                    \
				strlen(#struct_member) + 1);                                                       \
		json_object->elements[json_object->length].value = (JsonValue *)malloc(sizeof(JsonValue)); \
		json_object->elements[json_object->length].value->type =                                   \
			NORMALIZE_JSON_TYPE(struct_member_type);                                               \
		json_set_json_value(&src_struct->struct_member,                                            \
							json_object->elements[json_object->length].value);                     \
		json_object->length++;                                                                     \
	} while (0);

#define MAP_STRUCT_TO_JSON(struct_type, ...)                         \
	JsonObject *map_##struct_type##_to_json(struct_type *src_struct) \
	{                                                                \
		JsonObject *json_object = malloc(sizeof(JsonObject));        \
		json_object->length = 0;                                     \
		json_object->elements = malloc(1);                           \
		MAP_TWO_ARGS(MAP_STRUCT_ELEMENT_TO_JSON, __VA_ARGS__)        \
		return json_object;                                          \
	}

#define JSON_STRUCT_INIT(struct_type, ...)       \
	typedef struct {                             \
		MAP_TWO_ARGS(STRUCT_LINE, __VA_ARGS__)   \
	} struct_type;                               \
	MAP_JSON_TO_STRUCT(struct_type, __VA_ARGS__) \
	MAP_STRUCT_TO_JSON(struct_type, __VA_ARGS__)


#endif // JSON_MAPPER_H