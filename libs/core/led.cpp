#include "pxt.h"

enum class DisplayMode_ {
    //% block="black and white"
    BlackAndWhite = DISPLAY_MODE_BLACK_AND_WHITE,
    //% blockHidden=true
    BackAndWhite = DISPLAY_MODE_BLACK_AND_WHITE,
    //% block="greyscale"
    Greyscale = DISPLAY_MODE_GREYSCALE,
    // TODO DISPLAY_MODE_BLACK_AND_WHITE_LIGHT_SENSE
};

//% color=#7600A8 weight=101 icon="\uf205"
namespace led {

    /**
     * Turn on the specified LED using x, y coordinates (x is horizontal, y is vertical). (0,0) is upper left.
     * @param x the horizontal coordinate of the LED starting at 0
     * @param y the vertical coordinate of the LED starting at 0
     */
    //% help=led/plot weight=78
    //% blockId=device_plot block="plot|x %x|y %y" blockGap=8
    //% x.label="x" y.label="y"
    //% parts="ledmatrix"
    //% x.min=0 x.max=4 y.min=0 y.max=4
    //% x.fieldOptions.precision=1 y.fieldOptions.precision=1
    void plot(int x, int y) {
      // TODO
      #ifndef NRF54L_SERIES
      uBit.display.image.setPixelValue(x, y, 0xff);
      #endif // NRF54L_SERIES
    }

    /**
     * Turn on the specified LED with specific brightness using x, y coordinates (x is horizontal, y is vertical). (0,0) is upper left.
     * @param x the horizontal coordinate of the LED starting at 0
     * @param y the vertical coordinate of the LED starting at 0
     * @param brightness the brightness from 0 (off) to 255 (bright), eg:255
     */
    //% help=led/plot-brightness weight=78
    //% blockId=device_plot_brightness block="plot|x %x|y %y|brightness %brightness" blockGap=8
    //% x.label="x" y.label="y" brightness.label="brightness"
    //% parts="ledmatrix"
    //% x.min=0 x.max=4 y.min=0 y.max=4 brightness.min=0 brightness.max=255
    //% x.fieldOptions.precision=1 y.fieldOptions.precision=1
    //% advanced=true
    void plotBrightness(int x, int y, int brightness) {
        brightness = max(0, min(0xff, brightness));
        // enable greyscale as needed
      // TODO
      #ifndef NRF54L_SERIES
        if (brightness != 0 && brightness != 0xff && uBit.display.getDisplayMode() != DISPLAY_MODE_GREYSCALE)
            uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
        uBit.display.image.setPixelValue(x, y, brightness);
      #endif // NRF54L_SERIES
    }

    /**
     * Turn off the specified LED using x, y coordinates (x is horizontal, y is vertical). (0,0) is upper left.
     * @param x the horizontal coordinate of the LED
     * @param y the vertical coordinate of the LED
     */
    //% help=led/unplot weight=77
    //% blockId=device_unplot block="unplot|x %x|y %y" blockGap=8
    //% x.label="x" y.label="y"
    //% parts="ledmatrix"
    //% x.min=0 x.max=4 y.min=0 y.max=4
    //% x.fieldOptions.precision=1 y.fieldOptions.precision=1
    void unplot(int x, int y) {
      // TODO
      #ifndef NRF54L_SERIES
      uBit.display.image.setPixelValue(x, y, 0);
      #endif // NRF54L_SERIES
    }

    /**
     * Get the brightness state of the specified LED using x, y coordinates. (0,0) is upper left.
     * @param x the horizontal coordinate of the LED
     * @param y the vertical coordinate of the LED
     */
    //% help=led/point-brightness weight=76
    //% blockId=device_point_brightness block="point|x %x|y %y brightness"
    //% x.label="x" y.label="y"
    //% parts="ledmatrix"
    //% x.min=0 x.max=4 y.min=0 y.max=4
    //% x.fieldOptions.precision=1 y.fieldOptions.precision=1
    //% advanced=true
    int pointBrightness(int x, int y) {
      // TODO
      #ifdef NRF54L_SERIES
      return 0;
      #else
      return uBit.display.image.getPixelValue(x, y);
      #endif // NRF54L_SERIES
    }

    /**
     * Get the screen brightness from 0 (off) to 255 (full bright).
     */
    //% help=led/brightness weight=60
    //% blockId=device_get_brightness block="brightness" blockGap=8
    //% parts="ledmatrix"
    //% advanced=true
    int brightness() {
      // TODO
      #ifdef NRF54L_SERIES
      return 0;
      #else
      return uBit.display.getBrightness();
      #endif // NRF54L_SERIES
    }

    /**
     * Set the screen brightness from 0 (off) to 255 (full bright).
     * @param value the brightness value, eg:255, 127, 0
     */
    //% help=led/set-brightness weight=59
    //% blockId=device_set_brightness block="set brightness %value"
    //% value.label="value"
    //% parts="ledmatrix"
    //% advanced=true
    //% value.min=0 value.max=255
    void setBrightness(int value) {
      // TODO
      #ifndef NRF54L_SERIES
       uBit.display.setBrightness(value);
      #endif // NRF54L_SERIES
    }

    /**
     * Cancels the current animation and clears other pending animations.
     */
    //% weight=50 help=led/stop-animation
    //% blockId=device_stop_animation block="stop animation"
    //% parts="ledmatrix"
    //% advanced=true
    void stopAnimation() {
      // TODO
      #ifndef NRF54L_SERIES
       uBit.display.stopAnimation();
      #endif // NRF54L_SERIES
    }

    /**
     * Sets the display mode between black and white and greyscale for rendering LEDs.
     * @param mode mode the display mode in which the screen operates
     */
    //% weight=1 help=led/set-display-mode
    //% parts="ledmatrix" advanced=true weight=1
    //% blockId="led_set_display_mode" block="set display mode $mode"
    void setDisplayMode(DisplayMode_ mode) {
      // TODO
      #ifndef NRF54L_SERIES
        uBit.display.setDisplayMode((DisplayMode)mode);
      #endif // NRF54L_SERIES
    }

    /**
    * Gets the current display mode
    */
    //% weight=1 parts="ledmatrix" advanced=true
    DisplayMode_ displayMode() {
      // TODO
      #ifdef NRF54L_SERIES
      return (DisplayMode_)0;
      #else
        return (DisplayMode_)uBit.display.getDisplayMode();
      #endif // NRF54L_SERIES
    }

    /**
    * Turns on or off the display
    */
    //% help=led/enable blockId=device_led_enable block="led enable %on"
    //% on.label="value"
    //% advanced=true parts="ledmatrix"
    void enable(bool on) {
      // TODO
      #ifndef NRF54L_SERIES
        if (on) uBit.display.enable();
        else uBit.display.disable();
      #endif // NRF54L_SERIES
    }

    /**
     * Takes a screenshot of the LED screen and returns an image.
     */
    //% help=led/screenshot
    //% parts="ledmatrix"
    Image screenshot() {
      // TODO
      #ifdef NRF54L_SERIES
        auto d = MicroBitImage(5, 5).leakData();
      #else
        auto d = uBit.display.screenShot().leakData();
      #endif // NRF54L_SERIES
        auto r = NEW_GC(RefMImage, d);
        d->decr();
        return r;
        /*
        let Image img;
        img = image.createImage("");
        for (let i = 0; i < 5; i++) {
            for (let j = 0; j < 5; j++) {
                if (led.point(i, j)) {
                    img.setPixel(i, j, true);
                }
            }
        }
        return img;
        */
    }
}
