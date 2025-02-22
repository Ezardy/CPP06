all: convert test

src=ScalarConverter
obj=$(addsuffix .o, $(src))

convert: $(obj) main.o
	c++ $(cflags) -o $@ $(obj) main.o

test: $(obj) test.o
	c++ $(cflags) -o $@ $(obj) test.o

cflags=-Wall -Wextra -Werror -std=c++98 -pedantic
depflags = -MT $@ -MMD -MP -MF $*.d

%.o: %.cpp %.d Makefile
	c++ $(cflags) $(depflags) -o $@ -c $<

clean:
	rm -f $(obj) $(obj:.o=.d) main.o main.d test.o test.d

fclean: clean
	rm -f convert test

re: fclean convert

debug: cflags+=-g
debug: test convert

test.d:
-include test.d

main.d:
-include main.d

$(obj:.o=.d):
-include $(obj:.o=.d)
