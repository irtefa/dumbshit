/*
   Anagram Finder (Lab 10)
   Created by Chase Geigle for CS225, Spring 2011
*/

#include "anagram_finder.h"

AnagramFinder::AnagramFinder( string ifile ) : file(true), filename(ifile) {
    /* nothing */
}

AnagramFinder::AnagramFinder( vector<string> istrings ) : file(false),
    strings(istrings) {
    /* nothing */
}

bool AnagramFinder::checkWord( string const & word, string const & test ) {
    // base case : check if they are of the same size
    if(word.size()!= test.size())
	{
		return false;
	}
	// your code here!
    //int len = word.size();
	//size_t length = word.length();
	LetterHash hasher;
	LPHashTable<char, int> wordHash(256, hasher);
	LPHashTable<char, int> testHash(256, hasher);
	
	for(unsigned int i = 0; i < word.size();i++)
	{
		int a = 0;
		if(wordHash.keyExists(word[i]))
		{
			a = wordHash.keyExists(word[i]);
		}
		wordHash.remove(word[i]);
		wordHash.insert(word[i], a+1);

		int b = 0;
		if(testHash.keyExists(word[i]))
		{
			b = testHash.find(word[i]);
		}
		testHash.remove(word[i]);
		testHash.insert(word[i],b+1);
	}

	vector< pair<char, int> > vect = wordHash.vectorize();
	for(unsigned int i = 0;i < vect.size();i++)
	{
		char key = vect[i].first;
		int val = vect[i].second;
		if(!testHash.keyExists(key)) 
		{
			return false;
		}
		int testVal = testHash.find(key);
		if(val != testVal)
		{
			return false;
		}
	}
	return true;
}

vector<string> AnagramFinder::getAnagrams( string word ) {
    // set up the return vector
    vector<string> ret;

    if( file ) {
        TextFile infile( filename );
        string line;
        vector<string> tests;
        while( infile.good() ) {
            string test = infile.getNextWord();
            if( checkWord( word, test ) ) 
                ret.push_back( test );
        }
    } else {
        for( unsigned int i = 0; i < strings.size(); i++ ) {
            if( checkWord( word, strings[i] ) )
                ret.push_back( strings[i] );
        }
    }
    return ret;
}

void AnagramFinder::writeAnagrams( string word, string output_file ) {
    vector<string> anagrams = getAnagrams( word );
    ofstream outfile(output_file.c_str());
    if( outfile.is_open() ) {
        for( unsigned int i = 0; i < anagrams.size(); i++ )
            outfile << anagrams[i] << endl;
    }
    outfile.close();
}
