include Makefile.inc

all: idle init sh help ps producer consumer sample philosophers chat

idle:
	cd idle; make

init:
	cd init; make

sh:
	cd sh; make

help:
	cd help; make

ps:
	cd ps; make

producer:
	cd producer; make

consumer:
	cd consumer; make

sample:
	cd sample; make

chat:
	cd chat; make

philosophers:
	cd philosophers; make

clean:
	cd idle; make clean
	cd init; make clean
	cd sh; make clean
	cd help; make clean
	cd ps; make clean
	cd producer; make clean
	cd consumer; make clean
	cd sample; make clean
	cd philosophers; make clean
	cd chat; make clean
	rm -rf *.bin


.PHONY: all clean idle init sh help ps producer consumer sample philosophers chat
