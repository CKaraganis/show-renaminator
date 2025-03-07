#include <expected>
#include <filesystem>
#include <istream>
#include <iostream>
#include <limits>
#include <ostream>
#include <sstream>

#pragma once

namespace input_getter
{
	std::expected<std::filesystem::path, std::string> get_working_directory_path(std::istream& input_stream, std::ostream& output_stream);
	std::expected<std::filesystem::path, std::string> get_output_directory_path(std::istream& input_stream, std::ostream& output_stream);
}