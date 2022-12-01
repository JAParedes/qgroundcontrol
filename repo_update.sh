make distclean
git submodule sync
git submodule update --init --recursive
git submodule update --remote --recursive 'libs/mavlink/include/mavlink/v2.0'
