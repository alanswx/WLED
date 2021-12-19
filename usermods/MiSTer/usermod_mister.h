#pragma once

#include "wled.h"
#include "palettes.h"
/*
 * Usermods allow you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 * 
 * This is an example for a v2 usermod.
 * v2 usermods are class inheritance based and can (but don't have to) implement more functions, each of them is shown in this example.
 * Multiple v2 usermods can be added to one compilation easily.
 * 
 * Creating a usermod:
 * This file serves as an example. If you want to create a usermod, it is recommended to use usermod_v2_empty.h from the usermods folder as a template.
 * Please remember to rename the class and file to a descriptive name.
 * You may also use multiple .h and .cpp files.
 * 
 * Using a usermod:
 * 1. Copy the usermod into the sketch folder (same folder as wled00.ino)
 * 2. Register the usermod by adding #include "usermod_filename.h" in the top and registerUsermod(new MyUsermodClass()) in the bottom of usermods_list.cpp
 */

//class name. Use something descriptive and leave the ": public Usermod" part :)
class MiSTerUsermod : public Usermod {
  private:
    //Private class members. You can declare variables and functions only accessible to your usermod here
    unsigned long lastTime = 0;

    // set your config variables to their boot default value (this can also be done in readFromConfig() or a constructor if you prefer)
    bool testBool = false;
    unsigned long testULong = 42424242;
    float testFloat = 42.42;
    String testString = "Forty-Two";

    // These config variables have defaults set inside readFromConfig()
    int testInt;
    long testLong;
    int8_t testPins[2];


String newCommand = "";                // Received Text, from MiSTer without "\n" currently (2021-01-11)
String prevCommand = "";
String actCorename = "No Core loaded"; // Actual Received Corename
String oldActCorename = "";



  public:
    //Functions called by WLED

    /*
     * setup() is called once at boot. WiFi is not yet connected at this point.
     * You can use it to initialize variables, sensors or similar.
     */
    void setup() {
     Serial.begin(115200);                      // 115200 for MiSTer ttyUSBx Device CP2102 Chip on ESP32
     //Serial.begin(9600);                      // 115200 for MiSTer ttyUSBx Device CP2102 Chip on ESP32

  Serial.flush();                            // Wait for empty Send Buffer
  Serial.setTimeout(500);                    // Set max. Serial "Waiting Time", default = 1000ms

  //randomSeed(analogRead(34));                // Init Random Generator with empty Port Analog value
   Serial.println("Hello from my usermod!");
    }


    /*
     * connected() is called every time the WiFi is (re)connected
     * Use it to initialize network interfaces
     */
    void connected() {
      Serial.println("Connected to WiFi!");
    }


    /*
     * loop() is called continuously. Here you can check for events, read sensors, etc.
     * 
     * Tips:
     * 1. You can use "if (WLED_CONNECTED)" to check for a successful network connection.
     *    Additionally, "if (WLED_MQTT_CONNECTED)" is available to check for a connection to an MQTT broker.
     * 
     * 2. Try to avoid using the delay() function. NEVER use delays longer than 10 milliseconds.
     *    Instead, use a timer check as shown here.
     */
    void loop() {

      if (millis() - lastTime > 5000) {
        Serial.println("I'm alive!");
        lastTime = millis();
      }

     // return;
  
  unsigned long currentMillis = millis();

 // Get Serial Data
  if (Serial.available()) {
	prevCommand = newCommand;                                // Save old Command
    newCommand = Serial.readStringUntil('\n');             // Read string from serial until NewLine "\n" (from MiSTer's echo command) is detected or timeout (1000ms) happens.
    //updateDisplay=true;                                    // Set Update-Display Flag

    Serial.printf("Received Corename or Command: %s\n", (char*)newCommand.c_str());
  }  // end serial available

    if (newCommand.endsWith("QWERTZ")) {                         // Process first Transmission after PowerOn/Reboot.
        // Do nothing, just receive one string to clear the buffer.
    }                    

    // ---------------------------------------------------
    // ---------------- C O M M A N D 's -----------------
    // ---------------------------------------------------

    else if (newCommand=="cls") {                                        // Clear Screen
     // oled.clearDisplay();
     // oled.display();
    }
    //else if (newCommand=="sorg")         oled_showStartScreen();
    //else if (newCommand=="bye")          oled_drawlogo64h(sorgelig_icon64_width, sorgelig_icon64);
    
    // ---------------------------------------------------
    // -------------- Command Mode V2 --------------------
    // ---------------------------------------------------

    // -- Test Commands --
    else if (newCommand=="CMDCLS") {                                        // Clear Screen
     // oled.clearDisplay();
     // oled.display();
    }
    
    else if (newCommand=="CMDSORG") {                                       // Show Startscreen
      //oled_showStartScreen();
    }
    
    else if (newCommand=="CMDBYE") {                                        // Show Sorgelig's Icon
      //oled_drawlogo64h(sorgelig_icon64_width, sorgelig_icon64);
    }

    else if (newCommand=="CMDHWINF") {                                      // Send HW Info
      //oled_sendHardwareInfo();
    }

    else if (newCommand=="CMDTEST") {                                       // Show Test-Picture
      //oled_drawlogo64h(TestPicture_width, TestPicture);
    }

    else if (newCommand=="CMDSNAM") {                                       // Show actual loaded Corename
      //usb2oled_showcorename();
    }

    else if (newCommand=="CMDSPIC") {                                       // Show actual loaded Picture with Transition
      //usb2oled_drawlogo(random(minEffect,maxEffect+1));
    }

    else if (newCommand=="CMDDOFF") {                                       // Switch Display Off
      //usb2oled_displayoff();
    }

    else if (newCommand=="CMDDON") {                                        // Switch Display On
      //usb2oled_displayon();
    }

    else if (newCommand=="CMDDUPD") {                                       // Update Display Content
      //usb2oled_updatedisplay();
    }

    else if (newCommand.startsWith("CMDTXT,")) {                            // Command from Serial to write Text
      //usb2oled_readnwritetext();                                            // Read and Write Text
    }
    
    else if (newCommand.startsWith("CMDGEO,")) {                            // Command from Serial to draw geometrics
      //usb2oled_readndrawgeo();                                              // Read and Draw Geometrics
    }

    else if (newCommand.startsWith("CMDAPD,")) {                            // Command from Serial to receive Picture Data via USB Serial from the MiSTer
      //usb2oled_readlogo();                                                  // ESP32 Receive Picture Data... 
    }

    else if (newCommand.startsWith("CMDCOR,")) {                            // Command from Serial to receive Picture Data via USB Serial from the MiSTer
      //if (usb2oled_readlogo()==1) {                                         // ESP32 Receive Picture Data... 
      //  usb2oled_drawlogo(random(minEffect,maxEffect+1));                   // ...and show them on the OLED with Transition Effect 1..10
      //}
    }

    else if (newCommand.startsWith("CMDCOR0,")) {                           // Command from Serial to receive Picture Data via USB Serial from the MiSTer
      //if (usb2oled_readlogo()==1) {                                         // ESP32 Receive Picture Data....
      //  usb2oled_drawlogo(0);                                               // ...and show them on the OLED with Transition Effect 0
      //}
    }
    
    else if (newCommand.startsWith("CMDCON,")) {                            // Command from Serial to receive Contrast-Level Data from the MiSTer
      //usb2oled_readnsetcontrast();                                          // Read and Set contrast                                   
    }

    else if (newCommand.startsWith("CMDROT,")) {                            // Command from Serial to set Rotation
      //usb2oled_readnsetrotation();                                          // Set Rotation
    }



    // The following Commands are only for ESP32
#ifdef ESP32  // OTA and Reset only for ESP32
    else if (newCommand=="CMDENOTA") {                                      // Command from Serial to enable OTA on the ESP
      //enableOTA();                                                          // Setup Wireless and enable OTA
    }

    else if (newCommand=="CMDRESET") {                                      // Command from Serial for Resetting the ESP
      //ESP.restart();                                                        // Reset ESP
    }
#endif

    // -- Unidentified Core Name, just write it on screen
    else {
          

      actCorename=newCommand;
      actCorename.trim();
      //Serial.println("checking ["+oldActCorename+"] vs["+actCorename+"]");
      if (oldActCorename!=actCorename) {
        Serial.println("about to lookup");
        Serial.print(actCorename);
//        lookup_preset_id_by_name(actCorename);
        lookup_palette_id_by_name(actCorename);
        oldActCorename=actCorename;
      }
      //actPicType=0;

     // usb2oled_showcorename();
    }  // end ifs

#ifdef XSENDACK
    delay(cDelay);                           // Command Response Delay
    Serial.print("ttyack;");                 // Handshake with delimiter; MiSTer: "read -d ";" ttyresponse < ${TTYDEVICE}"
    Serial.flush();                          // Wait for sendbuffer is clear
#endif

      if (millis() - lastTime > 1000) {
        Serial.println("I'm alive!");
        lastTime = millis();
      }
    }

void lookup_preset_id_by_name(String name) {
  // extract the values
    const char *filename ="/presets.json" ;
    DynamicJsonDocument doc(JSON_BUFFER_SIZE);
    errorFlag= readObjectFromFile(filename, NULL, &doc);
    Serial.print("error: ");
  Serial.println(errorFlag);
JsonObject list = doc.as<JsonObject>();
for(JsonPair kv : list) {
    int preset_num = 0;
    if (kv.key().c_str()){
      Serial.println(kv.key().c_str());
       preset_num  = atoi(kv.key().c_str());
    }
    const char* val = kv.value()["n"];
    if (val) {
        Serial.print("val: [");
        Serial.print(val);
        Serial.print("] == name: [");
        Serial.print(name);
        Serial.println("]");
        
       if (!strcasecmp(val,name.c_str() ))
      {
          Serial.print("apply preset ");
          Serial.println(preset_num);
          applyPreset(preset_num);

      }

    }
    

}
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void lookup_palette_id_by_name(String lname) {

Serial.println(sizeof(gGradientPalettes));
Serial.println(sizeof(const byte*));
Serial.print("looking up: ");
Serial.println(lname);

//Serial.println(sizeof(gGradientPalettes/sizeof(byte*)));
int len = sizeof(gGradientPalettes)/sizeof(const byte*) ;
Serial.println(len);
Serial.println(GRADIENT_PALETTE_COUNT);
len = len + 13;
Serial.println(len);
String fname="MISTER-"+lname;
Serial.print("looking up: ");
Serial.println(fname);

for (size_t i=0; i< len;i++) {
  Serial.print("line: ");
  Serial.println(i);
  String name = getValue(JSON_palette_names,',',i);
  name.trim();
  name.replace("[","");
  name.replace("]","");
  name.replace("\"","");
  Serial.println(name);
  if (name==fname){
    Serial.println("***FOUND***");
    for (uint8_t i = 0; i < strip.getMaxSegments(); i++) {
        WS2812FX::Segment& seg = strip.getSegment(i);
        if (!seg.isSelected()) continue;
        seg.palette = i;
      }
  }
}

    

}


    /*
     * addToJsonInfo() can be used to add custom entries to the /json/info part of the JSON API.
     * Creating an "u" object allows you to add custom key/value pairs to the Info section of the WLED web UI.
     * Below it is shown how this could be used for e.g. a light sensor
     */
    /*
    void addToJsonInfo(JsonObject& root)
    {
      int reading = 20;
      //this code adds "u":{"Light":[20," lux"]} to the info object
      JsonObject user = root["u"];
      if (user.isNull()) user = root.createNestedObject("u");

      JsonArray lightArr = user.createNestedArray("Light"); //name
      lightArr.add(reading); //value
      lightArr.add(" lux"); //unit
    }
    */


    /*
     * addToJsonState() can be used to add custom entries to the /json/state part of the JSON API (state object).
     * Values in the state object may be modified by connected clients
     */
  /*  void addToJsonState(JsonObject& root)
    {
      //root["user0"] = userVar0;
    }
*/

    /*
     * readFromJsonState() can be used to receive data clients send to the /json/state part of the JSON API (state object).
     * Values in the state object may be modified by connected clients
     */
    /*
    void readFromJsonState(JsonObject& root)
    {
      userVar0 = root["user0"] | userVar0; //if "user0" key exists in JSON, update, else keep old value
      //if (root["bri"] == 255) Serial.println(F("Don't burn down your garage!"));
    }
*/

    /*
     * addToConfig() can be used to add custom persistent settings to the cfg.json file in the "um" (usermod) object.
     * It will be called by WLED when settings are actually saved (for example, LED settings are saved)
     * If you want to force saving the current state, use serializeConfig() in your loop().
     * 
     * CAUTION: serializeConfig() will initiate a filesystem write operation.
     * It might cause the LEDs to stutter and will cause flash wear if called too often.
     * Use it sparingly and always in the loop, never in network callbacks!
     * 
     * addToConfig() will make your settings editable through the Usermod Settings page automatically.
     *
     * Usermod Settings Overview:
     * - Numeric values are treated as floats in the browser.
     *   - If the numeric value entered into the browser contains a decimal point, it will be parsed as a C float
     *     before being returned to the Usermod.  The float data type has only 6-7 decimal digits of precision, and
     *     doubles are not supported, numbers will be rounded to the nearest float value when being parsed.
     *     The range accepted by the input field is +/- 1.175494351e-38 to +/- 3.402823466e+38.
     *   - If the numeric value entered into the browser doesn't contain a decimal point, it will be parsed as a
     *     C int32_t (range: -2147483648 to 2147483647) before being returned to the usermod.
     *     Overflows or underflows are truncated to the max/min value for an int32_t, and again truncated to the type
     *     used in the Usermod when reading the value from ArduinoJson.
     * - Pin values can be treated differently from an integer value by using the key name "pin"
     *   - "pin" can contain a single or array of integer values
     *   - On the Usermod Settings page there is simple checking for pin conflicts and warnings for special pins
     *     - Red color indicates a conflict.  Yellow color indicates a pin with a warning (e.g. an input-only pin)
     *   - Tip: use int8_t to store the pin value in the Usermod, so a -1 value (pin not set) can be used
     *
     * See usermod_v2_auto_save.h for an example that saves Flash space by reusing ArduinoJson key name strings
     * 
     * If you need a dedicated settings page with custom layout for your Usermod, that takes a lot more work.  
     * You will have to add the setting to the HTML, xml.cpp and set.cpp manually.
     * See the WLED Soundreactive fork (code and wiki) for reference.  https://github.com/atuline/WLED
     * 
     * I highly recommend checking out the basics of ArduinoJson serialization and deserialization in order to use custom settings!
     */
    /*
    void addToConfig(JsonObject& root)
    {
      JsonObject top = root.createNestedObject("exampleUsermod");
      top["great"] = userVar0; //save these vars persistently whenever settings are saved
      top["testBool"] = testBool;
      top["testInt"] = testInt;
      top["testLong"] = testLong;
      top["testULong"] = testULong;
      top["testFloat"] = testFloat;
      top["testString"] = testString;
      JsonArray pinArray = top.createNestedArray("pin");
      pinArray.add(testPins[0]);
      pinArray.add(testPins[1]); 
    }
*/

    /*
     * readFromConfig() can be used to read back the custom settings you added with addToConfig().
     * This is called by WLED when settings are loaded (currently this only happens immediately after boot, or after saving on the Usermod Settings page)
     * 
     * readFromConfig() is called BEFORE setup(). This means you can use your persistent values in setup() (e.g. pin assignments, buffer sizes),
     * but also that if you want to write persistent values to a dynamic buffer, you'd need to allocate it here instead of in setup.
     * If you don't know what that is, don't fret. It most likely doesn't affect your use case :)
     * 
     * Return true in case the config values returned from Usermod Settings were complete, or false if you'd like WLED to save your defaults to disk (so any missing values are editable in Usermod Settings)
     * 
     * getJsonValue() returns false if the value is missing, or copies the value into the variable provided and returns true if the value is present
     * The configComplete variable is true only if the "exampleUsermod" object and all values are present.  If any values are missing, WLED will know to call addToConfig() to save them
     * 
     * This function is guaranteed to be called on boot, but could also be called every time settings are updated
     */
    /*
    bool readFromConfig(JsonObject& root)
    {
      // default settings values could be set here (or below using the 3-argument getJsonValue()) instead of in the class definition or constructor
      // setting them inside readFromConfig() is slightly more robust, handling the rare but plausible use case of single value being missing after boot (e.g. if the cfg.json was manually edited and a value was removed)

      JsonObject top = root["exampleUsermod"];

      bool configComplete = !top.isNull();

      configComplete &= getJsonValue(top["great"], userVar0);
      configComplete &= getJsonValue(top["testBool"], testBool);
      configComplete &= getJsonValue(top["testULong"], testULong);
      configComplete &= getJsonValue(top["testFloat"], testFloat);
      configComplete &= getJsonValue(top["testString"], testString);

      // A 3-argument getJsonValue() assigns the 3rd argument as a default value if the Json value is missing
      configComplete &= getJsonValue(top["testInt"], testInt, 42);  
      configComplete &= getJsonValue(top["testLong"], testLong, -42424242);
      configComplete &= getJsonValue(top["pin"][0], testPins[0], -1);
      configComplete &= getJsonValue(top["pin"][1], testPins[1], -1);

      return configComplete;
    }

   */

    /*
     * getId() allows you to optionally give your V2 usermod an unique ID (please define it in const.h!).
     * This could be used in the future for the system to determine whether your usermod is installed.
     */
    uint16_t getId()
    {
      return USERMOD_ID_MISTER;
    }

   //More methods can be added in the future, this example will then be extended.
   //Your usermod will remain compatible as it does not need to implement all methods from the Usermod base class!
};