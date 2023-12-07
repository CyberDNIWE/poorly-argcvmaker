#pragma once
#include <vector>

namespace poorly
{


class ArgCvMaker
{
public:
	struct ArgCV
	{
		size_t c;
		char** v;
	};

	ArgCvMaker() = default;
	ArgCvMaker(size_t newsize);
	~ArgCvMaker() = default;

	void reserve(size_t newsize, size_t bookKeepSizeScaler = 4);
	void reset() noexcept;
	void resetArgV() noexcept;

	// Any previously made ArgCVs are invalid after call
	void add(const std::string& data);
	
	// Any previously made ArgCVs are invalid after call
	const ArgCV& makeArgCV();


private:
	size_t m_totalElements	= 0;
	size_t m_curIdx			= 0;

	std::vector<char>	m_data	= {};
	std::vector<size_t> m_idxs	= {};
	std::vector<char*>	m_argv	= {};
	ArgCV				m_cv	= {};
};


};
