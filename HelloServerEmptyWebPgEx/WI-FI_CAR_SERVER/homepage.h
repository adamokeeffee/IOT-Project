// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en" > <!-- Needed for Screenreaders !-->
<head>
<!-- UTF-8 character set covers most characters in the world -->
  <meta charset="utf-8">
  <!-- Make page respond to screen size !-->
  <meta name="viewport" content="width=device-width, initial-scale=1, viewport-fit=cover">
 
<!--Include a Title. Used by Search Engines -->
<title> WI-FI Car Server </title>
<style>
   
   <!--choose good contrast between background and foreground colours -->
   body {       
	background-color: Red;
	}
	.flex-Container{
        display: flex;
        flex-direction: column;
        background-color: Red;
        align-items: center;
      }
    h1{
    font: bold;
    font-size: 40px;
    font-family: Arial;
    color: navy;
	text-align: center;
  }
  p{
    font-size: 25px;
    font-family: Arial;
    color: navy;
	text-align: center;
   }  
  th, td {
    font-size: 25px;
    padding: 8px;
    text-align: left;
    border-bottom: 1px solid #ddd;
}
</style>
</head><body>
<div class="flex-Container">
<h1> WI-FI CAR WEBSITE </h1>

<iframe width="560" height="315" src ="http://192.168.249.227/" frameborder="0" alt ="camera stream" allowfullscreen
></iframe>
 
<p>WI-FI Car controlls</p>
 
<table>
 <tr>
 <th>forward</th>
 <th>back</th>
 <th>left</th>
 <th>right</th>
 </tr>
 <tr>
 <td></td>
 )=====");
String homePagePart2 = F(R"=====(<td>STOP</td>
 <td></td>
 </tr>
 </table>
 </div>
</body>
</html>)=====");
