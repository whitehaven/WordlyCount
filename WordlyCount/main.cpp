//
//  main.cpp
//  WordlyCount
//
//  Created by Alex Crist on 8/27/14.
//  Copyright (c) 2014 White Haven Informatics. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

void stripInput( string & subject )
{
    for( int i = 0; i < subject.length(); i++ )
    {
        if ( subject.at(i) == '\'' && subject.length() > i )
        {
            if ( subject.at(i+1) == 's' )
                subject.erase( i, 2 );
        }
        else if ( subject.at(i) < 'Z' && subject.at(i) > 'A' )
        {
            subject.at(i) -= 'A' - 'a';
        }
        else if ( subject.at(i) > 'z' || subject.at(i) < 'a' )
        {
            subject.erase(i, 1);
            i--;
        }
    }
}

int main(int argc, const char * argv[])
{
    bool useGreaterThan1OnlyMode = false;
    
    ifstream fin;
    
    if ( !strncmp(argv[1], "-g", 2 ) )
    {
        cout << "Using greater-than-1 mode." << endl;
        useGreaterThan1OnlyMode = true;
        fin.open( argv[2] );
    }
    else
    {
        fin.open( argv[1] );
    }
    
    map<string , int> words;
    
    string currentWord;
    
    while( fin >> currentWord )
    {
        stripInput( currentWord );
        
        if( currentWord.empty() )
            continue;
        // incrementing for each found, or starting at 1
        words[currentWord]++;
    }
    
    multiset< pair<int, string> > wordCompiler;
    
    pair<int, string> currentEntry;

    for ( map<string, int>::iterator itermap = words.begin(); itermap != words.end(); itermap++ )
    {
        if ( (useGreaterThan1OnlyMode && itermap->second > 1) )
        {
            currentEntry.first = itermap->second;
            currentEntry.second = itermap->first;
            wordCompiler.insert(currentEntry);
        }
        else
            continue;
    }
    
    for( multiset< pair< int, string > >::iterator itermset = wordCompiler.begin(); itermset != wordCompiler.end(); itermset++ )
    {
        cout << itermset->first << "\t";
        cout << itermset->second << endl;
    }
    
    return 0;
}

