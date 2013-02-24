#pragma once

#include <vector>
#include <string>
#include "kanji.hpp"


namespace wanikani
{
class API
{
public:
	static std::vector<Kanji> get(std::string key); 
};
}
