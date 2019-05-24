PROGNAME = FaceUphill
GENSRCS = $(PROGNAME).cpp $(PROGNAME).h
EMFRPOPTS = --cpp --nomain

.PNONY: clean allclean

$(GENSRCS): $(PROGNAME).mfrp
	emfrp $(EMFRPOPTS) $<

clean:
	$(RM) $(GENSRCS)
	$(RM) $(PROGNAME).c
	$(RM) $(PROGNAME)Main.*

allclean: clean
	$(RM) *.o
	$(RM) *~
	$(RM) .DS_Store
