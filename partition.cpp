// Возвращает индекс опорного элемента. begin и end включительно. begin <= end.
// Опорный - последний.
int Partition( vector<int>& arr, int begin, int end ) {
	assert( begin <= end );
	assert( begin >= 0 && end + 1 <= static_cast<int>( arr.size() ) );
	if( begin == end ) {
		return begin;
	}
	int pivot = arr[end];
	int i = begin;
	int j = end - 1;
	while( i <= j ) {
		// Не проверяем, что i < end, т.к. arr[end] == pivot.
		for( ; arr[i] < pivot; ++i ) {}
		for( ; j >= 0 && arr[j] >= pivot; --j ) {}
		if( i < j ) {
			std::swap( arr[i], arr[j] );
			++i;
			--j;
		}
	}
	std::swap( arr[i], arr[end] );
	return i;
}