cmake_minimum_required(VERSION 3.13)
project(Piscine)

set(CMAKE_CXX_STANDARD 14)

add_executable(Piscine main.cpp graphe.cpp graphe.h sommet.cpp sommet.h Arete.cpp Arete.h Svgfile.cpp Svgfile.h)