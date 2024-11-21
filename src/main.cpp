#include <iostream>
#include "../inc/main.h"

string XMLFile =
 "<users><user><id>1</id><name>Ahmed Ali</name><posts><post><body>Lorem ipsum dolor sit amet, /consectetur adipiscing elit, /sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, /quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topics></post><post><body>Lorem ipsum dolor sit amet, /consectetur adipiscing elit, /sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, /quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>solar_energy</topic></topics></post></posts><followers><follower><id>2</id></follower><follower><id>3</id></follower></followers></user><user><id>2</id><name>Yasser Ahmed</name><posts><post><body>Lorem ipsum dolor sit amet, /consectetur adipiscing elit, /sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, /quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>education</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user><user><id>3</id><name>Mohamed Sherif</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>sports</topic></topics></post></posts><followers><follower><id>1</id></follower></followers></user></users>";


int main(){

    string xml = "<t1>\n<t2>\nhi\n</t2>\n</t1>\n"; 
    vector<string> linedXML{100};

    stringToLines(xml, linedXML);

    for(int i=0;i<linedXML.size();i++) 
    cout<< linedXML[i]<<endl;
    return 0;
}
