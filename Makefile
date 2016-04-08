.PHONY: all run clean

all:
	@ninja

run: all
	@./build/ricky

clean:
	@ninja -t clean
