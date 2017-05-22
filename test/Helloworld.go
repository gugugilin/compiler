/*
 * Example with Functions
 */

// variables
var a int = 5
//a=5
var c int

// function declaration
func int add(b int) {
  a=a+b
}

// main function
func int main() {
  c = add(a, 10)
  if (c > 10) {
    print -c
  }
  else {
    print c
  }
  println "Hello World"
}
