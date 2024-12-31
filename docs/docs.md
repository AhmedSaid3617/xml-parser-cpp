---
title: "CSE331s -- Data Structures and Algorithms"
subtitle: "Project Report"
author:
  - "Yousef Mahmoud Mohamed -- 2100994"
  - "Kareem Gaber El Halaby -- 2101545"
  - "Omar Tamer Mohamed -- 2100528"
  - "Mohamed Hussien Mansour -- 2100919"
  - "Fares Khalaf Salman Sultan -- 2101371"
  - "Shams El-Din Mohamed Abdel-Monem -- CSE 2101442"
  - "Abdel-Rahman Sherif -- CSE 2100735"
  - "Ahmed Said Sayed -- CSE 2101546"
date: "January 1, 2025"
geometry: a4paper
fontsize: 12pt
linestretch: 1.5
header-includes:
  - \usepackage{float}
---

---

\newpage

| **Student**                    | **Contribution**                                    |
|--------------------------------|-----------------------------------------------------|
| **Yousef Mahmoud Mohamed**     | Formatting XML                                      |
| **Kareem Gaber El Halaby**     | Tree Data Structure and JSON Formatting             |
| **Omar Tamer Mohamed**         | Console Front-end and XML Consistency               |
| **Mohamed Hussien Mansour**    | Compression, XML Minify                             |
| **Fares Khalaf Salman Sultan** | XML Check, Social Network Algorithms                |
| **Shams El-Din Mohamed**       | XML Tree to JSON, Graph, Graph Visualization        |
| **Abdel-Rahman Sherif**        | Hashtable Data structure, Social Network Algorithms |
| **Ahmed Said**                 | GUI Front-end, User and Post encapsulated classes   |


# GitHub and Video Links

[GitHub Repo](https://github.com/AhmedSaid3617/xml-parser-cpp)

[Video](https://drive.google.com/drive/folders/1qTJ10HcB0t2p3L8tXQt3FFvpTsUe8v2H?usp=sharing)

---

\newpage

\tableofcontents

\newpage

# Abstract
## XML Parser and Social Network analyzer

Project consists of three main parts:
- Core: The main algorithms, data structures, data and utility classes and encapsulation are present
- Console: The Console interface *Front-end* that interfaces with the *Core* part through clean and intuitive interfaces
- GUI: The Graphical-User Interface implemented using QT, that also interfaces with *Core* part.
- Tests: A group of seperate tests using vanilla C++ and `CTest`, an attempt was made to use `Google Test` but we didn't proceed to have minimal impact on Team.

Dependencies:
- QT6 Libraries for GUI
- Graphviz library for graph visualization and export

Different parts are developed separately and interfaces are agreed on, design patterns were used as much as possible and general clean code was practiced as much as possible.

Also, a fully functional `CMakeLists.txt` is maintained and is used for debuggung, running and compiling.

Variables are needed in the `CMakeLists.txt` to be able to run everything

```shell
-DCOMPILE_GUI_QT_GCC_64_FOLDER=/home/path/to/Qt/6.8.0/gcc_64
-DCOMPILE_GUI=1 -DCOMPILE_GVC=1 -DGRAPHVIZ_INCLUDE_DIR=/usr/include/graphviz
-DGRAPHVIZ_LIBRARIES=/usr/lib64/libgvc.so;/usr/lib64/libcgraph.so
```

\newpage

# Core

## XML Consistency

### tokenizeXML

#### Purpose:
This function tokenizes an XML string by identifying and extracting tags (enclosed within `<` and `>`) and stores the result in a vector of `Tag` objects.

#### Parameters:
- `string &XML_data`: The XML string to be tokenized.
- `vector<Tag> &TokenizedXML`: A reference to a vector where the tokenized tags will be stored.

#### Process:
##### Initialization:
- `name`: A string to hold the tag being processed.
- `line`: Tracks the current line number (starts at 1).
- `index`: Tracks the tag index in the `TokenizedXML` vector.

##### Iterate Through `XML_data`:
1. For every character:
    - If it is a newline (`'\n'`), increment the `line` counter.
    - If it is a `<`, start extracting the tag:
        - Continue until the closing `>` is found.
        - Append all characters to `name` during this process.
2. Once a complete tag is formed:
    - Create a `Tag` object with the tag name, current line number, and tag index.
    - Add it to the `TokenizedXML` vector.
    - Clear the `name` variable for the next tag.

#### Return Value:
The tokenized tags are stored in `TokenizedXML`.


- **Time complexity:** (O(n)), where (n) is the size of `XML_data`.


---

### stringToLines

#### Purpose:
This function splits an XML string into separate lines, storing each line as an element in a vector.

#### Parameters:
- `string &XML`: The XML string to be split.
- `vector<string> &LinedXml`: A reference to a vector where the lines will be stored.

#### Process:
##### Initialization:
- `line_number`: Tracks the current line index (starts at 0).
- `LinedXml`: Initialized with an empty string for the first line.

##### Iterate Through `XML`:
1. For every character:
    - If it is not a newline (`'\n'`), append it to the current line.
    - If it is a newline:
        - Increment the `line_number`.
        - Start a new line in `LinedXml`.

#### Return Value:
The split lines are stored in `LinedXml`.

- **Time complexity:** (O(n)), where (n) is the size of `XML`.
- Processes each character once.

#### Notes:
- The `line_to_be_fixed` attribute is used for corrective suggestions, indicating where fixes should be made in the XML structure.

---

## XML Formatting

### **generateIndentation**

#### **Purpose:**
Generates a string containing repeated spaces based on the specified indentation level.

#### **Parameters:**
- **`const string& space`**: A reference to a string representing the unit of indentation (e.g., "    " for 4 spaces).
- **`int level`**: The number of indentation levels.

#### **Process:**
1. Initialize an empty string `result`.
2. Use a `for` loop that iterates from 0 to `level - 1`.
    - Append the `space` string to `result` in each iteration.
3. Return the concatenated string.

#### **Return Value:**
- A string containing `level` repetitions of the `space` string.

#### **Complexity:**
- **Time complexity:** (O(m . n)), where (m) is the size of `space` and (n) is the `level`.
- **Space complexity:** (O(m . n)), for storing the resulting string.


---

## Tree Data Structure
### **TreeNode Class**

The `TreeNode` class represents the core data structure for storing hierarchical information, such as that found in XML documents. Each `TreeNode` corresponds to an XML element, containing its tag name, value, parent, and children.

* * * * *

#### **TreeNode Class Overview**

1.  **Attributes**:

    -   `std::string tag_name`: Name of the XML tag
    -   `std::string tag_value`: Content inside the tag
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

#### **Tree to JSON Conversion**

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

### Project Description: Byte Pair Encoding (BPE) Compression

This C++ program implements **Byte Pair Encoding (BPE)** for compressing and decompressing data, with additional features for file handling and data storage. 

#### **How it Works:**

1. **Compression Process:**
   - **Minification:** Removes spaces and newlines from the input to reduce size.
   - **Frequency Calculation:** Identifies the most frequent byte pairs in the text.
   - **Pair Replacement:** Replaces frequent pairs with unique tokens (starting from ASCII 128).
   - **Mapping Storage:** Tracks token-to-pair mappings in a hash table for later decompression.
   - The compression terminates after replacing 150 pairs or when no significant patterns remain.

2. **Decompression Process:**
   - **Token Replacement:** Iteratively replaces tokens with their corresponding pairs using a stack to ensure reverse-order replacement.
   - **Reconstruction:** Gradually reconstructs the original text.

3. **File Handling:**
   - The compressed text, mappings, and tokens are saved into a file.
   - Loading functions parse these components for decompression or reuse.

4. **Helper Functions:**
   - `readFile`: Reads input data from a file.
   - `writeStringToFile`: Saves compressed data to a file.
   - `loadData`: Parses compressed data into a usable structure.

#### **Time Complexity:**
- **Compression:** \(O(n^2)\)  
  Calculating frequencies for \(n\)-length text involves \(O(n)\) per replacement. Multiple replacements depend on pair occurrences.
- **Decompression:** \(O(n^2)\)  
  Token replacement checks every substring against mappings.

#### **Space Complexity:**
- \(O(n + m + t)\), where:
  - \(n\): Original text size.
  - \(m\): Mapping size.
  - \(t\): Stack size.

### Compression Ratio
When testing on a 15 MB file, the  compressed file was 2.9MB for a total of 80.67% lossless compression.

This efficient BPE implementation is suitable for applications needing lightweight compression, like XML minification or preprocessing large datasets.

---

## Data

This code defines two classes, and encapsulates any intuitive functionalities needed, **`User`** and **`Post`**, for managing social network users and their posts.

---

#### **`User` Class:**
Represents a user in the network with an `id`, `name`, and a list of posts. It includes a parameterized constructor for initialization and grants access to its private members to the **`SocialNetwork`** class.

---

#### **`Post` Class:**
Represents a post made by a user, with a `body` and associated `topics`. It includes a method `contains()` to check if the post body contains a given string. The **`User`** and **`SocialNetwork`** classes have access to its private members.

---

### Key Design Aspects:
1. **Encapsulation**: Both classes encapsulate data, exposing only necessary methods.
2. **Friendship**: **`SocialNetwork`** class can access private data to manage relationships and interactions.
3. **Separation of Concerns**: Clear distinction between user data (`User`) and post data (`Post`), ensuring modularity.

---

## Graph
### Brief

Adjacency List Implementation was chosen, as it was determined that graph would be more sparse than being more dense.

For handling followers and followee a trick was used, we used Undirected graph, but the "tuples" used to define an edge are used in way where `(a, b)` is not like `(b, a)` this way we can exploit this feature, and it was agreed that

```c++
Edge<User>(User_A, User_B); // Means User A follows --> user B
```

This way we can access all followers and all followee's of any user in `O(N)` time, where `N` is number of incident relations in that user, *Not the total number of users*, this gives us greater performance.

### Some Functions Time Complexity

#### Graph<T>::Graph(uint32_t capacity)**

*   **Description:** Constructs a new graph with an initial capacity for vertices.
*   **Time Complexity:** O(1) - Constant time.

#### Graph<T>::add_vertex(T* vertex)**

*   **Description:** Adds a new vertex to the graph and returns its key.
*   **Time Complexity:**
    *   Best Case: O(1) - If there is enough space in the underlying array.
    *   Worst Case: O(n) - If the array needs to be resized to accommodate the new vertex.

#### Graph<T>::get_vertex(graph_key_t key)**

*   **Description:** Retrieves the vertex associated with the given key.
*   **Time Complexity:** O(1) - Constant time access using the key.

#### Graph<T>::add_edge(Edge<T>* edge)**

*   **Description:** Adds an edge to the graph, connecting the two vertices involved.
*   **Time Complexity:** O(1) or worst case O(N) number of already present edges in that relation.


### Graph Key
To differentiate graph node id, and user normal id, a "pair" like struct was used called `user_id_graph_key_t` to make sure a compile error is thrown if someone tries to use user id in an operation that needs graph id.

---

## Social Network

The SocialNetwork class, inheriting from Graph<User>, is designed to represent and manage data extracted from social network XML files. As a specialized graph, it encapsulates the relationships and interactions between User objects as nodes and edges. The class provides functionality to:

1. Store Users and Relationships: Each User represents an individual with relevant attributes (e.g., ID, name, metadata), and edges define their connections (e.g., friendships or interactions).
2. Support Visualizations: By integrating seamlessly with visualization modules, the class enables generating clear graphical representations of the social network.
3. Dynamic Updates: The class supports adding, removing, and updating users and relationships dynamically based on the extracted XML data.

This design ensures that the SocialNetwork class is both versatile and efficient for analyzing and visualizing social network data.

### extract_data

The `extract_data` function processes XML input to populate the social network with users and their relationships. It works as follows:

1. **Parse XML into a Tree Structure**:
    - An `XML_To_Tree2` object converts the XML string into a tree structure with `TreeNode` objects.
    - The `children` of the root node are accessed to retrieve nodes corresponding to individual users.

2. **Extract User Information**:
    - For each user node:
        - A `User` object is created and populated with attributes like `name` and `id` by iterating through its children tags.
        - Posts are extracted from the `posts` tag, with each post containing a body and associated topics. These posts are stored in the user's post list and the global list of posts.

3. **Add Users to the Network**:
    - Each `User` object is added to the social network graph.

4. **Add Followers to the Network**:
    - The function loops through the user nodes again to extract and add follower-followee relationships. This is achieved by retrieving follower IDs and associating them with the corresponding followee IDs.

This method ensures that the social network is populated with complete user data and connections derived from the provided XML.

This function works in O(N) where N is the number of users + posts + topics + tags  + followers for this xml file.

### `suggest_users_to_follow`

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

- **Time complexity:** (O(n . m)), where:
    - (n): Number of first-degree connections.
    - (m): Average number of second-degree connections for each user.
- The `unordered_set` ensures (O(1)) lookup for checking duplicate IDs.

---

# Console Front-end
## `main` Function
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

The XML editor built with Qt enables users to analyze and visualize data related to social networks. It provides tools to parse and edit XML files, extract relevant social network data, and generate visual representations such as graphs or charts. These visualizations help users interpret relationships, connections, and trends within the data. The application combines XML manipulation with an intuitive user interface and powerful visualization features.

It contains an editor text box and buttons that call the various functions developed throughout this project. It can also handle file read write operations in a visually intuitive way.

Each of the buttons has a slot that corresponds to a function that calls one of the back-end functions.

# Visualization using Graphviz

Graphviz library was used to visualize graph, it is simple had documentation and examples available easily.

A `GraphVisualizationSocialNetworkVisitor` abstract class was made, and it followed **Visitor** design pattern to allow adding functionality to the `SocialNetwork` class without changing the class directly.

`FileExportGraphVisualization` is a concrete Visitor that visits Social Network class and exports into a file directly.

`QImageGraphVisualiztion` is a concrete Visitor that visits Social Network and returns a `QImage` to be used within QT GUI to show the graph.