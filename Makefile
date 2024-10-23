PREFIX: /usr/local/bin

all: basen

basen: basen.c
	cc -Wall -pedantic -Wno-missing-braces -o $@ $<

clean:
	rm -f basen

install: basen
	cp basen ${PREFIX}/basen


.PHONY: all clean install
