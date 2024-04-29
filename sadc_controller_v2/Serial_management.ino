#include "sadc_controller.h"

byte i = 0;

void GetMessage(){
  if (Serial.available()){
    byte error = 0;
    byte id = 0;
    i = 3;
    String str = Serial.readString();
    str.toLowerCase();

    String calling = str.substring(0,3);
    if (calling == OIN_CALLING) {
      id = getID(str);
      if (id == 0)
        error = 2;
      else {
        switch (str[i++]) {
          case 'p': {
            Serial.write(OIN_PING);
            Serial.write(id);
            break;
          }
          case 'o': {
            error = setOinTurnedTo(str, id);
            break;
          }
          case 'c': {
            error = changeID(str, id);
            break;
          }
          case 'r': {
            Serial.write(OIN_REQUEST);
            Serial.write(id);
            Serial.write(OIN_RESET_ID);
            break;
          }
          case 's': {
            error = setOinOuts(str, id);
            break;
          }
          default: {
            error = 3;
            break;
          }
        }
      }
    } else if (calling == ARDUINO_CALLING) {
      switch (str[i++]){
        case 's': {
          setStartStop(str);
          break;
        }
        case 'r': {
          setResistance(str);
          break;
        }
      }   
    } else {
      error = 1;
    }
    if (error != 0){
      Serial.print("Occured error: ");
      Serial.println(error);
      Serial.print("Bad request: ");
      Serial.println(str);
    }

  }
}

byte getID(String str){
  i = 3;
  byte id = 0;

  String idS = "";
  while ((str[i] >= '0') && (str[i] <= '9')){
    idS += str[i++];
  } 
  if ((idS.length() > 0) && (idS.length() < 4))
    id = idS.toInt();
  else
    id = 0; 
  return id;
}

byte changeID (String str, byte id){
  return 0;
}

byte setOinTurnedTo(String str, byte id){
  Serial.write(OIN_REQUEST);
  Serial.write(id);
  if (str.length() <= i)
    return 40;
  if (str[i] == 'n') 
    Serial.write(OIN_TURN_ON);
  else if ((str[i++] == 'f') && (str.length() > i)){
    if (str[i] == 'f')
      Serial.write(OIN_TURN_OFF);
  }
  else
    return 44;
  return 0;
}

byte setOinOuts(String str, byte id){
  Serial.write(OIN_REQUEST);
  Serial.write(id);
  if (str.length() >= 10){
    byte comMask = 0;
    switch (str[7]){
      case '0': {
        comMask = 0 & COM_COMPORATOR_MASK;
        break;
      }
      case '1': {
        comMask = 255 & COM_OIN_MINUS1_MASK;
        break;
      }
      case '2': {
        comMask = 255 & COM_OIN_MINUS2_MASK;
        break;
      }
      case '3': {
        comMask = 255 & COM_COMPORATOR_MASK;
        break;
      }
      default:
      // comMask = 255 & COM_OIN_PLUS2_MASK;
        return 41;
    }
    byte powMask = 0;
    switch (str[8]){
      case '0': {
        powMask = 0 & COM_POWER_MASK;
        break;
      }
      case '1': {
        powMask = 255 & COM_POWER_MASK;
        break;
      }
      default:
        return 42;
    }
    byte balMask = 0;
    switch (str[9]){
      case '0': {
        balMask = 0 & COM_BALANCE_MASK;
        break;
      }
      case '1': {
        balMask = 255 & COM_OIN_PLUS1_MASK;
        break;
      }
      case '2': {
        balMask = 255 & COM_OIN_PLUS2_MASK;
        break;
      }
      case '3': {
        balMask = 255 & COM_BALANCE_MASK;
        break;
      }
      default:
        return 43;
    }
    byte cmd = OIN_DISABLE | comMask | powMask | balMask;
    Serial.write(cmd);
  } else 
    return 40;
  return 0;
}

byte setStartStop(String str){
  if (str[i] == 'm'){
    if (str[++i] == '0')
      measureMode = 0;
    else if (str[i] == '1')
      measureMode = 1;
    else
      return 50;
  } else if (str[i] == 'r'){
    if (str[++i] == '0')
      resistanceMode = 0;
    else if (str[i] == '1')
      resistanceMode = 1;
    else 
      return 51;
  } else 
    return 40;
  return 0;
}

byte setResistance(String str){
  byte resistance = 0;
  String resistanceS = "";
  while ((str[i] >= '0') && (str[i] <= '9')){
    resistanceS += str[i++];
  } 
  if ((resistanceS.length() > 0) && (resistanceS.length() < 4)){
    resistance = resistanceS.toInt();
    setResistanceAD8402(1, resistance); 
  }
  else
    return 40; 
  return 0;
}
