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

## validateXML

### Purpose:
This function validates a sequence of XML tags provided in a vector. It ensures the XML structure adheres to standard rules, such as proper nesting and matching of opening and closing tags. The function identifies errors and assigns corrective information to the relevant tag.

---

### Parameters:
- **`vector<Tag> &tags`**: A reference to a vector of `Tag` objects. Each `Tag` contains the following attributes:
  - `name`: The name of the tag.
  - `opening`: A boolean indicating if the tag is an opening tag (`true`) or closing tag (`false`).
  - `line_to_be_fixed`: An integer used to store error correction metadata.
  - `index`: The position of the tag in the vector.

---

### Process:
1. **Initialization**:
   - `tokens`: A stack to track unmatched opening tags.
   - `flag`: A boolean to check if a mismatched closing tag has a corresponding opening tag elsewhere in the vector.
   - `index`: Holds the index of a problematic tag, initialized to `-1`.

2. **Validation Rules**:
   - If the first tag is a closing tag:
     - Set `line_to_be_fixed` to `-3` for the tag.
     - Return `0` to indicate invalid XML.
   - Iterate through the `tags` vector:
     1. **Empty Stack with Closing Tag**:
        - If a closing tag is encountered and the stack is empty:
          - Set `line_to_be_fixed` to `-2` for the tag.
          - Return the tag's `index`.
     2. **Consecutive Identical Tags**:
        - If two identical tags are consecutive and both are either opening or closing:
          - For consecutive closing tags, set `line_to_be_fixed` to `-5` and return the `index`.
          - For consecutive opening tags, set `line_to_be_fixed` to `-6` and return the `index`.
     3. **Opening Tags**:
        - Push the tag onto the stack.
     4. **Matching Tags**:
        - If a closing tag matches the name of the tag on top of the stack, pop the stack.
     5. **Mismatched Tags**:
        - If a closing tag does not match the tag on top of the stack:
          - Search for its matching opening tag in the remaining `tags`.
          - If found:
            - Assign `line_to_be_fixed` for the mismatched closing tag as the line number of the unmatched opening tag.
            - Return the `index` of the closing tag.
          - If not found:
            - Mark the opening tag on top of the stack as the problematic tag.
            - Set its `line_to_be_fixed` to the line number of the mismatched closing tag.
            - Return the `index` of the opening tag.

3. **Unclosed Tags**:
   - After iterating through all `tags`, if the stack is not empty:
     - Mark the last unmatched opening tag as problematic.
     - Set its `line_to_be_fixed` to `-4` (indicating a missing closing tag).
     - Return the `index` of the unmatched opening tag.

---

### Return Value:
- Returns the `index` of the first problematic tag based on the validation rules.
- Returns `0` if the first tag is invalid.
- Returns `-1` if the XML is valid and no unmatched tags are found.

---

### Edge Cases:
1. The first tag is a closing tag.
2. Multiple unmatched tags.
3. A closing tag mismatches the tag on top of the stack but matches one later in the vector.
4. An opening tag without a corresponding closing tag.

---

### Time Complexity:
- **`O(n^2)`** in the worst case:
  - The inner loop for searching mismatched tags makes this quadratic.
- **`O(n)`** in typical cases:
  - Each tag is processed once, and stack operations are \(O(1)\).

---

### Notes:
- The `line_to_be_fixed` attribute is used for corrective suggestions, indicating where fixes should be made in the XML structure.

## fix_error

### Purpose:
This function attempts to fix an XML error in a given set of lines based on the error information provided in the `tags` vector. It modifies the `lines` vector to correct the issue.

---

### Parameters:
1. **`vector<string> &lines`**:
   - A reference to a vector of strings representing the lines of the XML document.

2. **`vector<Tag> &tags`**:
   - A reference to a vector of `Tag` objects. Each `Tag` contains information about the XML structure, such as:
     - `name`: The name of the tag.
     - `opening`: A boolean indicating if the tag is opening (`true`) or closing (`false`).
     - `line`: The line number of the tag in the XML document.
     - `line_to_be_fixed`: Indicates the type of error to correct.

3. **`int error_index`**:
   - The index of the `Tag` in the `tags` vector that represents the error to be fixed.

---

### Process:
1. Retrieve the `Tag` causing the error using `error_index`.
2. Determine the type of error based on `error.line_to_be_fixed`:
   - **`-3` (First tag is closing):**
     - If the error tag matches the last tag, remove the first erroneous tag from `lines[0]`.
     - Otherwise, insert the correct opening tag at the beginning of `lines`.

   - **`-5` (Duplicate closing tag):**
     - Remove the duplicate closing tag from `lines[error.line - 1]`.

   - **`-6` (Duplicate opening tag):**
     - Locate the position of the opening `<` and insert a `/` to convert it into a closing tag.

   - **`-4` (Unmatched opening tag):**
     - If the error tag matches the first tag, add a `/` to convert it into a closing tag.
     - Otherwise, append the correct closing tag to the end of `lines`.

   - **`-2` (Unmatched closing tag):**
     - If the error is at the last index, insert the correct opening tag at the beginning of `lines`.
     - Otherwise, insert the correct opening tag at the corresponding position.

   - **Positive values (Mismatched tag):**
     - If the error is in an opening tag, insert the corresponding closing tag at `line_to_be_fixed - 1`.
     - If the error is in a closing tag, insert the corresponding opening tag after the error line.

---

### Return Value:
- **`void`**: The function modifies the `lines` vector directly to fix the error.

---

### Edge Cases:
1. The first tag is a closing tag (`-3`).
2. Duplicate tags (`-5` or `-6`).
3. Unmatched opening or closing tags (`-4` or `-2`).
4. Mismatched tags (`line_to_be_fixed > 0`).

---

### Time Complexity:
- **`O(m + n)`**, where:
  - `m` is the length of the longest string in `lines` (for string operations like insert and erase).
  - `n` is the number of lines in `lines` (for inserting new lines).

---

## verify

### Purpose:
This function verifies the structural validity of an XML string. It identifies if the XML contains any structural issues (e.g., unmatched tags, improper nesting) and returns the line number of the first error, if found.

---

### Parameters:
- **`string XML`**: A string containing the XML document to be validated.

---

### Process:
1. **Tokenization**:
   - Initialize a `vector<Tag>` called `tokens` to store XML tags.
   - Use the `tokenizeXML` function to parse the `XML` string and populate `tokens` with tag information.

2. **Validation**:
   - Call the `validateXML` function with the `tokens` vector:
     - If the XML is valid (`index == -1`), return `-1`.
     - If invalid, retrieve the error index from `validateXML`.

3. **Error Line Retrieval**:
   - Use the error index to find the corresponding tag in `tokens`.
   - Return the line number (`tokens[index].line`) of the problematic tag.

---

### Return Value:
- **`-1`**: Indicates that the XML is valid and contains no structural issues.
- **`int`**: The line number of the first error in the XML, if found.

---

### Time Complexity:
- **`O(n)`**, where `n` is the length of the XML string:
  - Tokenization (`tokenizeXML`) and validation (`validateXML`) process each character of the XML once.

---

## fix_file

### Purpose:
The `fix_file` function attempts to correct structural errors in an XML string recursively. It ensures that the XML string is valid by fixing one error at a time until all issues are resolved.

---

### Parameters:
- **`string XML`**:
  - A string containing the XML document to be validated and potentially corrected.

---

### Process:
1. **Initialization**:
   - Create a `vector<string>` named `lines` to store individual lines of the XML.
   - Create a `vector<Tag>` named `tokens` to store parsed XML tags.
   - Initialize an empty `string` named `data` for constructing the corrected XML.

2. **Tokenization and Line Splitting**:
   - Use `tokenizeXML` to parse `XML` and populate `tokens` with tag information.
   - Use `stringToLines` to split `XML` into separate lines and store them in `lines`.

3. **Validation**:
   - Call `validateXML` with `tokens`:
     - If the XML is valid (`index == -1`), return the input `XML` as it needs no further corrections.

4. **Error Correction**:
   - If an error exists (`index != -1`), call `fix_error` to correct the issue in `lines` using `tokens` and the error index.

5. **Reconstruction**:
   - Reconstruct the corrected XML string by concatenating the lines in `lines` with newline characters.

6. **Recursion**:
   - Recursively call `fix_file` with the reconstructed XML (`data`) to check for and fix any remaining errors.

7. **Termination**:
   - The recursion terminates when `validateXML` returns `-1`, indicating no errors remain.

---

### Return Value:
- **`string`**:
  - The corrected XML string after all errors have been resolved.

---

### Time Complexity:
- **`O(n * m)`**, where:
  - `n` is the number of tags in the XML.
  - `m` is the number of recursive calls required to fix all errors (one per error).

---

### Notes:
- The function uses recursion to handle errors one at a time.
- Care must be taken to avoid stack overflow with deeply nested or heavily erroneous XML files.

---
## Format

Kareem : Formatted json

---
## Tree

Kareem - abdo - shams

---
## Convert XML to Tree

Kareem - abdo - shams

---
## Hashtable

write here

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
   
   - **Verify**:
     - If the `verify` operation is chosen, the program validates the XML file. If errors are found, it fixes them using the `fix_file()` function. The corrected file is saved to the specified output path.
   
   - **Format**:
     - The `format` operation formats the XML file to make it human-readable. The formatted file is saved to the specified output path.

   - **JSON**:
     - The `json` operation converts the XML file into JSON format and saves it to the output path.

   - **Mini**:
     - The `mini` operation minifies the XML file by removing unnecessary whitespaces and line breaks, then saves the minified version.

   - **Compress**:
     - The `compress` operation minifies the XML and compresses it, then saves the compressed XML.

   - **Decompress**:
     - The `decompress` operation decompresses the XML file, formats it, and saves the formatted version.

   - **Social Network Operations**:
     - The program allows various operations related to a social network, including:
       - **Mutual Followers**: Finds mutual followers of specified users.
       - **Suggest Users**: Suggests users to follow based on a given user.
       - **Search Posts**: Searches for posts based on keywords or topics.
       - **Most Active User**: Finds the most active user in the social network.
       - **Most Influential User**: Finds the most influential user in the social network.
       - **Draw**: If the `GRAPH_VIZ` flag is enabled, it generates a visualization of the social network graph.

---

### Return Value:
- **`int`**:
  - The return value of the program is typically `0`, indicating successful execution. If errors occur during the processing of the XML file or social network operations, appropriate messages are displayed to the user.

---

### Edge Cases:
1. **Invalid Command-Line Arguments**:
   - If the arguments are invalid or missing, the program prints usage instructions and exits.
   
2. **Empty XML File**:
   - If the XML file cannot be read or is empty, the program prints an error message and exits.

3. **Unsupported Operations**:
   - If an unsupported operation is passed, the program prints an error message.

4. **Social Network Operation Errors**:
   - If there are invalid user IDs or no matching results for searches or suggestions, the program prints an appropriate error message.

---

### Time Complexity:
- **`O(n)`**, where `n` is the size of the input XML file or the number of operations in the social network, depending on the chosen operation.

---

# GUI using QT

write here
