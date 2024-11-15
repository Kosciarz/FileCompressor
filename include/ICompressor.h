#pragma once


class ICompressor
{
public:
    virtual void Run() = 0;

    virtual ~ICompressor() = default;
};
