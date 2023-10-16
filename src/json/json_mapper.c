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

#include "json/json_mapper.h"

// void map_json_to_member(JsonValue *val, void *dest)
// {
// 	switch (val->type) {
// 	case JSON_TYPE_NUMBER:
// 		*(JsonNum *)dest = val->value.number;
// 		break;
// 	case JSON_TYPE_STRING:
// 		*(JsonStr *)dest = malloc(strlen(val->value.string) + 1);
// 		strncpy(*(JsonStr *)dest, val->value.string, strlen(val->value.string) + 1);
// 		break;
// 	case JSON_TYPE_BOOLEAN:
// 		*(bool *)dest = val->value.boolean;
// 		break;
// 	case JSON_TYPE_NULL:
// 		*(void **)dest = NULL;
// 		break;
// 	// TODO add support for arrays and s
// 	default:
// 		break;
// 	}
// }

void map_json_to_JsonStr_internal(JsonValue *val, JsonStr *dest)
{
	*dest = malloc(strlen(val->value.string) + 1);
	strncpy(*dest, val->value.string, strlen(val->value.string) + 1);
}

void map_json_to_JsonNum_internal(JsonValue *val, JsonNum *dest)
{
	*dest = val->value.number;
}

void map_json_to_JsonBool_internal(JsonValue *val, JsonBool *dest)
{
	*dest = val->value.boolean;
}

void map_json_to_JsonStrArray_internal(JsonValue *val, JsonStrArray *dest)
{
	dest->length = val->value.array->length;
	dest->array = malloc(sizeof(JsonStr) * val->value.array->length);
	for (size_t i = 0; i < val->value.array->length; i++) {
		map_json_to_JsonStr_internal(val->value.array->values[i], dest->array + i);
	}
}

void map_json_to_JsonNumArray_internal(JsonValue *val, JsonNumArray *dest)
{
	dest->length = val->value.array->length;
	dest->array = malloc(sizeof(JsonNum) * val->value.array->length);
	for (size_t i = 0; i < val->value.array->length; i++) {
		map_json_to_JsonNum_internal(val->value.array->values[i], dest->array + i);
	}
}

void map_json_to_JsonBoolArray_internal(JsonValue *val, JsonBoolArray *dest)
{
	dest->length = val->value.array->length;
	dest->array = malloc(sizeof(JsonBool) * val->value.array->length);
	for (size_t i = 0; i < val->value.array->length; i++) {
		map_json_to_JsonBool_internal(val->value.array->values[i], dest->array + i);
	}
}

JsonValue *map_JsonStr_to_json_internal(JsonStr *src)
{
	JsonValue *dest = malloc(sizeof(JsonValue));
	dest->type = JSON_TYPE_STRING;
	dest->value.string = malloc(strlen(*src) + 1);
	strncpy(dest->value.string, *src, strlen(*src) + 1);
	return dest;
}

JsonValue *map_JsonNum_to_json_internal(JsonNum *src)
{
	JsonValue *dest = malloc(sizeof(JsonValue));
	dest->type = JSON_TYPE_NUMBER;
	dest->value.number = *src;
	return dest;
}

JsonValue *map_JsonBool_to_json_internal(JsonBool *src)
{
	JsonValue *dest = malloc(sizeof(JsonValue));
	dest->type = JSON_TYPE_BOOLEAN;
	dest->value.boolean = *src;
	return dest;
}

JsonValue *map_JsonStrArray_to_json_internal(JsonStrArray *src)
{
	JsonValue *dest = malloc(sizeof(JsonValue));
	dest->type = JSON_TYPE_ARRAY;
	dest->value.array = malloc(sizeof(JsonArray));
	dest->value.array->length = src->length;
	dest->value.array->values = malloc(sizeof(JsonValue *) * dest->value.array->length);
	for (size_t i = 0; i < dest->value.array->length; i++) {
		dest->value.array->values[i] = map_JsonStr_to_json_internal(src->array + i);
	}
	return dest;
}

JsonValue *map_JsonNumArray_to_json_internal(JsonNumArray *src)
{
	JsonValue *dest = malloc(sizeof(JsonValue));
	dest->type = JSON_TYPE_ARRAY;
	dest->value.array = malloc(sizeof(JsonArray));
	dest->value.array->length = src->length;
	dest->value.array->values = malloc(sizeof(JsonValue *) * dest->value.array->length);
	for (size_t i = 0; i < dest->value.array->length; i++) {
		dest->value.array->values[i] = map_JsonNum_to_json_internal(src->array + i);
	}
	return dest;
}

JsonValue *map_JsonBoolArray_to_json_internal(JsonBoolArray *src)
{
	JsonValue *dest = malloc(sizeof(JsonValue));
	dest->type = JSON_TYPE_ARRAY;
	dest->value.array = malloc(sizeof(JsonArray));
	dest->value.array->length = src->length;
	dest->value.array->values = malloc(sizeof(JsonValue *) * dest->value.array->length);
	for (size_t i = 0; i < dest->value.array->length; i++) {
		dest->value.array->values[i] = map_JsonBool_to_json_internal(src->array + i);
	}
	return dest;
}