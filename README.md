## Rotary Encoder with a Push Button

Easily read rotary encoder buttons that also incorporate a push button, like Adafruit Rotary Encoder.

https://www.adafruit.com/product/377

This is a simple wrapper library for the wonderful [Encoder Library](http://www.pjrc.com/teensy/td_libs_Encoder.html) that
provides a couple of small additional convenient methods.

It returns delta instead of absolute values, which makes it easier to use Rotary in applications, and also provides
support for detecting and handling button press.  In this case we do not care about holding a button, or double
clicking, which are all possible valid applications.  We are making the most simple obvious single button press
really easy to use, which was my goal.

## Dependencies

 * [Encoder](http://www.pjrc.com/teensy/td_libs_Encoder.html)

To run the example, also need

 * [Simple Timer](https://github.com/infomaniac50/SimpleTimer)


## Example

```c++
#include <RotaryEncoderWithButton.h>

// pinA, pinB, pinButton
RotaryEncoderWithButton rotary(2,3,4);

void setup() {
	Serial.begin(9600);

	// required to initials button pin, assumes built-in pull up resistor
	rotary.begin();
}

void loop() {
    long delta = rotary.rotaryDelta();
    if (delta > 0) {
        // turned right
    } else if (delta < 0) {
        // turned left
    }

    if (rotary.buttonClicked()) {
        // button was clicked
    }
}

```

## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Added some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request

## Author

Konstantin Gredeskoul, @kig, http://github.com/kigster

## License

MIT.  See LICENSE file for more details.

