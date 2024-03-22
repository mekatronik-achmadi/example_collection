package main

import "fmt"

func msg(strMsg string){
    fmt.Println(strMsg)
}

func main() {
    var msgStr string
    msgStr = "GoLang Template"

    msg(msgStr)
}

