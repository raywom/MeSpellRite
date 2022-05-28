cmake_minimum_required(VERSION 3.22)
project(MeSpellRite)

set(CMAKE_CXX_STANDARD 14)

add_executable(MeSpellRite main.cpp BBST.h Trie.cpp Trie.h Hashtable.cpp Hashtable.h)
