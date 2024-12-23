#!/bin/bash

sudo apt update
sudo apt install openssl
sudo apt install libssl-dev


# -- oatpp
#git clone https://github.com/oatpp/oatpp.git
cd oatpp 
rm -rf build
cmake -B build -DOATPP_BUILD_TESTS=OFF 
cmake --build build
sudo make -C build install
cd ..

# -- oatpp-swagger
#git clone https://github.com/oatpp/oatpp-swagger.git
cd oatpp-swagger 
rm -rf build
cmake -B build 
cmake --build build
sudo make -C build install
cd ..

# -- oatpp-sqlite
#git clone https://github.com/oatpp/oatpp-sqlite.git
cd oatpp-sqlite
rm -rf build
cmake -B build -DOATPP_SQLITE_AMALGAMATION=ON
cmake --build build
sudo make -C build install
cd ..

# -- json
#git clone https://github.com/nlohmann/json.git
cd json
rm -rf build
cmake -B build -DJSON_BuildTests=OFF
cmake --build build
sudo make -C build install
cd ..

# -- hiredis
#git clone  https://github.com/redis/hiredis.git
cd hiredis
rm -rf build
cmake -B build 
cmake --build build
sudo make -C build install
cd ..

# -- redis-plus-plus
#git clone  https://github.com/sewenew/redis-plus-plus.git
cd redis-plus-plus
rm -rf build
cmake -B build 
cmake --build build
sudo make -C build install
cd ..

# -- useragent
#git clone  https://github.com/zcmaye/useragent.git
cd useragent
rm -rf build
cmake -B build 
cmake --build build
sudo make -C build install
cd ..

# -- jwt-cpp
#git clone  https://github.com/Thalhammer/jwt-cpp.git
cd jwt-cpp
rm -rf build
cmake -B build
cmake --build build
sudo make -C build install
cd ..
