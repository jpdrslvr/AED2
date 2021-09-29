DEPS = grafos.h
OBJS = kruskal.o grafos.o

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

kruskal: $(OBJS)
	gcc -o $@ $^

clean:
	rm -f $(OBJS) kruskal
