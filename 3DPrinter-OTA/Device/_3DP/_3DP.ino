#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <SD.h>

//Config host name
const char* host = "printer";

//Config wifi
//const char* ssid      = "NHA TRO HONG HANH";
//const char* password  = "11113333";

const char* ssid      = "Arduino_Coffee_F1";
const char* password  = "78lelai@";

//Config authentication
String username_auth = "admin";
String password_auth = "admin";

//Create server
ESP8266WebServer server(80);

//Static IP
IPAddress ip(192, 168, 1, 200);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet (255, 255, 255, 0);

//Create file 
File myFile;

String login_page     = "<html> <head> <meta charset='UTF-8'> <title>3D Printer Login</title> <link rel='stylesheet prefetch' href='http://netdna.bootstrapcdn.com/bootstrap/3.0.2/css/bootstrap.min.css'> <style>body{background: #eee !important;}.wrapper{margin-top: 80px; margin-bottom: 80px;}.form-signin{max-width: 380px; padding: 15px 35px 45px; margin: 0 auto; background-color: #fff; border: 1px solid rgba(0, 0, 0, 0.1);}.form-signin .form-signin-heading, .form-signin{margin-bottom: 30px;}.form-signin{font-weight: normal;}.form-signin .form-control{position: relative; font-size: 16px; height: auto; padding: 10px; -webkit-box-sizing: border-box; -moz-box-sizing: border-box; box-sizing: border-box;}.form-signin .form-control:focus{z-index: 2;}.form-signin input[type='text']{margin-bottom: -1px; border-bottom-left-radius: 0; border-bottom-right-radius: 0;}.form-signin input[type='password']{margin-bottom: 20px; border-top-left-radius: 0; border-top-right-radius: 0;}</style></head><body> <div class='wrapper'> <form class='form-signin'> <h2 class='form-signin-heading'>Please login</h2> <input type='text' class='form-control' name='USERNAME' placeholder='Username' required='' autofocus=''/> <input type='password' class='form-control' name='PASSWORD' placeholder='Password' required=''/> <input type='submit' class='btn btn-lg btn-primary btn-block' name='LOGIN' value='Login'></form> </form> </div></body></html>";
String dashboard_page = "<html> <head><title>My Printer Dashboard </title> <link rel='stylesheet' type='text/css' href='https://maxcdn.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css'> <script src='https://code.jquery.com/jquery-3.2.1.slim.min.js' integrity='sha256-k2WSCIexGzOj3Euiig+TlR8gA0EmPjuc79OEeY5L45g=' crossorigin='anonymous'> </script> <style>#header{background-color: rgb(0, 91, 110); position: relative; height: 60px; color: white;}.left-item{float: left; margin-top: -5px; margin-left: 20px;}.right-item{float:right; margin-top: 7px; margin-right: 20px; font-size: 40px;}.item-header{margin-right: 20px;}.container{margin-top: 20px; margin-left: 3%; margin-right: 3%; width: 93%; height: 300px; border: 3px solid grey; border-radius: 30px;}.label{margin-left: 30px;}.file-button{width: 50%; font-size: 20px; margin-top: 40px; margin-left: 32%; margin-right: 35%;}.submit-button{width: 150px; height: 50px; margin-top: 30px; margin-left: 42%; margin-right: 35%; border: none; color: white; font-size: 20px; background-color: rgb(0, 91, 110); border-radius: 15px;}.file-button:hover, .submit-button:hover .item-header:hover{cursor: pointer;}.container{display: none;}.right-item-tab{float: right; font-size: 25px;}.content-status{margin-left: 32%; margin-top: 40px;}.reset-button{text-align: center; width: 150px; height: 40px; margin-top: 5%; margin-left: 42%; margin-right: 35%; border: none; color: white; font-size: 28px; background-color: rgb(0, 91, 110); border-radius: 15px;}.content-user{border-radius: 4px; width: 250px; height: 40px; background-color: lightblue; border: 1px solid #555; margin-left: 38%; margin-top: 20px;}.content-sdcard{margin-left: 30%;}#user:hover{cursor: pointer;}.fa-folder-open-o li{display: none;}.clear-history-button{text-align: center; width: 150px; height: 30px; margin-top: 3%; margin-left: 39%; margin-right: 35%; border: none; color: white; font-size: 20px; background-color: rgb(0, 91, 110); border-radius: 15px;}.tabs{list-style-type: none; padding: 0; overflow: hidden;}.tab{display: block; float: left; padding: 10px; font-size: 20px;}.tab.active{position: relative; border: 2px solid rgba(0,0,0,.2); border-bottom: none; border-radius: 4px 4px 0px 0px;}.tab.active::after, .tab.active::before{display: block; content: ''; position: absolute; bottom: 0; height: 0px; width: 999em; border-bottom: 2px solid rgba(0,0,0,.2); pointer-events: none;}.tab.active::before{right: 100%; margin-right: 2px;}.tab.active::after{left: 100%; margin-left: 2px;}a{color: inherit; text-decoration: none;}</style> <script>$(document).ready(function(){$('.container-status').show(); $('.tab').click(function(event){id='#' + event.target.id; $('.tab').removeClass('active'); $(id).addClass('active'); $('.container').hide(); showElement='.container-' + event.target.id; $(showElement).show();}); $('#user').click(function(event){$('.tab').removeClass('active'); $('.container').hide(); $('.container-user').show();});}); </script> </head> <body> <div id='header'> <div class='left-item'> <span class='flaticon-airplane49'></span> <h2> My Printer</h2> </div><div class='right-item'> <i id='user' class='fa fa-user item-header' aria-hidden='true'></i> <i class='fa fa-cog item-header' aria-hidden='true'></i> <a href='/login?DISCONNECT=YES'><i class='fa fa-sign-out item-header' aria-hidden='true'></i></a> </div></div><div id='content'> <ul class='tabs'> <li><a id='status' class='tab active' href='#'>Status</a></li><li><a id='print' class='tab' href='#'>Print</a></li><li><a id='sdcard' class='tab' href='#'>SD Card</a></li><li><a id='other' class='tab' href='#'>Other tab</a></li><li class='right-item-tab'><i class='fa fa-thermometer-empty' aria-hidden='true'></i> 130 &#8451;</li></ul> <div class='container container-status'> <div class='label'> <h3>Status device: </h3> </div><hr> <h3 class='content-status'><i class='fa fa-hourglass-end' aria-hidden='true'></i>&nbsp;&nbsp;Active Hours&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;:&nbsp;130 hours 25 minutes</h3> <h3 class='content-status'><i class='fa fa-hourglass-half' aria-hidden='true'></i>&nbsp;&nbsp;Running Hours &nbsp;: 15 hours 25 minutes</h3> <div class='clear-history-button'><a href='/clearhistory' class='content-other'>Clear History</a> </div></div><div class='container container-print'> <div class='label'> <h3>Choose file for printer:</h3> </div><hr> <form action='/upload' method='POST' enctype='multipart/form-data'> <input class='content-print file-button' type='FILE' value='ABC'> <br><input class='content-print submit-button' type='submit' value='Upload'> </form> </div><div class='container container-sdcard'> <div class='label'> <h3>Sd card files: </h3> </div><hr> <div class='content-sdcard'> <ul> <li><i class='fa fa-folder-open-o' aria-hidden='true'></i> Folder 1</li><ul> <li> <i class='fa fa-file-o' aria-hidden='true'></i> File 1</li><li> <i class='fa fa-file-o' aria-hidden='true'></i> File 2</li><li> <i class='fa fa-file-o' aria-hidden='true'></i> File 3</li><li> <i class='fa fa-file-o' aria-hidden='true'></i> File 4</li><li> <i class='fa fa-file-o' aria-hidden='true'></i> File 5</li></ul> <li><i class='fa fa-folder-o' aria-hidden='true'></i> Folder 2 </li><li><i class='fa fa-folder-o' aria-hidden='true'></i> Folder 3</li><li><i class='fa fa-folder-o' aria-hidden='true'></i> Folder 4</li><li><i class='fa fa-folder-o' aria-hidden='true'></i> Folder 5</li></ul> </div></div><div id='other' class='container container-other'> <div class='label'> <h3>Other: </h3> </div><hr> <div class='reset-button'><a href='/reset' class='content-other'>Reset</a> </div></div><div id='other' class='container container-user'> <div class='label'> <h3>Change user account: </h3> </div><hr> <form action='/user' method='POST' enctype='multipart/form-data'> <input class='content-user' type='password' name='PASSWORD' placeholder=' Password'> <br><input class='content-user' type='password' placeholder=' Confirm Password'> <br><input class='submit-button' type='submit' value='Submit'> </form> </div></div></body></html>";
void setup() {
  Serial.begin(115200);
  initWebServer();
//  initSDCard();
  initmDNS();
}

void loop() {
  loopWebServer();
}
