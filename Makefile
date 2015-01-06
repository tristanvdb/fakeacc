
fakeacc:
	make -C lib fakeacc
	make -C src fakeacc

viz:
	make -C lib viz
	make -C src viz

clean:
	make -C lib clean
	make -C src clean
	make -C examples clean

