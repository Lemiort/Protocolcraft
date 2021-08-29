#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetExperiencePacket : public BaseMessage<ClientboundSetExperiencePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x40;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x43;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x47;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x48;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x48;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x48;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x51;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Experience";
        }

        virtual ~ClientboundSetExperiencePacket() override
        {

        }

        void SetExperienceProgress(const float experience_progress_)
        {
            experience_progress = experience_progress_;
        }

        void SetTotalExperience(const int total_experience_)
        {
            total_experience = total_experience_;
        }

        void SetExperienceLevel(const int experience_level_)
        {
            experience_level = experience_level_;
        }


        const float GetExperienceProgress() const
        {
            return experience_progress;
        }

        const int GetTotalExperience() const
        {
            return total_experience;
        }

        const int GetExperienceLevel() const
        {
            return experience_level;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            experience_progress = ReadData<float>(iter, length);
            experience_level = ReadData<VarInt>(iter, length);
            total_experience = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(experience_progress, container);
            WriteData<VarInt>(experience_level, container);
            WriteData<VarInt>(total_experience, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["experience_progress"] = experience_progress;
            output["experience_level"] = experience_level;
            output["total_experience"] = total_experience;

            return output;
        }

    private:
        float experience_progress;
        int total_experience;
        int experience_level;

    };
} //ProtocolCraft