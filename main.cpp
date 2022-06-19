#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>

#include "calendergenerator/htmlgenerator.h"

constexpr char HELP_OPTION[] = {"help"};
constexpr char YEAR_OPTION[] = {"year"};
constexpr char FILE_OPTION[] = {"file"};

boost::program_options::options_description commandline_options() {
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
      (HELP_OPTION, "produce help message")
      (YEAR_OPTION, po::value<int>(), "set year")
      (FILE_OPTION, po::value<std::string>(), "set output filename");

    return desc;
}

int main(int argc, char** argv) {
    namespace po = boost::program_options;

    auto const options = commandline_options();
    po::variables_map variables_map;
    po::store(po::parse_command_line(argc, argv, options), variables_map);
    po::notify(variables_map);

    if (variables_map.count(HELP_OPTION)) {
        std::cout << options << "\n";
        return 1;
    }

    if (!variables_map.count(YEAR_OPTION) || !variables_map.count(FILE_OPTION)) {
        std::cout << " set year and file options to continue\n" << options << "\n" << std::endl;
        return 1;
    }

    auto const html = calendergenerator::htmlgenerator::generate_calender(variables_map[YEAR_OPTION].as<int>());

    std::ofstream out(variables_map[FILE_OPTION].as<std::string>());
    out << html;
    out.close();

    return 0;
}
