#include <iostream>
using namespace std;

template <typename T1, typename T2>
class hash_table
 {
private:
    T1* arr; 
    T2* arr2;
    int size;            
    int capacity;        

    
    void resize()
    {
        capacity *= 2;
        T1* temp = new T1[capacity];
        T2* temp2 = new T2[capacity];
        for (int i = 0; i < size; ++i) {
            temp[i] = arr[i];
            temp2[i] = arr2[i];
        }
        delete[] arr;
        delete[] arr2;
        arr = temp;
        arr2=temp2;
    }

public:
    hash_table(int initial_capacity = 40) 
    {
        size = 0;
        capacity = initial_capacity;
        arr = new T1[capacity];
        arr2 = new T2[capacity];
    }

    ~hash_table() 
    {
        delete[] arr;
        delete[] arr2;
    }

    void insert(T1 key, T2 value) 
    {
        if (size == capacity - 1) 
        {
            resize();
        }
        arr[size] =  key;
        arr2[size] =  value;
        size++;
    }
    void delete_key(T1 key)
    {
        int index=-1;
        for (int i = 0; i < size; i++) 
        {
            if (arr[i] == key) 
            {
                index=i;
                break;
            }
        }
        if (index==-1) return;
       for (int i = index; i < size - 1; i++) 
        {
            arr[i] = arr[i + 1];
            arr2[i] = arr2[i + 1];
        }

        size--; 

    }
// indexer
    T2& operator[](T1 key) 
    {
        for (int i = 0; i < size; i++) 
        {
            if (arr[i] == key) 
            {
                return arr2[i];
            }
        }
    }

    void print() 
    {
        for (int i = 0; i < size; ++i) 
        {
            cout << "Key: " << arr[i] << ", Value: " << arr2[i] << endl;
        }
    }
};
