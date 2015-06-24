
all:
	make -C lib all
	make -C src all
	make -C examples all

check:
	make -C examples check
	make -C src check

clean:
	make -C lib clean
	make -C src clean
	make -C examples clean

