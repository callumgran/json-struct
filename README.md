# JSON-Struct-Mapper

JSON-Struct-Mapper is a lightweight C library that enables the seamless mapping of JSON data to C structs and vice versa. It provides a simple and efficient way to work with JSON data and C structs in your C projects. With JSON-Struct-Mapper, you can parse JSON data, create C structs, and easily convert between them.

## Features

- **JSON Parsing**: The library includes a JSON parser that allows you to parse JSON data and convert it into a structured format that can be manipulated in your C code.

- **Struct Mapping**: You can initialize a JSON mappable struct using a simple macro. This allows you to define C structs that mirror the structure of your JSON data, including objects, arrays, strings, numbers, and booleans.

- **JSON Serialization**: The library provides functions to convert your structured C data (JSON-Structs) back into JSON strings, making it easy to work with and communicate JSON data in your applications.

## Library Functions

### JSON Parsing

- `json_parse(const char *json)`: Parse a JSON string and return a `JsonObject` structure.

- `json_free(JsonObject *json)`: Release the memory associated with a `JsonObject` structure.

- `json_print(JsonObject *json)`: Print the contents of a `JsonObject` for debugging and inspection.

- `json_to_string(JsonObject *json)`: Serialize a `JsonObject` back into a JSON string.

### Struct Mapping

The library provides macros for initializing JSON mappable structs:

Simply initialize a JSON mappable struct using the `JSON_STRUCT_INIT` macro:

```c
JSON_STRUCT_INIT(Contact, JsonStr, type, JsonStr, value);

JSON_STRUCT_INIT(Person, JsonNum, age, JsonStr, name, JsonStrArray, hobbies, ContactArray, contacts);
```

This creates the equivalent of the following C structs:

```c
typedef struct {
    JsonStr type;
    JsonStr value;
} Contact;

typedef struct {
    size_t length;
    Contact *array;
} ContactArray;

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

```
And generates the following functions for mapping to and from JSON:

```c
Contact *map_json_to_Contact(JsonObject *json_object)
{
	Contact *dest_struct = malloc(sizeof(Contact));
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "type") == 0) {
			map_json_to_JsonStr_internal(json_object->elements[i].value, &dest_struct->type);
		}
	}
	for (size_t i = 0; i < json_object->length; i++) {
		if (strcmp(json_object->elements[i].key, "value") == 0) {
			map_json_to_JsonStr_internal(json_object->elements[i].value, &dest_struct->value);
		}
	}
	return dest_struct;
}

JsonObject *map_Contact_to_json(Contact *src_struct)
{
	JsonObject *json_object = malloc(sizeof(JsonObject));
	json_object->length = 0;
	json_object->elements = malloc(1);
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("type") + 1);
	strncpy(json_object->elements[json_object->length].key, "type", strlen("type") + 1);
	json_object->elements[json_object->length].value =
		map_JsonStr_to_json_internal(&src_struct->type);
	json_object->length++;
	json_object->elements =
		realloc(json_object->elements, sizeof(JsonElement) * (json_object->length + 1));
	json_object->elements[json_object->length].key = malloc(strlen("value") + 1);
	strncpy(json_object->elements[json_object->length].key, "value", strlen("value") + 1);
	json_object->elements[json_object->length].value =
		map_JsonStr_to_json_internal(&src_struct->value);
	json_object->length++;
	return json_object;
}

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
```

These macros allow you to create C structs that mirror the structure of your JSON data, and automatically generate functions for mapping to and from JSON.
## Supported Data Types

JSON-Struct-Mapper supports the following data types for mapping:

    String
    Number
    Boolean
    Array
    Object
    Array of JsonStructs

The library is designed to make it easy to work with JSON data in C applications while adhering to JSON data types.
## Usage

    Include the library in your C project.

    Define your JSON mappable structs using the JSON_STRUCT_INIT macro.

    Use the provided functions to parse, serialize, and work with your JSON data.

    Enjoy the simplicity and efficiency of mapping between JSON and C structs.

## Getting Started

To get started, check out the example code and documentation in the project's repository. The provided examples and documentation will help you quickly integrate JSON-Struct-Mapper into your C project.