#include "input_getter.h"
#include "file_getter.h"
#include <vector>

int main()
{
	auto working_directory = input_getter::get_working_directory_path(std::cin, std::cout);
	if (!working_directory.has_value()) {
		std::cout << working_directory.error() << '\n';
		return -1;
	}

	auto output_directory = input_getter::get_output_directory_path(std::cin, std::cout);
	if (!working_directory.has_value()) {
		std::cout << output_directory.error() << '\n';
		return -2;
	}

	auto shows = file_getter::get_shows(working_directory.value());

	std::cout << "Found " << shows.size() << " shows.\n";
	
	for (auto& sh : shows)
	{
		std::cout << sh.old_path.filename() << " (" << sh.seasons.size() << "): " << sh.old_path << '\n';
		for (auto& se : sh.seasons)
		{
			std::cout << "\tSeason " << se.get_season_number() << " (" << se.episodes.size() << "): " << se.old_path << '\n';
			for (auto& ep : se.episodes)
			{
				std::cout << "\t\tEpisode " << ep.get_episode_number() << ": " << ep.old_path << '\n';
			}
		}
	}

	return 0;
}
