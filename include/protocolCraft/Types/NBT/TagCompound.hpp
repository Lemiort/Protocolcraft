#pragma once

#include <memory>
#include <map>

#include "protocolCraft/Types/NBT/Tag.hpp"

namespace ProtocolCraft
{
    class TagCompound : public Tag
    {
    public:
        TagCompound();
        virtual ~TagCompound();

        const std::map<std::string, std::shared_ptr<Tag> >& GetValues() const;
        void SetValues(const std::map<std::string, std::shared_ptr<Tag> > &v);

        virtual const TagType GetType() const override;

        virtual void ReadImpl(ReadIterator &iterator, size_t &length) override;
        virtual void WriteImpl(WriteContainer &container) const override;
        virtual const nlohmann::json SerializeImpl() const override;

    private:
        std::map<std::string, std::shared_ptr<Tag> > tags;
    };
}