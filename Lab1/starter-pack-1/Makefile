.PHONY: instructions
instructions:
	@echo Run % make step1 until it works
	@echo Then run % make step2 until it works
	@echo etc...


.PHONY: step1
step1: step1.cpp Playlist.h Playlist.cpp
	$(CXX) -o step1 -std=c++14 step1.cpp
	./step1

.PHONY: step2
step2: step2.cpp main.cpp Playlist.h Playlist.cpp
	$(CXX) -o step2 -std=c++14 step2.cpp
	./step2

.PHONY: step3
step3: step3.cpp main.cpp Playlist.h Playlist.cpp
	$(CXX) -o step3 -std=c++14 step3.cpp
	./step3

.PHONY: lab1
lab1: main.cpp Playlist.h Playlist.cpp
	$(CXX) -o lab1 -std=c++14 main.cpp Playlist.cpp
