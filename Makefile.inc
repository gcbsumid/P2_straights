CXX = clang++  
CXXFLAGS = -g -Wall -MMD `pkg-config gtkmm-2.4 --cflags --libs`
