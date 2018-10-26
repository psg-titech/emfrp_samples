PROGNAME = LCDClock
GENSRCS = $(PROGNAME).cpp $(PROGNAME).h

.PNONY: clean allclean

$(GENSRCS): $(PROGNAME).mfrp
	emfrp $<
	mv $(PROGNAME).c $(PROGNAME).cpp
	rm $(PROGNAME)Main.c.gen

clean:
	$(RM) $(GENSRCS)
	$(RM) $(PROGNAME)Main.*

allclean: clean
	$(RM) -rf BUILD
	$(RM) .mbed
	$(RM) *.o
	$(RM) *~
	$(RM) .DS_Store
