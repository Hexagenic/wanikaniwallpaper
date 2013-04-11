#include "api.hpp"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
#include <utf8.h>

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
	std::string url = "http://www.wanikani.com/api/v1/user/" + key + "/kanji";

	if(curl)
	{

		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		res = curl_easy_perform(curl);
	}
	if(res)
	{
		std::cerr << "Error accesing api, " << curl_easy_strerror(res) << std::endl;
		exit(1);
	}
	
	Json::Value root;
	Json::Reader reader;

	bool successfullParse = reader.parse(buffer, root);

	if(!successfullParse)
	{
		std::cerr << "Was not able to parse api, is it really json?\n";
		exit(1);
	}

	Json::Value requested_information = root["requested_information"];
	
	if(requested_information.isNull())
	{
		Json::Value wanikani_error = root["error"];
		if(wanikani_error.isNull())
		{
			std::cerr << "Wanikani didn't return requested information, but did not return error either. Site might be under construction.\n";
			exit(1);
		}
		else
		{
			std::string errorCode = wanikani_error["code"].asString();
			std::string errorMessage = wanikani_error["message"].asString();
			std::cerr << "API error (" << errorCode << "): " << errorMessage << std::endl;
			exit(1);
		}

	}

	for(int i = 0; i < requested_information.size(); i++)
	{
		std::string character = requested_information[i]["character"].asString();

		const char *c_char = character.c_str();

		std::vector<int> wideChar;
		utf8::utf8to32(c_char, c_char + character.size(), back_inserter(wideChar));

        if(wideChar.size() != 1)
			std::cout << "Problem with: " << character << std::endl;

		Json::Value stats = requested_information[i]["stats"];
		WaniKaniSRS SRS;
		
		if(stats.isNull())
			SRS = SRS_UNSEEN;
		else
		{
			std::string SRSString = stats["srs"].asString();

			if(SRSString == "apprentice")
				SRS = SRS_APPRENTICE;
			else if(SRSString == "guru")
				SRS = SRS_GURU;
			else if(SRSString == "master")
				SRS = SRS_MASTER;
			else if(SRSString == "enlighten")
				SRS = SRS_ENLIGHTENED;
			else if(SRSString == "burned")
				SRS = SRS_BURNED;
			else
				SRS = SRS_ERROR;
		}
		list.push_back(Kanji(wideChar[0], SRS));
	}

	return list;
}

}
