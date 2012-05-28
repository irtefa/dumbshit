/*
   Logfile Parser (Lab 10)
   Created by Chase Geigle for CS225, Spring 2011
*/

#include "logfile_parser.h"

#include <iostream>

// creates a LogLine from the given line---you can ignore this.
LogfileParser::LogLine::LogLine( string line ) {
    istringstream iss( line );
    iss >> customer;
    customer = customer.substr(1, customer.length()-3);
    iss >> url;
    string dte = "";
    string dline;
    do {
        iss >> dline;
        dte += dline;
    } while( iss );

    date = time(NULL);
    tm * tme = localtime( &date );
    // force DST
    tme->tm_isdst = 1;
    strptime( dte.c_str(), "%c", tme );
    date = mktime( tme );
}

LogfileParser::LogfileParser( string fname ) : whenVisitedTable(256, hasher) {
    LPHashTable< string, bool > pageVisitedTable(256, hasher);
    ifstream infile( fname.c_str() );
    string line;
    while( infile.good() ) {
        getline( infile, line );
        
        // if the line's length is 0, move to the next loop iteration
        if( line.length() == 0 )
            continue;

        LogLine ll( line );
        // given the LogLine above, update the member variable hash table and
        // any other hash tables necessary to solve this problem. this should
        // also build the uniqueURLs vector.
        string key = ll.url + ll.customer;
	   
        if(!pageVisitedTable.keyExists(ll.url))
        {
            pageVisitedTable.insert(ll.url, true);
            uniqueURLs.push_back(ll.url);
        }    

        if(!whenVisitedTable.keyExists(key))
        {
            whenVisitedTable.insert(key, ll.date);
        }
        else
        {
            if(ll.date > whenVisitedTable.find(key))
            {
                whenVisitedTable.remove(key);
                whenVisitedTable.insert(key, ll.date);
            }
        }
    }
}

pair< bool, time_t > LogfileParser::dateVisited( string customer, string url ) {
    pair< bool, time_t > ret;
    string k = url + customer;
	// your code here! query your hash table for this function---should be short
    if(!whenVisitedTable.keyExists(k))
	{
		ret.first = false;
	}
	else
	{
		ret.first = true;
		ret.second = whenVisitedTable.find(k);
	}
	return ret;
}

vector<string> LogfileParser::uniquePages() {
    return uniqueURLs;
}
