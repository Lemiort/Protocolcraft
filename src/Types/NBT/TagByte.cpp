#include "protocolCraft/Types/NBT/TagByte.hpp"

namespace ProtocolCraft
{
    TagByte::TagByte()
    {

    }

    TagByte::~TagByte()
    {

    }

    const char TagByte::GetValue() const
    {
        return value;
    }

    void TagByte::SetValue(const char v)
    {
        value = v;
    }

    const TagType TagByte::GetType() const
    {
        return TagType::Byte;
    }

    void TagByte::ReadImpl(ReadIterator &iterator, size_t &length)
    {
        value = ReadData<char>(iterator, length);
    }

    void TagByte::WriteImpl(WriteContainer &container) const
    {
        WriteData<char>(value, container);
    }

    const nlohmann::json TagByte::SerializeImpl() const
    {
        return nlohmann::json(value);
    }
}