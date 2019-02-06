#include "ofFileUtils.h"
#include "ofUtils.h"
#include "ofLog.h"
#include "ect_helpers.h"

std::string getAppConfigDir()
{
#if defined(TARGET_LINUX) || defined(TARGET_OSX)
    std::string dir = ofFilePath::join( ofFilePath::getUserHomeDir(),  ".config/NatNet2OSC_bridge" );
    if ( ! ofDirectory::createDirectory( dir, false, true ) )
    {
        ofLogNotice() << "couldn't create or open " << dir << "reverting to bin/data";
        return "";
    }
    return dir;
#elif defined(TARGET_WINDOWS) || defined(TARGET_WIN32)
    std::string appdata = ofGetEnv( "APPDATA" );
    std::string dir = ofFilePath::join( appdata,  "\\NatNet2OSC_bridge" );
    if ( ! ofDirectory::createDirectory( dir, false, true ) )
    {
        ofLogNotice() << "couldn't create or open " << dir << "reverting to bin/data";
        return "";
    }
    return dir;
#else
    return "";
#endif
}

void browseAppConfigDir()
{
#if defined(TARGET_LINUX)
    ofLogVerbose("Not yet implemented");
#elif defined(TARGET_OSX)
    ofSystem("open " + getAppConfigDir());
#elif defined(TARGET_WINDOWS) || defined(TARGET_WIN32)
    ofSystem("explorer " + getAppConfigDir());
#endif
}

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

// https://stackoverflow.com/questions/3596781/how-to-detect-if-the-current-process-is-being-run-by-gdb
bool gdbIsAttached()
{
    char buf[4096];

    const int status_fd = ::open("/proc/self/status", O_RDONLY);
    if (status_fd == -1)
        return false;

    const ssize_t num_read = ::read(status_fd, buf, sizeof(buf) - 1);
    if (num_read <= 0)
        return false;

    buf[num_read] = '\0';
    constexpr char tracerPidString[] = "TracerPid:";
    const auto tracer_pid_ptr = ::strstr(buf, tracerPidString);
    if (!tracer_pid_ptr)
        return false;

    for (const char* characterPtr = tracer_pid_ptr + sizeof(tracerPidString) - 1; characterPtr <= buf + num_read; ++characterPtr)
    {
        if (::isspace(*characterPtr))
            continue;
        else
            return ::isdigit(*characterPtr) != 0 && *characterPtr != '0';
    }

    return false;
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
