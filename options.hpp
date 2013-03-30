#pragma once

#include <string>
#include <boost/optional.hpp>

namespace wanikani
{

class Options
{
public:
	Options(int argc, char **argv);

    const boost::optional<std::string> apikey() const;
	const int width() const;
	const int height() const;
	const std::string outFileName() const;
	const std::string fontFileName() const;
	const int marginLeft() const;
	const int marginRight() const;
	const int marginTop() const;
	const int marginBottom() const;
	const bool helpRequested() const;
private:
	boost::optional<std::string> apikey_;
	int width_, height_;
	int marginLeft_, marginRight_, marginTop_, marginBottom_;
	std::string outFileName_;
	std::string fontFileName_;
	bool helpRequested_;
};

}
