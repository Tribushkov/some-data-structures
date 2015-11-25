#include <iostream>
#include <vector>
using std::cin;
using std::vector;

struct CPoint {
  int X;
  int Y;
  CPoint() : X( 0 ), Y( 0 ) {}
  CPoint( int x, int y ) : X( x ), Y( y ) {}
};

bool pointLess( const CPoint& a, const CPoint& b ) {
  return a.X < b.X;
};

// Строго меньше.
bool myLess( const int& a, const int& b ) {
  return a < b;
}

template<class T, class Compare>
void SimpleSort( vector<T>& arr, Compare comparator )
{
  for( size_t i = 0; i < arr.size(); ++i ) {
    for( size_t j = 0; j < arr.size() - 1; j++ ) {
      if( comparator( arr[j + 1], arr[j] ) ) {
        std::swap( arr[j], arr[j + 1] );
      }
    }
  }
}

int main()
{
  vector<int> arr;
  while( true ) {
    int data = 0;
    cin >> data;
    if( cin.fail() ) {
      break;
    }
    arr.push_back( data );
  }
  SimpleSort( arr, myLess );
  SimpleSort( arr, std::less<int>() );
  for( size_t i = 0; i < arr.size(); ++i ) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  // ===========================================
  
  vector<CPoint> points;
  points.push_back( CPoint( 5, 2 ) );
  points.push_back( CPoint( 3, 4 ) );
  SimpleSort( points, &pointLess );

  for( size_t i = 0; i < points.size(); ++i ) {
    std::cout << points[i].X << " " << points[i].Y << std::endl;
  }
  return 0;
}