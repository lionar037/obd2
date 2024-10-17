#include "oled.hpp"
#include "SSD1306_OLED.hpp" // La librería que utilizas para la pantalla

#define FULLSCREEN (width_ * (height_ / 8))


namespace OLED{

    Oled_t::Oled_t(uint16_t width, uint16_t height, uint16_t i2c_speed, uint8_t i2c_address)
        : width_(width), height_(height), i2c_speed_(i2c_speed), i2c_address_(i2c_address), i2c_debug_(false), screenBuffer_(nullptr),
        myOLED(width, height) // Inicializar el objeto SSD1306 aquí
    {}

    Oled_t::~Oled_t() {
        powerDown();
    }

    bool Oled_t::begin(bool i2c_debug) {
        i2c_debug_ = i2c_debug;
        
        if (!bcm2835_init()) {
            printf("Error: init bcm2835 library failed\n");
            return false;
        }

        if (!initI2C()) {
            bcm2835_close();
            return false;
        }

        myOLED.OLEDbegin(i2c_speed_, i2c_address_, i2c_debug_);
        screenBuffer_ = new uint8_t[FULLSCREEN];
        myOLED.OLEDSetBufferPtr(width_, height_, screenBuffer_, FULLSCREEN);
        //myOLED.OLEDFillScreen(0xF0, 0);
        bcm2835_delay(100);

        return true;
    }

    void Oled_t::clearScreen() {
        myOLED.OLEDclearBuffer();
    }

    void Oled_t::displayText(const char* text, int x, int y) {
        myOLED.setTextColor(WHITE);
        myOLED.setCursor(x, y);
        myOLED.print(text);
        myOLED.OLEDupdate();
    }

    void Oled_t::powerDown() {
        myOLED.OLEDPowerDown();
        closeI2C();
        bcm2835_close();
        delete[] screenBuffer_;
    }

    bool Oled_t::initI2C() {
        if (!myOLED.OLED_I2C_ON()) {
            printf("Error: Cannot start I2C\n");
            return false;
        }
        return true;
    }

    void Oled_t::closeI2C() {
        myOLED.OLED_I2C_OFF();
    }

}
