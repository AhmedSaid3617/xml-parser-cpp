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

# Console

write here

# GUI using QT

write here
