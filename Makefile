all: testprograms

testprograms:
	$(MAKE) -C test_programs/ all

clean:
	$(MAKE) -C test_programs/ clean
