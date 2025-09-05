#include "include/Display.h"

void Display::display(Message msg)
{
	clear_screen();

	bool hasArt = !msg.artwork.empty();
	bool hasText = !msg.messages.empty();

	// If both art and messages present, display normal
	if (hasArt && hasText)
	{
		std::cout << msg.artwork << std::string(MAX_WIDTH, '=') << "\n\n";
		print_messages(msg, false);
	}
	// If art is empty only display text
	else if (!hasArt && hasText)
	{
		// Align the height of the messages to the centre of the console
		int centerText = (MAX_HEIGHT / 2) - msg.messages.size();
		std::cout << std::string(centerText, '\n');

		print_messages(msg, true);
	}
	// If messages are empty display the artwork only
	else if (hasArt && !hasText)
	{
		std::cout << msg.artwork
			<< std::string(MAX_WIDTH, '=') << "\n\n";
		system("pause");
	}
	// Neither text nor art were supplied
	else
	{
		display_error("Error: Neither Artwork nor Message was supplied to the display function in main.cpp");
	}
}

void Display::print_messages(Message msg, bool centerText)
{
	if (!msg.name.empty())
	{
		std::cout << msg.name;
	}

	for (size_t i = 0; i < msg.messages.size(); i++)
	{
		std::string message = msg.messages[i];
		std::string wrappedText;
		std::string paddingLeft = "";

		if (centerText && message.size() < MAX_WIDTH)
		{
			int paddingAmount = (MAX_WIDTH - message.size()) / 2;
			paddingLeft = std::string(paddingAmount, ' ');
			std::cout << paddingLeft;
		}

		if (i == 0)
		{
			wrappedText = word_wrap((paddingLeft + msg.name + message), MAX_WIDTH);
			wrappedText.erase(0, (paddingLeft.size() + msg.name.size()));
		}
		else
		{
			wrappedText = word_wrap((paddingLeft + message), MAX_WIDTH);
			wrappedText.erase(0, paddingLeft.size());
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(msg.delayMs));

		crawl_text(wrappedText, msg.crawlDelayMlt);
	}
}

void Display::crawl_text(std::string message, float crawlSpeed)
{
	TermUtils termUtils;
	int tempDelayMs = crawlDelayMs * crawlSpeed;
	bool isInput = false;
	bool kbhitBool = false;

	for (char& c : message) {
		if (termUtils.kbhit())
			kbhitBool = true;

		// check if the message begins with a char between '0' and '9'
		if (c >= '0' && c <= '9')
			isInput = true;

		if (isInput || kbhitBool)
			tempDelayMs = 0;

		std::cout << c;
		fflush(stdout);
		std::this_thread::sleep_for(std::chrono::milliseconds(tempDelayMs));

		// Add a little pause for punctuation.
		if(c == '.' || c == ',' || c == '?' || c == '!')
			std::this_thread::sleep_for(std::chrono::milliseconds(tempDelayMs * 2));
	}
	if (kbhitBool)
		termUtils.kbhit();

	if (!isInput)
		termUtils.kbhit();

	std::cout << std::endl;
}

std::string Display::word_wrap(std::string message, int width)
{
	std::string ans = message;
	size_t lastSpacePos = -1;
	for (size_t i = 0; i < message.length(); i++)
	{
		if (message[i] == ' ')
		{
			lastSpacePos = i;
		}

		if (i > 0 && i % width == 0)
		{
			ans.replace(lastSpacePos, 1, 1, '\n');
		}
	}

	return ans;
}

void Display::display_error(std::string errorMessage)
{
	clear_screen();
	std::cout << errorMessage << "\nExiting Game...";
	exit(0);
}

void Display::clear_screen()
{
	// Clear the screen and move the cursor to the top left
	std::cout << "\033[2J\033[1;1H";
}