const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <title>Live Weather Station Dashboard</title>
    <link
      rel="shortcut icon"
      href="https://img-premium.flaticon.com/png/512/578/578116.png?token=exp=1621482257~hmac=a8f569a485470791b585e0aaf7fdb3bf"
      type="image/png"
    />
    <link
      rel="stylesheet"
      href="https://use.fontawesome.com/releases/v5.15.3/css/all.css"
    />
  </head>
  <style>
    @import url(https://fonts.googleapis.com/css?family=Inter);
    * {
      margin: 0;
      padding: 0;
    }

    body {
      background: #544947;
      font-family: Inter, Arial, sans-serif;
    }

    h2 {
      font-size: 14px;
    }

    .widget {
      box-shadow: 0 40px 10px 5px rgba(0, 0, 0, 0.4);
      margin: 100px auto;
      height: 330px;
      position: relative;
      width: 500px;
    }

    .upper {
      border-radius: 5px 5px 0 0;
      background: #f5f5f5;
      height: 200px;
      padding: 20px;
    }

    .date {
      font-size: 40px;
    }

    .year {
      font-size: 30px;
      color: #c1c1c1;
    }

    .place {
      color: #222;
      font-size: 40px;
    }

    .lower {
      background: #00a8a9;
      border-radius: 0 0 5px 5px;
      font-family: "Inter";
      font-weight: 200;
      height: 130px;
      width: 100%;
    }

    .clock {
      background: #00a8a9;
      border-radius: 100%;
      box-shadow: 0 0 0 15px #f5f5f5, 0 10px 10px 5px rgba(0, 0, 0, 0.3);
      height: 150px;
      position: absolute;
      right: 25px;
      top: -35px;
      width: 150px;
    }

    .hour {
      background: #f5f5f5;
      height: 50px;
      left: 50%;
      position: absolute;
      top: 25px;
      width: 4px;
    }

    .min {
      background: #f5f5f5;
      height: 65px;
      left: 50%;
      position: absolute;
      top: 10px;
      transform: rotate(100deg);
      width: 4px;
    }

    .min,
    .hour {
      border-radius: 5px;
      transform-origin: bottom center;
      transition: all 0.5s linear;
    }

    .infos {
      list-style: none;
    }

    .info {
      color: #fff;
      float: left;
      height: 100%;
      padding-top: 10px;
      text-align: center;
      width: 25%;
    }

    .info span {
      display: inline-block;
      font-size: 35px;
      margin-top: 20px;
    }

    .anim {
      animation: fade 0.8s linear;
    }

    @keyframes fade {
      0% {
        opacity: 0;
      }
      100% {
        opacity: 1;
      }
    }

    a {
      text-align: center;
      text-decoration: none;
      color: white;
      font-size: 15px;
      font-weight: 500;
    }
  </style>
  <body>
    <div class="widget">
      <div class="clock">
        <div class="min" id="min"></div>
        <div class="hour" id="hour"></div>
      </div>
      <div class="upper">
        <div class="date" id="date">Month 00, 0000</div>
        <div class="year">
          <i class="fas fa-thermometer-three-quarters"></i> Temperature
        </div>
        <div class="place update" id="temp">0 &deg;C</div>
      </div>
      <div style="text-align: center">
        <a href="https://rezarinaldi.github.io/">Reza Rinaldi</a>
      </div>
      <div class="lower">
        <ul class="infos">
          <li class="info weather">
            <h2 class="title"><i class="fas fa-wind"></i> PRESSURE (mb)</h2>
            <span class="update" id="pressuremb">0 mb</span>
          </li>
          <li class="info weather">
            <h2 class="title"><i class="fas fa-wind"></i> PRESSURE (hg)</h2>
            <span class="update" id="pressurehg">0 hg</span>
          </li>
          <li class="info wind">
            <h2 class="title"><i class="fas fa-cloud-rain"></i> RAIN</h2>
            <span class="update" id="rain">0</span>
          </li>
          <li class="info humidity">
            <h2 class="title"><i class="fas fa-tint"></i> HUMIDITY</h2>
            <span class="update" id="humidity">0%</span>
          </li>
        </ul>
      </div>
    </div>

    <script>
      setInterval(drawClock, 2000);

      function drawClock() {
        var now = new Date();
        var hour = now.getHours();
        var minute = now.getMinutes();
        var second = now.getSeconds();

        //Date
        var options = { year: "numeric", month: "long", day: "numeric" };
        var today = new Date();
        document.getElementById("date").innerHTML = today.toLocaleDateString(
          "en-US",
          options
        );

        //hour
        var hourAngle = 360 * (hour / 12) + (360 / 12) * (minute / 60);
        var minAngle = 360 * (minute / 60);
        document.getElementById("hour").style.transform =
          "rotate(" + hourAngle + "deg)";
        //minute
        document.getElementById("min").style.transform =
          "rotate(" + minAngle + "deg)";

        //Get Humidity Temperature and Rain Data
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            var txt = this.responseText;
            var obj = JSON.parse(txt); //Ref: https://www.w3schools.com/js/js_json_parse.asp
            document.getElementById("rain").innerHTML = obj.Rain;
            document.getElementById("temp").innerHTML =
              Math.round(obj.Temperature) + "&deg;C";
            document.getElementById("humidity").innerHTML =
              Math.round(obj.Humidity) + "%";
            document.getElementById("pressuremb").innerHTML =
              Math.round(obj.Pressuremb) + " mb";
            document.getElementById("pressurehg").innerHTML =
              Math.round(obj.Pressurehg) + " hg";
          }
        };
        xhttp.open("GET", "readADC", true); //Handle readADC server on ESP8266
        xhttp.send();
      }
    </script>
  </body>
</html>
)=====";
