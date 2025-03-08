#include "file_copier.h"
#include <filesystem>

void file::create_copies(std::vector<show::Show>& shows)
{
	for (auto& show : shows)
	{
		if (!std::filesystem::exists(show.get_new_path()))
			std::filesystem::create_directory(show.get_new_path());

		for (auto& season : show.seasons)
		{
			if (!std::filesystem::exists(season.get_new_path()))
				std::filesystem::create_directory(season.get_new_path());

			for (auto& episode : season.episodes)
			{
				std::filesystem::copy_file(episode.get_old_path(), episode.get_new_path());
			}
		}
	}
}