#include <vector>
#include <filesystem>
#include "show.h";
#pragma once

namespace file
{
	std::vector<show::Show> get_shows(std::filesystem::path& working_directory, std::filesystem::path& output_directory);
}