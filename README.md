Build the project
- make

Run the program
- make run file={.csv file}
- ./output.exe {.csv file}

Check for memory leaks
- make check file={.csv file}
- valgrind --leak-check=yes ./output.exe file={.csv file}

Clean
- make clean
