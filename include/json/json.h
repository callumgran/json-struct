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

#ifndef JSON_H
#define JSON_H

#include <stdbool.h>
#include <stddef.h>

#include "common.h"

typedef char *JsonStr;
typedef double JsonNum;
typedef bool JsonBool;

typedef struct {
	JsonStr *array;
	size_t length;
} JsonStrArray;

typedef struct {
	JsonNum *array;
	size_t length;
} JsonNumArray;

typedef struct {
	JsonBool *array;
	size_t length;
} JsonBoolArray;

typedef enum JsonType {
	JSON_TYPE_NULL,
	JSON_TYPE_BOOLEAN,
	JSON_TYPE_NUMBER,
	JSON_TYPE_STRING,
	JSON_TYPE_ARRAY,
	JSON_TYPE_OBJECT,
	JSON_TYPE_COUNT
} JsonType;

typedef struct JsonValue {
	JsonType type;
	union {
		JsonBool boolean;
		JsonNum number;
		JsonStr string;
		struct JsonArray *array;
		struct JsonObject *object;
	} value;
} JsonValue;

typedef struct JsonArray {
	size_t length;
	JsonValue **values;
} JsonArray;

typedef struct JsonElement {
	char *key;
	JsonValue *value;
} JsonElement;

typedef struct JsonObject {
	size_t length;
	JsonElement *elements;
} JsonObject;

JsonObject *json_parse(const char *json);

void json_free(JsonObject *json);

void json_print(JsonObject *json);

char *json_to_string(JsonObject *json);

bool json_get_bool(JsonObject *json, const char *key);

JsonNum json_get_number(JsonObject *json, const char *key);

JsonStr json_get_string(JsonObject *json, const char *key);

JsonArray *json_get_array(JsonObject *json, const char *key);

JsonObject *json_get_object(JsonObject *json, const char *key);

#endif // JSON_H