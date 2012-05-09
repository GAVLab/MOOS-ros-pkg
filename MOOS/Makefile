all: installed

SVN_DIR = build/MOOS_svn
SVN_URL = svn://login2.robots.ox.ac.uk/MOOS/trunk
SVN_REVISION=-r2354
include $(shell rospack find mk)/svn_checkout.mk

CMAKE = cmake
CMAKE_ARGS = 	-D CMAKE_BUILD_TYPE=DEBUG \
				-D CMAKE_OSX_ARCHITECTURES="x86_64" \
				-D CMAKE_INSTALL_PREFIX="$(shell rospack find MOOS)/" \
				-D CMAKE_FIND_INSTALL_PATH="$(shell rospack find MOOS)/" \
				-D BUILD_TOOLS=TRUE \
				-D BUILD_GRAPHICAL_TOOLS=TRUE \
				-D BUILD_UMS=TRUE \
				-D BUILD_UPB=TRUE \
				-D BUILD_UPBINDEXED=TRUE


installed: $(SVN_DIR)
	mkdir -p lib include Modules
	mkdir -p $(SVN_DIR)/build
	cd $(SVN_DIR)/build && $(CMAKE) $(CMAKE_ARGS) ..
	cd $(SVN_DIR)/build && make $(ROS_PARALLEL_JOBS) && make install
	cp -r $(SVN_DIR)/build/MOOSBin/uMS* bin/
	touch installed

cleaned: Makefile
	make clean
	touch cleaned

clean:
	-rm -rf $(SVN_DIR)/build rospack_nosubdirs patched installed include bin *~ Modules lib

wiped: Makefile
	make wipe
	touch wiped

wipe: clean
	rm -rf build cleaned
