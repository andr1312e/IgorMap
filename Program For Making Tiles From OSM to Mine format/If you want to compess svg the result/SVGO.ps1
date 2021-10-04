$destinationPath="E:/MAP/"
$MaxFirst=27;
$MaxSecond=19;
$fisrt=0
$second=0
while ($fisrt -le $MaxFirst){
    while ($second -le $MaxSecond){
        $name ="$fisrt" + "_"+ "$second" + ".svg"
        $saveName="$destinationPath"+"$fisrt" + "_"+ "$second" + ".svg"
        Write-Output $saveName;
        svgo "$name" -o "&saveName"
        $second= $second +1
    }
    $second=0
    $fisrt=$fisrt+1
}