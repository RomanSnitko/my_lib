#include <gtest/gtest.h>
#include "writer.hpp"
#include <fstream>
#include <string>

TEST(Writer, WriteFixedCreatesFileAndWritesText)
{
    const std::string path = "gtest_out.txt";
    ASSERT_TRUE(write_fixed(path));

    std::ifstream in(path);
    ASSERT_TRUE(in.good());

    std::string content;
    std::getline(in, content);
    ASSERT_FALSE(content.empty());
}

TEST(Writer, AppendFixedAppends)
{
    const std::string path = "gtest_append.txt";
    ASSERT_TRUE(write_fixed(path));
    ASSERT_TRUE(append_fixed(path));

    std::ifstream in(path);
    ASSERT_TRUE(in.good());

    std::string all((std::istreambuf_iterator<char>(in)),
                     std::istreambuf_iterator<char>());
    ASSERT_FALSE(all.empty());
}
