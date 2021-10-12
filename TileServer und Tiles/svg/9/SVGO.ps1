$MaxFirst=111;
$MaxSecond=79;
$fisrt=0
$second=0
while ($fisrt -le $MaxFirst){
    while ($second -le $MaxSecond){
        $name ="$fisrt" + "_"+ "$second" + ".svg"
        svgo "$name"
        $second= $second +1
    }
    $second=0
    $fisrt=$fisrt+1
}