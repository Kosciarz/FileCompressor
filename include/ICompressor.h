#pragma once


class ICompressor
{
public:
	virtual void Process() = 0;

	ICompressor() = default;

	ICompressor(const ICompressor&) = default;

	ICompressor(ICompressor&&) = default;

	ICompressor& operator=(const ICompressor&) = default;

	ICompressor& operator=(ICompressor&&) = default;

	virtual ~ICompressor() = default;
};
