#ifndef ECT_HELPERS_H
#define ECT_HELPERS_H

#pragma once


#include <string>
#include "imgui.h"
#include "Poco/Net/HostEntry.h"
#include "Poco/Net/IPAddress.h"
#include "Poco/Net/NetworkInterface.h"

// return the path to where the user can save application data
std::string getAppConfigDir();
// opens a file browser to the app config dir (so people can find their setups)
void		browseAppConfigDir();

/// \brief A typedef for Poco::Net::NetworkInterface.
typedef Poco::Net::NetworkInterface NetworkInterface;

/// \brief A typedef for Poco::Net::NetworkInterface::NetworkInterfaceList.
typedef Poco::Net::NetworkInterface::NetworkInterfaceList NetworkInterfaceList;

/// \brief An enumeration of address types.
enum AddressType
{
    /// \brief Any address type.
    ANY,
    /// \brief Wildcard address (e.g. all zeros)
    WILDCARD,
    /// \brief Broadcast address (e.g. all bits are 1)
    BROADCAST,
    /// \brief Loopback address (e.g. 127.0.0.1 / ::1)
    LOOPBACK,
    /// \brief Multicast address (e.g. 224.0.0.0 to 239.255.255.255 range)
    MULTICAST,
    /// \brief Unicast address (e.g. not a wildcard, broadcast or multicast address)
    UNICAST,
    /// \brief Linklocal address (e.g. 169.254.0.0/16 (aka self-assigned))
    LINK_LOCAL,
    /// \brief Broadcast address (e.g. 10.0.0.0/24, 192.168.0.0/16 or 172.16.0.0 to 172.31.255.255)
    SITE_LOCAL
};

NetworkInterfaceList listNetworkInterfaces(AddressType addressType,
                                           NetworkInterface::IPVersion ipVersion = NetworkInterface::IPv4_OR_IPv6);
namespace ImGui
{
bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values);
}

#endif // ECT_HELPERS_H
