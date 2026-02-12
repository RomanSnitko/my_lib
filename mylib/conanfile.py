from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout, CMakeToolchain, CMakeDeps

class mylibRecipe(ConanFile):
    name = "mylib"
    version = "1.0.0"
    settings = "os", "ubuntu", "compiler", "build_type"

    exports_sources = (
        "CMakeLists.txt",
        "src/*",
        "include/*",
        "cmake/*",
        "tools/*",
        "test/*",
    )

    def requirements(self):
        self.requires("zlib/1.3.1")

    def build_requirements(self):
        self.test_requires("gtest/1.14.0")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure(variables={"MYLIB_BUILD_TESTS": "OFF"})
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "mylib")
        self.cpp_info.set_property("cmake_target_name", "mylib::mylib")
