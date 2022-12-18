#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <cpputils/iterators/FilterIterator.hpp>
#include <cpputils/iterators/StandaloneIndexIterator.hpp>
#include <cpputils/iterators/LinkedIndexIterator.hpp>
#include <cpputils/iterators/ReverseIterator.hpp>
#include <cpputils/iterators/MapIterator.hpp>
#include <cpputils/iterators/ZipIterator.hpp>
#include <cpputils/range/Range.hpp>
#include <cpputils/range/zip.hpp>
#include <cpputils/range/index.hpp>
#include <cpputils/range/enumerate.hpp>

using namespace cpputils;

template<std::random_access_iterator T>
using Dio = T;

int main()
{

	Dio<iterators::StandaloneIndexIterator<std::size_t>> z;
	std::vector<int> v{ 0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,0,1,2,3,9 };
	std::vector<int> nv{ -0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-0,-1,-2,-3,-4,-0,-1,-2,-3,-9 };


	auto r = range::Range<std::vector<int>::iterator>{ v.begin(), v.end() }.immutable();
	std::cout << "Size: " << r.size() << std::endl;
	for (const auto& v0 : r)
	{
		std::cout << v0 << "," << v0 << std::endl;
	}
	return EXIT_SUCCESS;
}