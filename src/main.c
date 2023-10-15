#include "../include/json/json.h"
#include "../include/json/json_mapper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Example usage:

JSON_STRUCT_INIT(Person, JsonNum, age, JsonStr, name);

int main()
{
	const char *json = "{"
					   "\"person\": {"
					   "\"name\": \"John Doe\","
					   "\"age\": 35,"
					   "\"address\": {"
					   "\"street\": \"123 Main St\","
					   "\"city\": \"New York\","
					   "\"zipcode\": \"10001\""
					   "},"
					   "\"contacts\": ["
					   "{"
					   "\"type\": \"email\","
					   "\"value\": \"john.doe@example.com\""
					   "},"
					   "{"
					   "\"type\": \"phone\","
					   "\"value\": \"555-555-5555\""
					   "}"
					   "]"
					   "},"
					   "\"friends\": ["
					   "{"
					   "\"name\": \"Alice\","
					   "\"age\": 30"
					   "},"
					   "{"
					   "\"name\": \"Bob\","
					   "\"age\": 32"
					   "}"
					   "],"
					   "\"hobbies\": [\"reading\", \"traveling\", \"photography\"],"
					   "\"isStudent\": false"
					   "}";

	JsonObject *json_object = json_parse(json);

	json_print(json_object);

	char *json_string = json_to_string(json_object);

	printf("json string: %s\n", json_string);

	free(json_string);

	json_free(json_object);

	const char *json_data = "{ \"age\": 30, \"name\": \"John\" }";

	json_object = json_parse(json_data);

	Person person;
	person.age = 0.0;
	person.name = malloc(sizeof(char) * 10);

	map_json_to_Person(json_object, &person);

	printf("age: %f\n", person.age);
	printf("name: %s\n", person.name);

	JsonObject *result = map_Person_to_json(&person);

	printf("result:");
	json_print(result);

	char *result_string = json_to_string(result);

	printf("result string: %s\n", result_string);

	free(result_string);

	json_free(json_object);

	json_free(result);

	return 0;
}