#include <iostream>

#include "include/Message.h"
#include "include/Database.h"
#include "include/Display.h"

int get_branch_decision();
Database db = Database();

int main() {
	TermUtils termUtils;
	termUtils.initTermios(0);

	Display disp = Display(db.get_max_width(), db.get_max_height(), db.get_crawl_delay());

	int textAreaSize = 6;
	int maxArtSize = db.get_max_height() - textAreaSize;

	size_t i = 0;
	while (i >= 0 && i < db.gameData.size())
	{
		Message currentMessage = Message(db.gameData[i]);
		currentMessage.artwork = db.load_art_file(currentMessage.artwork, maxArtSize);

		disp.display(currentMessage);


		if (currentMessage.branchIndexes.empty())
		{
			i++;
		}
		else
		{
			int decision = 0;

			if (currentMessage.branchIndexes.size() > 1)
			{
				termUtils.resetTermios();
				decision = get_branch_decision();
				termUtils.initTermios(0);
			}

			// Reprint the current message if the decision is out of the bounds of the index vector
			if (decision >= 0 && decision < currentMessage.branchIndexes.size())
				i = currentMessage.branchIndexes[decision];
		}
	}

	termUtils.resetTermios();

	return 0;
}

int get_branch_decision()
{
	int offset = (db.get_max_width() / 2) - 3;
	std::string paddingLeft = std::string(offset, ' ');
	std::cout << paddingLeft << "~> ";
	int ans;
	while (true)
	{
		std::cin >> ans;
		if (!std::cin)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else break;
	}
	return ans;
}

