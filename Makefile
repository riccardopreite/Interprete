#ARCH1718.riccardo.preite.0000839635

VMTranslator: mainvm.o 
	gcc mainvm.o -o VMTranslator


mainvm.o: mainvm.c
	gcc -c mainvm.c


clean:
	rm -f *.o VMTranslator
