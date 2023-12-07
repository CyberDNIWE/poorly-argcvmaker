// ArgcvparserSTL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <vector>
#include <array>

#include "ArgCvMaker.h"

struct SomeData 
{
	std::string m_data1;
	std::string m_data2;
	std::string m_data3;

	size_t size() const noexcept { return m_data1.size() + m_data2.size() + m_data3.size(); }
};

const std::array<SomeData, 2> datas = 
{
	SomeData{"First", "Second", "Third"},
	SomeData{"1", "2", "3"}
};

size_t getPredictedSize()
{
	size_t ret = 0;
	for(const auto& elem : datas)
	{
		ret += elem.size();
	}

	return ret;
}


int main(int argc, char **argv)
{
	const auto possibleSize = getPredictedSize();

	poorly::ArgCvMaker argMaker = {possibleSize};
	for(const auto& d : datas)
	{
		argMaker.add(d.m_data1);
		argMaker.add(d.m_data2);
		argMaker.add(d.m_data3);
	}

	//Checking case with lots of stuff
	{
		char** my_argv = argMaker.makeArgV(); // Yeeee!
		size_t my_argc = argMaker.makeArgC();
		
		for(size_t i = 0; i < my_argc; ++i) // displays "First" "Second" etc
		{
			printf(my_argv[i]);
			printf("\n");
		}
	}

	// Checking case with no data
	{
		argMaker.reset();
		char** my_argv = argMaker.makeArgV();
		size_t my_argc = argMaker.makeArgC();

		printf(std::to_string(my_argc).c_str());
	}

	int dbg = 2;
}