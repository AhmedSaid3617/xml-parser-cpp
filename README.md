# XML Editor

An advanced XML editor designed to simplify the processing and analysis of XML data. This program comes with a variety of powerful features for handling XML and JSON files, as well as analyzing and visualizing social network data.

## Features

### XML Handling
- **Consistency Check**: Verify the structure and consistency of XML files.
- **Formatting (Prettifying)**: Automatically format XML files for improved readability.
- **XML to JSON Conversion**: Seamlessly convert XML data into JSON format.
- **Space Removal**: Remove unnecessary spaces from XML files for compactness.
- **Data Compression**: Compress XML or JSON files to reduce storage size.
- **Data Decompression**: Decompress previously compressed files.

### Social Network Data Analysis
- **Graph Representation**: Represent social network data using a graph data structure for efficient analysis.
- **Influencer Detection**: Identify the user with the most followers.
- **Activity Analysis**: Find the most active user (connected to the most users).
- **Mutual Followers**: Discover mutual followers among a group of users.
- **Follow Recommendations**: Suggest a list of users to follow for each user based on network connections.

### Post Analysis
- **Keyword Search**: Search for posts containing a specific word or topic and retrieve them efficiently.

### Visualization
- **Graph Visualization**: Visualize the social network graph for intuitive understanding of user connections and influence.

## Installation

This project provides both a GUI application built using Qt and a command-line tool.

### GUI Application
1. Clone the repository:
   ```bash
   git clone https://github.com/AhmedSaid3617/xml-parser-cpp
   ```
2. Navigate to the project directory:
   ```bash
   cd xml-parser-cpp
   ```
3. Open the project in Qt Creator.
4. Build and run the application.

## Usage

### GUI Application
1. Open the application.
2. Use the menu options to perform the desired operations on your XML/JSON data.
3. For social network analysis, load the appropriate dataset and select analysis or visualization tools.

### Command-Line Tool
1. Run the tool from the command line and provide the necessary arguments for the desired operation. For example:
   ```bash
   xml_editor compress -i input_file.xml -o output_file.xml
   ```

## Examples

### Prettifying XML
Input:
```xml
<root><child>value</child></root>
```
Output:
```xml
<root>
    <child>value</child>
</root>
```

### Converting XML to JSON
Input:
```xml
<user>
    <id>1</id>
    <name>John Doe</name>
</user>
```
Output:
```json
{
    "user": {
        "id": 1,
        "name": "John Doe"
    }
}
```