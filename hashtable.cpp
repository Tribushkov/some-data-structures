#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using std::string;
using std::vector;
using std::cin;
using std::cout;

const int HashParamA = 37;
const int InitialTableSize = 8;

int Hash( const string& s, int m ) {
        int result = 0;
        for( int i = 0; i < static_cast<int>( s.length() ); ++i ) {
                result = ( result * HashParamA + s[i] ) % m;
        }
        return result;
}

class CHashTable {
public:
        CHashTable();

        bool Has( const string& s );
        // Возвращает false, если элемент уже есть.
        bool Add( const string& s );
        // Возвращает false, если элемента нет.
        bool Remove( const string& s );

private:
        struct CNode {
                string Data;
                CNode* Next;

                CNode( const string& data ) : Data( data ), Next( 0 ) {}
        };
        vector<CNode*> table;
        int size; // Количество элементов.
};

CHashTable::CHashTable() :
        size( 0 )
{
        table.resize( InitialTableSize, 0 );
}

bool CHashTable::Has( const string& s ) {
        int hash = Hash( s, table.size() );
        for( CNode* node = table[hash]; node != 0; node = node->Next ) {
                if( node->Data == s ) {
                        return true;
                }
        }
        return false;
}

bool CHashTable::Add( const string& s ) {
        int hash = Hash( s, table.size() );
        if( table[hash] == 0 ) {
                table[hash] = new CNode( s );
		++size;
                return true;
        }

        CNode* currentNode = table[hash];
        while( true ) {
                if( currentNode->Data == s ) {
                        return false;
                }
                if( currentNode->Next == 0 ) {
                        break;
                }
                currentNode = currentNode->Next;
        }
        currentNode->Next = new CNode( s );
	++size;
        return true;
}

bool CHashTable::Remove( const string& s ) {
        int hash = Hash( s, table.size() );
        if( table[hash] == 0 ) {
                return false;
        }
        if( table[hash]->Data == s ) {
                CNode* toDelete = table[hash];
                table[hash] = table[hash]->Next;
                delete toDelete;
		--size;
                return true;
        }
        CNode* node = table[hash];
        while( node->Next != 0 ) {
                if( node->Next->Data == s ) {
                        CNode* toDelete = node->Next;
                        node->Next = toDelete->Next;
                        delete toDelete;
			--size;
                        return true;
                }
        }
        return false;
}

int main() {
        CHashTable hashTable;
        char command = 0;
        string data;
        while( cin >> command >> data ) {
                switch( command ) {
                        case '+':
                                cout << ( hashTable.Add( data ) ? "OK" : "FAIL" ) << std::endl;
                                break;
                        case '-':
                                cout << ( hashTable.Remove( data ) ? "OK" : "FAIL" ) << std::endl;
                                break;
                        case '?':
                                cout << ( hashTable.Has( data ) ? "OK" : "FAIL" ) << std::endl;
                                break;
                        default:
                                assert( false );
                }
        }
        return 0;
}