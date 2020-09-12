#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;
static const int min_limit = 2;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (distance(range_begin, range_end) < min_limit)
		return;

	vector<typename RandomIt::value_type> vec(make_move_iterator(range_begin),
		make_move_iterator(range_end));

	const int left_border  = vec.size() / 3;
	const int right_border = left_border * 2;

	MergeSort(move(vec.begin()), move(vec.begin() + left_border));
	MergeSort(move(vec.begin() + left_border), move(vec.begin() + right_border));
	MergeSort(move(vec.begin() + right_border), move(vec.end()));

	vector<typename RandomIt::value_type> last_vec;

	merge(make_move_iterator(vec.begin()),
		make_move_iterator(vec.begin() + left_border),
		make_move_iterator(vec.begin() + left_border),
		make_move_iterator(vec.begin() + right_border),
		back_inserter(last_vec));

	merge(make_move_iterator(last_vec.begin()),
		make_move_iterator(last_vec.end()),
		make_move_iterator(vec.begin() + right_border),
		make_move_iterator(vec.end()),
		range_begin);
	// не копируя сортируемые элементы
}

void TestIntVector() {
	vector<int> numbers = { 6, 1, 3, 9, 1, 9, 8, 12, 1 };
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}