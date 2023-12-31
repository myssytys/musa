program: window.c
	gcc -Wall -L/usr/lib/ -I/usr/include/atk-1.0/ -I/usr/include/gtk-3.0 -I/usr/include/libsoup-3.0/  -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/sysprof-4 -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/fribidi -I/usr/include/libxml2 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/graphene-1.0 -I/usr/lib64/graphene-1.0/include -I/usr/include/libxml2-mfpmath=sse -I/usr/include/webkitgtk-4.1/  -msse -msse2 -I/usr/include/gio-unix-2.0 -pthread -lgtk-3 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -c window.c -o window.o
run: window.o
	gcc -L/usr/lib/ -L/usr/lib64/ -lwebkit2gtk-4.1 -lsoup-3.0 -lgtk-3 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -o musicmix window.o 
install: install
	cp ./musicmix /usr/bin/.
	cp ./musicmix.gif /usr/share/icons/.
	cp ./musicmix.desktop /usr/share/applications/.

