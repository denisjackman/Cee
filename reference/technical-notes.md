when generating a random number you need to first declare 

```
    srand(time(0));
```

This will seed the randomiser suing the time since epoch 
when ever you need a random number 

```
    int diceroll = rand() % sides + 1 ;
```

where ```sides``` is the number of sides of the dice.

## Tinyxml 
* [tinyxml](http://www.cs.cmu.edu/~preethi/src/tinyxml/docs/tutorial0.html)

for this to work 
* tinyxml2.cpp 
* tinyxml2.h 
has to be in the project folder 

the tinxml2.cpp has to be added to the compiler 
*  g++ -Wall -DDEBUG tinyxml2.cpp xmlexample.cpp -o xmlexample

## GIT
Branches
* git checkout -b new-feature-test 
* git push origin new-feature-test 