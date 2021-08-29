# Botcraft

![Linux](https://github.com/Lemiort/Protocolcraft/workflows/Linux/badge.svg) ![Windows](https://github.com/Lemiort/Protocolcraft/workflows/Windows/badge.svg)

ProtocolCraft is a full implementation of the minecraft protocol for all supported versions. It used to be based on the protocol description on the [Wiki](https://wiki.vg/Protocol). However, as it seems to no longer be up to date after 1.16.5, I transitioned it to be based on the [official source code mapping](https://www.minecraft.net/en-us/article/minecraft-snapshot-19w36a) provided by Mojang.

Transitioning from one protocol description to the other was a breaking change, as all the packets and many variable names were changed. But this should be easier to maintain and update in the future, as it is now directly based on the official game source code, instead of a third-party documentation.

## Dependencies

All dependencies are managed by conanfile so you need conan.

## Building and Installation

To build the library for the latest version of the game with both encryption and compression support, but without OpenGL rendering support:

```console
git clone git@github.com:Lemiort/Protocolcraft.git
cd Protocolcraft
mkdir build
cd build
conan install .. --build=missing
cmake -DGAME_VERSION=latest -DBOTCRAFT_COMPRESSION=ON -DBOTCRAFT_ENCRYPTION=ON ..
make all
```

There are several cmake options you can modify:

- GAME_VERSION [1.XX.X or latest]
- BOTCRAFT_COMPRESSION [ON/OFF] Add compression ability, must be ON to connect to a server with compression enabled
- BOTCRAFT_ENCRYPTION [ON/OFF] Add encryption ability, must be ON to connect to a server in online mode

## License

GPL v3
