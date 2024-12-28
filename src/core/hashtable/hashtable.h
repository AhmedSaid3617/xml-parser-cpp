#include <iostream>
#include <list>
using namespace std;



template<typename T1,typename T2>
class mypair { // the class used as collection of the key and value
public: T1 key;
    T2 value;
    mypair(T1 k,T2 v) {
        key=k;
        value=v;
    }
};

unsigned long fnv1a_hash(const string& str) { // hashing algorithm for strings
    const unsigned long FNV_PRIME = 16777619;
    const unsigned long OFFSET_BASIS = 2166136261;

    unsigned long hash = OFFSET_BASIS;
    for (char c : str) {
        hash ^= c;
        hash *= FNV_PRIME;
    }
    return hash;
}

template <typename T2>
class hash_table
{
private:
    static const int capacity = 1000; // Fixed capacity
    list<mypair<string, T2>> table[capacity]; // Array of linked lists to handle collisions
    int size;




public:
    hash_table()
    {
        size=0;

    }

    ~hash_table()
    {
    }

    void insert(string key, T2 value)
    {
        int hash=fnv1a_hash(key)%capacity; // make the hashing fit into the array size
        for (auto& entry : table[hash]) {  // iterate to check if this key is already existing if yes then update its value
            if (entry.key == key) {
                entry.value = value; // Update the value if the key exists
                return;
            }
        }
        mypair<string, T2> new_entry(key, value); // if it doesnot exist then add a new onr
        table[hash].push_back(new_entry);

        size++; // increment size
    }
    void delete_key(string key)
    {
        int hash=fnv1a_hash(key)%capacity;// make the hashing fit into the array size
        for (auto it = table[hash].begin(); it != table[hash].end(); ++it) {// iterating on the nodes of pairs to delete the one specified
            if (it->key == key) {
                table[hash].erase(it);
                size--;
                return;
            }
        }


    }
    // indexer
    T2& operator[](string key)
    {
        int hash=fnv1a_hash(key)%capacity;// make the hashing fit into the array size
        for (auto& entry : table[hash]) {//iterate on the nodes till get the value required
            if (entry.key == key) {
                return entry.value;
            }
        }
        table[hash].push_back(mypair<string, T2>(key, T2()));// if didnot find the key existed then add a new one and pass it
        size++;
        for (auto& entry : table[hash]) {
            if (entry.key == key) {
                return entry.value; // return the newly inserted value
            }
        }
    }

    void print()
    {
        for (int i = 0; i < capacity; ++i)
        {
            if (!table[i].empty()) {
                for (auto& entry : table[i]) {
                    cout<<"the Key ="<<entry.key<<"\tthe value ="<<entry.value<<endl;
                }
            }

        }
    }
};
