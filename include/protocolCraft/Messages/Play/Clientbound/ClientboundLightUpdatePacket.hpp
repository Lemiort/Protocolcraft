#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 404
namespace ProtocolCraft
{
    class ClientboundLightUpdatePacket : public BaseMessage<ClientboundLightUpdatePacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x24;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x25;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x24;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x23;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x25;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Light Update";
        }

        virtual ~ClientboundLightUpdatePacket() override
        {

        }

        void SetX(const int x_)
        {
            x = x_;
        }

        void SetZ(const int z_)
        {
            z = z_;
        }

#if PROTOCOL_VERSION < 755
        void SetSkyYMask(const int sky_Y_mask_)
        {
            sky_Y_mask = sky_Y_mask_;
        }

        void SetBlockYMask(const int block_Y_mask_)
        {
            block_Y_mask = block_Y_mask_;
        }

        void SetEmptySkyYMask(const int empty_sky_Y_mask_)
        {
            empty_sky_Y_mask = empty_sky_Y_mask_;
        }

        void SetEmptyBlockYMask(const int empty_block_Y_mask_)
        {
            empty_block_Y_mask = empty_block_Y_mask_;
        }
#else
        void SetSkyYMask(const std::vector<unsigned long long int>& sky_Y_mask_)
        {
            sky_Y_mask = sky_Y_mask_;
        }

        void SetBlockYMask(const std::vector<unsigned long long int>& block_Y_mask_)
        {
            block_Y_mask = block_Y_mask_;
        }

        void SetEmptySkyYMask(const std::vector<unsigned long long int>& empty_sky_Y_mask_)
        {
            empty_sky_Y_mask = empty_sky_Y_mask_;
        }

        void SetEmptyBlockYMask(const std::vector<unsigned long long int>& empty_block_Y_mask_)
        {
            empty_block_Y_mask = empty_block_Y_mask_;
        }
#endif

        void SetSkyUpdates(std::vector<std::vector<char> >& sky_updates_)
        {
            sky_updates = sky_updates_;
        }

        void SetBlockUpdates(std::vector<std::vector<char> >& block_updates_)
        {
            block_updates = block_updates_;
        }

#if PROTOCOL_VERSION > 722
        void SetTrustEdges(const bool trust_edges_)
        {
            trust_edges = trust_edges_;
        }
#endif


        const int GetX() const
        {
            return x;
        }

        const int GetZ() const
        {
            return z;
        }

#if PROTOCOL_VERSION < 755
        const int GetSkyYMask() const
        {
            return sky_Y_mask;
        }

        const int GetBlockYMask() const
        {
            return block_Y_mask;
        }

        const int GetEmptySkyYMask() const
        {
            return empty_sky_Y_mask;
        }

        const int GetEmptyBlockYMask() const
        {
            return empty_block_Y_mask;
        }
#else
        const std::vector<unsigned long long int>& GetSkyYMask() const
        {
            return sky_Y_mask;
        }

        const std::vector<unsigned long long int>& GetBlockYMask() const
        {
            return block_Y_mask;
        }

        const std::vector<unsigned long long int>& GetEmptySkyYMask() const
        {
            return empty_sky_Y_mask;
        }

        const std::vector<unsigned long long int>& GetEmptyBlockYMask() const
        {
            return empty_block_Y_mask;
        }

#endif

        const std::vector<std::vector<char> >& GetSkyUpdates() const
        {
            return sky_updates;
        }

        const std::vector<std::vector<char> >& GetBlockUpdates() const
        {
            return block_updates;
        }

#if PROTOCOL_VERSION > 722
        const bool GetTrustEdges() const
        {
            return trust_edges;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<VarInt>(iter, length);
            z = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION > 722
            trust_edges = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION < 755
            sky_Y_mask = ReadData<VarInt>(iter, length);
            block_Y_mask = ReadData<VarInt>(iter, length);
            empty_sky_Y_mask = ReadData<VarInt>(iter, length);
            empty_block_Y_mask = ReadData<VarInt>(iter, length);
#else
            const int sky_Y_mask_size = ReadData<VarInt>(iter, length);
            sky_Y_mask = std::vector<unsigned long long int>(sky_Y_mask_size);
            for (int i = 0; i < sky_Y_mask_size; ++i)
            {
                sky_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int block_Y_mask_size = ReadData<VarInt>(iter, length);
            block_Y_mask = std::vector<unsigned long long int>(block_Y_mask_size);
            for (int i = 0; i < block_Y_mask_size; ++i)
            {
                block_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int empty_sky_Y_mask_size = ReadData<VarInt>(iter, length);
            empty_sky_Y_mask = std::vector<unsigned long long int>(empty_sky_Y_mask_size);
            for (int i = 0; i < empty_sky_Y_mask_size; ++i)
            {
                empty_sky_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int empty_block_Y_mask_size = ReadData<VarInt>(iter, length);
            empty_block_Y_mask = std::vector<unsigned long long int>(empty_block_Y_mask_size);
            for (int i = 0; i < empty_block_Y_mask_size; ++i)
            {
                empty_block_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
#endif

#if PROTOCOL_VERSION < 755
            sky_updates.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((sky_Y_mask >> i) & 1)
                {
                    const int array_length = ReadData<VarInt>(iter, length); // Should be 2048
                    sky_updates.push_back(ReadArrayData<char>(iter, length, array_length));
                }
            }

            block_updates.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((block_Y_mask >> i) & 1)
                {
                    const int array_length = ReadData<VarInt>(iter, length); // Should be 2048
                    block_updates.push_back(ReadArrayData<char>(iter, length, array_length));
                }
            }
#else
            const int sky_updates_size = ReadData<VarInt>(iter, length);
            sky_updates = std::vector<std::vector<char> >(sky_updates_size);
            for (int i = 0; i < sky_updates_size; ++i)
            {
                const int array_length = ReadData<VarInt>(iter, length); // Should be 2048
                sky_updates[i] = ReadArrayData<char>(iter, length, 2048);
            }

            const int block_updates_size = ReadData<VarInt>(iter, length);
            block_updates = std::vector<std::vector<char> >(block_updates_size);
            for (int i = 0; i < block_updates_size; ++i)
            {
                const int array_length = ReadData<VarInt>(iter, length); // Should be 2048
                block_updates[i] = ReadArrayData<char>(iter, length, 2048);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(x, container);
            WriteData<VarInt>(z, container);
#if PROTOCOL_VERSION > 722
            WriteData<bool>(trust_edges, container);
#endif
#if PROTOCOL_VERSION < 755
            WriteData<VarInt>(sky_Y_mask, container);
            WriteData<VarInt>(block_Y_mask, container);
            WriteData<VarInt>(empty_sky_Y_mask, container);
            WriteData<VarInt>(empty_block_Y_mask, container);
#else
            WriteData<VarInt>(sky_Y_mask.size(), container);
            for (int i = 0; i < sky_Y_mask.size(); ++i)
            {
                 WriteData<unsigned long long int>(sky_Y_mask[i], container);
            }
            WriteData<VarInt>(block_Y_mask.size(), container);
            for (int i = 0; i < block_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(block_Y_mask[i], container);
            }
            WriteData<VarInt>(empty_sky_Y_mask.size(), container);
            for (int i = 0; i < empty_sky_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(empty_sky_Y_mask[i], container);
            }
            WriteData<VarInt>(empty_block_Y_mask.size(), container);
            for (int i = 0; i < empty_block_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(empty_block_Y_mask[i], container);
            }
#endif

#if PROTOCOL_VERSION > 754
            WriteData<VarInt>(sky_updates.size(), container);
#endif
            for (int i = 0; i < sky_updates.size(); ++i)
            {
                WriteData<VarInt>(sky_updates[i].size(), container);
                WriteArrayData(sky_updates[i], container);
            }

#if PROTOCOL_VERSION > 754
            WriteData<VarInt>(block_updates.size(), container);
#endif
            for (int i = 0; i < block_updates.size(); ++i)
            {
                WriteData<VarInt>(block_updates[i].size(), container);
                WriteArrayData(block_updates[i], container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["x"] = x;
            output["z"] = z;
#if PROTOCOL_VERSION > 722
            output["trust_edges"] = trust_edges;
#endif
            output["sky_Y_mask"] = sky_Y_mask;
            output["block_Y_mask"] = block_Y_mask;
            output["empty_sky_Y_mask"] = empty_sky_Y_mask;
            output["empty_block_Y_mask"] = empty_block_Y_mask;

            output["sky_updates"] = nlohmann::json::array();
            for (int i = 0; i < sky_updates.size(); ++i)
            {
                output["sky_updates"].push_back(sky_updates[i]);
            }

            output["block_updates"] = nlohmann::json::array();
            for (int i = 0; i < block_updates.size(); ++i)
            {
                output["block_updates"].push_back(block_updates[i]);
            }

            return output;
        }

    private:
        int x;
        int z;
#if PROTOCOL_VERSION < 755
        int sky_Y_mask;
        int block_Y_mask;
        int empty_sky_Y_mask;
        int empty_block_Y_mask;
#else
        std::vector<unsigned long long int> sky_Y_mask;
        std::vector<unsigned long long int> block_Y_mask;
        std::vector<unsigned long long int> empty_sky_Y_mask;
        std::vector<unsigned long long int> empty_block_Y_mask;
#endif
        std::vector<std::vector<char> > sky_updates;
        std::vector<std::vector<char> > block_updates;
#if PROTOCOL_VERSION > 722
        bool trust_edges;
#endif
    };
} //ProtocolCraft

#endif