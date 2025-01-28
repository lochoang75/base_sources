#include "control/auto_complete_director.h"

#include "blogger.h"

namespace SystemAPI {
    static int GetNetworkInterface(const CommandData &data, std::vector<std::string> &output)
    {
        std::vector<std::string> interface_valid{"wlan0", "eth0", "ppp0"};
        output = interface_valid;
        return 0;
    }
};

AutoCompleteDirector:: AutoCompleteDirector()
{
}

AutoCompleteDirector:: ~AutoCompleteDirector()
{
}

AutoCompleteEntry *AutoCompleteDirector:: MakeExampleCommand()
{
    AutoCompleteEntry *complete_entry = new AutoCompleteEntry();
    if (complete_entry == nullptr)
    {
        BLOG(LOG_ERR, "Failed to allocate memory for entry");
        return nullptr;
    }

    std::vector<std::string> parameter{"ex_p1", "ex_p2"};
    complete_entry->SetCommand("ex");
    complete_entry->AddStaticParameter(parameter);
    complete_entry->AddDynamicParameter(SystemAPI::GetNetworkInterface);
    return complete_entry;
}