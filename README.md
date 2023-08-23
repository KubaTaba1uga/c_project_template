Some src and tests are included so cmock installation can be tested easilly.

To use valgrind or gdb UNIT_TEST env variable has to be set up.
All test units (tests executables) can be found in `./build/test` dir.

Based on included project:
```
TEST_UNIT=test_gardener make memory_test

```

Debugging memory is hard, narrowing it to one test file at a time is the least i can do.

To delete src/ and /test content use:
```
rm src/* test/*
```


To build and run tests:
```
make setup && make test
```
