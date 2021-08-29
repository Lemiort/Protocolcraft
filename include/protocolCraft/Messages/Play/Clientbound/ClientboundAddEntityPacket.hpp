#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddEntityPacket : public BaseMessage<ClientboundAddEntityPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x00;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x00;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x00;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x00;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x00;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x00;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x00;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Add Entity";
        }

        virtual ~ClientboundAddEntityPacket() override
        {

        }

        void SetId_(const int id__)
        {
            id_ = id__;
        }

        void SetUUID(const UUID& uuid_)
        {
            uuid = uuid_;
        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetXa(const short xa_)
        {
            xa = xa_;
        }

        void SetYa(const short ya_)
        {
            ya = ya_;
        }

        void SetZa(const short za_)
        {
            za = za_;
        }

        void SetXRot(const Angle xRot_)
        {
            xRot = xRot_;
        }

        void SetYRot(const Angle yRot_)
        {
            yRot = yRot_;
        }

        void SetType(const char type_)
        {
            type = type_;
        }

        void SetData(const int data_)
        {
            data = data_;
        }

        const int GetId_() const
        {
            return id_;
        }

        const UUID& GetUUID() const
        {
            return uuid;
        }

        const double GetX() const
        {
            return x;
        }

        const double GetY() const
        {
            return y;
        }

        const double GetZ() const
        {
            return z;
        }

        const short GetXa() const
        {
            return xa;
        }

        const short GetYa() const
        {
            return ya;
        }

        const short GetZa() const
        {
            return za;
        }

        const Angle GetXRot() const
        {
            return xRot;
        }

        const Angle GetYRot() const
        {
            return yRot;
        }

        const char GetType() const
        {
            return type;
        }

        const int GetData() const
        {
            return data;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            id_ = ReadData<VarInt>(iter, length);
            uuid = ReadData<UUID>(iter, length);
#if PROTOCOL_VERSION < 458
            type = ReadData<char>(iter, length);
#else
            type = ReadData<VarInt>(iter, length);
#endif
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            xRot = ReadData<Angle>(iter, length);
            yRot = ReadData<Angle>(iter, length);
            data = ReadData<int>(iter, length);
            xa = ReadData<short>(iter, length);
            ya = ReadData<short>(iter, length);
            za = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(id_, container);
            WriteData<UUID>(uuid, container);
#if PROTOCOL_VERSION < 458
            WriteData<char>(type, container);
#else
            WriteData<VarInt>(type, container);
#endif
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(xRot, container);
            WriteData<Angle>(yRot, container);
            WriteData<int>(data, container);
            WriteData<short>(xa, container);
            WriteData<short>(ya, container);
            WriteData<short>(za, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["id_"] = id_;
            output["uuid"] = uuid;
            output["type"] = type;
            output["x"] = x;
            output["y"] = y;
            output["z"] = z;
            output["xRot"] = xRot;
            output["yRot"] = yRot;
            output["data"] = data;
            output["xa"] = xa;
            output["ya"] = ya;
            output["za"] = za;

            return output;
    }

    private:
        int id_;
        UUID uuid;
#if PROTOCOL_VERSION < 458
        char type;
#else
        int type;
#endif
        double x;
        double y;
        double z;
        short xa;
        short ya;
        short za;
        Angle xRot;
        Angle yRot;
        int data;

    };
} //ProtocolCraft