#define SOUND_BUTTON_ONE    2
#define SOUND_BUTTON_TWO    3
#define SOUND_BUTTON_THREE  4
#define SOUND_MIC_SWITCH    5
#define SET_BUTTON_ONE      6
#define SET_BUTTON_TWO      7
#define SET_BUTTON_THREE    8
#define SET_BUTTON_FOUR     9
#define SPECIAL_FOG_SWITCH  10
#define SPECIAL_FIRE_BUTTON 11

#define SPECIAL_CURTAIN_POT        A0
#define SPECIAL_LIGHT_SLIDER_ONE   A1
#define SPECIAL_LIGHT_SLIDER_TWO   A2
#define SPECIAL_LIGHT_SLIDER_THREE A3

void setup() {
  analogReference(EXTERNAL); 
  Serial.begin(115200);
}

void loop() {

  if(Serial.available() > 0){
    while(Serial.available() > 0){
      Serial.read();
    }
    Serial.print("-");
  }
  
  int soundButtonOne          = digitalRead(SOUND_BUTTON_ONE);
  int soundButtonTwo          = digitalRead(SOUND_BUTTON_TWO);
  int soundButtonThree        = digitalRead(SOUND_BUTTON_THREE);
  int soundMicSwitch          = digitalRead(SOUND_MIC_SWITCH);
  int setButtonOne            = digitalRead(SET_BUTTON_ONE);
  int setButtonTwo            = digitalRead(SET_BUTTON_TWO);
  int setButtonThree          = digitalRead(SET_BUTTON_THREE);
  int setButtonFour           = digitalRead(SET_BUTTON_FOUR);
  int specialFogSwitch        = digitalRead(SPECIAL_FOG_SWITCH);
  int specialFireButton       = digitalRead(SPECIAL_FIRE_BUTTON);

  int specialCurtainPot       = analogRead(SPECIAL_CURTAIN_POT);
  int specialLightSliderOne   = analogRead(SPECIAL_LIGHT_SLIDER_ONE);
  int specialLightSliderTwo   = analogRead(SPECIAL_LIGHT_SLIDER_TWO);
  int specialLightSliderThree = analogRead(SPECIAL_LIGHT_SLIDER_THREE);

  Serial.print("[");
  Serial.print(soundButtonOne);
  Serial.print(",");
  Serial.print(soundButtonTwo);
  Serial.print(",");
  Serial.print(soundButtonThree);
  Serial.print(",");
  Serial.print(soundMicSwitch);
  Serial.print(",");
  Serial.print(setButtonOne);
  Serial.print(",");
  Serial.print(setButtonTwo); 
  Serial.print(",");
  Serial.print(setButtonThree);
  Serial.print(",");
  Serial.print(setButtonFour);
  Serial.print(",");
  Serial.print(specialFogSwitch);
  Serial.print(",");
  Serial.print(specialFireButton);
  Serial.print(",");
  Serial.print(specialCurtainPot);
  Serial.print(",");
  Serial.print(specialLightSliderOne);
  Serial.print(",");
  Serial.print(specialLightSliderTwo);
  Serial.print(",");
  Serial.print(specialLightSliderThree);
  Serial.print("]\n");
}
