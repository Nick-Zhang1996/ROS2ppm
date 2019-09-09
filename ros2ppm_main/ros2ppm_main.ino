// ppm generation
// Nick Zhang 2019
// The PPM signal is generated with the following convention
// A complete PPM frame is about 22.5 ms (can vary between manufacturer), and signal low state is always 0.3 ms. It begins with a start frame (high state for more than 2 ms). Each channel (up to 8) is encoded by the time of the high state (PPM high state + 0.3 × (PPM low state) = servo PWM pulse width).
// This means a 1000-2000 PWM translates to ???? High state

#include <Arduino.h>
#include <ros.h>
#include <rcvip_msgs/RCchannel.h>

// Channel, if more channels are needed make sure you update msg/RCchannel.msg as well
#define CHANNEL_NO 4
#define RC_MAX 2000
#define RC_MIN 1000

const int output_pin = 4;
// channels go from 1 - channel_no
// the extra channel 0 is reserved for TSYNC to indicate end of a frame
// unit of value is us for servo PWM
// realistically 
// XXX There may be a race condition on this variable
volatile uint16_t channel[CHANNEL_NO+1] = {0};
volatile bool lock_channel = false;

// Timer 1 COMPA would generate rising edge
// Timer 1 COMPB would generate falling edge
void timer1_init(){
    //set timer1 interrupt 
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCCR1C = 0; // PWM related stuff
    TIFR1 |= (1<<TOV1) | (1<<OCF1B) | (1<<OCF1A); // writing 1 to TOV1 clears the flag, preventing the ISR to be activated as soon as sei();
    TCNT1 = 0;

    // prescaler: 64
    // duty cycle: (16*10^6) / (64*65536) Hz = 38Hz (3300us between overflow)
    // overflow interval (64*65536)/(16e6) = 26ms 
    // per count(resolution) : 0.4us
    // this starts counting
    TCCR1B |= (1 << CS11) | (1 << CS10) ; 

    // enable timer compare interrupt and overflow interrupt
    TIMSK1 = (1 << OCIE1A) | ( 1 << OCIE1B); 
// for reference, ovf interrupt
    //TIMSK1 = (1 << TOIE1);
}

// this will set ISR(TIMER1_COMPA_vect) to fire in specified delay
// the ISR will determine the proper action to take depending on the value in pending_action
void next_action_t1a(float us){

    uint16_t ticks = TCNT1 + (us/4);

    cli();// is this really necessary?
    OCR1A  = ticks;
    sei();

}

void next_action_t1b(float us){

    uint16_t ticks = TCNT1 + (us/4);

    cli();// is this really necessary?
    OCR1B  = ticks;
    sei();

}

// raise output at proper timing
volatile uint8_t next_channel = 0;
ISR(TIMER1_COMPA_vect) {
    // TODO assembly this
    digitalWrite(output_pin,HIGH);
    next_channel++;
    next_channel %= CHANNEL_NO + 1;

    // assert channel[?] > 300
    if (next_channel==0){
        next_action_t1a(4500);
        next_action_t1b(300);
    }else{
        next_action_t1a(channel[next_channel]);
        next_action_t1b(channel[next_channel]-300);
    }
}

ISR(TIMER1_COMPB_vect) {
    // TODO assembly this
    digitalWrite(output_pin,LOW);
}

ros::NodeHandle nh;

//XXX this may create a race condition
void readChannelsTopic(const rcvip_msgs::RCchannel& msg_RCchannel){
  for(int i=0; i<CHANNEL_NO; i++){
    channel[i+1] = min(max(msg_RCchannel.ch[i],RC_MIN),RC_MAX);
  }
  // DEBUG XXX 
  if (channel[1] > 1600){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }

}

ros::Subscriber<rcvip_msgs::RCchannel> subRCchannel("vip_rc/channel", &readChannelsTopic);

void setup(){
    // start of the frame
    channel[0] = 12000;

    channel[1] = 1000;
    channel[2] = 800;
    channel[3] = 1000;
    channel[4] = 1000;
    pinMode(output_pin,OUTPUT);
    pinMode(13,OUTPUT);
    timer1_init();
    nh.initNode();
    nh.subscribe(subRCchannel);
}

void loop(){
  /*
    if (Serial.available()>0) {
        float val = Serial.parseFloat();
        //ctrl_phase = fmap(val,0,360,0,2*pi);
        if (val<2000 and val >350){
            cli();
            channel[1] = val;
            sei();
        Serial.println(val);
        }
        
    }
    delay(10);
    */
  nh.spinOnce();
  delay(1);

}
