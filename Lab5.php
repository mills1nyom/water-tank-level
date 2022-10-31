<?php


$servername="localhost";
$username="root";
$password="";    
$dbname="iot_midsem";
$WaterLevel=$_GET['WaterLevel'];
$tankID = $_GET['tankID'];
$con = mysqli_connect($servername,$username,$password,$dbname);


$sql = "INSERT INTO tanks (WaterLevel,tankID) VALUES ('{$WaterLevel}','{$tankID}')";


if (mysqli_query($con, $sql)){
echo "New record created successfully";
}
else{
    echo "Failed";
}

?>

