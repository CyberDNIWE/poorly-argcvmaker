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

	// Checking case with lots of stuff
	{
		const poorly::ArgCvMaker::ArgCV& argcv = argMaker.makeArgCV();
		size_t my_argc = argcv.c;
		char** my_argv = argcv.v; // Yeeee!
		
		for(size_t i = 0; i < my_argc; ++i) // displays "First" "Second" etc
		{
			printf(my_argv[i]);
			printf("\n");
		}
	}
	
	// Checking case with previously made argCV, adding new strings after resetArgV()
	{
		argMaker.resetArgV();
		argMaker.add("Hey, hey hey, people, argV here!");

		const auto& argcv = argMaker.makeArgCV();
		size_t my_argc = argcv.c;
		char** my_argv = argcv.v;
		
		for(size_t i = 0; i < my_argc; ++i) // displays "First"etc and the added one
		{
			printf(my_argv[i]);
			printf("\n");
		}
	}
	// Checking case with no data
	{
		argMaker.reset();
		const auto& argcv = argMaker.makeArgCV();
		size_t my_argc = argcv.c;
		char** my_argv = argcv.v;

		printf(std::to_string(my_argc).c_str());
	}

	int dbg = 2;
}