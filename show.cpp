#include "show.h"

static int parse_group_index(const std::filesystem::path& old_path)
{
	std::string delimter = "Title ";
	std::string str = old_path.filename().string();
	int start_index = str.find_first_of(delimter) + delimter.length() + 1;
	int end_index = str.find(".mp4");
	std::string sub = str.substr(start_index, end_index - start_index);
	return std::stoi(sub);
}

static int parse_group_number(const std::filesystem::path& old_path)
{
	std::string str = old_path.filename().string();
	int first_hyphen_index = str.find_first_of('-');
	std::string sub = str.substr(0, first_hyphen_index);
	return std::stoi(sub);
}

void show::Episode::init(const std::filesystem::path& old_path, const std::filesystem::path& season_path, const std::string& show_name, const int season_number)
{
	this->old_path = old_path;
	group_index = parse_group_index(old_path);
	group_number = parse_group_number(old_path);
	episode_number = group_number + group_index - 1;

	std::string file_name = show_name + " - s" + std::to_string(season_number) + 'e' + std::to_string(episode_number) + ".mp4";
	new_path = season_path / file_name;
}

static int parse_season_number(const std::filesystem::path old_path)
{
	std::string str = old_path.filename().string();
	std::string delimter = "Season ";
	int start_index = str.find_first_of(delimter) + delimter.length();
	int len = str.length();
	std::string sub = str.substr(start_index, len - start_index + 1);
	return std::stoi(sub);
}

void show::Season::init(const std::filesystem::path& old_path, const std::filesystem::path& show_path)
{
	this->old_path = old_path;
	season_number = parse_season_number(old_path);
	new_path = show_path / get_season_number_text();
}

void show::Show::init(const std::filesystem::path& old_path, const std::filesystem::path& output_directory)
{
	this->old_path = old_path;
	show_name = old_path.filename().string();
	new_path = output_directory / show_name;
}