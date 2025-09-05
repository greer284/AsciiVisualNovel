#include "include/Database.h"

nlohmann::json Database::load_json_data(std::string path)
{
	std::ifstream File;
    nlohmann::json jsonResult;

	File.open(path, std::ios::in); // Add some error handling here

    if (File.is_open())
    {
        jsonResult = nlohmann::json::parse(File);
    }
    else
    {
        //std::cout << "Cannot open file for reading.\n";
    }

	File.close();

	return jsonResult;
}

std::string Database::load_art_file(std::string artFile, int linesToRead)
{
    if (artFile.empty())
        return "";

    std::ifstream File;
    std::string path = "GameArt/" + artFile;
    std::string line;
    std::string result = "";

    File.open(path, std::ios::in);

    // check if file successfully opened
    if (File.is_open())
    {
        // Read each line in ifstream to string using '\n' delimeter
        for (size_t i = 0; i < linesToRead; i++)
        {
            if(getline(File, line, '\n'))
                result.append(line + '\n');
        }
    }
    else
    {
        result = "Error: Cannot open file for reading.\n";
    }

    File.close();

    return result;
}