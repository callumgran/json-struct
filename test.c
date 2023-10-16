typedef struct {
	JsonNum age;
	JsonStr name;
	JsonStrArray hobbies;
	ContactArray contacts;
} Person;
typedef struct {
	size_t length;
	Person *array;
} PersonArray;
Person *map_json_to_Person(JsonObject *json_object)
{
	Person *dest_struct = malloc(sizeof(Person));
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "age") == 0) {
			map_json_to_JsonNum_internal(json_object->elements[i].value, &dest_struct->age);
		}
	}
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "name") == 0) {
			map_json_to_JsonStr_internal(json_object->elements[i].value, &dest_struct->name);
		}
	}
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "hobbies") == 0) {
			map_json_to_JsonStrArray_internal(json_object->elements[i].value,
											  &dest_struct->hobbies);
		}
	}
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "contacts") == 0) {
			map_json_to_ContactArray_internal(json_object->elements[i].value,
											  &dest_struct->contacts);
		}
	}
	return dest_struct;
}
JsonObject *map_Person_to_json(Person *src_struct)
{
	JsonObject *json_object = malloc(sizeof(JsonObject));
	json_object->length = 0;
	json_object->elements = malloc(1);
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("age") + 1);
	strncpy(json_object->elements[json_object->length].key, "age", strlen("age") + 1);
	json_object->elements[json_object->length].value =
		map_JsonNum_to_json_internal(&src_struct->age);
	json_object->length++;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("name") + 1);
	strncpy(json_object->elements[json_object->length].key, "name", strlen("name") + 1);
	json_object->elements[json_object->length].value =
		map_JsonStr_to_json_internal(&src_struct->name);
	json_object->length++;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("hobbies") + 1);
	strncpy(json_object->elements[json_object->length].key, "hobbies", strlen("hobbies") + 1);
	json_object->elements[json_object->length].value =
		map_JsonStrArray_to_json_internal(&src_struct->hobbies);
	json_object->length++;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("contacts") + 1);
	strncpy(json_object->elements[json_object->length].key, "contacts", strlen("contacts") + 1);
	json_object->elements[json_object->length].value =
		map_ContactArray_to_json_internal(&src_struct->contacts);
	json_object->length++;
	return json_object;
}
void map_json_to_Person_internal(JsonValue *json_val, Person *dest_struct)
{
	JsonObject *json_object = json_val->value.object;
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "age") == 0) {
			map_json_to_JsonNum_internal(json_object->elements[i].value, &dest_struct->age);
		}
	}
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "name") == 0) {
			map_json_to_JsonStr_internal(json_object->elements[i].value, &dest_struct->name);
		}
	}
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "hobbies") == 0) {
			map_json_to_JsonStrArray_internal(json_object->elements[i].value,
											  &dest_struct->hobbies);
		}
	}
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "contacts") == 0) {
			map_json_to_ContactArray_internal(json_object->elements[i].value,
											  &dest_struct->contacts);
		}
	}
}
JsonValue *map_Person_to_json_internal(Person *src_struct)
{
	JsonValue *json_val = malloc(sizeof(JsonValue));
	JsonObject *json_object = malloc(sizeof(JsonObject));
	json_object->length = 0;
	json_object->elements = malloc(1);
	json_val->type = JSON_TYPE_OBJECT;
	json_val->value.object = json_object;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("age") + 1);
	strncpy(json_object->elements[json_object->length].key, "age", strlen("age") + 1);
	json_object->elements[json_object->length].value =
		map_JsonNum_to_json_internal(&src_struct->age);
	json_object->length++;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("name") + 1);
	strncpy(json_object->elements[json_object->length].key, "name", strlen("name") + 1);
	json_object->elements[json_object->length].value =
		map_JsonStr_to_json_internal(&src_struct->name);
	json_object->length++;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("hobbies") + 1);
	strncpy(json_object->elements[json_object->length].key, "hobbies", strlen("hobbies") + 1);
	json_object->elements[json_object->length].value =
		map_JsonStrArray_to_json_internal(&src_struct->hobbies);
	json_object->length++;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("contacts") + 1);
	strncpy(json_object->elements[json_object->length].key, "contacts", strlen("contacts") + 1);
	json_object->elements[json_object->length].value =
		map_ContactArray_to_json_internal(&src_struct->contacts);
	json_object->length++;
	return json_val;
}
JsonValue *map_PersonArray_to_json_internal(PersonArray *src)
{
	JsonValue *dest = malloc(sizeof(JsonValue));
	dest->type = JSON_TYPE_ARRAY;
	dest->value.array = malloc(sizeof(JsonArray));
	dest->value.array->length = src->length;
	dest->value.array->values = malloc(sizeof(JsonValue *) * dest->value.array->length);
	for (size_t i = 0; i < dest->value.array->length; i++) {
		dest->value.array->values[i] = map_Person_to_json_internal(src->array + i);
	}
	return dest;
}
void map_json_to_PersonArray_internal(JsonValue *val, PersonArray *dest)
{
	dest->length = val->value.array->length;
	dest->array = malloc(sizeof(Person) * val->value.array->length);
	for (size_t i = 0; i < val->value.array->length; i++) {
		map_json_to_Person_internal(val->value.array->values[i], dest->array + i);
	}
}