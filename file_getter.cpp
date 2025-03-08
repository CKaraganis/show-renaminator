#include "file_getter.h"
#include "show.h"

std::vector<show::Show> file::get_shows(std::filesystem::path& working_directory, std::filesystem::path& output_directory)
{
	auto show_subdirectories = std::filesystem::directory_iterator(working_directory);
	std::vector<show::Show> shows{};

	for (const std::filesystem::directory_entry& show_sub : show_subdirectories)
	{
		if (!std::filesystem::is_directory(show_sub) || std::filesystem::is_empty(show_sub))
			continue;

		show::Show show{};
		show.init(show_sub.path(), output_directory);

		auto season_subdirectories = std::filesystem::directory_iterator(show_sub);

		for (auto& season_sub : season_subdirectories)
		{
			if (!std::filesystem::is_directory(season_sub) || std::filesystem::is_empty(season_sub) || !season_sub.path().filename().string().contains("Season"))
				continue;

			show::Season season{};

			auto episodes = std::filesystem::directory_iterator(season_sub);
			season.init(season_sub.path(), show.get_new_path());

			for (auto& episode : episodes)
			{
				if (std::filesystem::is_directory(episode))
					continue;

				show::Episode ep;
				ep.init(episode.path(), season.get_new_path(), show.get_show_name(), season.get_season_number());
				auto episode_number = ep.get_episode_number();

				auto existing = find_if(season.episodes.begin(), season.episodes.end(), [episode_number](show::Episode e) {
					return e.get_episode_number() == episode_number;
					});
				if (existing != season.episodes.end())
					continue;

				season.episodes.push_back(ep);
			}

			if (!season.episodes.empty())
				show.seasons.push_back(season);
		}

		shows.push_back(show);
	}

	return shows;
}