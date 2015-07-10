# KarnaughMapSimplifier #
A program in c++ used to simplify expressions using Karnaugh Map.

## Using the binary executable ##
Enter the sum of products or product of sum expression separated by spaces. 
Sample input: 0 2 4 8

## Using the Simplifier.cpp and Map.cpp ##
1. Set whether the Map is for sum of products or product of sum using the `isSOP(bool)`
2. Call the `parseLine(std::string)` and enter a string such as "0 2 4 8"
3. Use the map as an argument for the Simplifier's constructor.
4. Call the `getSimplifiedExpression()` to get the answer.

See main.cpp for more details.

## License ##
MIT License
