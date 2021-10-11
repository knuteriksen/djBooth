#define RELAY_PIN 12        //D12
#define BUTTON_PIN 2        //D2

#define TIMEOUT   900000    //15*60*1000 = 15 min -> milliSeconds
// #define TIMEOUT 60000

unsigned long time_start = 0;
bool timer_active = false;
volatile int button_pushed = 0;

void lights_off() {
  digitalWrite(RELAY_PIN, LOW);
}

void lights_on() {
  digitalWrite(RELAY_PIN, HIGH);
}

bool is_timeout() {
  return (timer_active && (millis() > time_start + TIMEOUT));
}

void start_timer() {
  time_start = millis();
  timer_active = true;
}

void stop_timer() {
  timer_active = false;
}

void on_interrupt() {
  button_pushed = 1;
}

void setup() {
  // put your setup code here, to run once:  
  pinMode(RELAY_PIN, OUTPUT);
  lights_off();

  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), on_interrupt, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:  
  if (button_pushed) {
    start_timer();
    lights_on();
    button_pushed = 0;
  }
  if (is_timeout()) {
    stop_timer();
    lights_off();
  }
}
