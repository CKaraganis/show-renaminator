#include <vector>
#include <filesystem>
#pragma once

namespace file_getter
{
	class Episode {
	public:
		std::filesystem::path old_path;
		std::filesystem::path new_path;

		int get_group_number();
		int get_group_index();
		int get_episode_number();
	};

	class Season {
	public:
		std::filesystem::path old_path;
		std::filesystem::path new_path;
		std::vector<Episode> episodes;

		int get_season_number();
	};

	class Show {
	public:
		std::filesystem::path old_path;
		std::filesystem::path new_path;
		std::vector<Season> seasons;
	};

	std::vector<Show> get_shows(std::filesystem::path working_directory);
}