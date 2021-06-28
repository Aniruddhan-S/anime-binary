# anime-binary

This is a simple C++ binary file handling program, to keep track of the anime that i've watched and that i'm watching.
It creates two separate binary files for anime and manga and stores data in it.

## Installation
Clone this repository.
```
git clone https://github.com/Igneel001/anime-binary.git
```
Compile this program using `g++` or a compiler of your choice.
```
g++ anime.cpp 
```
or 
```
g++ animeWithoutANSI.cpp
```
Now execute the output file in the terminal depending on your operating system.

## Note
- **In Windows**: It is recommended that this program is executed through the `Windows Terminal` as certain features may break if it is executed in the standard `Command Prompt` or `Powershell`.
- Make sure the terminal where you execute this program supports mouse scroll and ANSI escape sequence.

Almost all the terminals support ANSI escape sequence, so it should not be a problem. But if yours does not and you see weird charactes like this when you're executing the program, then go ahead and use `animeWithoutANSI.cpp` instead of `anime.cpp`

![Weird Characters](https://github.com/Igneel001/anime-binary/blob/main/screenshots/weird-characters.JPG)

`animeWithoutANSI.cpp` as the name suggests, does not have any ANSI escape characters. Hence you won't see any weird characters.

## Features
- Anime:
  - add
    - anime name
    - anime completed (yes/no)
      - if no: season and recent episode watched
  - update 
  - display 
  - delete 

- Manga:
  - add
    - manga name
    - manga completed (yes/no)
      - if no: recent chapter read
  - update 
  - display 
  - delete


## A little insight on why i did this

It has been long since i used C++, so i thought i'd do something simple in it, just to keep in touch with the language. 

I've been watching a lot of anime recently and i was finding it difficult to keep track of what im watching and what i've watched. So i thought, "okay i'll make a text file and save the names of all the anime i've watched". But since i wanted to try out C++ again i decided that i'll make a C++ file handling program to create and write the text file. 

But then i thought why text file if i'm going to do it as a program. Even if i can't finish the program, i can just type and save the text file by myself. There would be no compulsion to finish the program.

Hence i decided, "i'll do it as a binary file program", so that i'll have no other way than to finish the program, because i cannot access that binary file if not through the program. 

Now you may ask, why binary? why so much effort when you can save it as a textfile by yourself, or use myanimelist?

Why?
Because i can.

Plus i'm bored and this is kind of a fun way to kill time.
