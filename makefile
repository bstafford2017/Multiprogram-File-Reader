all:
	./remove
	g++ hw9-benjaminstafford.cpp -o hw9 -std=c++11
	g++ p.cpp -o pn -std=c++11
clean:
	rm -R hw9 pn
