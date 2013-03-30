#include "options.hpp"
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>

namespace po = boost::program_options;

namespace wanikani
{

Options::Options(int argc, char **argv)
	:helpRequested_(false)
{

	std::string colorBackgroundString, 
		colorUnseenString, 
		colorApprenticeString,
		colorGuruString,
		colorMasterString,
		colorEnlightenedString,
		colorBurnedString,
		colorErrorString;

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
		("color-background", po::value<std::string>(&colorBackgroundString)->default_value("0x000000"), "Color for background")
		("color-unseen", po::value<std::string>(&colorUnseenString)->default_value("0x303030"), "Color for unseen characters")
		("color-apprentice", po::value<std::string>(&colorApprenticeString)->default_value("0xDD0093"), "Color for apprentice characters")
		("color-guru", po::value<std::string>(&colorGuruString)->default_value("0x882D9E"), "Color for guru characters")
		("color-master", po::value<std::string>(&colorMasterString)->default_value("0x294DDB"), "Color for master characters")
		("color-enlightened", po::value<std::string>(&colorEnlightenedString)->default_value("0x0093DD"), "Color for enlightened characters")
		("color-burned", po::value<std::string>(&colorBurnedString)->default_value("0xFFFFFF"), "Color for burned characters")
		("color-error", po::value<std::string>(&colorErrorString)->default_value("0xFF0000"), "Color for error\'ed characters")
		("help", "Produce this help message")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, cmdline), vm);
	
	std::ifstream config_file("config.ini", std::ifstream::in);
	if(config_file.good())
	{
		po::store(po::parse_config_file(config_file, cmdline), vm);
	}
	
	po::notify(vm);

	if(vm.count("help"))
	{
		std::cout << cmdline << std::endl;
		std::cout << "These options can also be saved in a config.ini file in this directory.\n";
		helpRequested_ = true;
	}

	if(vm.count("apikey"))
	{
		apikey_ = vm["apikey"].as<std::string>();
	}

	colorBackground_ = Color(colorBackgroundString);
	colorUnseen_ = Color(colorUnseenString);
	colorApprentice_ = Color(colorApprenticeString);
	colorGuru_ = Color(colorGuruString);
	colorMaster_ = Color(colorMasterString);
	colorEnlightened_ = Color(colorEnlightenedString);
	colorBurned_ = Color(colorBurnedString);
	colorError_ = Color(colorErrorString);
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

const Color Options::colorBackground() const { return colorBackground_; }
const Color Options::colorUnseen() const { return colorUnseen_; }
const Color Options::colorApprentice() const { return colorApprentice_; }
const Color Options::colorGuru() const { return colorGuru_; }
const Color Options::colorMaster() const { return colorMaster_; }
const Color Options::colorEnlightened() const { return colorEnlightened_; }
const Color Options::colorBurned() const { return colorBurned_; }
const Color Options::colorError() const { return colorError_; }

const bool Options::helpRequested() const
{
	return helpRequested_;
}

}
