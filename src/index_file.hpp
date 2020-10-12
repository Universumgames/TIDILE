#pragma once

#pragma region UIkeywords
#define COLORHOURKEYWORD "{{colorHourKeyword}}"
#define COLORMINUTEKEYWORD "{{colorMinuteKeyword}}"
#define COLORSECONDSKEYWORD "{{colorSecondKeyword}}"
#define DIMMSECONDSKEYWORD "{{dimmSecondsKeyword}}"
#define BRIGHTNESSKEYWORD "{{brightnessKeyword}}"
#define COLORTEMPERATUREKEYWORD "{{colorTemperatureKeyword}}"
#define COLORPRESSUREKEYWORD "{{colorPressureKeyword}}"
#define SHOWSECONDSKEYWORD "{{secondsEnabledKeyword}}"
#define NIGHTTIMESTARTKEYWORD "{{nighttimeStartKeyword}}"
#define NIGHTTIMEENDKEYWORD "{{nighttimeEndKeyword}}"
#define NIGHTTIMEENABLEDKEYWORD "{{nightTimeEnabledKeyword}}"
#define INFLUENCEKEYWORD "{{envLightInfluence}}"
#define CURRENTTIMEKEYWORD "{{currentTimeKeyword}}"
#pragma endregion

const char index_html[] = R"rawliteral(
<html>
<head>
  <title>TIDILE Interface</title>
  <meta charset="UTF-8">
</head>
<style>
  * {
    font-family: 'Calibri', sans-serif;
    color: white;
  }
  body {
    background-color: black;
    text-align: center;
  }
  form {
    display: grid;
    grid-template-columns: 1fr 1fr;
    gap: 0.7rem;
    margin: auto;
    width: 60rem;
    text-align: left;
  }
  input {
    outline: none;
    border: none;
    background-color: orangered;
    border-radius: 3px;
    font-size: 1.5rem;
  }
  .submit {
    grid-column: 1 / 3;
    justify-self: center;
  }
  h3, h2, h1 {
    text-decoration: underline;
    align-self: center;
  }
  .clock {
    margin: 2rem auto 1rem auto;
    width: 60rem;
    display: block;
  }
  .minutes {
    padding: 0.5rem;
    background-color: {{colorMinuteKeyword}};
    border-radius: 5px;
    filter: blur(5px);
    width: calc(100% * ({{minutesKeyword}}/60));
  }
  .hour {
    padding: 0.5rem;
    background-color: {{colorHourKeyword}};
    border-radius: 5px;
    filter: blur(5px);
    width: 1%;
    margin-left: calc(100% * ({{hoursKeyword}}/60));
    margin-top: -1rem;
  }
  .spacer {
    width: 10%;
  }
  .seconds {
    padding: 0.5rem;
    background-color: {{colorSecondsKeyword}}
    border-radius: 5px;
    filter: blur(7px);
    width: 1%;
    margin-top: -1rem;
    margin-left: calc(100% * ({{secondsKeyword}}/60));
  }
</style>
<body>
  <h1>TIDILE Interface</h1>
  <div>Current Time (d/m/y): {{currentTimeKeyword}}</div>
  <div class="clock">
      <div class="minutes"></div>
      <div class="hour"></div>
      <div class="seconds"></div>
  </div>
  <h3>Night Time</h3>
  <form action="/time">
    <label>Enable Night Time<small>Info: Between both times should be 12pm</small></label>
    <input type="checkbox" name="time_enabled" {{nightTimeEnabledKeyword}}>
    <label for="timeB">Begin of Night Time at</label>
    <div>
      <input id="timeB" type="time" name="begin_time" value="{{nighttimeStartKeyword}}" width="auto">
      <small>Enter the time when the clock should start to turn off if it´s dark in the room</small>
    </div>
    <label for="timeE">End of Night Time at</label>
    <div>
      <input id="timeE" type="time" name="end_time" value="{{nighttimeEndKeyword}}" width="auto">
      <small>Enter the time when the clock should stop to turn off if it´s dark in the room</small>
    </div>
  <input type="submit" class="submit" value="Set Night Time">
  </form>
  <h3>Colors for Time</h3>
  <form action="/colors">
    <label for="cl_h">Hours</label>
    <input id="cl_h" type="color" name="color_hour" value="{{colorHourKeyword}}">
    <label for="cl_m">Minutes</label>
    <input id="cl_m" type="color" name="color_min" value="{{colorMinuteKeyword}}" width="auto">
    <label id="dimm_label" for="cl_s">Seconds</label>
    <input id="cl_s" type="color" name="color_sec" value="{{colorSecondKeyword}}" width="auto">
    <label for="dim_sec">Dimm Seconds instead of using different color</label>
    <input id="dim_sec" type="checkbox" name="dimm_seconds" {{dimmSecondsKeyword}} onchange="onDimmSecondsChange()">
    <input type="submit" class="submit" value="Set Color">
  </form>
  <script>
    function onDimmSecondsChange(){
      var checked = document.getElementById("dim_sec").checked;
      var colorSelector = document.getElementById("cl_s");
      var dimmLabel = document.getElementById("dimm_label");
      if(checked){ 
        colorSelector.style.visibility = "hidden";
        dimmLabel.style.visibility = "hidden";
      }else{
        colorSelector.style.visibility = "visible";
        dimmLabel.style.visibility = "visible";
      }
    };
    onDimmSecondsChange();
  </script>
  <h3>Blinking & Brightness</h3>
  <form action="/blink">
    <label>Show Seconds</label>
    <input type="checkbox" name="show_seconds" {{secondsEnabledKeyword}}>
    <lable for="bright">Brightness</lable>
    <div>
      <input id="bright" type="number" name="brightness" min="0" max="255" value="{{brightnessKeyword}}">
      <br>
      <small>Enter a value between 0 and 255 to set the LED brightness (Caution: Higher brightness results in a higher energy consumption. e.g. with 144 LEDS in use and the brightness set to 200 the power consumption is around 2 amps</small>
    </div>
    <label>Enviroment Light Influence</label>
    <input id="influence" type="number" name="influence" min="0" max="100" value="{{envLightInfluence}}">
    <input type="submit" class="submit" value="Set Blinking & Brightness">
  </form>
  <!--- env begin --->
  <h3>Enviroment Colors</h3>
  <form action="/envcolors">
    <label>Temperature</label>
    <input type="color" name="color_temp" value="{{colorTemperatureKeyword}}">
    <label>Pressure</label>
    <input type="color" name="color_press" value="{{colorPressureKeyword}}">
    <input type="submit" class="submit" value="Set Colors">
  </form>
  <!--- env end --->
</body>
</html>
)rawliteral";
