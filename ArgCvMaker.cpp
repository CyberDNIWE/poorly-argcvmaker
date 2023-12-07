#include <string>
#include "ArgCvMaker.h"

using namespace poorly;

namespace // unnamed namespace
{
	static char _null_term = '\0';
};

ArgCvMaker::ArgCvMaker(size_t newsize)
{
	reserve(newsize);
}

void ArgCvMaker::reserve(size_t newsize, size_t bookKeepSizeScaler)
{
	m_data.reserve(newsize);
	m_idxs.reserve(newsize / (bookKeepSizeScaler > 0 ? bookKeepSizeScaler : 1));
}

void ArgCvMaker::reset() noexcept
{
	m_totalElements = 0;
	m_curIdx = 0;

	m_data.clear();
	m_idxs.clear();
}

void ArgCvMaker::add(const std::string& data)
{
	m_idxs.emplace_back(m_curIdx);
	for(const auto& character : data)
	{
		m_data.emplace_back(character);
		++m_curIdx;
	}
	// C-str spec ends in null term
	m_data.emplace_back(_null_term);
	++m_curIdx;
	// Update total elements
	++m_totalElements;
}

const ArgCvMaker::ArgCV& ArgCvMaker::makeArgCV()
{
	m_argv.clear();
	if(m_totalElements)
	{
		m_argv.reserve(m_totalElements);

		for(const auto& index : m_idxs)
		{
			m_argv.emplace_back(&m_data[index]);
		}
	}
	else// Fill with empty c-str, in case someone tries to access
	{	// without prior nullptr checking (which nobody does anyway)
		m_argv.emplace_back(&_null_term);
	}

	m_cv = { m_totalElements, &m_argv[0] };
	return m_cv;
}
