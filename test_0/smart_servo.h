#include "pid.h"
#include "motor.h"

class SmartServo{

	private:
		PID pid;
		Motor motor;

		uint8_t mode = 1;
		uint16_t current_pos;
		uint16_t target_pos;
		uint8_t power;
		uint16_t min_pos;
		uint16_t max_pos;
    bool direction;
	public:

		SmartServo();
		void init_pid(float kp, float kd, float ki, uint8_t min, uint8_t max);
		void init_motor(uint8_t e_pin, uint8_t d_pin);
		void setMinPos(uint16_t min_p);
		void setMaxPos(uint16_t max_p);
		void setTargetPos(uint16_t t_pos, uint8_t pow);
		void setTargetPos(uint16_t t_pos);
    void stop();
		void update();
    void increase();
    void decrease();
    bool getDirection();
    void setDirection(bool dir);
		uint16_t getCurrentPos();
};
