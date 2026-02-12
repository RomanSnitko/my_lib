#include <gtest/gtest.h>
#include "writer.hpp"
#include <fstream>

TEST(Gzip, CompressFile)
{
    const std::string in_path = "in.txt";
    const std::string out_path = "out.txt.gz";

    {
        std::ofstream out(in_path, std::ios::binary);
        ASSERT_TRUE((bool)out);
        out << "hello";
    }

    ASSERT_TRUE(gzip_file(in_path, out_path));

    std::ifstream gz(out_path, std::ios::binary);
    ASSERT_TRUE((bool)gz);
}
