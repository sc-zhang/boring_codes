package main

import(
  "fmt"
  "math/rand"
  "time"
  "strings"
)


func main(){
  arr := []int{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
  rand.Seed(time.Now().UnixNano())
  rand.Shuffle(len(arr), func(i, j int){
    arr[i], arr[j] = arr[j], arr[i]
  })
  input_map := make(map[byte]int)
  const N int = 10
  curr_cnt := 1
  for {
    if curr_cnt > N{
      break
    }
    fmt.Println("[", curr_cnt, "/", N, "] Input a non-repeat four-digit number:" )
    var input string
    fmt.Scanln(&input)
    if strings.Count(input, "") != 5{
      fmt.Println("Input error, retry")
      continue
    }
    isvalid := true
    input_map = make(map[byte]int)
    for i:=0; i<4; i++{
      if _, ok := input_map[input[i]]; ok{
        input_map[input[i]]++
      }else{
        input_map[input[i]] = 1
      }
      if input_map[input[i]] > 1{
        isvalid = false
        break
      }
    }
    if !isvalid{
      fmt.Println("Repeat Number found, retry")
      continue
    }
    corr_cnt := 0
    semi_corr_cnt := 0
    for i:=0; i<4; i++{
      if(input[i] == byte(arr[i])+'0'){
        corr_cnt++
      }else{
        if _, ok := input_map[byte(arr[i])+'0']; ok{
          semi_corr_cnt++
        }
      }
    }
    if corr_cnt == 4{
      fmt.Println("You win!")
      return
    }else{
      fmt.Printf("%dA%dB\n", corr_cnt, semi_corr_cnt)
    }
    curr_cnt++
  }
  fmt.Println("You lose!")
}
