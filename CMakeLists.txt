cmake_minimum_required(VERSION 3.21)
project(oasis-crawler)

set(CMAKE_CXX_STANDARD 14)

add_executable(oasis-crawler main.cpp world.cpp header/world.h player.cpp header/player.h enemy.cpp header/enemy.h gameHandler.cpp header/gameHandler.h header/gameUtils.h)
