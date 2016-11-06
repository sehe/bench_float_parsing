#SET(CMAKE_CXX_COMPILER clang++-3.6)
SET(CMAKE_CXX_COMPILER g++-5)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -isystem /home/sehe/custom/boost \
    -I/home/sehe/custom/nonius/include \
    -std=c++14 -O3 -pthread -march=native -flto"
)
#-DDEBUG \
#-fsanitize=undefined,address \

ADD_EXECUTABLE(bench_float_parsing main.cpp x3.cpp qi.cpp)
TARGET_LINK_LIBRARIES(bench_float_parsing boost_system boost_iostreams)
