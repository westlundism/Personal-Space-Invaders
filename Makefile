#
# Makefile for Personal Space Invaders
#

# Folders
SRC = src

# Compiler (g++)
CCC = g++

# Compiling flags
CCFLAGS +=  -Wno-deprecated-declarations -Wall -Wextra -pedantic -std=c++1z -Weffc++ -I$(SFML_ROOT)/include
LDFLAGS += -L$(SFML_ROOT)/lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# Pre-processor flags
CPPFLAGS += -I$(SRC)

# Object modules
OBJECTS = personal_space_invaders.o Game.o Game_State.o Actor.o Button.o Top_List.o Text_Box.o Info_Strip.o Controllers.o

# Main objetice - created with 'make' or 'make personal_space_invaders'.
personal_space_invaders: $(OBJECTS) Makefile
	$(CCC) $(CPPFLAGS) $(CCFLAGS) $(LDFLAGS) -o personal_space_invaders $(OBJECTS)

# Part objectives
personal_space_invaders.o: $(SRC)/personal_space_invaders.cpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/personal_space_invaders.cpp

Game.o: $(SRC)/Game.cpp $(SRC)/Game.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Game.cpp

Game_State.o: $(SRC)/Game_State.cpp $(SRC)/Game_State.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Game_State.cpp

Actor.o: $(SRC)/Actor.cpp $(SRC)/Actor.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Actor.cpp

Button.o: $(SRC)/Button.cpp $(SRC)/Button.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Button.cpp

Top_List.o: $(SRC)/Top_List.cpp $(SRC)/Top_List.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Top_List.cpp

Text_Box.o: $(SRC)/Text_Box.cpp $(SRC)/Text_Box.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Text_Box.cpp

Info_Strip.o: $(SRC)/Info_Strip.cpp $(SRC)/Info_Strip.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Info_Strip.cpp

Controllers.o: $(SRC)/Controllers.cpp $(SRC)/Controllers.hpp
	$(CCC) $(CPPFLAGS) $(CCFLAGS) -c $(SRC)/Controllers.cpp

# 'make clean' removes object files and memory dumps.
clean:
	@ \rm -rf *.o *.gch core

# 'make zap' also removes the executable and backup files.
zap: clean
	@ \rm -rf personal_space_invaders *~
