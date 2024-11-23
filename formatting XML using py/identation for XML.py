def prettify_xml(xml_string, output_file):
    
    result = []
    indent_level = 0
    indent_space = "   "
    
    # Splitting xml to to tokens
    tokens = xml_string.replace(">", ">\n").replace("<", "\n<").split("\n")
    tokens = [token.strip() for token in tokens if token.strip()]
    
    i = 0
    while i < len(tokens):
        
        token = tokens[i]
        modified_token = indent_space * indent_level + token
        
        if token.startswith("</"):  # Closing tag
            indent_level -= 1
            result.append(modified_token)
            
        elif token.startswith("<") and not token.endswith("/>"):  # Opening tag
        
                result.append(modified_token)
                indent_level += 1
                
        else:  # Content 
            result.append(modified_token)
            
        i += 1
    
    pretty_xml = "\n".join(result)
    
    # Save to a file
    with open(output_file, "w") as file:
        file.write(pretty_xml)
    
    return pretty_xml

# Example XML string
xml_string = """<users>
<user>
<id>
1
</id>
<name>
user1
</name>
<posts>
<post>
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.</post><post>Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.
</post>
</posts>
<followers>
<follower>
<id>2</id>
</follower>
<follower>
<id>4
</id>
</follower>
</followers>
</user>
</users>"""

# Prettify the XML 
output_file = "modified_XML.xml"
pretty_xml = prettify_xml(xml_string, output_file)

print(f"Formatted XML saved to {output_file}")
