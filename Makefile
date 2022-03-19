SFML_INCLUDE = -I EXTLIBS
SFML_FRAMEWORKS = -F/Library/Frameworks

LIBS=-framework sfml-window -framework sfml-graphics -framework sfml-system
CXX = g++
CXXFLAGS = -std=c++11

all:
	$(CXX) $(CXXFLAGS) $(SFML_FRAMEWORKS) $(SFML_INCLUDE) $(LIBS) main.cpp -o run

.PHONY: clean
clean:
	rm run
