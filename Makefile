font.h : main.c
	gcc main.c `pkg-config freetype2 --libs --cflags` -std=c99  -o bitmap
	./bitmap wqy-microhei.ttc > font.h
