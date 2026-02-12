#pragma once
#include <string>

bool write_fixed(const std::string& path);
bool append_fixed(const std::string& path);

bool gzip_file(const std::string& in_path, const std::string& out_gz_path);
