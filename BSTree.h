#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        int nelem;
	BSNode<T> *root;
	BSNode<T>* search(BSNode<T>* n, T e) const{
		if (n == nullptr){
			throw std::runtime_error("Nodo no encontrado");
		}else if(n->elem < e){
			return search(n->right,e);
		}else if(n->elem > e){
			return search(n->left,e);
		}else {
			return n;
		}
	}

	BSNode<T>* insert(BSNode<T>* n, T e) {
		
		if (n == nullptr){
                        return new BSNode<T>(e);
		}else if(n->elem == e){
			throw std::runtime_error("Nodo duplicado");
                }else if(n->elem < e){
                        n->right = insert(n->right, e);
                }else {
                        n->left = insert(n->left, e);
		}
		
		return n;
	}
	
	void print_inorder(std::ostream &out, BSNode<T>* n) const{
	    if (n != nullptr) {  
              print_inorder(out, n->left);
              
              out << n->elem << " ";
        
              print_inorder(out, n->right);
    }
	}
	
	BSNode<T>* remove(BSNode<T>* n, T e){
	    if (n == nullptr) {
                throw std::runtime_error("Element e no encontrado");
            }else if (n->elem < e) {
                n->right = remove(n->right, e);
            }else if (n->elem > e) {
                n->left = remove(n->left, e); 
            }else{
                if ((n->left != nullptr) && (n->right != nullptr)) { 
                    n->elem = max(n->left);
                    n->left= remove_max(n->left);
                    nelem--;
                }else{
                    n = (n->left != nullptr)? n->left: n->right;
                    nelem--;
                }
            }
              return n;
	    }
	
	T max(BSNode<T>* n) const{
	    if (n == nullptr){
              throw std::runtime_error("Nodo no encontrado");
            }else if (n->right != nullptr){
              return max(n->right);
            }else{
              return n->elem;
            }

	}
	
	BSNode<T>* remove_max(BSNode<T>* n){
	  if (n->right == nullptr) {
            return n->left;
          }else{
            n->right = remove_max(n->right);
            return n;
          }
	}
	
	void delete_cascada(BSNode<T>* n) {
            if (n) {
              delete_cascada(n->left);
              delete_cascada(n->right);
              delete n;
        }
    }

    public:
        BSTree(){
          nelem=0;
          root =nullptr;
        }
        int size() const{
	  return nelem;
        }

        T search(T e) const{
	  return search(root,e)->elem;
        }

        T operator[](T e) const{
	  return search(root,e)->elem;
        }

        void insert(T e){
	  if (root == nullptr) {
            root = new BSNode<T>(e);
            nelem++;
          } else {
            root = insert(root, e);
            nelem++;
          }
        }
        
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            if (bst.root != nullptr) {
            bst.print_inorder(out, bst.root);
            }
            return out;
        }
        
        void remove (T e){
          root = remove(root, e);
        }
        
        ~BSTree() {
          delete_cascada(root);
        }
        
};

#endif
