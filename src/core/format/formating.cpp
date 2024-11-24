#include "formatting.h"
#include "tree/tree.h"

using namespace std;

string erase_unwanted_chars(string str, bool erase_white_space) {
    vector<char> sequences = { '\a','\b','\r','\n','\v','\t' };
    for (int i = 0; i < str.length(); ++i) {
        for (char seq : sequences) {
            if (erase_white_space) {
                while (str[i] == ' ' && (str[i + 1] == ' ')) {
                    str.erase(i, 2);
                }
            }
            if (str[i] == seq) {
                str.erase(i, 1);
                while (str[i] == ' ' && (str[i + 1] == ' ')) {
                    str.erase(i, 2);
                }
                i--;
                break;
            }
        }
    }
    return str;
}
string format_newLine(string str, int level, int maxChar) {
    string new_str = "";
    for (int i = 0; i < str.length(); ++i) {
        if ((i + 1) % maxChar != 0) new_str += str[i];
        else {
            int j = 20;
            while (str[i] != ' ' && j != 0) {
                new_str += str[i];
                i++;
                j--;
                if (i == str.length() - 1) break;
            }
            new_str += "\n" + insert_taps(level) + str[i];
        }
    }
    return new_str;
}