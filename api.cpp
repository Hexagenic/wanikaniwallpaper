#include "api.hpp"
#include <sstream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

std::stringstream buffer;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	const char *data = (const char*)ptr;
	buffer.write(data, size * nmemb);
	return size * nmemb;
}

namespace wanikani
{

std::vector<Kanji> API::get(std::string key)
{
	std::vector<Kanji> list;

	CURL *curl = curl_easy_init();
	CURLcode res;

	if(curl)
	{
		std::string url = "http://www.wanikani.com/api/user/" + key + "/kanji";

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		res = curl_easy_perform(curl);
	}
	
	Json::Value root;
	Json::Reader reader;

	reader.parse(buffer, root);

	Json::Value requested_information = root["requested_information"];
	
	for(int i = 0; i < requested_information.size(); i++)
	{
		std::string character = requested_information[i]["character"].asString();
		
		Json::Value stats = requested_information[i]["stats"];
		Knowledge knowledge;
		
		if(stats.isNull())
			knowledge = UNSEEN;
		else
		{
			std::string srs = requested_information[i]["stats"]["srs"].asString();

			if(srs == "apprentice")
				knowledge = APPRENTICE;
			else if(srs == "guru")
				knowledge = GURU;
			else if(srs == "master")
				knowledge = MASTER;
			else if(srs == "enlighten")
				knowledge = ENLIGHTENED;
			else if(srs == "burned")
				knowledge = BURNED;
			else
				knowledge = ERROR;
		}
		list.push_back(Kanji(character, knowledge));
	}

	return list;
}

}
