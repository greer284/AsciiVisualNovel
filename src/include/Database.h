#pragma once
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

class Database 
{
private:
	nlohmann::json load_json_data(std::string path);
	nlohmann::json settingsData;

	// Default values
	int maxWidth = 80;
	int maxHeight = 24;
	int crawlDelayMs = 30;

public:
	Database() 
	{ 
		this->gameData = load_json_data("GameData.json");
		this->settingsData = load_json_data("Settings.json");

		if (!settingsData["MAX_CONSOLE_WITH"].is_null())
		{
			int width = settingsData["MAX_CONSOLE_WITH"];

			if(width > maxWidth)
				this->maxWidth = width;
		}

		if (!settingsData["MAX_CONSOLE_HIGHT"].is_null())
		{
			int height = settingsData["MAX_CONSOLE_HIGHT"];

			if(height > maxHeight)
				this->maxHeight = height;
		}			

		if (!settingsData["CrawlDelayMs"].is_null())
		{
			int delayMs = settingsData["CrawlDelayMs"];

			if (delayMs >= 0)
				this->crawlDelayMs = delayMs;
		}
	}
	~Database() {}

	std::string load_art_file(std::string fileName, int linesToRead);
	nlohmann::json gameData;

	// Getters
	int get_max_height() { return maxHeight; }
	int get_max_width() { return maxWidth; }
	int get_crawl_delay() { return crawlDelayMs; }
};