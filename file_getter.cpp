#include "file_getter.h"


int file_getter::Episode::get_group_number() {
	std::string str = old_path.filename().string();
	int first_hyphen_index = str.find_first_of('-');
	std::string sub = str.substr(0, first_hyphen_index);
	return std::stoi(sub);
}

int file_getter::Episode::get_group_index() {
	std::string delimter = "Title ";
	std::string str = old_path.filename().string();
	int start_index = str.find_first_of(delimter) + delimter.length() + 1;
	int end_index = str.find(".mp4");
	std::string sub = str.substr(start_index, end_index - start_index);
	return std::stoi(sub);
}

int file_getter::Episode::get_episode_number() {
	int group_number = get_group_number();
	int group_index = get_group_index();
	return group_number + group_index - 1;
}

int file_getter::Season::get_season_number() {
	std::string str = old_path.filename().string();
	std::string delimter = "Season ";
	int start_index = str.find_first_of(delimter) + delimter.length();
	int len = str.length();
	std::string sub = str.substr(start_index, len - start_index + 1);
	return std::stoi(sub);
}

std::vector<file_getter::Show> file_getter::get_shows(std::filesystem::path working_directory)
{
	auto show_subdirectories = std::filesystem::directory_iterator(working_directory);
	std::vector<file_getter::Show> shows{};

	for (auto show_sub : show_subdirectories)
	{
		if (!std::filesystem::is_directory(show_sub) || std::filesystem::is_empty(show_sub))
			continue;

		file_getter::Show show{};

		auto season_subdirectories = std::filesystem::directory_iterator(show_sub);

		for (auto season_sub : season_subdirectories)
		{
			if (!std::filesystem::is_directory(season_sub) || std::filesystem::is_empty(season_sub) || !season_sub.path().filename().string().contains("Season"))
				continue;

			file_getter::Season season{};

			auto episodes = std::filesystem::directory_iterator(season_sub);
			season.old_path = season_sub.path();

			for (auto episode : episodes)
			{
				if (std::filesystem::is_directory(episode))
					continue;

				file_getter::Episode ep;
				ep.old_path = episode.path();

				season.episodes.push_back(ep);
			}

			if (!season.episodes.empty())
				show.seasons.push_back(season);
		}

		shows.push_back(show);
	}

	return shows;
}