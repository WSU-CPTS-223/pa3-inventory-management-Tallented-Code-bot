[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# PA4 Skeleton Code
We expect a fully functioninig command line REPL application for an inventory querying system. Feel free to modify the skeleton code as you see fit.

### How to run the current skeleton code
`make` will compile and execute the skeleton code

Feel free to modify Makefile as you see fit.



## General Requirements
The REPL should support the following commands:

1. `find <inventoryid>` - Finds if a product exists whose `Uniq id` matches the
`inventoryid`. If it exists, print the details of the product. If not, print
"Inventory/Product not found".
2. `listInventory <category_string>` - Lists the `Uniq Id` and `Product Name` of
all products whose `Category` matches `category_string`. If the
`category_string` does not match any `Category`, then print "Invalid Category".


The dataset has some quirks:

1. Please note that a product can belong to multiple categories. For example,
   the product "VTech Twist and Hug Koala Rattle" belongs to "Toys & Games",
   "Kids' Electronics", and "Electronic Learning Toys". In the CSV file, the '|'
   symbol is used as the delimiter for categories.
2. Sometimes, data might be missing. For example, the product "Woodstock—Collage
   500 pc Puzzle" is missing category data (i.e. the category column is empty).
   In such cases, you can use "NA" as the category to indicate that the category
   information is not available.
3. You may need to do additional cleanup. Please make your own decisions and
   document them in the readme file (readme.md).

### Implementation Requirements
1. We are going to leave most of the design decisions to you.
2. We need a functioning application that highlights the following.
  1. Your ability to identify the correct data structure(s) for the problem.
  2. Your ability to implement the data structure container(s) using templates.
  3. Your ability to utilize the container to implement the application.
  4. We would also expect you to follow good/professional programming practices.
3. First, you must decide on the data structure(s) best suited for solving the
   problem. But you can’t use out-of-the-box STL containers. Instead, you need
   to implement the container from scratch.
  1. First, write the container from scratch. For this, you should write them as
     class templates.
  2. Once you test your container on simple problems to verify that it is
     working as expected, you can use it for the Amazon Inventory System.
4. If you decide to use a hashtable as one of your data structures, you can use
   std::hash or other openly available hash functions. In other words, you don’t
   have to implement any complicated hashing like murmurhash2 by yourself. Just
   use what is already available.


### Software Testing
- Testing catches bugs early and validates that your data structure works correctly before
building the application on top of it, saving significant debugging time and ensuring
correctness.
- Testing is fundamentally about creating a reasonable subset of (input, expected output)
pairs. You cannot test every possible input, so you select representative cases covering
normal usage, edge cases, and error conditions.
- You must implement test functions using cassert to test all operations of your
container(s) with simple data before integrating them into the inventory application.
Each test should use at least two test cases, one for the normal case and one for the
edge case.
- Document your testing approach in your README.md file, including what test cases you
created and why you chose them.
