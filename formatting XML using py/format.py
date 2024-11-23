from xml.dom.minidom import parseString
import xml.etree.ElementTree as ET

xml_string = """
<users>
<user>
<id>1
</id>
<name>
user1</name>
<posts>
<post>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.</post>
<post>Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</post>
</posts>
<followers>
<follower><id>2</id></follower>
<follower>
<id>4
</id></follower>
</followers>
</user>
</users>"""

# Parse and prettify XML
def ident_xml(xml_string):
    # Parse the XML string to an ElementTree and then prettify using minidom
    dom = parseString(ET.tostring(ET.fromstring(xml_string)))
    return dom.toprettyxml(indent="  ")

# Pretty XML output
XML = ident_xml(xml_string)
print(XML)

# Save the prettified XML to a file
with open('GO_output.xml', 'w') as f:
    f.write(XML)
