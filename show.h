#ifndef SHOW_H
#define SHOW_H

#include <filesystem>
#include <vector>

namespace show
{
	class Episode {
	private:
		std::filesystem::path old_path;
		std::filesystem::path new_path;
		int group_number;
		int group_index;
		int episode_number;

	public:
		void init(const std::filesystem::path& old_path, const std::filesystem::path& season_path, const std::string& show_name, const int season_number);
		int get_group_number() { return group_number; }
		int get_group_index() { return group_index; }
		int get_episode_number() { return episode_number; }
		std::filesystem::path get_old_path() { return old_path; }
		std::filesystem::path get_new_path() { return new_path; }
	};

	class Season {
	private:
		std::filesystem::path old_path;
		std::filesystem::path new_path;
		int season_number;
	public:
		std::vector<Episode> episodes;
		void init(const std::filesystem::path& old_path, const std::filesystem::path& show_path);
		int get_season_number() { return season_number; }
		std::string get_season_number_text() { return "Season " + std::to_string(season_number); }
		std::filesystem::path get_old_path() { return old_path; }
		std::filesystem::path get_new_path() { return new_path; }
	};

	class Show {
	private:
		std::filesystem::path old_path;
		std::filesystem::path new_path;
		std::string show_name;
	public:
		std::vector<Season> seasons;
		void init(const std::filesystem::path& old_path, const std::filesystem::path& output_directory);
		std::string get_show_name() { return show_name; }
		std::filesystem::path get_old_path() { return old_path; }
		std::filesystem::path get_new_path() { return new_path; }
	};
}
#endif