// UNIT_TEST(name, #1, #2, 1000){
// code goes here
// ends with PASS, ASSERT(bool condition), or FAIL("message")
// }
#include <algorithm>
#include <map>
#include <vector>

#include "simple_hash.h"
#include "textfile.h"

#include "lphashtable.h"
#include "schashtable.h"
#include "word_counter.h"
#include "anagram_finder.h"

#include "util.h"
#include "proxy.h"

using namespace std;
using namespace util;

#if MONAD_SPLIT
UNIT_TEST(testRemoveEASY, 10, 10, 5000){
	TextFile infile( "textEasy.txt" );
	SimpleHash hasher;
	SCHashTable<string, int> hashTable(32, hasher);
	while( infile.good() ) {
		string word = infile.getNextWord();
		hashTable.insert(word, 0);
	}
	hashTable.remove("john");
	if( hashTable.keyExists("john") )
		FAIL("Did not remove key: 'john'");
	hashTable.remove("bananas");
	if( hashTable.keyExists("bananas") )
		FAIL("Did not remove key: 'bananas'");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testRemoveHard, 15, 15, 5000){
	TextFile infile( "textHard.txt" );
	SimpleHash hasher;
	SCHashTable<string, int> hashTable(32, hasher);
	while( infile.good() ) {
		string word = infile.getNextWord();
		if( hashTable.keyExists(word) ){
			hashTable.remove(word);
			if( hashTable.keyExists(word) )
				FAIL("Did not remove key on update");
			hashTable.insert(word, 1);
		}
		else
			hashTable.insert(word, 0);
	}
	hashTable.remove("shells");
	if( hashTable.keyExists("shells") )
		FAIL("Did not remove key: 'shells'");
	hashTable.remove("shore");
	if( hashTable.keyExists("shore") )
		FAIL("Did not remove key: 'shore'");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testResizeOnce, 10, 10, 5000){
	TextFile infile( "textLong.txt" );
	SimpleHash hasher;
	SCHashTable<string, int> hashTable(16, hasher);
	int val = 0;
	while( infile.good() ) {
		val++;	
		string word = infile.getNextWord();
		if( !hashTable.keyExists(word) )
			hashTable.insert(word, val);
	}
	ASSERT(hashTable.tableSize() >= val / 0.7);
	if( hashTable.find("photomosaic") != 2 )
		FAIL("Didn't copy over existing lists properly on resize");
	if( hashTable.find("is") != 3 )
		FAIL("Didn't re-hash keys properly");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testResizeAll, 15, 15, 5000){
	vector<string> strings;
	for(int i = 'a'; i <= 'z'; i++) {
		string word = "";
		word += ((char)i);
		strings.push_back(word);
	}
	SimpleHash hasher;
	SCHashTable<string, int> hashTable(16, hasher);
	int val = 0;
	for(unsigned int i = 0; i < strings.size(); i++) {
		val++;
		hashTable.insert(strings[i], val);
	}
	ASSERT(hashTable.tableSize() >= strings.size() / 0.7);
	for(int i = 'a'; i <= 'z'; i++) {
		string word = "";
		word += ((char)i);
		if( !hashTable.keyExists(word) )
			FAIL("Missed a key during resize");
	}
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testInsertEasy, 10, 10, 5000){
	TextFile infile( "textEasy.txt" );
	SimpleHash hasher;
	LPHashTable<string, int> hashTable(32, hasher);
	int val = 0;
	while( infile.good() ) {
		val++;
		string word = infile.getNextWord();
		hashTable.insert(word, val);
	}
	if( !hashTable.keyExists("john") )
		FAIL("Did not insert key: 'john'");
	if( !hashTable.keyExists("bananas") )
		FAIL("Did not insert key: 'bananas'");
	if( hashTable.find("mary") != 3 )
		FAIL("Did not insert key-value pair properly");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testInsertHard, 15, 15, 5000){
	TextFile infile( "textHard.txt" );
	SimpleHash hasher;
	LPHashTable<string, int> hashTable(32, hasher);
	while( infile.good() ) {
		string word = infile.getNextWord();
		if( hashTable.keyExists(word) ){
			int val = hashTable.find(word);
			hashTable.remove(word);
			hashTable.insert(word, val + 1);
		}
		else
			hashTable.insert(word, 0);
	}
	if( !hashTable.keyExists("shells") )
		FAIL("Did not insert properly key: 'shells'");
	if( !hashTable.keyExists("shore") )
		FAIL("Did not insert properly key: 'shore'");
	if( hashTable.find("the") != 0 )
		FAIL("Did not insert key-value pair properly");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testAnagrams, 10, 10, 5000){
	vector<string> strings;
	strings.push_back("derp");
	strings.push_back("repd");
	strings.push_back("igloo");
	strings.push_back("dog");
	strings.push_back("per");
	strings.push_back("derrp");
	strings.push_back("drep");

	AnagramFinder finder(strings);
	vector<string> result = finder.getAnagrams("derp");
	if( result.size() > 3 )
		FAIL("Found too many anagrams");
	if( result.size() < 3 )
		FAIL("Did not find enough anagrams");
	vector<string> expected;
	expected.push_back("derp");
	expected.push_back("repd");
	expected.push_back("drep");
	
	sort(expected.begin(), expected.end());
	sort(result.begin(), result.end());
	for(unsigned int i = 0; i < expected.size(); i++)
		if( expected[i].compare(result[i]) != 0 )
			FAIL("anagrams did not match");
}
#endif

#if MONAD_SPLIT
UNIT_TEST(testWordCount, 15, 15, 5000){
	WordFreq wf("wordCount.txt");
	vector< pair<string, int> > result = wf.getWords(5);
	if( result.size() > 4 )
		FAIL("Found too many words");
	if( result.size() < 4 )
		FAIL("Did not find all words");

	map<string, int> expected;
	expected["the"  ] = 6;
	expected["is"   ] = 5;
	expected["can"  ] = 4;
	expected["dog"  ] = 3;
	expected["dgo"  ] = 1;
	expected["data" ] = 1;
	expected["apple"] = 7;
	expected["red"  ] = 6;

	for (unsigned int i = 0; i < result.size(); i++)
		if (expected[result[i].first] != result[i].second)
			FAIL("'" + result[i].first + "' gave " + result[i].second + ", expected " + expected[result[i].first]);
}
#endif

#if MONAD_SPLIT

#include "logfile_parser.h"
// The following is a hack, but useful so that all the extra credit code falls
// within a MONAD_SPLIT block to resolve compilation issues
#include "logfile_parser.cpp"

UNIT_TEST(testLogfileParse, 20, 20, 5000){
	LogfileParser lfp("log.txt");
	vector<string> urls = lfp.uniquePages();
	if( urls.size() > 4 )
		FAIL("Found too many URLs");
	if( urls.size() < 4 )
		FAIL("Did not find enough URLs");

	vector<string> expected;
	expected.push_back("/product/3/");
	expected.push_back("/product/1/");
	expected.push_back("/product/2/");
	expected.push_back("/product/4/");

	sort(expected.begin(), expected.end());
	sort(urls.begin(), urls.end());
	for(unsigned int i = 0; i < expected.size(); i++)
		if( expected[i].compare(urls[i]) != 0 )
			FAIL("URLs did not match");

	pair<bool, time_t> result1, result2, result3;
	result1 = lfp.dateVisited("chase", "/product/1/");
	result2 = lfp.dateVisited("alex", "/product/3/");
	result3 = lfp.dateVisited("dave", "/product/2/");
	if( !result1.first || !result2.first || !result3.first )
		FAIL("Failed to find visit");

	time_t res1 = time(NULL);
	time_t res2 = time(NULL);
	time_t res3 = time(NULL);

	tm * tme = localtime( &res1 );
	strptime( "Sun Apr 10 09:39:34 2011", "%c", tme );
	tme->tm_isdst = 1;
	res1 = mktime( tme );
	strptime( "Sat Apr  9 07:56:24 2011", "%c", tme );
	tme->tm_isdst = 1;
	res2 = mktime( tme );
	strptime( "Sat Apr  9 08:19:33 2011", "%c", tme );
	tme->tm_isdst = 1;
	res3 = mktime( tme );


	ASSERT_EQUALS(result1.second, res1);
	ASSERT_EQUALS(result2.second, res2);
	ASSERT_EQUALS(result3.second, res3);
}
#endif
