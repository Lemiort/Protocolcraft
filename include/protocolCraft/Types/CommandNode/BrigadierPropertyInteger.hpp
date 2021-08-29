#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyInteger : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyInteger()
        {

        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }
        
        void SetMin(const int min_)
        {
            min = min_;
        }
        
        void SetMax(const int max_)
        {
            max = max_;
        }
        
        
        const char GetFlags() const
        {
            return flags;
        }
        
        const int GetMin() const
        {
            return min;
        }
        
        const int GetMax() const
        {
            return max;
        }

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
            if (flags & 0x01)
            {
                min = ReadData<int>(iter, length);
            }
            else
            {
                min = -2147483648;
            }
            if (flags & 0x02)
            {
                max = ReadData<int>(iter, length);
            }
            else
            {
                max = 2147483647;
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            if (flags & 0x01)
            {
                WriteData<int>(min, container);
            }
            if (flags & 0x02)
            {
                WriteData<int>(max, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["flags"] = flags;
            output["min"] = min;
            output["max"] = max;

            return output;
        }

    private:
        char flags;
        int min;
        int max;
    };
}
#endif
