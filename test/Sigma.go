/* final test*/
const max = 100
var a int = 5
var c int
// main function
func int fact(a int ,b int){
    var ans int =1
    if(b==0){
        ans=1
    }
    else{
        ans=a * fact(a+1,b-1)
    }
    return ans
}
func void main( ) {
    var b int
    for (c=2;c<=3;c=c+1){
        var b int = 1
        b=b+1
        println c
        println b
    }
    b=b+5
    println b
    const d = 4
    if (b<max){
        println fact(2,3)
    }
    else{
        println fact(2,d)
    }
    if (false){
        println fact(2,3)
    }
    else{
        println fact(2,d)
    }
    return 
}
