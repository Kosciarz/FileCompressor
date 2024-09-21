#pragma once

class ICompressor
{
public:
    virtual void Process() = 0;

    virtual ~ICompressor() = default;
};
