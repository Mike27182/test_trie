#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

struct Trie
{
    unordered_map<char, unique_ptr<Trie>> ch;
    int wc = 0;
};

Trie createTrie( const vector<string>& elements )
{
    Trie t; 
    for( const string& s : elements )
    {
        Trie* p = &t;
        for( char ch : s )
        {
            unique_ptr<Trie>& ptr = p->ch[ch];
            if( !ptr )
                ptr.reset( new Trie );
            p = ptr.get();
        }
        ++p->wc;

    }

    return t;
}

bool f( const char* s, Trie& trRoot, vector<vector<char>>& resVec )
{
    vector<char> path;
    Trie* tr = &trRoot;
    for( ;; )
    {
        if( *s==0 )
        {
            if( tr->wc==0 )
                return false;

            resVec.push_back( path );
            return true;
        }

        if( tr->wc )
        {
            --tr->wc;
            resVec.push_back( path );
            if( f( s, trRoot, resVec ) )
            {
                ++tr->wc;
                return true;
            }
            ++tr->wc;
            resVec.pop_back();
        }

        auto it = tr->ch.find( *s );
        if( it == tr->ch.end() )
            return false;

        path.push_back( *s );
        ++s;
        tr = it->second.get();
    }
}

int main() 
{
    vector<string> elements = {"ac", "at", "c", "ca", "f", "h", "k", "o", "p", "po", "s", "s", "scse", "se", "tc", "te", "yt", "csey"};
    //vector<string> elements = {"ac", "at", "c", "ca", "f", "h", "k", "o", "p", "po", "s", "sc", "se", "tc", "te", "y", "yt"};
    Trie tr = createTrie(elements);
    for( string s: {"spooky", "spookyy", "cat", "capoosscsey", "caspoosscse", "capoosscse", "casspoosscse"} )
    //for( string s: {"spooky", "cat"} )
    {
        cout<<s;
        vector<vector<char>> resVec;
        if( f( s.c_str(), tr, resVec ) )
        {
            const char* delim = " -> ";
            for( auto el : resVec )
            {
                cout<<delim;
                for( char c : el )
                    cout<<c;
                delim="-";
            }
            cout<<endl;
        }
        else
        {
            cout<<endl;
        }
    }

    return 0;
}

