.PHONY: all run clean

all:
	@ninja

run: all
	@./ricky

clean:
	@ninja -t clean
