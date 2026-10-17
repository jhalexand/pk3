#ifndef HashTable_H
#define HashTable_H

/**************************************************************
 *	Name: Benoit Hudson (bh)
 *	File: HashTable.h
 *	Date: Tue Aug  4 14:48:18 EDT 1998
 *      Desc: A hash table, of <key,element> pairs.  Templated by
 *            both key and element.  The key is stored as-is;
 *            the element is stored by pointer.
 **************************************************************/

#include <stdlib.h>
#include <string.h> // memset

#include <debug.h>

#include "Array.h"


extern const unsigned int SIZES [] ;
/*    5u,          11u,         37u,        53u,         97u,
    193u,        389u,        769u,       1543u,       3079u,
    6151u,       12289u,      24593u,     49157u,      98317u,
    196613u,     393241u,     786433u,    1572869u,    3145739u,
    6291469u,    12582917u,   25165843u,  50331653u,   100663319u,  
    201326611u,  402653189u,  805306457u, 1610612741u, 3221225473u
} ;*/

template <class K, class E> class HTNode;
template <class K, class E> class HTIterator;

template <class K, class E>
class HashTable {
    friend class HTIterator<K,E>;
private:
    unsigned size_; // number of elements
    unsigned allocIdx_;
    HTNode<K,E> **table_;

public:

    HashTable() {
        allocIdx_ = 0;
        size_ = 0;
        allocTable();
    }

    virtual ~HashTable() {
        clear();
        free(table_);
    }

    void clear() {
        for(unsigned i=0; i<SIZES[allocIdx_]; i++) {
            HTNode<K,E> *cur = table_[i];
            while(cur) {
                HTNode<K,E> *next = cur->next_;
                delete cur;
                cur = next;
            }
        }
        memset(table_, 0, SIZES[allocIdx_]*sizeof(HTNode<K,E>*));
        size_ = 0;
    }

    int size() const {
        return size_;
    }
    
    int allocated() const {
        return SIZES[allocIdx_];
    }
    
    // makes the table have at least the given number of buckets
    void resize(unsigned size) {
        unsigned i;
        for(i=0; SIZES[i] < size; i++) { }
        setSize(i);
    }

    // add the <k,e> pair to the table
    void put(const K &key, E element) {
        assert(!has(key));

        // if load factor > 1, resize
        if(size_ >= SIZES[allocIdx_]) {
            setSize(allocIdx_+1);
        }

        unsigned index = hash(key);
        table_[index] = new HTNode<K,E>(key,element, table_[index]);
        size_++;
    }
    
    // change the element of the <k,e> pair already in the table
    void change(K key, E element) {
        assert(has(key));
        HTNode<K,E> *found = find(key);
        found->element_ = element;
    }
    
    // either change or, if it's not already there, put.
    boolean set(K key, E element) {
        if(has(key)) {
            change(key, element);
            return false;
        } else {
            put(key, element);
            return true;
        }
    }
    
    // return true if the key is in the table, false otherwise.
    boolean has(K key) const {
        return find(key) != null;
    }

    // get the element corresponding to the key, 0 if there is none.
    E get(K key) const {
        HTNode<K,E> *cur = find(key);
        if(cur) return cur->element_;
        else    return 0; // 0 for integer types, null for pointer types
    }
    
    // for typing convenience
    E operator[] (K key) const {
        return get(key);
    }
    
    // remove the key; return the elt
    E remove(const K &key) {
        unsigned index = hash(key);
        HTNode<K,E> *cur, *prev;
        prev = NULL;
        cur = table_[index];
        while(cur) {
            if(equal(cur->key_,key)) {
                // remove the node, decrement the size, then we're done
                if(prev) { prev->next_   = cur->next_; } 
                else     { table_[index] = cur->next_; }
                E elt = cur->element_;
                delete cur;
                size_--;
                return elt;
            }
            prev = cur;
            cur = cur->next_;
        }
        return 0; // not found
    }
    
private:
    void allocTable() {
        table_ = (HTNode<K,E>**)malloc(SIZES[allocIdx_]*sizeof(HTNode<K,E>*));
        memset(table_, 0, SIZES[allocIdx_]*sizeof(HTNode<K,E>*));
    }

    HTNode<K,E> *find(K key) const {
        unsigned index = hash(key);
        HTNode<K,E> *cur = table_[index];
        while(cur) {
            if(equal(cur->key_,key)) {
                return cur;
            }
            cur = cur->next_;
        }
        return null;
    }


    void setSize(unsigned newidx) {
        // first we copy the old table
        HTNode<K,E> **oldTable = table_;
        unsigned oldAlloc = allocIdx_;

        // then we allocate the new
        allocIdx_ = newidx;
        allocTable();
        size_ = 0;

        // finally, we copy from one to the other, deallocating as we go
        for(unsigned i=0; i<SIZES[oldAlloc]; i++) {
            HTNode<K,E> *cur = oldTable[i], *next;

            while(cur) {
                put(cur->key_, cur->element_);
                next = cur->next_;
                delete cur;
                cur = next;
            }
        }
        free(oldTable);
    }


protected:
    // Note to the implementor of a sub-class:
    // internal_hash must be defined.  equal may be redefined; if not,
    // it checks ==.
    //
    // internal_hash should be some hash code based on the key.  This hash 
    // code need not be small, as hash (which cannot be redefined) mods it by
    // the size of the hash table.
    
    // equal should return whether the two keys are equal, in some sense.
    // The default sense uses operator ==.


    unsigned hash(K key) const {
        return internal_hash(key) % allocated();
    }
    virtual boolean equal(K k1, K k2) const {
        return k1==k2;
    }
    virtual unsigned internal_hash(K) const = 0 ;
    

} ;

// the storage class for the internal lists
template <class K, class E>
class HTNode {
    friend class HashTable<K,E>;
    friend class HTIterator<K,E>;
public:
    K key_;
    E element_;
    HTNode<K,E> *next_;

    HTNode(K k, E e, HTNode<K,E> *n) {
        key_ = k; 
        element_ = e; 
        next_ = n;
    }
} ;


template <class K, class E>
class HTIterator {
private:
    const HashTable<K,E> *table_;
    HTNode<K,E> *node_;
    unsigned tableIdx_;
public:
    HTIterator(const HashTable<K,E>& ht) : table_(&ht) {
        // if we didn't find anything, then our pointer is null
        node_ = null;
        tableIdx_ = (unsigned)-1; // so that ++ gets to 0
        internal_next();
    }

    ~HTIterator() { ; }

    K key()     { return node_->key_; }
    E element() { return node_->element_; }

    void next() { 
        node_ = node_->next_;
        if(!node_) internal_next();
    }

    // prefix
    void operator ++ () { next(); }

    operator boolean () const { return node_!=null; }
    
private:
    void internal_next() {
        for(tableIdx_++ ; tableIdx_<SIZES[table_->allocIdx_]; tableIdx_++) {
            if(table_->table_[tableIdx_]) {
                node_ = table_->table_[tableIdx_];
                return;
            }
        }
    }

} ;


template <class E>
class IntHash : public HashTable<int,E> {
protected:
    virtual unsigned internal_hash(int key) const {
        return key;
    }
} ;

#endif
