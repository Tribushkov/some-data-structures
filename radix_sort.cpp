#include <vector>
#include <iostream>

using std::vector;

// Последняя цифра.
int f( int key )
{
	return key % 10;
}

void CountingSort( vector<int>& a )
{
	// Считаем, сколько раз встречаются f( a[i] ).
	vector<int> counts( 10, 0 );
	for( int i = 0; i < a.size(); ++i ) {
		++counts[f( a[i] )];
	}
	// Преобразуем в индексы концов групп.
	for( int i = 1; i < 10; ++i ) {
		counts[i] += counts[i - 1];
	}
	// Сразу строим результат.
	vector<int> result( a.size() );
	for( int i = a.size() - 1; i >= 0; --i ) {
		int groupNumber = f( a[i] );
		--counts[groupNumber];
		result[counts[groupNumber]] = a[i];
	}
	std::swap( a, result );
}

int main()
{
	int n = 0;
	std::cin >> n;
	vector<int> a( n, 0 );
	for( int i = 0; i < n; ++i ) {
		std::cin >> a[i];
	}

	CountingSort( a );

	for( int i = 0; i < n; ++i ) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}