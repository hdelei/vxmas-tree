const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-BR">
  <title>Mendes Xmas Tree</title>
  <head>
  <link rel="icon" type="image/ico" href="http://ervamatt.com.br/favicon.ico">
  <meta charset="utf-8">
  <script
      src="https://code.jquery.com/jquery-3.2.1.min.js"
      integrity="sha256-hwg4gsxgFZhOsEEamdOYGBf13FyQuiTwlAQgxVSNgt4="
      crossorigin="anonymous">
    </script>
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <style>
    .tree {
      color: green;
      font-size:250px;
    }    
    .on {
      color: #e8d125;
      font-size:100px;
    }
    .off {
      color: #353412;
      font-size:100px;
    }
    body{
    background-color:#171326;
    color:#fffadb;
    font-family: "Lucida Sans Unicode", "Lucida Grande", sans-serif;
    font-size: 50px;
    }
    </style>
  </head>
  <body>
  <p></p><p></p>
    <div style="text-align:center;">
      <span id="star" class="fa fa-star fa-2x off"></span><br>
      <span id="tree" class="fa fa-tree fa-5x tree" onclick="change();"></span><br>
      <span id="text">Clique na árvore</span>
    </div>

    <script>    
    function myRequest(urlRequest){
      $.ajax({
        url: urlRequest,
        success: function(response){
          var tree = JSON.parse(response); 
          console.log(tree);
          if(tree.status.pin_0 == "1"){
            if($("#star").hasClass("off")){
              setOn();
            }            
          }         
        }
      });   
    }
    
    function change(){
      if($('#star').hasClass('off')){         
         setOn();
         myRequest("set?gpio_0=on");
      }
      else{       
        setOff();
        myRequest("set?gpio_0=off");
      }
    }    

    function setOn(){
      $("#star").toggleClass('off on');
      $("#text").text('árvore de Natal ligada');
    }

    function setOff(){
      $("#star").toggleClass('on off');
      $("#text").text('árvore de Natal desligada');
    }
    
    myRequest("status");
         
    </script>    
  </body>
</html>
)=====";
