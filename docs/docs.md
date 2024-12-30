# Abstract
## XML Parser and Social Network analyzer

write here

# Core

### Consistency

# tokenizeXML

## Purpose:
This function tokenizes an XML string by identifying and extracting tags (enclosed within `<` and `>`) and stores the result in a vector of `Tag` objects.

## Parameters:
- `string &XML_data`: The XML string to be tokenized.
- `vector<Tag> &TokenizedXML`: A reference to a vector where the tokenized tags will be stored.

## Process:
### Initialization:
- `name`: A string to hold the tag being processed.
- `line`: Tracks the current line number (starts at 1).
- `index`: Tracks the tag index in the `TokenizedXML` vector.

### Iterate Through `XML_data`:
1. For every character:
   - If it is a newline (`'\n'`), increment the `line` counter.
   - If it is a `<`, start extracting the tag:
     - Continue until the closing `>` is found.
     - Append all characters to `name` during this process.
2. Once a complete tag is formed:
   - Create a `Tag` object with the tag name, current line number, and tag index.
   - Add it to the `TokenizedXML` vector.
   - Clear the `name` variable for the next tag.

## Return Value:
The tokenized tags are stored in `TokenizedXML`.


- **Time complexity:** \(O(n)\), where \(n\) is the size of `XML_data`.



---

# stringToLines

## Purpose:
This function splits an XML string into separate lines, storing each line as an element in a vector.

## Parameters:
- `string &XML`: The XML string to be split.
- `vector<string> &LinedXml`: A reference to a vector where the lines will be stored.

## Process:
### Initialization:
- `line_number`: Tracks the current line index (starts at 0).
- `LinedXml`: Initialized with an empty string for the first line.

### Iterate Through `XML`:
1. For every character:
   - If it is not a newline (`'\n'`), append it to the current line.
   - If it is a newline:
     - Increment the `line_number`.
     - Start a new line in `LinedXml`.

## Return Value:
The split lines are stored in `LinedXml`.

- **Time complexity:** \(O(n)\), where \(n\) is the size of `XML`.
- Processes each character once.


---

// validateXML - Summary

/*
Purpose:
Validates XML tags in a vector, ensuring proper nesting and matching. Flags errors with metadata.

Parameters:
- vector<Tag> &tags: Contains:
  - name: Tag name.
  - opening: True for opening tag, false for closing.
  - line_to_be_fixed: Stores correction info.
  - index: Position in the vector.

Process:
1. Use a stack to track unmatched opening tags.
2. Validation:
   - First tag closing: Set `line_to_be_fixed = -3`, return 0.
   - Empty stack with closing tag: Mark as `-2`, return index.
   - Consecutive identical tags: Mark as `-5` (closing) or `-6` (opening), return index.
   - Mismatched tags: Flag error, set `line_to_be_fixed`, return problematic index.
3. Unclosed tags: Mark as `-4`, return index.

Return:
- Index of first problematic tag, 0 if invalid start, -1 if valid XML.

Time Complexity:
- O(n^2) worst case (nested searches), O(n) typical (stack processing).
*/


### Notes:
- The `line_to_be_fixed` attribute is used for corrective suggestions, indicating where fixes should be made in the XML structure.

// fix_error - Summary

/*
Purpose:
Corrects an XML error in `lines` based on error details in `tags`.

Parameters:
1. vector<string> &lines: XML document lines.
2. vector<Tag> &tags: Contains tag metadata (name, type, line, error info).
3. int error_index: Index of the problematic tag in `tags`.

Process:
1. Retrieve the error tag using `error_index`.
2. Fix based on `line_to_be_fixed`:
   - `-3`: Fix an incorrect first closing tag.
   - `-5`: Remove duplicate closing tag.
   - `-6`: Convert duplicate opening tag to closing.
   - `-4`: Add missing closing tag.
   - `-2`: Add missing opening tag.
   - Positive value: Insert matching opening/closing tag.

Return:
- void: Updates `lines` directly.

Time Complexity:
- O(n): Modifications involve a single line or insertion.
*/

---

// verify - Summary

/*
Purpose:
Checks the structural validity of an XML string and identifies the line number of the first error, if any.

Parameters:
- string XML: The XML document to validate.

Process:
1. Tokenize:
   - Use `tokenizeXML` to parse `XML` into a `vector<Tag>` called `tokens`.
2. Validate:
   - Call `validateXML` with `tokens`.
   - If valid (`index == -1`), return `-1`.
   - If invalid, get the error index.
3. Error Line:
   - Use the error index to find the tag in `tokens` and return its line number.

Return:
- -1: XML is valid.
- int: Line number of the first error.

Time Complexity:
- O(n): Tokenization and validation process each character once.
*/


// fix_file - Summary

/*
Purpose:
Recursively corrects structural errors in an XML string until it becomes valid.

Parameters:
- string XML: The XML document to validate and correct.

Process:
1. Initialize:
   - Split `XML` into `lines` (vector<string>).
   - Parse tags into `tokens` (vector<Tag>) using `tokenizeXML`.
2. Validate:
   - Call `validateXML` with `tokens`.
   - If valid (`index == -1`), return the input `XML`.
3. Correct Errors:
   - If invalid (`index != -1`), use `fix_error` to fix the issue in `lines`.
4. Reconstruct:
   - Combine `lines` into a corrected XML string (`data`).
5. Recur:
   - Call `fix_file` with the corrected XML (`data`) until valid.

Return:
- string: The corrected XML string.

Time Complexity:
- O(n * m), where:
  - n = number of tags in the XML.
  - m = number of recursive calls (errors to fix).
*/

---

## Format
Yousef Mahmoud 

### Consistency

# **generateIndentation**

## **Purpose:**
Generates a string containing repeated spaces based on the specified indentation level.

## **Parameters:**
- **`const string& space`**: A reference to a string representing the unit of indentation (e.g., "    " for 4 spaces).
- **`int level`**: The number of indentation levels.

## **Process:**
1. Initialize an empty string `result`.
2. Use a `for` loop that iterates from 0 to `level - 1`.
   - Append the `space` string to `result` in each iteration.
3. Return the concatenated string.

## **Return Value:**
- A string containing `level` repetitions of the `space` string.

## **Complexity:**
- **Time complexity:** \(O(m . n)\), where \(m\) is the size of `space` and \(n\) is the `level`.
- **Space complexity:** \(O(m . n)\), for storing the resulting string.



---
## Tree
### **TreeNode Class**

The `TreeNode` class represents the core data structure for storing hierarchical information, such as that found in XML documents. Each `TreeNode` corresponds to an XML element, containing its tag name, value, parent, and children.

* * * * *

#### **TreeNode Class Overview**

1.  **Attributes**:

    -   `std::string tag_name`: Name of the XML tag (e.g., `<tag_name>`).
    -   `std::string tag_value`: Content inside the tag (e.g., `<tag_name>tag_value</tag_name>`).
    -   `TreeNode* parent`: Pointer to the parent node.
    -   `std::vector<TreeNode*> children`: A list of pointers to child nodes.
2.  **Constructors**:

    -   `TreeNode()`: Initializes an empty node.
    -   `TreeNode(std::string name, std::string value, TreeNode* parent)`: Initializes a node with a tag name, value, and a pointer to its parent.
    -   `TreeNode(std::string name, std::string value, TreeNode* parent, std::vector<TreeNode*> children)`: Initializes a node with specified children.
3.  **Key Functions**:

    -   **`void set_children(std::vector<TreeNode*> children)`**:
        -   Adds multiple children to the current node.
    -   **`void add_child(TreeNode* child)`**:
        -   Adds a single child to the current node.
    -   **`bool siblings_same_type()`**:
        -   Checks if all sibling nodes under the same parent share the same tag name.
4.  **Static Utility Functions**:

    -   **`TreeNode* Parse_XML(const std::string data)`**:
        -   Parses an XML string and builds a tree structure with `TreeNode` as the root.
    -   **`void Free_XML(TreeNode* root)`**:
        -   Recursively deletes all nodes in the tree to free allocated memory.

* * * * *

#### **Use Cases**

-   Represents and manipulates hierarchical structures like XML documents or JSON objects.
-   Facilitates traversal, querying, and modification of tree structures.

* * * * *

#### **Complexity**

-   **Space Complexity**: O(m) , where m is the number of nodes (each node requires memory for its attributes and children pointers).
-   **Time Complexity**: Dependent on operations:
    -   Adding children or checking sibling properties is O(c) , where c is the number of children.

* * * * *

### **Tree to JSON Conversion**

The functionality to convert a `TreeNode` structure into JSON provides a seamless way to represent hierarchical XML data in a widely-used text-based format.

* * * * *

#### **Key Functions**

1.  **`std::string convert_json(TreeNode* node, bool wrap = true)`**:

    -   Recursively converts a `TreeNode` into its JSON representation.
    -   **Parameters**:
        -   `TreeNode* node`: Root node of the subtree to convert.
        -   `bool wrap`: If true, includes the outermost braces (`{}`) for JSON objects.
    -   **Behavior**:
        -   Nodes with children:
            -   If children share the same tag name, they are represented as an array (`[ ]`).
            -   Otherwise, they are represented as an object with child tag names as keys.
        -   Nodes without children:
            -   Represented as a key-value pair where the key is the tag name, and the value is the tag value.
2.  **`std::string xml_to_json(std::string xml)`**:

    -   Converts an XML string to JSON.
    -   **Steps**:
        -   Parses the XML string into a `TreeNode` tree using `XML_To_Tree2::convert()`.
        -   Converts the tree to JSON using `convert_json(TreeNode*)`.
        -   Cleans up memory by deleting the tree structure.
3.  **`std::string insert_taps(int level):`**:

    -   Generates a formatted string of tabs (`\t`) for JSON indentation. It helps create hierarchical, readable JSON by aligning nested structures appropriately.
    -   **Steps**:
        - Calculates the indentation depth based on the nesting level.
        - Returns a string with the appropriate number of tabs for formatting.

* * * * *

#### **Use Cases**

-   Converting XML data into a JSON format for web APIs or data serialization.
-   Simplifying hierarchical data transformation.

* * * * *

#### **Complexity**

1.  **JSON Conversion**:

    -   **Time Complexity**: O(m) , where m is the number of nodes in the tree (each node is processed once).
    -   **Space Complexity**: O(m) , for recursion stack and JSON string storage.
2.  **XML-to-JSON Conversion (`xml_to_json`)**:

    -   **Time Complexity**: O(n+m) , where nnn is the length of the XML string (parsing time) and mmm is the number of nodes (JSON conversion time).
    -   **Space Complexity**: O(m) , for tree storage and JSON string.
3. **Json Formatting (`insert_taps`)**:

   -   **Time Complexity**: O(level) , where `level` is the number of indentation levels. This is because the function concatenates `level` number of tab characters (`\t`).
   -   **Space Complexity**: O(level) , for storing the resulting string of tabs.
   -   **Note**: This function's impact on overall JSON conversion complexity is minimal, as it's called once per indentation level.
---
## Hashtable

This implementation is a generic hash table using string keys and values of type T2. It handles collisions with separate chaining (linked lists) and uses the FNV-1a hash function for hashing.

Template Class: mypair
- Represents a key-value pair.
- Members: key (T1), value (T2).
- Constructor: Initializes key and value.

Function: fnv1a_hash
- Computes hash for a string using the FNV-1a algorithm.
- Time: O(n). Space: O(1).

Template Class: hash_table
- Fixed capacity (1000). Stores data as an array of linked lists.

Methods:
1. Constructor: Initializes an empty table.
2. Destructor: Cleans up resources.
3. insert(key, value): Adds or updates a key-value pair. Time: O(1) (avg) | O(n) (worst).
4. delete_key(key): Removes a key-value pair. Time: O(1) (avg)| O(n) (worst).
5. operator[]: Accesses/creates value for a key. Time: O(1) (avg)| O(n) (worst).
6. print(): Displays all key-value pairs. Time: O(n).

Time Complexity Summary:
- Insert/Delete/Access: O(1) (average), O(n) (worst).
- Print: O(n).

Space Complexity: O(n) (linked list storage).


---
## Compression

write here

---
## Data

write here

---
## Graph

write here

---
## Social Network

write here

### function1

write here

### function2

write here

### `suggest_users_to_follow` 

## Functionality

### Inputs:
- **`current_user`**: A pointer to the current `User` object for whom we are generating suggestions.

### Outputs:
- A `std::vector` of pointers to `User` objects representing the suggested users to follow.

### Process:
1. **Step 1:** Fetch the list of users that the `current_user` is directly following and add their IDs to a set (`following_set`) to track whom the `current_user` already follows.
2. **Step 2:** Add the `current_user`'s own ID to `following_set` to avoid self-suggestions.
3. **Step 3:** For each user that the `current_user` follows (first-degree connections):
   - Fetch their followings (second-degree connections).
   - Check if these second-degree connections are already in the `following_set`.
   - If not, add them to the `suggestions` list and `following_set` to prevent duplicates.
4. **Return:** The `suggestions` list contains all second-degree connections not already followed by `current_user`.

---

- **Time complexity:** \(O(n \cdot m)\), where:
  - \(n\): Number of first-degree connections.
  - \(m\): Average number of second-degree connections for each user.
- The `unordered_set` ensures \(O(1)\) lookup for checking duplicate IDs.

---


# Console

### Purpose:
The `main` function serves as the entry point for the program, which processes XML files and performs various operations on them. It validates XML files, formats them, converts them to JSON, minifies or compresses them, and processes social network operations, such as finding mutual followers, suggesting users, and searching for posts.

---

### Parameters:
- **`int argc`**:
  - The number of command-line arguments passed to the program.
- **`char *argv[]`**:
  - An array of strings representing the command-line arguments.

---

### Process:

1. **Validate Command-Line Arguments**:
   - The program checks if the command-line arguments are valid using the `validCommand()` function. If the arguments are invalid, it prints the usage instructions and exits.

2. **Help Command**:
   - If the operation is `-help`, the program displays a list of all available commands using the `print_all_commands()` function and exits.

3. **Read XML File**:
   - The program retrieves the XML file path from the command-line arguments using `get_input_path()`.
   - The file contents are then read into a string using `File_to_string()`.

4. **Error Handling**:
   - If the XML file is empty, the program prints an error message (`printWrongArgument()`) and exits.

5. **Operations**:
   - Based on the selected operation (e.g., `verify`, `format`, `json`, `mini`, `compress`, etc.), the program performs the corresponding task.
   - By calling the corresponding function

---

### Time Complexity:
- **`O(n)`**, where `n` is the size of the input XML file or the number of operations in the social network, depending on the chosen operation.

---

# GUI using QT

write here
