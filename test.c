typedef struct {
	JsonStr type;
	JsonStr value;
} Contact;
Contact *map_json_to_Contact(JsonObject *json_object)
{
	Contact *dest_struct = malloc(sizeof(Contact));
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "type") == 0) {
				dest_struct->type = map_json_to_JsonStr_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "value") == 0) {
				dest_struct->value = map_json_to_JsonStr_internal(json_object->elements[i].value);
			}
		}
	} while (0);
}
JsonObject *map_Contact_to_json(Contact *src_struct)
{
	JsonObject *json_object = malloc(sizeof(JsonObject));
	json_object->length = 0;
	json_object->elements = malloc(1);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("type") + 1);
		strncpy(json_object->elements[json_object->length].key, "type", strlen("type") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStr_to_json_internal(&src_struct->type);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("value") + 1);
		strncpy(json_object->elements[json_object->length].key, "value", strlen("value") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStr_to_json_internal(&src_struct->value);
		json_object->length++;
	} while (0);
	return json_object;
}
Contact *map_json_to_Contact_internal(JsonValue *json_val)
{
	JsonObject *json_object = json_val->value.object;
	Contact *dest_struct = malloc(sizeof(Contact));
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "type") == 0) {
				dest_struct->type = map_json_to_JsonStr_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "value") == 0) {
				dest_struct->value = map_json_to_JsonStr_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	return dest_struct;
}
JsonObject *map_Contact_to_json_internal(Contact *src_struct)
{
	JsonObject *json_object = malloc(sizeof(JsonObject));
	json_object->length = 0;
	json_object->elements = malloc(1);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("type") + 1);
		strncpy(json_object->elements[json_object->length].key, "type", strlen("type") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStr_to_json_internal(&src_struct->type);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("value") + 1);
		strncpy(json_object->elements[json_object->length].key, "value", strlen("value") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStr_to_json_internal(&src_struct->value);
		json_object->length++;
	} while (0);
	return json_object;
}
typedef struct {
	JsonNum age;
	JsonStr name;
	JsonStrArray hobbies;
	Contact contact;
} Person;
Person *map_json_to_Person(JsonObject *json_object)
{
	Person *dest_struct = malloc(sizeof(Person));
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "age") == 0) {
				dest_struct->age = map_json_to_JsonNum_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "name") == 0) {
				dest_struct->name = map_json_to_JsonStr_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "hobbies") == 0) {
				dest_struct->hobbies =
					map_json_to_JsonStrArray_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "contact") == 0) {
				dest_struct->contact = map_json_to_Contact_internal(json_object->elements[i].value);
			}
		}
	} while (0);
}
JsonObject *map_Person_to_json(Person *src_struct)
{
	JsonObject *json_object = malloc(sizeof(JsonObject));
	json_object->length = 0;
	json_object->elements = malloc(1);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("age") + 1);
		strncpy(json_object->elements[json_object->length].key, "age", strlen("age") + 1);
		json_object->elements[json_object->length].value =
			map_JsonNum_to_json_internal(&src_struct->age);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("name") + 1);
		strncpy(json_object->elements[json_object->length].key, "name", strlen("name") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStr_to_json_internal(&src_struct->name);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("hobbies") + 1);
		strncpy(json_object->elements[json_object->length].key, "hobbies", strlen("hobbies") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStrArray_to_json_internal(&src_struct->hobbies);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("contact") + 1);
		strncpy(json_object->elements[json_object->length].key, "contact", strlen("contact") + 1);
		json_object->elements[json_object->length].value =
			map_Contact_to_json_internal(&src_struct->contact);
		json_object->length++;
	} while (0);
	return json_object;
}
Person *map_json_to_Person_internal(JsonValue *json_val)
{
	JsonObject *json_object = json_val->value.object;
	Person *dest_struct = malloc(sizeof(Person));
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "age") == 0) {
				dest_struct->age = map_json_to_JsonNum_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "name") == 0) {
				dest_struct->name = map_json_to_JsonStr_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "hobbies") == 0) {
				dest_struct->hobbies =
					map_json_to_JsonStrArray_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	do {
		for (size_t i = 0; i < json_object->length; i++) {
			if (strcmp(json_object->elements[i].key, "contact") == 0) {
				dest_struct->contact = map_json_to_Contact_internal(json_object->elements[i].value);
			}
		}
	} while (0);
	return dest_struct;
}
JsonObject *map_Person_to_json_internal(Person *src_struct)
{
	JsonObject *json_object = malloc(sizeof(JsonObject));
	json_object->length = 0;
	json_object->elements = malloc(1);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("age") + 1);
		strncpy(json_object->elements[json_object->length].key, "age", strlen("age") + 1);
		json_object->elements[json_object->length].value =
			map_JsonNum_to_json_internal(&src_struct->age);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("name") + 1);
		strncpy(json_object->elements[json_object->length].key, "name", strlen("name") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStr_to_json_internal(&src_struct->name);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("hobbies") + 1);
		strncpy(json_object->elements[json_object->length].key, "hobbies", strlen("hobbies") + 1);
		json_object->elements[json_object->length].value =
			map_JsonStrArray_to_json_internal(&src_struct->hobbies);
		json_object->length++;
	} while (0);
	do {
		json_object->elements =
			realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
		json_object->elements[json_object->length].key = malloc(strlen("contact") + 1);
		strncpy(json_object->elements[json_object->length].key, "contact", strlen("contact") + 1);
		json_object->elements[json_object->length].value =
			map_Contact_to_json_internal(&src_struct->contact);
		json_object->length++;
	} while (0);
	return json_object;
}