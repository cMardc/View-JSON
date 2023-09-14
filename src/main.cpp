#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#define USAGE_ERROR 1
#define NOT_A_JSON 2
#define OPENING_ERROR 3
#define PARSE_ERROR 4
#define NOT_AN_OBJECT 5

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

void printTable(const vector<vector<string>>& tableData) {
  if (tableData.empty()) {
    cout << "Table is empty." << '\n';
    return;
  }

  // Calculate column widths
  vector<size_t> colWidths(tableData[0].size(), 0);
  for (const auto& row : tableData) {
    for (size_t i = 0; i < row.size(); ++i) {
      if (row[i].length() > colWidths[i]) {
        colWidths[i] = row[i].length();
      }
    }
  }

  // Calculate total table width
  size_t totalWidth = 1;  // Start with 1 for the left border
  for (size_t width : colWidths) {
    totalWidth += width + 3;  // Add 3 for cell content, right border, and space
  }

  // Print table top border
  cout << "+";
  for (size_t i = 0; i < totalWidth - 2; ++i) {
    cout << "-";
  }
  cout << "+" << '\n';

  // Print table rows
  for (size_t i = 0; i < tableData.size(); ++i) {
    cout << "| ";
    for (size_t j = 0; j < tableData[i].size(); ++j) {
      cout << left << setw(colWidths[j]) << tableData[i][j] << " | ";
    }
    cout << '\n';

    // Print header-row separator after the first row
    if (i == 0) {
      cout << "+";
      for (size_t k = 0; k < totalWidth - 2; ++k) {
        cout << "-";
      }
      cout << "+" << '\n';
    }
  }

  // Print table bottom border
  cout << "+";
  for (size_t i = 0; i < totalWidth - 2; ++i) {
    cout << "-";
  }
  cout << "+" << '\n';
}

string formatJsonValue(const json& value) {
  if (value.is_string()) {
    return value.get<string>();
  } else if (value.is_number()) {
    double number = value.get<double>();
    if (number == static_cast<int>(number)) {
      return std::to_string(static_cast<int>(number));
    } else {
      std::ostringstream ss;
      ss << std::fixed << std::setprecision(2) << number;
      return ss.str();
    }
  } else if (value.is_boolean()) {
    return value.get<bool>() ? "True" : "False";
  } else if (value.is_object()) {
    return "(JSON)";
  } else {
    return "N/A";
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <JSON_PATH> [JSON_KEY] ..." << '\n';
    return USAGE_ERROR;
  }

  const char* jsonPath = argv[1];

  if (fs::path(jsonPath).extension() != ".json") {
    cerr << "The provided file is not a JSON file (extension is not .json)."
         << '\n';
    return NOT_A_JSON;
  }

  ifstream file(jsonPath);
  if (!file.is_open()) {
    cerr << "Failed to open JSON file." << '\n';
    return OPENING_ERROR;
  }

  json jsonData;

  try {
    file >> jsonData;
  } catch (json::exception& e) {
    cerr << "Failed to parse JSON: " << e.what() << '\n';
    return PARSE_ERROR;
  }

  for (int i = 2; i < argc; ++i) {
    string jsonKey = argv[i];
    if (jsonData.find(jsonKey) != jsonData.end() &&
        jsonData[jsonKey].is_object()) {
      // Display the nested JSON object
      jsonData = jsonData[jsonKey];
    } else {
      cerr << "The specified JSON key is not found or does not contain a JSON "
              "object."
           << '\n';
      return NOT_AN_OBJECT;
    }
  }

  vector<vector<string>> tableData;

  vector<string> row_V;
  row_V.push_back("Key");    // Use the member name as the key
  row_V.push_back("Value");  // Format the JSON value

  tableData.push_back(row_V);
  // Convert the JSON object into a table
  for (json::iterator it = jsonData.begin(); it != jsonData.end(); ++it) {
    vector<string> row;
    row.push_back(it.key());  // Use the member name as the key
    row.push_back(formatJsonValue(it.value()));  // Format the JSON value

    tableData.push_back(row);
  }

  // Print the table
  printTable(tableData);

  return 0;
}
