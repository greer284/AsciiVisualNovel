#pragma once
#include <thread>
#include <chrono>
#include "Message.h"
#include "TermUtils.h"

class Display 
{
private:
	void clear_screen();
	void crawl_text(std::string message, float crawlDelayMlt);
	std::string word_wrap(std::string message, int width);
	void print_messages(Message msg, bool centerText = false);
	void display_error(std::string errorMessage);

	int MAX_WIDTH;
	int MAX_HEIGHT;
	int crawlDelayMs;
protected:
public:
	Display(int width, int height, int delayMs) 
	{
		// Default values
		this->MAX_WIDTH = width;
		this->MAX_HEIGHT = height;
		this->crawlDelayMs = delayMs;
	}
	~Display() {}

	void display(Message msg);
};