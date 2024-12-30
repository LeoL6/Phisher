#pragma once

#include <DNSServer.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h> 
#include <WebSocketsServer.h>
#include <esp_wifi.h>

#include "global.h"

// WI-FI SETTINGS
const char *ssid = "Free Wifi";
const int http_port = 80;
const int max_clients = 4;
const int wifi_channel = 6;

// WEBSOCKET SETTINGS
const int ws_port = 1337;

// ADMIN PAGE
const char *auser = "admin";
const char *apass = "password";

// AP CONSTANTS
const IPAddress localIP(192, 168, 4, 1);
const IPAddress subnetMask(255, 255, 255, 0);

const String localIPURL = "http://192.168.4.1";

const char ADMIN_PAGE[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en" class="js-focus-visible">

<title>Admin</title>

  <style>
    table {
      position: relative;
      width:100%;
      border-spacing: 0px;
    }
    tr {
      border: 1px solid white;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
    }
    th {
      height: 20px;
      padding: 3px 15px;
      background-color: #343a40;
      color: #FFFFFF !important;
      }
    td {
      height: 20px;
       padding: 3px 15px;
    }
    .bodytext {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 24px;
      text-align: left;
      font-weight: light;
      border-radius: 5px;
      display:inline;
    }
    .navbar {
      width: 100%;
      height: 50px;
      margin: 0;
      padding: 10px 0px;
      background-color: #FFF;
      color: #000000;
      border-bottom: 5px solid #293578;
    }
    .fixed-top {
      position: fixed;
      top: 0;
      right: 0;
      left: 0;
      z-index: 1030;
    }
    .navtitle {
      float: left;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 50px;
      font-weight: bold;
      line-height: 50px;
      padding-left: 20px;
    }
   .navheading {
     position: fixed;
     left: 60%;
     height: 50px;
     font-family: "Verdana", "Arial", sans-serif;
     font-size: 20px;
     font-weight: bold;
     line-height: 20px;
     padding-right: 20px;
   }
   .navdata {
      justify-content: flex-end;
      position: fixed;
      left: 70%;
      height: 50px;
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      font-weight: bold;
      line-height: 20px;
      padding-right: 20px;
   }
    .category {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: bold;
      font-size: 32px;
      line-height: 50px;
      padding: 20px 10px 0px 10px;
      color: #000000;
    }
    .heading {
      font-family: "Verdana", "Arial", sans-serif;
      font-weight: normal;
      font-size: 28px;
      text-align: left;
    }
  
  	.textbox {
     height: 30px;
    }
    
    #btn0 {
      background-color: #f50a0a;
      color: white;
    }
    .btn {
      background-color: #444444;
      border: none;
      color: white;
      padding: 10px 20px;
      text-align: center;
      text-decoration: none;
      display: inline-block;
      font-size: 16px;
      margin: 4px 2px;
      cursor: pointer;
    }
    .foot {
      font-family: "Verdana", "Arial", sans-serif;
      font-size: 20px;
      position: relative;
      height:   30px;
      text-align: center;   
      color: #AAAAAA;
      line-height: 20px;
    }
    .container {
      max-width: 1800px;
      margin: 0 auto;
    }
    table tr:first-child th:first-child {
      border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
      border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
      border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
      border-bottom-right-radius: 5px;
    }
    
  </style>

  <body style="background-color: #efefef" onload="process()">
  
    <header>
      <div class="navbar fixed-top">
          <div class="container">
            <div class="navtitle">Control Panel</div>
            <div class="navdata" id = "date">mm/dd/yyyy</div>
            <div class="navheading">DATE</div><br>
            <div class="navdata" id = "time">00:00:00</div>
            <div class="navheading">TIME</div>
            
          </div>
      </div>
    </header>
  
    <main class="container" style="margin-top:70px">
      <div class="category">Credentials</div>
      <br>
      <div style="border-radius: 10px !important;">
      <table style="width:50%" id="cred-table">
        <colgroup>
          <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
          <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
          <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
        </colgroup>
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <tr>
          <th colspan="1"><div class="heading">#</div></th>
          <th colspan="1"><div class="heading">Email</div></th>
          <th colspan="1"><div class="heading">Password</div></th>
        </tr>
        <tr>
          <td>0</td>
          <td>cminer@gmail.com</td>
          <td>idk123$</td>
        </tr>
      </table>
    </div>
    <br>
    <div class="category">Controls</div>
    <br>
    <div class="bodytext">Change SSID </div>
    	<input type="text" class="textbox" name="username" value="" minlength="1" maxlength="32" size="20">
    	<button type="button" class = "btn" id = "btn1" onclick="ButtonPress0()">Restart</button>
    </div>
    <br>
    <br>
    <button type="button" class = "btn" id = "btn0" onclick="ButtonPress1()">Shutdown</button>
    <br>
  </main>
  </body>


  <script language="javascript" type="text/javascript">
  


    function ButtonPress0() {
    
    }

    function ButtonPress1() {
      insertCreds("User", "Password123$");
    }

	function insertCreds(username, password){
      var parenttbl = document.getElementById("cred-table");
      var newel = document.createElement('tr');
      
      var elementid = document.getElementsByTagName("tr").length
      
      var indexTd = document.createElement('td');
      var userTd = document.createElement('td');
      var passTd = document.createElement('td');
      
      indexTd.innerHTML = (elementid - 1)
      userTd.innerHTML = username
      passTd.innerHTML = password
      
      parenttbl.appendChild(newel);
      
      newel.appendChild(indexTd);
      newel.appendChild(userTd);
      newel.appendChild(passTd);
    }
  </script>

</html>
  
)=====";
