/*
   Linear Probing Hash Table Iterator (Lab 10)
   Created by Chase Geigle for CS225, Spring 2011
*/

template <class K, class V>
LPHashTable<K,V>::iterator::iterator( LPHashTable<K,V> const * ht, int j ) : table(ht), i(j) {
    if( ht != NULL && i < ht->size && ht->table[i] == NULL )
        operator++();
}

template <class K, class V>
typename LPHashTable<K,V>::iterator & LPHashTable<K,V>::iterator::operator++() {
    if( table != NULL ) {
        while( ++i < table->size && table->table[i] == NULL );
    }
    return *this;
}

template <class K, class V>
typename LPHashTable<K,V>::iterator LPHashTable<K,V>::iterator::operator++(int) {
    iterator tmp(*this);
    operator++();
    return tmp;
}

template <class K, class V>
bool LPHashTable<K,V>::iterator::operator==( iterator const & rhs ) {
    return table == rhs.table && i == rhs.i;
}

template <class K, class V>
bool LPHashTable<K,V>::iterator::operator!=( iterator const & rhs ) {
    return !(operator==(rhs));
}

template <class K, class V>
pair<K,V> const & LPHashTable<K,V>::iterator::operator*() {
    return *(table->table[i]);
}

template <class K, class V>
pair<K,V> const * LPHashTable<K,V>::iterator::operator->() {
    return table->table[i];
}
