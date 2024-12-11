#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../../Practica1/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
	int n;
	int max;
	ListLinked<TableEntry<V>>*table;	
	int h(std::string key){
		int sum = 0;
    		for (int i = 0; i < key.length(); ++i) {
        		sum += int(key.at(i));
   		 }
    		return sum % max;
	}
    public:

        HashTable(int size){
		n=0;
		max=size;
		table = new ListLinked<TableEntry<V>>[max];
	}

	~HashTable() {
		delete[] table;
	}
        
	int capacity(){
		return max;
	}

	friend std::ostream&operator<<(std::ostream &out, const HashTable<V> &ht){
		
		out << "HashTable [entries: " << const_cast<HashTable<V>&>(ht).entries() << " , capacity: " << const_cast<HashTable<V>&>(ht).capacity() << " ]"<< std::endl;
		out << "==============" << std::endl;
		out << "" << std::endl;
		for (int i = 0; i < ht.max;i++) {
            		out << "== Cubeta " << i << " == " << std::endl;
			out << "List => " << ht.table[i] << std::endl;
        	}
        	return out;
	}

	V operator[](std::string key) {
    		return search(key);
	}

	void insert(std::string key, V value) override {
    		int indice = h(key); 
    		ListLinked<TableEntry<V>>& nodos = table[indice];
    		TableEntry<V> Tabla = TableEntry<V>(key, value);
    		if (nodos.search(Tabla) == -1){
    		  nodos.append(Tabla);
    		  n++;
    		}
	}

	V search(std::string key) override {
    		int indice = h(key); 
    		ListLinked<TableEntry<V>>& nodos = table[indice]; 

    		
    		for (int i = 0; i < nodos.size(); i++) {
        		if (nodos.get(i).key == key) {
            			return nodos.get(i).value; 
        		}
    		}

    		throw std::runtime_error("Clave no encontrada");
	}
	
	V remove(std::string key) override {
    		int indice = h(key); 
    		ListLinked<TableEntry<V>>& nodos = table[indice];
    		
    		for (int i = 0; i < nodos.size(); i++) {
        		if (nodos.get(i).key == key) {
        		    int valor = nodos.get(i).value;
            		    nodos.remove(i); 
            		    n--;
            		    return valor;
        		}
    		}

    		throw std::runtime_error("Clave no encontrada");
	}

	int entries() override {
    		return n;
	}



};

#endif
