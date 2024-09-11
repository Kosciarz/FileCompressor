#pragma once

#include <map>
#include <string>


class Base {
protected:
    int m_DictSize = 256;
    std::map<std::string, int> m_Dict;
};
