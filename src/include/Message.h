#pragma once
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

class Message {
private:
public:
	Message(nlohmann::json jsonObject)
	{
		if(!jsonObject["artwork"].is_null())
			this->artwork = jsonObject["artwork"];

		if (!jsonObject["name"].is_null())
		{
			this->name = jsonObject["name"];

			if (!name.empty())
				this->name += ": ";
		}

		if (!jsonObject["messages"].is_null())
			this->messages = jsonObject["messages"];

		if (!jsonObject["delayMs"].is_null())
			this->delayMs = jsonObject["delayMs"];

		if (!jsonObject["crawlDelayMlt"].is_null())
			this->crawlDelayMlt = jsonObject["crawlDelayMlt"];

		if (!jsonObject["branchIndexes"].is_null()) {
			std::vector<size_t> temp = jsonObject["branchIndexes"];
			this->branchIndexes = temp;
		}


	}
	~Message() {}

	std::string artwork="";
	std::string name="";
	std::vector<std::string> messages = { };
	std::vector<size_t> branchIndexes;
	size_t delayMs = 0;
	float crawlDelayMlt = 1.0;
};