#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;  

public:
    
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    
    ~BSTreeDict() {
        delete tree;
    }

    
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    
    V search(std::string key) override {
        TableEntry<V> entry(key);
        TableEntry<V> result = tree->search(entry);  
        return result.value; 
    }

    
    V remove(std::string key) override {
        TableEntry<V> entry(key);
        V removedValue = search(key);  
        tree->remove(entry);  
        return removedValue;  
    }

    
    int entries() override {
        return tree->size(); 
    }

    
    V operator[](std::string key) {
        return search(key);
    }

    
    friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& dict) {
        out << *(dict.tree); 
        return out;
    }
};

#endif


