#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundBossEventPacket : public BaseMessage<ClientboundBossEventPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0C;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0D;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x0C;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0C;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x0D;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Boss Event";
        }

        virtual ~ClientboundBossEventPacket() override
        {

        }

        void SetId_(const UUID& id__)
        {
            id_ = id__;
        }

        void SetOperation(const int operation_)
        {
            operation = operation_;
        }

        void SetName_(const Chat& name__)
        {
            name_ = name__;
        }

        void SetPct(const float pct_)
        {
            pct = pct_;
        }

        void SetColor(const int color_)
        {
            color = color_;
        }

        void SetOverlay(const int overlay_)
        {
            overlay = overlay_;
        }

        void SetFlags(const unsigned char flags_)
        {
            flags = flags_;
        }


        const UUID& GetId_() const
        {
            return id_;
        }

        const int GetOperation() const
        {
            return operation;
        }

        const Chat& GetName_() const
        {
            return name_;
        }

        const float GetPct() const
        {
            return pct;
        }

        const int GetColor() const
        {
            return color;
        }

        const int GetOverlay() const
        {
            return overlay;
        }

        const unsigned char GetFlags() const
        {
            return flags;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            id_ = ReadData<UUID>(iter, length);
            operation = ReadData<VarInt>(iter, length);
            switch (operation)
            {
            case 0:
                name_.Read(iter, length);
                pct = ReadData<float>(iter, length);
                color = ReadData<VarInt>(iter, length);
                overlay = ReadData<VarInt>(iter, length);
                flags = ReadData<unsigned char>(iter, length);
                break;
            case 1:
                break;
            case 2:
                pct = ReadData<float>(iter, length);
                break;
            case 3:
                name_.Read(iter, length);
                break;
            case 4:
                color = ReadData<VarInt>(iter, length);
                overlay = ReadData<VarInt>(iter, length);
                break;
            case 5:
                flags = ReadData<unsigned char>(iter, length);
                break;
            default:
                break;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<UUID>(id_, container);
            WriteData<VarInt>((int)operation, container);
            switch (operation)
            {
            case 0:
                name_.Write(container);
                WriteData<float>(pct, container);
                WriteData<VarInt>(color, container);
                WriteData<VarInt>(overlay, container);
                WriteData<unsigned char>(flags, container);
                break;
            case 1:
                break;
            case 2:
                WriteData<float>(pct, container);
                break;
            case 3:
                name_.Write(container);
                break;
            case 4:
                WriteData<VarInt>(color, container);
                WriteData<VarInt>(overlay, container);
                break;
            case 5:
                WriteData<unsigned char>(flags, container);
                break;
            default:
                break;
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["id_"] = id_;
            output["operation"] = operation;

            switch (operation)
            {
            case 0:
                output["name_"] = name_.Serialize();
                output["pct"] = pct;
                output["color"] = color;
                output["overlay"] = overlay;
                output["flags"] = flags;
                break;
            case 1:
                break;
            case 2:
                output["pct"] = pct;
                break;
            case 3:
                output["name_"] = name_.Serialize();
                break;
            case 4:
                output["color"] = color;
                output["overlay"] = overlay;
                break;
            case 5:
                output["flags"] = flags;
                break;
            default:
                break;
            }

            return output;
        }

    private:
        UUID id_;
        int operation;
        Chat name_;
        float pct;
        int color;
        int overlay;
        unsigned char flags;

    };
} //ProtocolCraft