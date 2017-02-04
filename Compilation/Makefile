OBJS := compilateur.o analyseur_lexical.o analyseur_syntaxique.o premiers.o suivants.o util.o

# link
compilateur: $(OBJS)
	gcc $(OBJS) -o compilateur

# compile
%.o: %.c
	gcc -c $(CFLAGS) $*.c -o $*.o
	gcc -MM $(CFLAGS) $*.c > $*.d
	@mv -f $*.d $*.d.tmp
	@sed -e 's|.*:|$*.o:|' < $*.d.tmp > $*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $*.d
	@rm -f $*.d.tmp

# remove compilation products
clean:
	rm -f *.o *.d

distclean:
	rm -f *.o *.d compilateur
