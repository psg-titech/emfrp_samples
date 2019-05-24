PROGNAME = LCDClock
GENSRCS = $(PROGNAME).cpp $(PROGNAME).h
EMFRPOPTS = --cpp --nomain

.PNONY: clean allclean

$(GENSRCS): $(PROGNAME).mfrp
	emfrp $(EMFRPOPTS) $<

clean:
	$(RM) $(GENSRCS)
	$(RM) $(PROGNAME)Main.*

allclean: clean
	$(RM) -rf BUILD
	$(RM) .mbed
	$(RM) *.o
	$(RM) *~
	$(RM) .DS_Store
