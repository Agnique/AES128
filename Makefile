CXX = g++
SOURCES = aes128.cpp main.cpp

AES128:
	$(CXX) -std=c++11 $(SOURCES) -o $@

clean:
	rm -rf AES128
	rm -rf *.o
	rm -rf KAT/*.rsp


