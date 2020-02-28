#include <Arduino.h>

class PID{
	
	private:
		float kp;
		float kd;
		float ki;
		float integr_sum;
		float min_val;
		float max_val;
		float last_err;
	public:
		PID(float p = 0, float d = 0, float i = 0, float min = NULL, float max = NULL){
			kp = p;
			kd = d;
			ki = i;
			min_val = min;
			max_val = max;
		}

		void init(float p, float d, float i, float min, float max){
			kp = p;
			kd = d;
			ki = i;
			min_val = min;
			max_val = max;
		}

		float calculate(float cur_err){
			float result;
			float p = kp * cur_err;
			float d = 0;
			if(last_err != NULL) d = kp * (cur_err - last_err); 
			float i = integr_sum;
			integr_sum += ki*cur_err;
			last_err = cur_err;
			result = p + i + d;
			if( min_val != NULL){
				if(result < min_val) result = min_val; 
			}
			else if(max_val != NULL){
				if(result > max_val) result = max_val; 	
			}
			return result;
		}

		void setMinVal(float min){
			min_val = min;
		}

		void setMaxVal(float max){
			max_val = max;
		}

	   void reset(){
	    integr_sum = 0;
	    last_err = NULL;
	   }

};
