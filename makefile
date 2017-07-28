all:
	make -C Parse
	make -C c++17

test:
	./Parse/parse
	./c++17/c++17
