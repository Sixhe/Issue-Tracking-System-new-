# Target to build the Windows executable
all: ITS.exe

# Linking the object files to create the ITS.exe
ITS.exe: main.cpp mainUI.cpp FileHandler.cpp Customer.cpp Employee.cpp Engineer.cpp
	x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++ main.cpp mainUI.cpp FileHandler.cpp Customer.cpp Employee.cpp Engineer.cpp -o ITS.exe


clean:
	rm -f ITS.exe requestgen.exe *.o
