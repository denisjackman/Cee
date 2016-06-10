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