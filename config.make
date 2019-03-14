################################################################################
# CONFIGURE PROJECT MAKEFILE (optional)
#   This file is where we make project specific configurations.
################################################################################

################################################################################
# OF ROOT
#   The location of your root openFrameworks installation
#       (default) OF_ROOT = ../../.. 
################################################################################
# OF_ROOT = ../../..

################################################################################
# PROJECT ROOT
#   The location of the project - a starting place for searching for files
#       (default) PROJECT_ROOT = . (this directory)
#    
################################################################################
# PROJECT_ROOT = .

################################################################################
# PROJECT SPECIFIC CHECKS
#   This is a project defined section to create internal makefile flags to 
#   conditionally enable or disable the addition of various features within 
#   this makefile.  For instance, if you want to make changes based on whether
#   GTK is installed, one might test that here and create a variable to check. 
################################################################################
# None

################################################################################
# PROJECT EXTERNAL SOURCE PATHS
#   These are fully qualified paths that are not within the PROJECT_ROOT folder.
#   Like source folders in the PROJECT_ROOT, these paths are subject to 
#   exlclusion via the PROJECT_EXLCUSIONS list.
#
#     (default) PROJECT_EXTERNAL_SOURCE_PATHS = (blank) 
#
#   Note: Leave a leading space when adding list items with the += operator
################################################################################
# PROJECT_EXTERNAL_SOURCE_PATHS = 

################################################################################
# PROJECT EXCLUSIONS
#   These makefiles assume that all folders in your current project directory 
#   and any listed in the PROJECT_EXTERNAL_SOURCH_PATHS are are valid locations
#   to look for source code. The any folders or files that match any of the 
#   items in the PROJECT_EXCLUSIONS list below will be ignored.
#
#   Each item in the PROJECT_EXCLUSIONS list will be treated as a complete 
#   string unless teh user adds a wildcard (%) operator to match subdirectories.
#   GNU make only allows one wildcard for matching.  The second wildcard (%) is
#   treated literally.
#
#      (default) PROJECT_EXCLUSIONS = (blank)
#
#		Will automatically exclude the following:
#
#			$(PROJECT_ROOT)/bin%
#			$(PROJECT_ROOT)/obj%
#			$(PROJECT_ROOT)/%.xcodeproj
#
#   Note: Leave a leading space when adding list items with the += operator
################################################################################
# PROJECT_EXCLUSIONS =

################################################################################
# PROJECT LINKER FLAGS
#	These flags will be sent to the linker when compiling the executable.
#
#		(default) PROJECT_LDFLAGS = -Wl,-rpath=./libs
#
#   Note: Leave a leading space when adding list items with the += operator
################################################################################

# Currently, shared libraries that are needed are copied to the 
# $(PROJECT_ROOT)/bin/libs directory.  The following LDFLAGS tell the linker to
# add a runtime path to search for those shared libraries, since they aren't 
# incorporated directly into the final executable application binary.
# TODO: should this be a default setting?
# PROJECT_LDFLAGS=-Wl,-rpath=./libs
PROJECT_LDFLAGS = $(PY_LDFLAGS)

################################################################################
# PROJECT DEFINES
#   Create a space-delimited list of DEFINES. The list will be converted into 
#   CFLAGS with the "-D" flag later in the makefile.
#
#		(default) PROJECT_DEFINES = (blank)
#
#   Note: Leave a leading space when adding list items with the += operator
################################################################################
PROJECT_DEFINES = VERSION=\"$(GIT_VERSION)\"

################################################################################
# PROJECT CFLAGS
#   This is a list of fully qualified CFLAGS required when compiling for this 
#   project.  These CFLAGS will be used IN ADDITION TO the PLATFORM_CFLAGS 
#   defined in your platform specific core configuration files. These flags are
#   presented to the compiler BEFORE the PROJECT_OPTIMIZATION_CFLAGS below. 
#
#		(default) PROJECT_CFLAGS = (blank)
#
#   Note: Before adding PROJECT_CFLAGS, note that the PLATFORM_CFLAGS defined in 
#   your platform specific configuration file will be applied by default and 
#   further flags here may not be needed.
#
#   Note: Leave a leading space when adding list items with the += operator
################################################################################
PROJECT_CFLAGS = $(PY_CFLAGS)

################################################################################
# PROJECT OPTIMIZATION CFLAGS
#   These are lists of CFLAGS that are target-specific.  While any flags could 
#   be conditionally added, they are usually limited to optimization flags. 
#   These flags are added BEFORE the PROJECT_CFLAGS.
#
#   PROJECT_OPTIMIZATION_CFLAGS_RELEASE flags are only applied to RELEASE targets.
#
#		(default) PROJECT_OPTIMIZATION_CFLAGS_RELEASE = (blank)
#
#   PROJECT_OPTIMIZATION_CFLAGS_DEBUG flags are only applied to DEBUG targets.
#
#		(default) PROJECT_OPTIMIZATION_CFLAGS_DEBUG = (blank)
#
#   Note: Before adding PROJECT_OPTIMIZATION_CFLAGS, please note that the 
#   PLATFORM_OPTIMIZATION_CFLAGS defined in your platform specific configuration 
#   file will be applied by default and further optimization flags here may not 
#   be needed.
#
#   Note: Leave a leading space when adding list items with the += operator
################################################################################
# PROJECT_OPTIMIZATION_CFLAGS_RELEASE = 
# PROJECT_OPTIMIZATION_CFLAGS_DEBUG = 

################################################################################
# PROJECT COMPILERS
#   Custom compilers can be set for CC and CXX
#		(default) PROJECT_CXX = (blank)
#		(default) PROJECT_CC = (blank)
#   Note: Leave a leading space when adding list items with the += operator
################################################################################
# PROJECT_CXX = 
# PROJECT_CC = 
GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)
PY_CFLAGS := $(shell ./bin/python/bin/python3-config --cflags)
PY_LDFLAGS := $(shell ./bin/python/bin/python3-config --ldflags)

ifeq ($(PY_CFLAGS),)
PY_CFLAGS := -Iext/cpython/Include -Iext/cpython
endif
ifeq ($(PY_LDFLAGS),)
PY_LDFLAGS := -L$(shell pwd)/bin/ -lpython37
endif

python_win:
	cd ext/cpython;	./configure
	wget https://www.python.org/ftp/python/3.7.2/python-3.7.2.post1-embed-win32.zip
	unzip -uo python-3.7.2.post1-embed-win32.zip -d bin/
	rm python-3.7.2.post1-embed-win32.zip

osx_bundle: 
	$(eval BIN_NAME = $(APPNAME)_debug)
# overwrite current Info.plist
	@echo $(APP_NAME)
	@echo '<?xml version="1.0" encoding="UTF-8"?>' > bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '<plist version="1.0">' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '<dict>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>CFBundleGetInfoString</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <string>$(BIN_NAME).app</string>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>CFBundleExecutable</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <string>$(BIN_NAME)</string>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>CFBundleIdentifier</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <string>nl.hku.ect</string>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>CFBundleName</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <string>$(BIN_NAME)</string>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>CFBundleShortVersionString</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <string>$(GIT_VERSION)</string>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>CFBundleInfoDictionaryVersion</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <string>6.0</string>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>CFBundlePackageType</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <string>APPL</string>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>IFMajorVersion</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <integer>0</integer>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <key>IFMinorVersion</key>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '  <integer>1</integer>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '</dict>' >> bin/$(BIN_NAME).app/Contents/Info.plist
	@echo '</plist>' >> bin/$(BIN_NAME).app/Contents/Info.plist

	@echo TARGET=$(TARGET)
	@mv bin/data bin/$(BIN_NAME).app/Contents/Resources
	@mv bin/python bin/$(BIN_NAME).app/Contents/Resources

# TODO create dmg
	@echo "TODO create DMG"

osx_dmg:
	@echo --------------------- Creating Disk Image for $(APPNAME) $(GIT_VERSION) --------------------
	@hdiutil create -fs HFSX -layout SPUD "$(APPNAME)_$(GIT_VERSION).dmg" -srcfolder bin -format UDBZ -volname "$(APPNAME)_$(GIT_VERSION)" -quiet
