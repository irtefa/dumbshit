/*
   Word Frequency Counter (Lab 10)
   Created by Chase Geigle for CS225, Spring 2011
*/

#include "word_counter.h"

WordFreq::WordFreq( string infile ) : filename(infile) { /* nothing */ }

vector< pair<string, int> > WordFreq::getWords( int threshold ) {
    vector< pair<string, int> > ret;
    
	TextFile infile(filename);
 
    StringHash hasher;

    SCHashTable<string, int> hashTable(256, hasher);
    
	while(infile.good())
    {
    	string word = infile.getNextWord();
    	int val = 0;
    	
		if(hashTable.keyExists(word))
		{
    		val = hashTable.find(word);
    	}
		hashTable.remove(word);
    	hashTable.insert(word,val + 1);
    } 

    vector<pair<string, int> > vect = hashTable.vectorize();
    

    for(unsigned int i=0; i < vect.size();i++)
    {
    	if(vect[i].second >= threshold)
    		ret.push_back(vect[i]);
    }
    return ret;
}
