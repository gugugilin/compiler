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
        var n int =1
        for(n=1;n<3;n=n+1){
            println n
        }
        println "======="
        if(c>2){
            println "test"
        }else{
            println "test2"
        }
    }
    b=b+5
    println "======="
    println b
    const d = 4
    if (b<max){
        var nn int
        for(nn=1;nn<2;nn=nn+1){
            println fact(2,3)
        }
        if(nn==2){
            println nn
        }
    }
    else{
        println fact(2,d)
    }
    println "======="
    if (false){
        println fact(2,3)
    }
    else{
        println fact(2,d)
    }
    var n int =1
    for(n=1;n<3;n=n+1){
        println n
    }
    return 
}
