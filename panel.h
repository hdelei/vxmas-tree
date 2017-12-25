const char PANEL_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">
  <title>Mendes Xmas Tree Panel</title>
  <head>  
  <meta charset="utf-8">
  <script
      src="https://code.jquery.com/jquery-3.2.1.min.js"
      integrity="sha256-hwg4gsxgFZhOsEEamdOYGBf13FyQuiTwlAQgxVSNgt4="
      crossorigin="anonymous">
    </script>  
    <style>    
    body{
    background-color:#171326;
    color:#fffadb;
    font-family: "Lucida Sans Unicode", "Lucida Grande", sans-serif;
    font-size: 20px;
    }
    </style>
  </head>
  <body>
  <p></p><p></p>  
  <h1>WIFI Manager Panel</h1>
  <hr>
  <form action="/setwifi" method="post">
  SSID:
  <input type="text" name="ssid">
  <br><br>
  Password:
  <input type="password" name="pass">
  <br><br>
  <input type="submit" value="Connect">
</form>
    
  </body>
</html>
)=====";
