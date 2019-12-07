SHELL = /bin/sh

GCC_STRICT_FLAGS = -pedantic -ansi -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2
GCC_SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
OTHER_SOURCE =
OTHER_INCLUDE = -I.
CPPFLAGS = -I. $(OTHER_INCLUDE)
CFLAGS = $(GCC_STRICT_FLAGS) 
LDFLAGS =
LDFLAGS_EFENCE = -L/usr/local/lib -lefence $(LDFLAGS)
#VALGRIND_FLAGS = --verbose --leak-check=full --undef-value-errors=yes --track-origins=yes
VALGRIND_FLAGS =  --leak-check=summary --undef-value-errors=yes --track-origins=yes

INDENT_FLAGS = -TFILE -Tsize_t -Tuint8_t -Tuint16_t -Tuint32_t -Tuint64_t

.PHONY: check vcheck scheck echeck check-examples indent stamp clean

TESTS     = t/test
EXAMPLES  = ex/from_stdin

cstrm.o: cstrm.c cstrm.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ cstrm.c

check:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c cstrm.c cbuf.c $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

vcheck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c cstrm.c cbuf.c $(LDFLAGS) ) \
	  && ( valgrind $(VALGRIND_FLAGS) t/a.out ); \
	done 

scheck: 
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(GCC_SANITIZE_FLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c cstrm.c cbuf.c $(LDFLAGS) ) \
	  && ( t/a.out ); \
	done 

echeck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i ..."; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c cstrm.c cbuf.c $(LDFLAGS_EFENCE) ) \
	  && ( LD_PRELOAD=libefence.so ./t/a.out ); \
	done 

check-examples:
	echo "--------------------"; \
	echo "Checking ex/ex_stdin_1.c  ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_stdin_1.c cstrm.c cbuf.c $(LDFLAGS) ) \
		&& ( valgrind $(VALGRIND_FLAGS) ex/a.out < README.md ); \
	echo "Checking ex/ex_stdin_2.c  ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_stdin_2.c cstrm.c cbuf.c $(LDFLAGS) ) \
		&& ( valgrind $(VALGRIND_FLAGS) ex/a.out < README.md ); \
	echo "Checking ex/ex_file_1.c  ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_file_1.c cstrm.c cbuf.c $(LDFLAGS) ) \
		&& ( valgrind $(VALGRIND_FLAGS) ex/a.out README.md ); \
	echo "Checking ex/ex_file_2.c  ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_file_2.c cstrm.c cbuf.c $(LDFLAGS) ) \
		&& ( valgrind $(VALGRIND_FLAGS) ex/a.out README.md ); \
	echo "Checking ex/ex_string_1.c  ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_string_1.c cstrm.c cbuf.c $(LDFLAGS) ) \
		&& ( valgrind $(VALGRIND_FLAGS) ex/a.out README.md ); \
	echo "Checking ex/ex_string_2.c  ..."; \
	( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o ex/a.out ex/ex_string_2.c cstrm.c cbuf.c $(LDFLAGS) ) \
		&& ( valgrind $(VALGRIND_FLAGS) ex/a.out README.md ); \

indent: stamp
	@indent $(INDENT_FLAGS) cstrm.c
	@indent $(INDENT_FLAGS) cstrm.h
	@indent $(INDENT_FLAGS) t/test.c
	@indent $(INDENT_FLAGS) ex/ex_file_1.c
	@indent $(INDENT_FLAGS) ex/ex_stdin_1.c
	@indent $(INDENT_FLAGS) ex/ex_stdin_2.c
	@indent $(INDENT_FLAGS) ex/ex_string_1.c
	@indent $(INDENT_FLAGS) ex/ex_string_2.c

stamp:
	@bash stamper.bash cstrm.c
	@bash stamper.bash cstrm.h

clean:
	@/bin/rm -f *.o *~ *.BAK *.bak core.* a.out
	@/bin/rm -f t/*.o t/*~ t/*.BAK t/*.bak t/core.* t/a.out
	@/bin/rm -f ex/*.o ex/*~ ex/*.BAK ex/*.bak ex/core.* ex/a.out
