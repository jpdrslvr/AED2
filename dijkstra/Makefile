DEPS = grafos.h
OBJS = dijkstra.o grafos.o

%.o: %.c $(DEPS)
	gcc -c -o $@ $<

dijkstra: $(OBJS)
	gcc -o $@ $^

clean:
	rm -f $(OBJS) dijkstra