#include <tuple>
#include <stdint.h>
#include <vector>

// remove reference
// get tuple size
// iterator tuple

using namespace std;
using MyTupleType = tuple<int64_t, bool>;

void TypeTest(void)
{
	auto tupleLength = tuple_size<MyTupleType>::value;
	MyTupleType myTuple = make_tuple(23, false);
	auto& refTuple = myTuple;
	vector<MyTupleType> vtTuple;

	vtTuple.push_back(myTuple);

	auto& refVtTupleBack = vtTuple.back();

	auto tupleLengthRef = tuple_size<remove_reference<decltype(refTuple)>::type>::value;
	auto tupleLengthRef2 = tuple_size<remove_reference<decltype(refVtTupleBack)>::type>::value;
}

