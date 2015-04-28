# Sullivan_CSCI2270_FinalProject


Project summary:
For our final project, my code will read in a list of supplements (as in protein, vitamins, fat burners, etc) from a file and sort them in a Binary Search Tree. The tree will be sorted by supplement names pulled from bodybuilding.com. The products will be top products purchased (top products may not have the highest ratings) on the website. As for the interface, the user will see a menu with options, which he/she can then select an option, produce output, and then see the menu again to continue the same process. My intention, on top of being able to print, search, buy, and count, is to sort the nodes by their rating - which I have stored in an array. However, this part of my code is not currently working. Any contributions to that portion would be greatly appreciated.

Dependencies:
the file "supplements.txt" will be read in.
when executing code, type :
compile: g++ -std=c++11 Driver.cpp suppTree.cpp -ljson
execute: ./a.out supplements.txt

System requirements:
I write and run code on a windows 8, however OS should not be a specific factor.

Group members:
me, myself, and I.

Contributors:
None as of 16 April 2015

Open Isuues/Bugs:
Seg fault when user wants "6", which contains my sort algorithm. From print statements, the code breaks on the if statement on line 643(suppTree.cpp). 





