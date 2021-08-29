#pragma once

#if PROTOCOL_VERSION > 451

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Slot.hpp"

namespace ProtocolCraft 
{
    class Trade : public NetworkType
    {
    public:
        virtual ~Trade() override
        {

        }

        void SetInputItem1(const Slot& input_item_1_)
        {
            input_item_1 = input_item_1_;
        }

        void SetOutputItem(const Slot& output_item_)
        {
            output_item = output_item_;
        }

        void SetHasSecondItem(const bool has_second_item_)
        {
            has_second_item = has_second_item_;
        }

        void SetInputItem2(const Slot& input_item_2_)
        {
            input_item_2 = input_item_2_;
        }

        void SetTradeDisabled(const bool trade_disabled_)
        {
            trade_disabled = trade_disabled_;
        }

        void SetNumberOfTradesUses(const int number_of_trades_uses_)
        {
            number_of_trades_uses = number_of_trades_uses_;
        }

        void SetMaximumNumberOfTradeUses(const int maximum_number_of_trade_uses_)
        {
            maximum_number_of_trade_uses = maximum_number_of_trade_uses_;
        }

        void SetXp(const int xp_)
        {
            xp = xp_;
        }

        void SetSpecialPrice(const int special_price_)
        {
            special_price = special_price_;
        }

        void SetPriceMultiplier(const float price_multiplier_)
        {
            price_multiplier = price_multiplier_;
        }

        void SetDemand(const int demand_)
        {
            demand = demand_;
        }


        const Slot& GetInputItem1() const
        {
            return input_item_1;
        }

        const Slot& GetOutputItem() const
        {
            return output_item;
        }

        const bool GetHasSecondItem() const
        {
            return has_second_item;
        }

        const Slot& GetInputItem2() const
        {
            return input_item_2;
        }

        const bool GetTradeDisabled() const
        {
            return trade_disabled;
        }

        const int GetNumberOfTradesUses() const
        {
            return number_of_trades_uses;
        }

        const int GetMaximumNumberOfTradeUses() const
        {
            return maximum_number_of_trade_uses;
        }

        const int GetXp() const
        {
            return xp;
        }

        const int GetSpecialPrice() const
        {
            return special_price;
        }

        const float GetPriceMultiplier() const
        {
            return price_multiplier;
        }

        const int GetDemand() const
        {
            return demand;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            input_item_1.Read(iter, length);
            output_item.Read(iter, length);
            has_second_item = ReadData<bool>(iter, length);
            if (has_second_item)
            {
                input_item_2.Read(iter, length);
            }
            trade_disabled = ReadData<bool>(iter, length);
            number_of_trades_uses = ReadData<int>(iter, length);
            maximum_number_of_trade_uses = ReadData<int>(iter, length);
            xp = ReadData<int>(iter, length);
            special_price = ReadData<int>(iter, length);
            price_multiplier = ReadData<float>(iter, length);
            demand = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            input_item_1.Write(container);
            output_item.Write(container);
            WriteData<bool>(has_second_item, container);
            if (has_second_item)
            {
                input_item_2.Write(container);
            }
            WriteData<bool>(trade_disabled, container);
            WriteData<int>(number_of_trades_uses, container);
            WriteData<int>(maximum_number_of_trade_uses, container);
            WriteData<int>(xp, container);
            WriteData<int>(special_price, container);
            WriteData<float>(price_multiplier, container);
            WriteData<int>(demand, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["input_item_1"] = input_item_1.Serialize();
            output["output_item"] = output_item.Serialize();
            output["has_second_item"] = has_second_item;
            if (has_second_item)
            {
                output["input_item_2"] = input_item_2.Serialize();
            }
            output["trade_disabled"] = trade_disabled;
            output["number_of_trades_uses"] = number_of_trades_uses;
            output["maximum_number_of_trade_uses"] = maximum_number_of_trade_uses;
            output["xp"] = xp;
            output["special_price"] = special_price;
            output["price_multiplier"] = price_multiplier;
            output["demand"] = demand;

            return output;
        }

    private:
        Slot input_item_1;
        Slot output_item;
        bool has_second_item;
        Slot input_item_2;
        bool trade_disabled;
        int number_of_trades_uses;
        int maximum_number_of_trade_uses;
        int xp;
        int special_price;
        float price_multiplier;
        int demand;
    };
} // ProtocolCraft
#endif
