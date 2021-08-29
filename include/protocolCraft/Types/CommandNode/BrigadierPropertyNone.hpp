#pragma once

#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

namespace ProtocolCraft
{
    class BrigadierPropertyNone : public BrigadierProperty
    {
    public:
        virtual ~BrigadierPropertyNone()
        {

        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            return output;
        }

    private:
    };
}
#endif
