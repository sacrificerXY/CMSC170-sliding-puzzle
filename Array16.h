#pragma once
#include <cstdint>
#include <string>
#include <array>
#include <vector>


//struct Array16
//{
//	int bits = 1;
//};

namespace arrays
{
	struct Array16
	{
		uint64_t bits;
	};

	Array16 get_ordered(int length);
	Array16 get_ordered(std::vector<int> order);


	void put(Array16& arr, int pos, int val);
	int get(const Array16& arr, int pos);

	void swap(Array16& arr, int pos1, int pos2);

	std::string to_bit_string(const Array16& arr);
	std::string to_int_string(const Array16& arr);
	
	std::array<int, 16> to_array(const Array16 & arr);

	bool operator< (const Array16& arr1, const Array16& arr2);
	bool operator== (const Array16& arr1, const Array16& arr2);

	namespace utils
	{

		constexpr uint64_t get_ordered(int length, int i = 0)
		{
			return
				(i >= length - 1)
				? 0
				: ((uint64_t(i) + 1) << (i * 4)) | get_ordered(length, i + 1);
		}

	}
}


	//void set(int pos, int val);




