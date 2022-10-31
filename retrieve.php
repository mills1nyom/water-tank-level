<?php
$con = mysqli_connect("localhost","root","","iotmidsem");
$rows = mysqli_query($con, "SELECT *  FROM tanks");
?>

<table>
    <tr>
        <td>Tank</td>
        <td>Water Level</td>
    </tr>

    <tr>
        <td>
            <?php
            echo $row

            ?>
        </td>
    </tr>


</table>