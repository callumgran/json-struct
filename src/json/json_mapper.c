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

void json_set_struct_member(JsonValue *val, void *dest)
{
	switch (val->type) {
	case JSON_TYPE_NUMBER:
		*(JsonNum *)dest = val->value.number;
		break;
	case JSON_TYPE_STRING:
		*(JsonStr *)dest = malloc(strlen(val->value.string) + 1);
		strncpy(*(JsonStr *)dest, val->value.string, strlen(val->value.string) + 1);
		break;
	case JSON_TYPE_BOOLEAN:
		*(bool *)dest = val->value.boolean;
		break;
	case JSON_TYPE_NULL:
		*(void **)dest = NULL;
		break;
	// TODO add support for arrays and objects
	default:
		break;
	}
}

void json_set_json_value(void *val, JsonValue *dest)
{
	switch (dest->type) {
	case JSON_TYPE_NUMBER:
		dest->value.number = *(JsonNum *)val;
		break;
	case JSON_TYPE_STRING:
		dest->value.string = malloc(strlen(*(JsonStr *)val) + 1);
		strncpy(dest->value.string, *(JsonStr *)val, strlen(*(JsonStr *)val) + 1);
		break;
	case JSON_TYPE_BOOLEAN:
		dest->value.boolean = *(bool *)val;
		break;
	case JSON_TYPE_NULL:
		dest->value.string = NULL;
		break;
	// TODO add support for arrays and objects
	default:
		break;
	}
}