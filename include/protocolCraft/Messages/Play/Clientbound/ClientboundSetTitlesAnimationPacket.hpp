#pragma once

#if PROTOCOL_VERSION > 754
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTitlesAnimationPacket : public BaseMessage<ClientboundSetTitlesAnimationPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x5A;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Titles Animation";
        }

        virtual ~ClientboundSetTitlesAnimationPacket() override
        {

        }


        void SetFadeIn(const int fade_in_)
        {
            fade_in = fade_in_;
        }

        void SetStay(const int stay_)
        {
            stay= stay_;
        }

        void SetFadeOut(const int fade_out_)
        {
            fade_out= fade_out_;
        }


        const int GetFadeIn() const
        {
            return fade_in;
        }

        const int GetStay() const
        {
            return stay;
        }

        const int GetFadeOut() const
        {
            return fade_out;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            fade_in = ReadData<int>(iter, length);
            stay = ReadData<int>(iter, length);
            fade_out = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(fade_in, container);
            WriteData<int>(stay, container);
            WriteData<int>(fade_out, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["fade_in"] = fade_in;
            output["stay"] = stay;
            output["fade_out"] = fade_out;

            return output;
        }

    private:
        int fade_in;
        int stay;
        int fade_out;

    };
} //ProtocolCraft
#endif