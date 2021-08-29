#include <iostream>
#include <string>

#define PROTOCOL_VERSION 756 // from <botcraft/Version.hpp>
#include <protocolCraft/Handler.hpp>

class ExampleClient : public ProtocolCraft::Handler
{
        protected:
        virtual void Handle(ProtocolCraft::Message &msg) override{

        }
        virtual void Handle(ProtocolCraft::ClientboundLoginDisconnectPacket &msg) override{}
        virtual void Handle(ProtocolCraft::ClientboundGameProfilePacket &msg) override{}
        virtual void Handle(ProtocolCraft::ClientboundChangeDifficultyPacket &msg) override{}
#if PROTOCOL_VERSION < 755
        virtual void Handle(ProtocolCraft::ClientboundContainerAckPacket &msg) override{}
#endif
        virtual void Handle(ProtocolCraft::ClientboundDisconnectPacket &msg) override{}
        virtual void Handle(ProtocolCraft::ClientboundLoginPacket &msg) override{}
        virtual void Handle(ProtocolCraft::ClientboundPlayerPositionPacket &msg) override{}
        virtual void Handle(ProtocolCraft::ClientboundSetHealthPacket &msg) override{}
        virtual void Handle(ProtocolCraft::ClientboundPlayerAbilitiesPacket &msg) override{}
        virtual void Handle(ProtocolCraft::ClientboundRespawnPacket &msg) override{}
};

int main(int argc, char* argv[])
{
    {
        ExampleClient client;
        std::cout << "ExampleClient address = " << std::hex<<static_cast<void*>(&client) << std::endl;
    }

    std::cout<<"No errors occurred, exiting..."<<std::endl;
    return 0;
}