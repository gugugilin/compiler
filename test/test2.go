var a0[5] int
var a1[5] string
var a2[5] bool
var a6 string = "S6"
var b0 int = 3
var b1 real = 3.3
var b2 string = "S3"
const c0 = "test"
const c1 = 1
const c2 = c1
const c3 = 2
//c0=5 //to test the const assigment
//a0[3]=c0 //test the type is error
//a0[5]=1 //test outside the func can't use the statement


func int lala(){
    var a4 real = (3.0+3.6+7.8)*2/4
    //var a5 real = (3+3.6+7.8)*2/0  //test the mod zero
    a0[3]=c2//test assigment
    a1[3]=c0
    //b0=a0[5]
    b1=3+3.3
    b2=c0
}
func string lala2(a5 int,a4 int,a2 int,a98 int,a99 int){
    a0[4]=c2//check can see the const 
    var a6 int = 5//redefine a6 to test m1=a6 
    //var a2 real =3.5 //this will error by a2 int(redefine)
    //a2=a4
    //a6=a2// if you catch the goble a2 than it is error
}

func void main(){
    {
        var a6 bool = !(false&true)//redefine a6 to test m1=a6 
        //var main bool = true
        var a7 bool = !(c2>b0|c2>b0)
        a6=a2[0]
    }
    var m1 string =c0//trace you can assigment the const Var
    m1=a6// trace you can assces var a6 string = "S6"
    a6=lala2(1,2,3,4,5)//return the func
    go lala2(1,2,3,4,5)
    //a6 = go lala() //no return
    var test int = 4
    //a0=0 //a0 is a array can't assigment a int
    for(a0[3]=0;b0>2;b0=b0+1){
        var test int = 5//test the for and scope
        b0=c2//check the value or type is change by b0=a0[5]
    }
    if (c2>b0){
        print test
        a0[0]=test
        println a0[0]+3.5
    }
    
}
