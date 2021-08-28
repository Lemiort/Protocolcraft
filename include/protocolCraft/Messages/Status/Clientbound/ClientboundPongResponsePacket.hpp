#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPongResponsePacket : public BaseMessage<ClientboundPongResponsePacket>
    {
    public:
        virtual const int GetId() const override
        {
            return 0x01;
        }

        virtual const std::string GetName() const override
        {
            return "Pong Response";
        }

        virtual ~ClientboundPongResponsePacket() override
        {

        }

        void SetTime(const long long int time_)
        {
            time = time_;
        }

        const long long int GetTime() const
        {
            return time;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            time = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<long long int>(time, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["time"] = time;

            return output;
        }

    private:
        long long int time;
    };
} //ProtocolCraft