#include "input_getter.h"
#include "file_getter.h"
#include "file_copier.h"
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

	auto shows = file::get_shows(working_directory.value(), output_directory.value());

	if (shows.empty())
	{
		std::cout << "No Shows found at " << working_directory.value().string() << '\n';
		return -1;
	}

	file::create_copies(shows);

	return 0;
}
