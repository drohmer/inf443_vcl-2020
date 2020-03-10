#pragma once

#include <string>

namespace vcl
{

void assert_file_exist(const std::string& filename);

/** Read a file given by its path and return its content as a string */
std::string read_file_text(const std::string& filename);

}
