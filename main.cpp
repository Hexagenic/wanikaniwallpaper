#include <iostream>
#include "order.hpp"
#include "api.hpp"
#include "renderer.hpp"
#include "options.hpp"

int main(int argc, char **argv)
{
	wanikani::Options options(argc, argv);

	if(!options.helpRequested() && options.apikey())
	{
		wanikani::Renderer renderer(options.width(), options.height(), options.fontFileName());

		wanikani::Order order;

		order.update(wanikani::API::get(options.apikey().get()));

		renderer.setMargins(options.marginLeft(), options.marginRight(), options.marginTop(), options.marginBottom());
		renderer.setBackground(options.colorBackground());
		renderer.setUnseen(options.colorUnseen());
		renderer.setApprentice(options.colorApprentice());
		renderer.setGuru(options.colorGuru());
		renderer.setMaster(options.colorMaster());
		renderer.setEnlightened(options.colorEnlightened());
		renderer.setBurned(options.colorBurned());
		renderer.setError(options.colorError());
		
		renderer.render(order);
		renderer.save(options.outFileName());
	}
	else if (!options.apikey() && !options.helpRequested())
	{
		std::cout << "Please provide an apikey. More info with --help.\n";
	}
	return 0;
}
