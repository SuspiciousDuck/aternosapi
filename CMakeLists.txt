cmake_minimum_required(VERSION 3.0.0)
project(aternosapi)

find_package(cpr REQUIRED)
find_package(cryptopp REQUIRED)

include_directories(src)
file(GLOB files_snake CONFIGURE_DEPENDS "src/*.h" "src/*.cpp" "src/*.c")

add_executable(scraper ${files_snake})
target_link_libraries(scraper PRIVATE cpr::cpr ${LIBXML2_LIBRARIES} cryptopp::cryptopp)