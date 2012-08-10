all: sudokuhub sudokuterm

sudokuterm: sudokuterm.c sudokupsr.h sudokupvmcommon.h
	gcc sudokuterm.c `pkg-config --cflags --libs glib-2.0` -lpvm3 -o sudokuterm
	
sudokuhub: sudokuhub.c sudokupsr.h sudokupvmcommon.h
	gcc sudokuhub.c `pkg-config --cflags --libs glib-2.0` -lpvm3 -o sudokuhub
