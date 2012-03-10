


main: main.cc nagiosParse.c
	g++ -o nparser main.cc nagiosParse.c -lfl


nagiosParse.c: nagiosParse.l 
	flex nagiosParse.l
	test -e lex.yy.c && mv lex.yy.c nagiosParse.c


clean:
	rm -f *.o a.out nagiosParse nagiosParse.c nparser


