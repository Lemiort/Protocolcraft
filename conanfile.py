from conans import ConanFile, CMake, tools
from conans.errors import ConanInvalidConfiguration


class ProtocolcraftConan(ConanFile):
    name = "protocolcraft"
    version = "0.1.0"
    license = "GPL-3.0-or-later"
    url = "https://github.com/Lemiort/Protocolcraft"
    description = "Protocolcraft is a cross-platform C++ library to connect with Minecraft servers."
    topics = ("minecraft", "protcol")
    settings = "os", "compiler", "build_type", "arch"
    options = { "compression": [
        True, False], "encryption": [True, False], "game_version": "ANY",
        "fPIC": [True, False]}
    default_options = {
                       "compression": True, "encryption": True, "game_version": "latest",
                        "fPIC": True}
    generators = "cmake"

    exports_sources =  "src/*", "include/*", "CMakeLists.txt",  "Assets/*", 
    _cmake = None

    @property
    def _source_subfolder(self):
        return "source_subfolder"

    def _supports_cpp17(self):
        supported_compilers = [
            ("gcc", "7"), ("clang", "5"), ("apple-clang", "10"), ("Visual Studio", "15.7")]
        compiler = self.settings.compiler
        version = tools.Version(compiler.version)
        return any(compiler == sc[0] and version >= sc[1] for sc in supported_compilers)

    def configure(self):
        if self.settings.compiler.get_safe("cppstd"):
            tools.check_min_cppstd(self, "17")
        elif not self._supports_cpp17():
            raise ConanInvalidConfiguration("Protocolcraft requires C++17 support")

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def requirements(self):
        self.requires("asio/1.18.2")
        self.requires("nlohmann_json/3.9.1")
        if self.options.compression:
            self.requires("zlib/1.2.11")
        if self.options.encryption:
            self.requires("openssl/1.1.1k")


    def _configure_cmake(self):
        if self._cmake:
            return self._cmake
        self._cmake = CMake(self)


        self._cmake.definitions["PROTOCOLCRAFT_COMPRESSION"] = self.options.compression
        self._cmake.definitions["PROTOCOLCRAFT_ENCRYPTION"] = self.options.encryption
        self._cmake.configure()
        return self._cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        self.copy("LICENSE", dst="licenses", src=self._source_subfolder)
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["protocolCraft"]
