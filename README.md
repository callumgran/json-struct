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

```c
#define JSON_STRUCT_INIT(struct_type, ...)     \
    typedef struct {                           \
        MAP_TWO_ARGS(STRUCT_LINE, __VA_ARGS__) \
    } struct_type;                             \
    MAP_JSON_TO_STRUCT(struct_type, __VA_ARGS__) \
    MAP_STRUCT_TO_JSON(struct_type, __VA_ARGS__) 
```
These macros allow you to create C structs that mirror the structure of your JSON data, and automatically generate functions for mapping to and from JSON.
## Supported Data Types

JSON-Struct-Mapper supports the following data types for mapping:

    String
    Number
    Boolean
    Array (work in progress)
    Object (work in progress)

The library is designed to make it easy to work with JSON data in C applications while adhering to JSON data types.
## Usage

    Include the library in your C project.

    Define your JSON mappable structs using the JSON_STRUCT_INIT macro.

    Use the provided functions to parse, serialize, and work with your JSON data.

    Enjoy the simplicity and efficiency of mapping between JSON and C structs.

## Getting Started

To get started, check out the example code and documentation in the project's repository. The provided examples and documentation will help you quickly integrate JSON-Struct-Mapper into your C project.

## Contributing

Contributions and bug reports are welcome! Feel free to open issues or submit pull requests on the project's GitHub repository.