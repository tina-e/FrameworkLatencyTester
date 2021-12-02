all: testprograms

testprograms:
	$(MAKE) -C test_programs/ all
	$(MAKE) -C latency_tester/ all
	$(MAKE) -C click_simulator/ all

clean:
	$(MAKE) -C test_programs/ clean
	$(MAKE) -C latency_tester/ clean
	$(MAKE) -C click_simulator/ clean
