#include <Arduino.h>

#define UP_DIR 1
#define DOWN_DIR 0

class Motor{
  private:
    uint8_t en_pin = NULL;
    uint8_t dir_pin = NULL;
  
  public:
    void attach(uint8_t e_pin, uint8_t d_pin){
    	en_pin = e_pin; 
    	dir_pin = d_pin;
        pinMode(en_pin, OUTPUT);
        pinMode(dir_pin, OUTPUT);
    } 
    
    void setSpeed(int power){
    	if(power >= 0 and power < 256){
    		digitalWrite(en_pin, 0);
    		digitalWrite(dir_pin, HIGH);
    		analogWrite(en_pin, power);
    	}
    	else if(power < 0 and power > -256){
    		digitalWrite(en_pin, 0);
    		digitalWrite(dir_pin, LOW);
    		analogWrite(en_pin, -1 * power);

    	}
    }

    void setSpeed(bool direction, uint8_t power){
    	//digitalWrite(en_pin, 0);
    	if(direction){
    		digitalWrite(dir_pin, HIGH);
    	}
    	else{
    		digitalWrite(dir_pin, LOW);
    	}
    	analogWrite(en_pin, power);
    }

    void stop(){
        digitalWrite(en_pin, 0);
    }
    
};
