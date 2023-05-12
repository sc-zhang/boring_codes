package main

import (
	"fmt"
	"os"
	"strconv"
)

func hanoi(n int, from, mid, to byte) {
	if n == 1 {
		fmt.Printf("move %c -> %c\n", from, to)
		return
	}
	hanoi(n-1, from, to, mid)
	hanoi(1, from, mid, to)
	hanoi(n-1, mid, from, to)
}

func main() {
	num := len(os.Args)
	if num < 2 {
		fmt.Println("usage: hanoi <number>")
	} else {
		n, _ := strconv.Atoi(os.Args[1])
		hanoi(n, 'A', 'B', 'C')
	}
}
