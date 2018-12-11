#include "helpers.h"

NetworkInterfaceList listNetworkInterfaces(AddressType addressType,
                                           NetworkInterface::IPVersion ipVersion)
{
    NetworkInterfaceList results;
    auto all = Poco::Net::NetworkInterface::list();
    auto iter = all.begin();

    while (iter != all.end())
    {
        bool match = false;

        Poco::Net::NetworkInterface iface = (*iter);
        Poco::Net::IPAddress address = iface.address();

        switch (addressType)
        {
            case ANY:
                match = true;
                break;
            case WILDCARD:
                match = address.isWildcard();
                break;
            case BROADCAST:
                match = address.isBroadcast();
                break;
            case LOOPBACK:
                match = address.isLoopback();
                break;
            case MULTICAST:
                match = address.isMulticast();
                break;
            case UNICAST:
                match = address.isUnicast();
                break;
            case LINK_LOCAL:
                match = address.isLinkLocal();
                break;
            case SITE_LOCAL:
                match = address.isSiteLocal();
                break;
        }

        if (match)
        {
            if ((ipVersion == NetworkInterface::IPv4_OR_IPv6) ||
                (ipVersion == NetworkInterface::IPv4_ONLY && !iface.supportsIPv6() && iface.supportsIPv4()) ||
                (ipVersion == NetworkInterface::IPv6_ONLY && !iface.supportsIPv4() && iface.supportsIPv6()))
            {
                results.push_back(iface);
            }
        }

        ++iter;
    }

    return results;
}

namespace ImGui
{
// from https://eliasdaler.github.io/using-imgui-with-sfml-pt2/#using-imgui-with-stl
static auto vector_getter = [](void* vec, int idx, const char** out_text)
{
    auto& vector = *static_cast<std::vector<std::string>*>(vec);
    if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
    *out_text = vector.at(idx).c_str();
    return true;
};

bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
{
    if (values.empty()) { return false; }
    return Combo(label, currIndex, vector_getter,
        static_cast<void*>(&values), values.size());
}

bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
{
    if (values.empty()) { return false; }
    return ListBox(label, currIndex, vector_getter,
        static_cast<void*>(&values), values.size());
}

}
