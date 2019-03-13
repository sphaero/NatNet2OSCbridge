import sys
import platform

def platform_details():
    return """dist: %s
linux_distribution: %s
system: %s
machine: %s
platform: %s
uname: %s
version: %s
mac_ver: %s
""" % (
str(platform.dist()),
platform.linux_distribution(),
platform.system(),
platform.machine(),
platform.platform(),
platform.uname(),
platform.version(),
platform.mac_ver(),
)

def python_details():
    return """python: {}
executable: {}
python prefix: {} 
python paths: {}""".format(sys.version, sys.executable, sys.prefix, sys.path)

if __name__ == "__main__":
    print(platform_details())
    print(python_details())
