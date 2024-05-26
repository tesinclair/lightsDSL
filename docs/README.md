# Lights DSL

A DSL created for interfacing with gpio - specifically for Raspberry Pis.

# Purpose

I created this for my [house controller](https://github.com/tesinclair/house-controller2.0) project so I
could create my own light scripts. Of the two options I had: write them in python and c or create my own
language to write them in, this just seemed the easiest. 

Essentially the point of this is to have a more direct approach when it comes to gpio programming.
The main feature of this is to interface with led strips, however I intend to expand it to allow
deep controll. 

# Usage

The first thing to be declared is the active pin(s):

```
@use pins { 10 };
```
This tells the program that we will be accessing only pin 10.

Next we can optionally declare the type of pin we are interfacing:

```
@decl type { strip };
```
Now the program knows that we are interfacing with an led strip, this
way we'll have access to strip keywords.

We don't need to tell the pins to be active or not. This is all done automatically.

If using strip, the next thing you need to declare is the number of addressable leds.

```
@decl addressable { 100 };
```
This tells the program there are 100 different leds we can access.

To output power to the leds we can simply reference the pins:
```
@color pin - { 10/30 } = (255, 255, 255); # Set pins 10 - 30 (inclusive) to white
@on pin; # Pin only needs to be specified if there are multiple active pins
```

Check out [examples](https://github.com/tesinclair/lightsDSL/examples) for some full examples.




