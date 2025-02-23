all: test

src=Base real_type test
obj=$(addsuffix .o, $(src))

test: $(obj)
	c++ $(cflags) -o $@ $(obj)

cflags=-Wall -Wextra -Werror -std=c++98 -pedantic
depflags = -MT $@ -MMD -MP -MF $*.d

%.o: %.cpp %.d Makefile
	c++ $(cflags) $(depflags) -o $@ -c $<

clean:
	rm -f $(obj) $(obj:.o=.d) main.o main.d test.o test.d

fclean: clean
	rm -f test

re: fclean all

debug: cflags+=-g
debug: test

$(obj:.o=.d):
-include $(obj:.o=.d)
