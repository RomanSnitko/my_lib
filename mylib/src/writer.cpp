#include "writer.hpp"
#include <fstream>
#include <vector>

#include <zlib.h>

static const std::string str = "im not love a history";

bool write_fixed(const std::string& path)
{
    std::ofstream out(path);
    if (!out) return false;
    out << str;
    return true;
}

bool append_fixed(const std::string& path)
{
    std::ofstream out(path, std::ios::app);
    if (!out) return false;
    out << str;
    return true;
}

bool gzip_file(const std::string& in_path, const std::string& out_gz_path)
{
    std::ifstream in(in_path, std::ios::binary);
    if (!in) return false;

    gzFile out = gzopen(out_gz_path.c_str(), "wb");
    if (!out) return false;

    std::vector<char> buf(64 * 1024);
    while (in) 
    {
        in.read(buf.data(), (std::streamsize)buf.size());
        std::streamsize n = in.gcount();
        if (n > 0) 
        {
            int written = gzwrite(out, buf.data(), (unsigned)n);
            if (written == 0) 
            {
                gzclose(out);
                return false;
            }
        }
    }

    gzclose(out);
    return true;
}
