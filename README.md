# JSON Viewer

JSON Viewer is a simple C++ program that reads and displays JSON data in a table format. You can use it to view JSON files and navigate through nested JSON objects.

## Prerequisites

- C++ compiler (e.g., g++)
- [nlohmann/json](https://github.com/nlohmann/json) library (already included in the project)

## Installation

Clone the repository:

<pre>
git clone https://github.com/yourusername/json-viewer.git
cd json-viewer
</pre>

Build the program using g++:

<pre>
g++ src/main.cpp -o build/view_json -Wall -Wextra
</pre>

## Usage

To view a JSON file:

<pre>
./build/view_json <JSON_PATH>
</pre>

To view a nested JSON object within a JSON file:

<pre>
./build/view_json <JSON_PATH> [JSON_KEY1] [JSON_KEY2] ...
</pre>

- `<JSON_PATH>`: The path to the JSON file.
- `[JSON_KEY1] [JSON_KEY2] ...`: Optional JSON keys to navigate nested objects.

## Examples

View a JSON file:

<pre>
./build/view_json data.json
</pre>

View a nested JSON object:

<pre>
./build/view_json data.json person address
</pre>

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
