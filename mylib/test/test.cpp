#include "writer.hpp"

int main()
{
    if (mylib_version_string().empty()) return 1;
    if (mylib_generated_string().empty()) return 2;
    return 0;
}
