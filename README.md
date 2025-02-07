# Dinamic Array

Contributions and comments are welcome! ❤️ Just send a PR or open a issue to
improve my code or correct the documentation spelling.


## TODOS

+   Describe what this project is all about in the header.
+   Add a *What I've learned* under the *Documentation* section of this repo.
+   List the refference resources that I used during the development.
+   Finish the `darr.c` file documentation.
+   Add a method that changes the value of an element given a position
+   Test that method in the `main.c` file afterwards.


## Documentation

To **generate the documentation HTML pages** automatically, you'll have to
install **`doxygen`** tool first to make the `make html` command work.

All the variables, functions or attributes that starts with an underscore (`_`)
is meant to be **private** for that specific file, in case of
functions/variables, or for the struct, in case of struct attributes. Even if
it's possible access them, **they aren't supposed to be changed nor read
directly**.


### Areas Of Improvement

+   Find a way to make the array work with multiple types all at once, allowing
    the user to store any kind of data (no clue how to implement that).
