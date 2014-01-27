#put libNBase58.so in current directory, add linker options to look for the lib in current dir while running the program
rm -rf testNExecutor
g++ TestNExecutor.cpp -I../src -Wl,-R../ -L../ -lNConcurrency -lpthread -o testNExecutor -ggdb3
rm -rf testNCountdownLatch
g++ TestNCountdownLatch.cpp -I../src -Wl,-R../ -L../ -lNConcurrency -lpthread -o testNCountdownLatch
