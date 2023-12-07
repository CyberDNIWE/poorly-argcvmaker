#pragma once
#include <vector>

namespace poorly
{

class ArgCvMaker
{
public:
	ArgCvMaker() = default;
	ArgCvMaker(size_t newsize);
	~ArgCvMaker() = default;

	void reserve(size_t newsize, size_t bookKeepSizeScaler = 4);
	void reset() noexcept;

	void add(const std::string& data);
	
	// Any previously made ArgVs are invalidated
	char** makeArgV();
	size_t makeArgC() const noexcept;


private:
	size_t m_totalElements	= 0;
	size_t m_curIdx			= 0;

	std::vector<char>	m_data	= {};
	std::vector<size_t> m_idxs	= {};
	std::vector<char*>	m_argv	= {};
};


};
