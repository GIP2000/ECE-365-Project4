ALL: isSubStr.out
.PHONY: clean 


isSubStr.out: isSubStr.cpp
	g++ -std=c++17 -g -o isSubStr.out isSubStr.cpp 

clean: 
	rm -f isSubStr.out

