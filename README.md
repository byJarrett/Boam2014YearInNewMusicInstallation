
# Boam 2014 Year In New Music Installation


### The Repo

This repo stores source code and pictures from the build for the Boam 2014 Year In New Music installation.  The explanation of the repo contents is below.



### Start with an Idea

For Christmas I got a [Bare Conductive](http://www.bareconductive.com/) [Touch Board](http://www.bareconductive.com/shop/touch-board/).  My mother-in-law sponsored Bare Conductive’s [Kickstarter campaign](https://www.kickstarter.com/projects/863853574/touch-board-interactivity-everywhere) to get it for me – very awesome!  So really this all started with a new toy.  I did some simple experiments, but nothing beyond that.  It seemed like such a waste.

Throughout the year though, I became interested in data visualizations.  There are many great companies and individuals doing amazing work in this space.  I started a [Pinterest board](https://www.pinterest.com/byjarrett/data-visualization/) to catalog different data visualizations that I find interesting.  Naturally, the urge to create my own began to fester.

When thinking about creating my own data visualization, I came across three dilemmas.  Most data visualizations require strong visual design skills, and I have less visual design skills than a middle school art student.  Since I work at a design studio and have previously worked at an agency, I have many creative friends and colleagues that could help me with visual design.  The second problem I wrought over was deciding what data to work with.  Should I just pick any data because this was supposed to be a simple exercise, or do I find something more compelling and rich, but which is possibly too complex for a first attempt?

For a while now I’ve been interested in the space where there is a mix of digital and physical elements - regardless of the project type.  I like the challenge of trying to use as few pixels as possible.  I feel augmenting physical objects with digital capabilities is a way of giving physical objects superpowers.  It is a way of bringing objects from the future to the present or from alien worlds to our world.  The key to making this successful is minimizing the impact of digital on the physical.  The tricky part is, how to do this with a data visualization and does it make sense to do it?  Is the second part of that question silly to begin with and irrelevant?

I was able to solve all of these problems with a single solution – [Eric Boam] (http://ericboam.com/).  It was amazing luck.  The gods were giving me good fortune.

Eric is a talented designer that has a strong interest in data and the field of quantified self.  Each year he tracks new music he discovers by recording detailed information which he later mines to surface “moments of significance.”  I approached him with the basic idea that I wanted to take his data and create an interactive installation.  It would be a physical interactive data visualization of his year in new music that used no screens or pixels of any form.  We had to use the Bare Conductive Touch Board and ink, but beyond that, there were no other constraints.

The result was a set of three canvas panels.  Each has a set of circles that varied in size.  The size of the circle corresponds to the number of songs associated with that data element.  The first panel represents the hour of day a song was discovered.  The middle panel is the year the song was released and if it was a favorite song of Eric’s in 2014.  The last panel matches to the day of the week the song was discovered.

To interact with the data you touch one circle from the first or last panel and one circle from the middle circle.  Doing so plays the song that matches that query.  The music stops when the touch is released.



## In the End


My favorite element to this installation was that the visual elements were printed on canvas, which was stretched and mounted like tradition canvas based art.  This, in some ways, gave the visualizations a gallery or museum art esthetic value.  We are taught to keep a distance from canvas that hangs on a wall and above all else never to touch it.  Our installation requires touch to make it interactive.  I found this juxtaposition playfully fun and amazing.  People were naturally reluctant to touch the canvas, but once they saw others doing it they lost their inhibitions and found the experience to be fun.

For a first foray into creating data visualizations, I think this project was a success.  It was simple, but still challenging.  I got to play with new technical hardware and dive deeper into interesting technologies.  On the design side, Eric taught me a few things about data visualizations and design in general.




### Making it Real

The installation was a relatively simple build, which is easy to say in hind site.  This project started with inspiration from a few new toys, which I had never used before.  This required several experiments and prototypes to understand how they worked.  These learnings also influenced the visual and interactive design.


Bare Conductive’s Electric Paint is the material for each touch point.  The paint is applied to the back side of the canvas.  This created some challenges and required the touch points to be proximity points due to the canvas.  The touch sensors were calibrated to detect proximity and not direct touch.

In total, there are 27 capacitive touch points.  Each touch point is considered a bit.  When touched these bits generate a number, which maps to a song.  No song or sound is played when there is not a mapped song.

The touch points are wired to MPR121 touch sensors.  This build uses three – two Adafruit MPR121 12-Key breakout boards and one Bare Conductive Touch Board.  The Touch Board is an Arduino-compatible device (Leonardo) that also includes an MP3 player and an audio output.  All code runs on the Touch Board.

The MPR121 chips use I2C to transport data.  The Touch Board by default maps to address 0x5C.  It was kept at this address.  The Adafruit MPR121 breakout boards by default map to address 0x5A.  One was kept at the default value and the other was changed to address 0x5B.  The pin to bit mapping is as follows:

Address | Pins   | Bit
------- | ------ | -----
0x5A    | 0-11   | 0-11
0x5B    | 0-11   | 12-23
0x5C    | 0-3    | 24-27

Pins 4-11 on the Touch Board were not used.  The IRQ pins were not used, but instead the values were read with each program loop.

I used a modified version of the Bare Conductive MPR121 library to communicate with all three MPR121 chips.  The changes were minor and largely to accommodate the specific nature of this installation.

Bill of Materials:

- [Touch Board](http://www.bareconductive.com/shop/touch-board/)
- [Electric Paint] (http://www.bareconductive.com/shop/electric-paint-50ml/)
- 2x [Adafruit 12-Key Capacitive Touch Sensor Breakout] (https://www.adafruit.com/product/1982)



Helpful resources for this project include:
-  [https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/overview] (https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/overview)
-  [http://www.bareconductive.com/make/setting-up-arduino-with-your-touch-board/] (http://www.bareconductive.com/make/setting-up-arduino-with-your-touch-board/)
-  [https://github.com/BareConductive/mpr121] (https://github.com/BareConductive/mpr121)
