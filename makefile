all:
	make -C Parse
	#make -C c++17
	make -C svPNG
	make -C notImplement
	make -C c++98bind2nd

test:
	./Parse/parse
	#./c++17/c++17
	./svPNG/svpng
	./notImplement/notImplement
	./c++98bind2nd/mybind2nd
