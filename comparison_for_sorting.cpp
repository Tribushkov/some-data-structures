#include <algorithm>
#include <iostream>

// Структура, массив объектов которых будем сортировать.
struct CDate {
	short Day;
	short Month;
	short Year;

	bool operator<( const CDate& other ) const;
};

// Вариант 1. Оператор сравнения.
bool CDate::operator<( const CDate& other ) const
{
	return Year < other.Year ||
		( Year == other.Year && ( Month < other.Month ||
			( Month == other.Month && Day < other.Day ) ) );
}

namespace std {
	// Явная специализация.
	template<>
	void swap<CDate>( CDate& left, CDate& right )
	{
		CDate temp = left;
		left = right;
		right = temp;
	}
}

// Вариант 2. Функция сравнения.
typedef bool( *TCompareFunction )( const CDate&, const CDate& );

bool MyCompareFunction( const CDate& left, const CDate& right )
{
	return left < right;
}

// Вариант 3. Функтор - класс с определенным оператором "круглые скобки от двух аргументов".
class CMyFunctor {
public:
	explicit CMyFunctor( bool _doCompare ) : doCompare( _doCompare ) {}
	bool operator()( const CDate& left, const CDate& right ) { return doCompare && left < right; }

private:
	bool doCompare;
};

// Собственно сортировка.
template<class T, class Functor>
void BubbleSort( T* vector, int n, Functor functor )
{
	for( int i = 0; i < n - 1; ++i ) {
		for( int j = 0; j < n - 1; ++j ) {
			if( functor( vector[j + 1], vector[j] ) ) {
				std::swap( vector[j], vector[j + 1] );
			}
		}
	}
}

int main()
{
	int n = 0;
	std::cin >> n;

	CDate* dates = new CDate[n];
	for( int i = 0; i < n; ++i ) {
		std::cin >> dates[i].Day;
		std::cin >> dates[i].Month;
		std::cin >> dates[i].Year;
	}
	CMyFunctor myFunctor( false );
	BubbleSort( dates, n, myFunctor );
	for( int i = 0; i < n; ++i ) {
		std::cout << dates[i].Day << "." << dates[i].Month << "." << dates[i].Year << std::endl;
	}
}