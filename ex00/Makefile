all: convert

src=ScalarConverter main
obj=$(addsuffix .o, $(src))

convert: $(obj)
	c++ -o $@ $(obj)

cflags=-Wall -Wextra -Werror -std=c++98 -pedantic
depflags = -MT $@ -MMD -MP -MF $*.d

%.o: %.cpp %.d Makefile
	c++ $(cflags) $(depflags) -o $@ -c $<

clean:
	rm -f $(obj) $(obj:.o=.d)

fclean: clean
	rm -f convert

re: fclean convert

debug: cflags+=-g
debug: convert

$(obj:.o=.d):
-include $(obj:.o=.d)
