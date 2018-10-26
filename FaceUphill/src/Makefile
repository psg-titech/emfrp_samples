PROGNAME = FaceUphill
GENSRCS = $(PROGNAME).cpp $(PROGNAME).h

$(GENSRCS): $(PROGNAME).mfrp
	emfrp $<
	mv $(PROGNAME).c $(PROGNAME).cpp
	$(RM) $(PROGNAME)Main.c.gen

clean:
	$(RM) $(GENSRCS)
	$(RM) $(PROGNAME)Main.*

allclean: clean
	$(RM) *~ a.out *.o
	$(RM) .DS_Store
