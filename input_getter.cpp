#include "input_getter.h"

static void clear_istream(std::istream& input_stream)
{
	input_stream.clear();
	input_stream.ignore();
}

std::expected<std::filesystem::path, std::string> input_getter::get_working_directory_path(std::istream& input_stream, std::ostream& output_stream)
{
	std::filesystem::path path = std::filesystem::current_path();
	char selection{};

	output_stream << "The current directory is:\n\n" << path.string() << "\n\nIs this correct (y/n) >> ";
	input_stream >> selection;

	if (selection == 'y')
	{
		return path;
	}
	else if (selection == 'n')
	{
		std::string input{};

		output_stream << "Enter your working directory >> ";
		clear_istream(input_stream);
		getline(input_stream, input, '\n');
		path = input;

		if (!std::filesystem::exists(path))
			return std::unexpected("That path doesn't exist");

		return path;
	}

	return std::unexpected("That wasn't an option");
}

std::expected<std::filesystem::path, std::string> input_getter::get_output_directory_path(std::istream& input_stream, std::ostream& output_stream)
{
	std::filesystem::path path{};
	std::string input{};

	output_stream << "Enter your target directory (it will be created if it doesn't exist) >> ";
	getline(input_stream, input, '\n');
	path = input;

	if (std::filesystem::exists(path) && !std::filesystem::is_directory(path))
	{
		output_stream << "Enter your target DIRECTORY(NOT FILE) (it will be created if it doesn't exist) >> ";
		clear_istream(input_stream);
		getline(input_stream, input, '\n');
		path = input;

		if (!std::filesystem::is_directory(path))
		{
			return std::unexpected("Try again!!!");
		}
	}

	if (!std::filesystem::exists(path))
	{
		try
		{
			std::filesystem::create_directory(path);
		}
		catch (std::exception ex)
		{
			const std::string msgBase = "Failed to create the output directory: ";
			std::string msg = msgBase + ex.what();

			return std::unexpected(msg);
		}
	}

	return path;
}