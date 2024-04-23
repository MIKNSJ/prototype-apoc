COMP = g++
PACKAGES = -I../packages/Include -L../packages/lib
BASIC_FLAGS?=-g -Wall -pedantic -Wextra -static-libstdc++
ADD_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TEST_FLAGS = -static-libstdc++
FILES = Menu.cpp Input.cpp -o apoc apoc.cpp

all:
	$(COMP) $(BASIC_FLAGS) $(PACKAGES) $(FILES) $(ADD_FLAGS)
	# apoc.exe