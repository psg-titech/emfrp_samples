PROGNAME = SimFanController
GENSRCS = $(PROGNAME).c $(PROGNAME).h
EMFRPOPTS = --nomain
OBJS = main.o $(PROGNAME).o
EXES = $(PROGNAME)

.PHONY: exe clean allclean

$(PROGNAME).c $(PROGNAME).h: $(PROGNAME).mfrp
	emfrp $(EMFRPOPTS) $<

exe: $(EXES)

$(PROGNAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(GENSRCS)
	$(RM) $(PROGNAME)Main.*
	$(RM) $(OBJS)
	$(RM) $(EXES)

allclean: clean
	$(RM) *.o
	$(RM) *~
	$(RM) .DS_Store
