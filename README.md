# raat

RAAT stands for *Rapid Arduino Autogenerator Tool*

It is a code generator for Arduinos and other similar microcontroller systems.

Describe your hardware in a simple XML or JSON file, run the tool and get a complete Arduino sketch, ready to deploy.

RAAT is designed to take you away from worrying about writing boilerplate code for common devices and programming patterns.

Much of the code is designed around the [YAPSY plugin system](http://yapsy.sourceforge.net/), making adding new functionality easy.

**Note: RAAT is still under development, a bit experimental, and is liable to break or be broken, especially around the edges.**

## Hardware Support

Using RAAT, you can specifiy the hardware you are using and start using them straight away, without writing any setup code.

 - Support for digital and analog IO, Neopixels, Ethernet, RFID...

## Serial Interface
 - When you create a sketch using RAAT, you get a serial protocol included that lets you talk to and control your hardware. This makes prototyping, testing and configuration quick and easy.
 - There is a really simple serial, efficient protocol that's useful for memory-constrained applications, or a "URL" style protocol to make things a bit easier on your brain.

## Helpful Code Modules

RAAT includes some C++ modules that can simplify your application development.

Among other things:

 - Simple but powerful task management (one shot tasks, repeating timers, repeating tasks)
 - Switch debouncing
 - Seven segment display mapping

## Parameter System

Specify parameters for your application and read/set them over serial. Optionally, place them into non-volatile storage.

Perfect for setting the colour of LEDs, IP addresses, delay timings. Also for reading variables from your application, like temperatures, counters, etc.

Numeric parameters can be specified with min/max limits so you don't have to worry about that yourself. Limited parameters can either clip out of range values or ignore them.

 - So far, there's support for integers, booleans, RGB triplets and strings

## Custom Code Support

RAAT can go a long way towards generating functional Arduino sketches, but sometimes you still need to write some code yourself!

By writing your own code and implement two functions (`raat_custom_setup` and `raat_custom_loop`), you get access to all your declared hardware and parameters, which you can interact with as you require!

## Arduino CLI Support (Even More Experimental)

You can open the generated sketch in the Arduino IDE, but if you like, RAAT is capable of using the [Arduino command line interface tool](https://github.com/arduino/arduino-cli) to compile and download your sketches. It will also install any required Arduino libraries and board support packages.

## Some Simple Examples

Implementing a "Hello, world!" blinking LED is as simple as creating the following XML file (let's call it *raat_example.xml*:

    <?xml version="1.0"?>
    
    <board type="Arduino Uno" name="Timed OnOff">
        <info>
            An example sketch for the timed onoff device
            Flashes the onboard LED every second
        </info>
        
        <devices>
            <device name="Onboard LED" type="Timed OnOff">
                <setting id="pin" name="LED" value="13"/>
                <setting id="ontime" value="500"/>
                <setting id="offtime" value="500"/>
            </device>
        </devices>
    </board>

And then running:

    raat_runner.py --make raat_example.xml --sketchbook=/path/to/your/sketchbook

And that's it! You'll find a new sketch in your sketchbook called "Timed_OnOff". Upload it to your Arduino Uno and Pin 13 will start blinking!

## More Examples

Each device, module and parameter comes with an `example.xml` file. These are excellent introductions to how RAAT works. Try running the sketches they produce and see what you can do.

## Unit Tests

The hardware-independent bits of RAAT are unit-tested and one day the results will be integrated into this Github repository so I can have more confidence in what I'm doing.

## Limitations

Here's what RAAT *isn't*:

 - Small: a RAAT sketch will use more RAM and FLASH than an "equivalent" non-RAAT sketch (maybe a lot more)
 - Fast: RAAT is not designed for applications that need lightning fast responses. The background processing takes up CPU cycles that could be used for other things. It's designed for speed of development, not speed of code!
 - Production Ready: because it can be driven by text files and command line programs, in theory it can be built into automated deployment pipelines - but as said above, it's experimental and liable to break!
 - Super-beginner-friendly: while RAAT certainly can be used by beginners to Arduino, it's better to have some idea of the ecosystem and how to code before jumping in. 

## BDD Testing

The RAAT code development is not exactly "behaviour driven", but it does have "BDD-style" tests supporting it!

The tests use [`behave`](https://behave.readthedocs.io/en/latest/) to implement them. RAAT is run using `subprocess`, and the generated output parsed using [`clang`](https://clang.llvm.org/).

The Python clang bindings are apparently not stable, so I've picked a version that works and I'm sticking with that. As long your clang version is >= 5 you should be OK. Importantly, your clang version and the Python bindings version need to match.

To run the tests, you need to:

 - Install behave to your local python environment (`pip install behave` should be enough).
 - clang - Either from your OS packages or from the [LLVM download page](http://releases.llvm.org/download.html).
 - Python clang bindings to match clang - you can force a matching version by using `pip install clang=X.x` where X.x is the version.
 