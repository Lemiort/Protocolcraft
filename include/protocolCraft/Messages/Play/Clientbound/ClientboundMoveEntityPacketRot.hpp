#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketRot : public BaseMessage<ClientboundMoveEntityPacketRot>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x28;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x2A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x2A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x2B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x2A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x29;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x2B;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Move Entity Rot";
        }

        virtual ~ClientboundMoveEntityPacketRot() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetYRot(const unsigned char yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const unsigned char xRot_)
        {
            xRot = xRot_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const unsigned char GetYRot() const
        {
            return yRot;
        }

        const unsigned char GetXRot() const
        {
            return xRot;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
            yRot = ReadData<unsigned char>(iter, length);
            xRot = ReadData<unsigned char>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<unsigned char>(yRot, container);
            WriteData<unsigned char>(xRot, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            output["yRot"] = yRot;
            output["xRot"] = xRot;
            output["on_ground"] = on_ground;

            return output;
        }

    private:
        int entity_id;
        unsigned char yRot;
        unsigned char xRot;
        bool on_ground;
    };
} //ProtocolCraft