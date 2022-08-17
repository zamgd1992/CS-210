# CS-210

This is a program that reads a file that contains a list of every item bought in a grocery store throughout the day. 
It has a menu that lets the user select from three options:
  1- Get a list of all items purchased in a day with the number of times each item was purchased.
  2- Lets the user enter an item name and displays the number of times that item was purchased throughout the day. 
  3- Display a histogram listing item purchased in a day.
The menu also has a fourth option which allows the user to exit the menu loop and end the program.
When option three is chosen the program not only reads from the file but creates a new file that has the same information as option one.
It then reads from this new file to print the histogram.
Using this program would allow a grocery store to find what items are selling better in a day.
This information can be used for item placement in the store. They can put more popular items in areas that are more visible in the hopes to increase sells.

This program utilizes both C++ and Python. C++ is used for the interface. It then passes information to Python.
This is done because Python has strengths in dealing with data.
This program, also, handles exception that might be thrown well. 
It considers the user entering in the wrong variable type as well as the user entering in an item name that does not exist in the file.
Exception handling helps the menu continue to loop until the user is ready to quit even if they enter in the wrong input.

This program would be more useful if it was expanded to work with a larger data base that would have information for more than just one day.
Therefore, Python was chosen for this functionality of the program. Working with more information would allow the grocery store to make more educated decisions.

The biggest challenge I faced in writing this code was getting the Visual Studios IDE set up to work with both C++ and Python. 
I had to try this several times to finally get it to work. This was beneficial because I go to the point where I could set this up without looking up how.
The functions that passed C++ code to Python were given to me 
but going through the process of setting up the IDE so many times helped me understand a little more what these functions did.

The most important thing that I got out of making this program is how multiple coding languages can be used together.
Some functionality may be better accomplished with one language over another.
Being able to pass functionality to a different language allows the program to utilize the strengths of multiple programming languages.
It can also be used to bypass a weakness of a certain language.

The code has block and in-line comments to better help others understand what each function does.
Each function or idea is seperated with a blank line.
Variable, function, and file names were given to help describe their purpose.
These things were done to help increase readability and maintainability 
