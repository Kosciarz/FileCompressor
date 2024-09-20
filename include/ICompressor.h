#pragma once


class ICompressor
{
public:
	virtual void Process();

	ICompressor() = default;

	ICompressor(const ICompressor&) = delete;

	ICompressor(ICompressor&&) = delete;

	ICompressor& operator=(const ICompressor&) = delete;

	ICompressor& operator=(ICompressor&&) = delete;

	virtual ~ICompressor() = default;
};
