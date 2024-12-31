program: window.c
	gcc -Wall -L/usr/lib -I/usr/include/webkitgtk-6.0 -I/usr/include/gtk-4.0 -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/webp -I/usr/include/cairo -I/usr/include/libxml2 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/pixman-1 -I/usr/include/graphene-1.0 -I/usr/lib64/graphene-1.0/include -mfpmath=sse -msse -msse2 -I/usr/include/libsoup-3.0 -I/usr/include/libmount -I/usr/include/blkid -DWITH_GZFILEOP -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/sysprof-6 -pthread -c window.c -o window.o
run: window.o
	gcc -L/usr/lib/ -L/usr/lib64/ -lwebkitgtk-6.0 -lgtk-4 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lvulkan -lgraphene-1.0 -lsoup-3.0 -lgmodule-2.0 -pthread -lgio-2.0 -ljavascriptcoregtk-6.0 -lgobject-2.0 -lglib-2.0 -o musicmix window.o 
install: install
	cp ./musicmix /usr/bin/.
	cp ./musicmix.gif /usr/share/icons/.
	cp ./musicmix.desktop /usr/share/applications/.

