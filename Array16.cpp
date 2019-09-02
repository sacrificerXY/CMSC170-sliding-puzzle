//#include "Array16.h"

#include <cassert>
#include <limits>
#include <bitset>
#include <sstream>
#include <iomanip>
#include "Array16.h"
using namespace std;

constexpr int SIZE = 4;
constexpr uint64_t MAX = numeric_limits<uint64_t>::max();
constexpr uint64_t B = 0b1111;


//void Array16::set(int pos, int val)
//{
//}
//
//int Array16::get(int pos) const
//{
//}
//
//void Array16::swap(int pos1, int pos2)
//{
//}
//
//std::string Array16::to_bit_string() const
//{
//}
//
//std::array<int, 16> Array16::to_array() const
//{
//}
//

namespace arrays
{
	Array16 get_ordered(int length)
	{
		Array16 a;
		a.bits = utils::get_ordered(length);
		//swap(a, length - 1, 15);
		return a;
	}
	Array16 get_ordered(std::vector<int> order)
	{
		int length = order.size();
		assert(length <= 16);
		Array16 arr = Array16();
		for (int i = 0; i < length; i++)
		{
			put(arr, i, order[i]);
		}
		return arr;
	}
	void put(Array16& arr, int pos, int val)
	{
		assert(0 <= pos && pos < 16);
		assert(0 <= val && val <= 15);
		int shift = SIZE * pos;

		// zero mask
		uint64_t mask = ~(B << shift);

		// set bits at pos to zero
		arr.bits &= mask;

		arr.bits |= static_cast<uint64_t>(val) << shift;

	}

	int get(const Array16& arr, int pos)
	{
		assert(0 <= pos && pos < 16);
		int shift = SIZE * pos;
		uint64_t mask = B << shift;
		return (arr.bits & mask) >> shift;
	}

	void swap(Array16& arr, int pos1, int pos2)
	{
		assert(0 <= pos1 && pos2 < 16);
		assert(0 <= pos1 && pos2 < 16);
		pos1 *= SIZE;
		pos2 *= SIZE;
		uint64_t x = ((arr.bits >> pos1) ^ (arr.bits >> pos2)) & ((uint64_t(1) << SIZE) - 1);
		arr.bits = arr.bits ^ ((x << pos1) | (x << pos2));
	}

	std::string to_bit_string(const Array16& arr)
	{
		return bitset<64>(arr.bits).to_string();
	}

	std::string to_int_string(const Array16& arr)
	{
		std::stringstream ss;
		for (int i = 0; i < 16; i++)
		{
			ss << setw(3) << get(arr, i);
		}
		return ss.str();
	}

	std::array<int, 16> to_array(const Array16 & arr)
	{
		std::array<int, 16> a;
		for (int i = 0; i < 16; i++)
		{
			a[i] = get(arr, i);
		}
		return a;
	}

	bool operator<(const Array16& arr1, const Array16& arr2)
	{
		return arr1.bits < arr2.bits;
	}

	bool operator==(const Array16& arr1, const Array16& arr2)
	{
		return arr1.bits == arr2.bits;
	}

	//constexpr uint64_t get_ordered(int length, int i)
	//{
	//	return 
	//		(i >= length) 
	//		? 0
	//		: ((uint64_t(i)+1) << (i * 4)) | get_ordered(length, i+1);
	//}

}

//bool arrays::operator<(const Array16& arr1, const Array16& arr2)
//{
//	return false;
//}
