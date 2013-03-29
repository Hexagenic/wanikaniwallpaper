#include <iostream>
#include "order.hpp"
#include "api.hpp"
#include "renderer.hpp"

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;

	wanikani::Renderer renderer(1024, 600, "/usr/share/fonts/OTF/ipag.ttf");

	wanikani::Order order;

	order.update(wanikani::API::get(argv[1]));

    renderer.render(order);
    renderer.save("out.png");
	return 0;
}
