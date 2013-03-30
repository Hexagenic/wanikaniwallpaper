#include "options.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

namespace wanikani
{

Options::Options(int argc, char **argv)
	:helpRequested_(false)
{
	po::options_description cmdline("Command line options");
	cmdline.add_options()
		("apikey,k", po::value<std::string>(), "API key")
		("width,w", po::value<int>(&width_)->default_value(1920), "Width of wallpaper")
		("height,h", po::value<int>(&height_)->default_value(1080), "Height of wallpaper")
		("out,o", po::value<std::string>(&outFileName_)->default_value("out.png"), "Output filename")
		("font,f", po::value<std::string>(&fontFileName_)->default_value("ipag.ttf"), "Relative or absolute font filepath")
		("margin-left", po::value<int>(&marginLeft_)->default_value(0), "Space to leave blank to the left")
		("margin-right", po::value<int>(&marginRight_)->default_value(0), "Space to leave blank to the right")
		("margin-top", po::value<int>(&marginTop_)->default_value(0), "Space to leave blank to the top")
		("margin-bottom", po::value<int>(&marginBottom_)->default_value(0), "Space to leave blank to the bottom")
		("help", "Produce this help message")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, cmdline), vm);
	po::notify(vm);

	if(vm.count("help"))
	{
		std::cout << cmdline << std::endl;
		helpRequested_ = true;
	}

	if(vm.count("apikey"))
	{
		apikey_ = vm["apikey"].as<std::string>();
	}

}

const boost::optional<std::string> Options::apikey() const
{
	return apikey_;
}

const int Options::width() const
{
	return width_;
}

const int Options::height() const
{
	return height_;
}

const std::string Options::outFileName() const
{
	return outFileName_;
}

const std::string Options::fontFileName() const
{
	return fontFileName_;
}

const int Options::marginLeft() const { return marginLeft_; }
const int Options::marginRight() const { return marginRight_; }
const int Options::marginTop() const { return marginTop_; }
const int Options::marginBottom() const { return marginBottom_; }

const bool Options::helpRequested() const
{
	return helpRequested_;
}

}
