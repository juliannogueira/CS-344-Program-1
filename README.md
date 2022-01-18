Build the project
- make

Run the program
- make run file={.csv file}
- ./movies {.csv file}

Check for memory leaks
- make check file={.csv file}
- valgrind --leak-check=yes ./movies file={.csv file}

Clean
- make clean
