all: installed

SVN_DIR = build/pyMOOS_svn
SVN_URL = https://pymoos.svn.sourceforge.net/svnroot/pymoos
SVN_PATCH = pymoos_r16_py3k_option.patch
SVN_REVISION=-r16
include $(shell rospack find mk)/svn_checkout.mk

CMAKE = cmake
CMAKE_ARGS = 	-D CMAKE_BUILD_TYPE=DEBUG \
				-D CMAKE_OSX_ARCHITECTURES="x86_64" \
				-D CMAKE_INSTALL_PREFIX="$(shell rospack find pyMOOS)/" \
				-D CMAKE_FIND_INSTALL_PATH="$(shell rospack find pyMOOS)/" 


installed: $(SVN_DIR)
	mkdir -p lib include Modules
	mkdir -p $(SVN_DIR)/build
	cd $(SVN_DIR)/build && $(CMAKE) $(CMAKE_ARGS) ..
	cd $(SVN_DIR)/build && make $(ROS_PARALLEL_JOBS) && make install
	mkdir -p src
	mv lib/python2.7/site-packages/pymoos src/pymoos
	rm -rf lib
	touch installed

cleaned: Makefile
	make clean
	touch cleaned

clean:
	-rm -rf $(SVN_DIR)/build rospack_nosubdirs patched installed include bin *~ Modules lib src

wiped: Makefile
	make wipe
	touch wiped

wipe: clean
	rm -rf build cleaned
