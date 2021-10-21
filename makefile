main: rat.cpp
	g++ -O2 -std=gnu++17 -pedantic rat.cpp -o rat
clean:
	rm -rf rat
cleanDebugFiles:
	rm -rf rat.dSYM
cleanAll: clean cleanDebugFiles
