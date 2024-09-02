# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Include directories
INCLUDES = -I/opt/homebrew/Cellar/cryptopp/8.9.0/include/ -I./include/ -I../lab5/include -I/opt/homebrew/Cellar/nlohmann-json/3.11.3/include/ -I/opt/homebrew/Cellar/howard-hinnant-date/3.0.1/include

# Source files
SRCS = ./src/main.cpp ./src/crypt_safe.cpp

# Header files
HDRS = ./include/crypt_safe.h

OBJS = /opt/homebrew/Cellar/cryptopp/8.9.0/lib/libcryptopp.a ./build/main.o ./build/crypt_safe.o /opt/homebrew/Cellar/howard-hinnant-date/3.0.1/lib/libdate-tz.3.0.0.dylib ../lab5/build/certificate.o ../lab5/build/certify_me.o

# Executable name
TARGET = cryptsafe

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): make_crypt_safe make_main
	$(CXX) $(CXXFLAGS) $(OBJS) -o app $(INCLUDES) 

# Compile source files into object files
make_crypt_safe:	
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/crypt_safe.o ./src/crypt_safe.cpp

make_main:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o ./build/main.o ./src/main.cpp

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)