#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class EntityLookAndRelativeMove : public BaseMessage<EntityLookAndRelativeMove>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x27;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x29;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x29;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575
			return 0x2A;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Look And Relative Move";
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const short GetDeltaX() const
        {
            return delta_x;
        }

        const short GetDeltaY() const
        {
            return delta_y;
        }

        const short GetDeltaZ() const
        {
            return delta_z;
        }

        const unsigned char GetYaw() const
        {
            return yaw;
        }

        const unsigned char GetPitch() const
        {
            return pitch;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadVarInt(iter, length);
            delta_x = ReadData<short>(iter, length);
            delta_y = ReadData<short>(iter, length);
            delta_z = ReadData<short>(iter, length);
            yaw = ReadData<unsigned char>(iter, length);
            pitch = ReadData<unsigned char>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        int entity_id;
        short delta_x;
        short delta_y;
        short delta_z;
        unsigned char yaw;
        unsigned char pitch;
        bool on_ground;
    };
} //Botcraft