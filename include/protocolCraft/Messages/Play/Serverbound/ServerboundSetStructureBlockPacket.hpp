#pragma once

#if PROTOCOL_VERSION > 385
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetStructureBlockPacket : public BaseMessage<ServerboundSetStructureBlockPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x25;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x28;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x28;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x29;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x2A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x2A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Structure Block";
        }

        virtual ~ServerboundSetStructureBlockPacket() override
        {

        }

        void SetPos(const NetworkPosition& pos_)
        {
            pos = pos_;
        }

        void SetUpdateType(const int update_type_)
        {
            update_type = update_type_;
        }

        void SetMode(const int mode_)
        {
            mode = mode_;
        }

        void SetName_(const std::string& name__)
        {
            name_ = name__;
        }

        void SetOffset(const NetworkPosition& offset_)
        {
            offset = offset_;
        }

        void SetSizeX(const NetworkPosition& size_)
        {
            size = size_;
        }

        void SetMirror(const int mirror_)
        {
            mirror = mirror_;
        }

        void SetRotation(const int rotation_)
        {
            rotation = rotation_;
        }

        void SetData(const std::string& data_)
        {
            data = data_;
        }

        void SetIntegrity(const float integrity_)
        {
            integrity = integrity_;
        }

        void SetSeed(const long long int seed_)
        {
            seed = seed_;
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }


        const NetworkPosition& GetPos() const
        {
            return pos;
        }

        const int GetUpdateType() const
        {
            return update_type;
        }

        const int GetMode() const
        {
            return mode;
        }

        const std::string& GetName_() const
        {
            return name_;
        }

        const NetworkPosition& GetOffset() const
        {
            return offset;
        }

        const NetworkPosition& GetSize() const
        {
            return size;
        }

        const int GetMirror() const
        {
            return mirror;
        }

        const int GetRotation() const
        {
            return rotation;
        }

        const std::string& GetData() const
        {
            return data;
        }

        const float GetIntegrity() const
        {
            return integrity;
        }

        const long long int GetSeed() const
        {
            return seed;
        }

        const char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            pos.Read(iter, length);
            update_type = ReadData<VarInt>(iter, length);
            mode = ReadData<VarInt>(iter, length);
            name_ = ReadData<std::string>(iter, length);
            offset.SetX(ReadData<char>(iter, length));
            offset.SetY(ReadData<char>(iter, length));
            offset.SetZ(ReadData<char>(iter, length));
            size.SetX(ReadData<char>(iter, length));
            size.SetY(ReadData<char>(iter, length));
            size.SetZ(ReadData<char>(iter, length));
            mirror = ReadData<VarInt>(iter, length);
            rotation = ReadData<VarInt>(iter, length);
            data = ReadData<std::string>(iter, length);
            integrity = ReadData<float>(iter, length);
            seed = ReadData<VarLong>(iter, length);
            flags = ReadData<char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            pos.Write(container);
            WriteData<VarInt>(update_type, container);
            WriteData<VarInt>(mode, container);
            WriteData<std::string>(name_, container);
            WriteData<char>(offset.GetX(), container);
            WriteData<char>(offset.GetY(), container);
            WriteData<char>(offset.GetZ(), container);
            WriteData<char>(size.GetX(), container);
            WriteData<char>(size.GetY(), container);
            WriteData<char>(size.GetZ(), container);
            WriteData<VarInt>(mirror, container);
            WriteData<VarInt>(rotation, container);
            WriteData<std::string>(data, container);
            WriteData<float>(integrity, container);
            WriteData<VarLong>(seed, container);
            WriteData<char>(flags, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["pos"] = pos.Serialize();
            output["update_type"] = update_type;
            output["mode"] = mode;
            output["name_"] = name_;
            output["offset"] = offset.Serialize();
            output["size"] = size.Serialize();
            output["mirror"] = mirror;
            output["rotation"] = rotation;
            output["data"] = data;
            output["integrity"] = integrity;
            output["seed"] = seed;
            output["flags"] = flags;

            return output;
        }

    private:
        NetworkPosition pos;
        int update_type;
        int mode;
        std::string name_;
        NetworkPosition offset;
        NetworkPosition size;
        int mirror;
        int rotation;
        std::string data;
        float integrity;
        long long int seed;
        char flags;

    };
} //ProtocolCraft
#endif