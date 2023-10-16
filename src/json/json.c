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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json/json.h"

static JsonValue *parse_value(const char *json, int *index);
static void json_print_value(JsonValue *value, int indent);

static void skip_whitespace(const char *json, int *index)
{
	while (json[*index] == ' ' || json[*index] == '\t' || json[*index] == '\n' ||
		   json[*index] == '\r') {
		(*index)++;
	}
}

static char *parse_string(const char *json, int *index)
{
	char *result = NULL;
	int start = *index + 1;
	int end = start;

	while (json[end] && json[end] != '\"') {
		if (json[end] == '\\' && json[end + 1]) {
			end += 2;
		} else {
			end++;
		}
	}

	if (json[end] == '\"') {
		result = malloc(end - start + 1);
		memcpy(result, json + start, end - start);
		result[end - start] = '\0';
		*index = end + 1;
	}

	return result;
}

static double parse_number(const char *json, int *index)
{
	char *endptr;
	double value = strtod(json + *index, &endptr);
	*index = endptr - json;
	return value;
}

static JsonObject *parse_object(const char *json, int *index)
{
	JsonObject *result = malloc(sizeof(JsonObject));
	result->length = 0;
	result->elements = malloc(1);

	(*index)++;

	skip_whitespace(json, index);

	if (json[*index] == '}') {
		(*index)++;
		return result;
	}

	while (true) {
		result->length++;
		result->elements = realloc(result->elements, result->length * sizeof(JsonElement));
		result->elements[result->length - 1].key = parse_string(json, index);

		skip_whitespace(json, index);

		(*index)++;

		skip_whitespace(json, index);

		result->elements[result->length - 1].value = parse_value(json, index);

		skip_whitespace(json, index);

		if (json[*index] == '}') {
			(*index)++;
			return result;
		}

		(*index)++;

		skip_whitespace(json, index);
	}
}

static JsonArray *parse_array(const char *json, int *index)
{
	JsonArray *result = malloc(sizeof(JsonArray));
	result->length = 0;
	result->values = malloc(1);

	(*index)++;

	skip_whitespace(json, index);

	if (json[*index] == ']') {
		(*index)++;
		return result;
	}

	while (true) {
		result->length++;
		result->values = realloc(result->values, result->length * sizeof(JsonValue *));
		result->values[result->length - 1] = parse_value(json, index);

		skip_whitespace(json, index);

		if (json[*index] == ']') {
			(*index)++;
			return result;
		}

		(*index)++;
	}
}

static JsonValue *parse_value(const char *json, int *index)
{
	skip_whitespace(json, index);

	JsonValue *result = malloc(sizeof(JsonValue));

	switch (json[*index]) {
	case 'n':
		(*index) += 4;
		result->type = JSON_TYPE_NULL;
		break;

	case 't':
		(*index) += 4;
		result->type = JSON_TYPE_BOOLEAN;
		result->value.boolean = true;
		break;

	case 'f':
		(*index) += 5;
		result->type = JSON_TYPE_BOOLEAN;
		result->value.boolean = false;
		break;

	case '\"':
		result->value.string = parse_string(json, index);
		result->type = JSON_TYPE_STRING;
		break;

	case '[':
		result->value.array = parse_array(json, index);
		result->type = JSON_TYPE_ARRAY;
		break;

	case '{':
		result->value.object = parse_object(json, index);
		result->type = JSON_TYPE_OBJECT;
		break;

	default:
		result->value.number = parse_number(json, index);
		result->type = JSON_TYPE_NUMBER;
		break;
	}

	return result;
}

JsonObject *json_parse(const char *json)
{
	int index = 0;
	return parse_object(json, &index);
}

static void json_free_value(JsonValue *value)
{
	switch (value->type) {
	case JSON_TYPE_STRING:
		free(value->value.string);
		break;

	case JSON_TYPE_ARRAY:
		for (size_t i = 0; i < value->value.array->length; i++) {
			json_free_value(value->value.array->values[i]);
		}

		free(value->value.array->values);
		free(value->value.array);
		break;

	case JSON_TYPE_OBJECT:
		for (size_t i = 0; i < value->value.object->length; i++) {
			free(value->value.object->elements[i].key);
			json_free_value(value->value.object->elements[i].value);
		}

		free(value->value.object->elements);
		free(value->value.object);
		break;

	default:
		break;
	}

	free(value);
}

void json_free(JsonObject *json)
{
	for (size_t i = 0; i < json->length; i++) {
		free(json->elements[i].key);
		json_free_value(json->elements[i].value);
	}

	free(json->elements);
	free(json);
}

static void json_print_value(JsonValue *value, int indent);

static void json_print_array(JsonArray *array, int indent)
{
	printf("[");

	printf("\n");

	for (int j = 0; j < indent + 1; j++) {
		printf("    ");
	}
	for (size_t i = 0; i < array->length; i++) {
		json_print_value(array->values[i], indent + 1);

		if (i < array->length + 1) {
			printf(", ");
		}
	}

	printf("\n");
	for (int j = 0; j < indent; j++) {
		printf("    ");
	}
	printf("]");
}

static void json_print_object(JsonObject *object, int indent)
{
	printf("\n");
	for (int j = 0; j < indent; j++) {
		printf("    ");
	}
	printf("{");

	for (size_t i = 0; i < object->length; i++) {
		printf("\n");
		for (int j = 0; j < indent + 1; j++) {
			printf("    ");
		}
		printf("\"%s\": ", object->elements[i].key);
		json_print_value(object->elements[i].value, indent + 1);

		if (i < object->length - 1) {
			printf(", ");
		}

		printf("\n");
	}

	for (int j = 0; j < indent; j++) {
		printf("    ");
	}
	printf("}");
}

static void json_print_value(JsonValue *value, int indent)
{
	switch (value->type) {
	case JSON_TYPE_NULL:
		printf("null");
		break;

	case JSON_TYPE_BOOLEAN:
		printf("%s", value->value.boolean ? "true" : "false");
		break;

	case JSON_TYPE_NUMBER:
		printf("%f", value->value.number);
		break;

	case JSON_TYPE_STRING:
		printf("\"%s\"", value->value.string);
		break;

	case JSON_TYPE_ARRAY:
		json_print_array(value->value.array, indent);
		break;

	case JSON_TYPE_OBJECT:
		json_print_object(value->value.object, indent);
		break;

	default:
		printf("?");
		break;
	}
}

void json_print(JsonObject *json)
{
	json_print_object(json, 0);
	printf("\n");
}

static void json_value_to_string(JsonValue *value, char **string);

static void append_to_string(char **string, const char *text)
{
	size_t old_len = strlen(*string);
	size_t text_len = strlen(text);
	*string = realloc(*string, old_len + text_len + 1);
	strcat(*string, text);
}

static void append_char_to_string(char **string, char c)
{
	size_t old_len = strlen(*string);
	*string = realloc(*string, old_len + 2);
	(*string)[old_len] = c;
	(*string)[old_len + 1] = '\0';
}

static void json_array_to_string(JsonArray *array, char **string)
{
	append_char_to_string(string, '[');

	for (size_t i = 0; i < array->length; i++) {
		json_value_to_string(array->values[i], string);

		if (i < array->length - 1) {
			append_to_string(string, ", ");
		}
	}

	append_char_to_string(string, ']');
}

static void json_object_to_string(JsonObject *object, char **string)
{
	append_char_to_string(string, '{');

	for (size_t i = 0; i < object->length; i++) {
		append_to_string(string, "\"");
		append_to_string(string, object->elements[i].key);
		append_to_string(string, "\": ");
		json_value_to_string(object->elements[i].value, string);

		if (i < object->length - 1) {
			append_to_string(string, ", ");
		}
	}

	append_char_to_string(string, '}');
}

static void json_value_to_string(JsonValue *value, char **string)
{
	switch (value->type) {
	case JSON_TYPE_NULL:
		append_to_string(string, "null");
		break;

	case JSON_TYPE_BOOLEAN:
		append_to_string(string, value->value.boolean ? "true" : "false");
		break;

	case JSON_TYPE_NUMBER: {
		char num_string[100];
		snprintf(num_string, sizeof(num_string), "%f", value->value.number);
		append_to_string(string, num_string);
	} break;

	case JSON_TYPE_STRING:
		append_to_string(string, "\"");
		append_to_string(string, value->value.string);
		append_to_string(string, "\"");
		break;

	case JSON_TYPE_ARRAY:
		json_array_to_string(value->value.array, string);
		break;

	case JSON_TYPE_OBJECT:
		json_object_to_string(value->value.object, string);
		break;

	default:
		append_char_to_string(string, '?');
		break;
	}
}

char *json_to_string(JsonObject *json)
{
	char *string = malloc(1);
	string[0] = '\0';

	json_object_to_string(json, &string);

	return string;
}

bool json_get_bool(JsonObject *obj, const char *key)
{
	for (size_t i = 0; i < obj->length; i++) {
		JsonElement elem = obj->elements[i];
		if (elem.value->type == JSON_TYPE_BOOLEAN) {
			if (strcmp(elem.key, key) == 0) {
				return elem.value->value.boolean;
			}
		}
	}

	return false;
}

JsonNum json_get_number(JsonObject *obj, const char *key)
{
	for (size_t i = 0; i < obj->length; i++) {
		JsonElement elem = obj->elements[i];
		if (elem.value->type == JSON_TYPE_NUMBER) {
			if (strcmp(elem.key, key) == 0) {
				return elem.value->value.number;
			}
		}
	}

	return 0.0;
}

JsonStr json_get_string(JsonObject *obj, const char *key)
{
	for (size_t i = 0; i < obj->length; i++) {
		JsonElement elem = obj->elements[i];
		if (elem.value->type == JSON_TYPE_STRING) {
			if (strcmp(elem.key, key) == 0) {
				return elem.value->value.string;
			}
		}
	}

	return NULL;
}

JsonArray *json_get_array(JsonObject *obj, const char *key)
{
	for (size_t i = 0; i < obj->length; i++) {
		JsonElement elem = obj->elements[i];
		if (elem.value->type == JSON_TYPE_ARRAY) {
			if (strcmp(elem.key, key) == 0) {
				return elem.value->value.array;
			}
		}
	}

	return NULL;
}

JsonObject *json_get_object(JsonObject *obj, const char *key)
{
	for (size_t i = 0; i < obj->length; i++) {
		JsonElement elem = obj->elements[i];
		if (elem.value->type == JSON_TYPE_OBJECT) {
			if (strcmp(elem.key, key) == 0) {
				return elem.value->value.object;
			}
		}
	}

	return NULL;
}