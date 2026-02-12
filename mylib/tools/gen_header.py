import sys

out = sys.argv[1]
with open(out, "w", encoding="utf-8") as f:
    f.write("#pragma once\n")
    f.write('#define MYLIB_GENERATED_TEXT "im about to jump out of the window"\n')
