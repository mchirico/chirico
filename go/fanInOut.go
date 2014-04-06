package main

import (
	"fmt"
	"sync"

)



func gen(done <-chan struct{}, nums ...int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for _, n := range nums {
			select {
			case out <- n:
			case <-done:
				return
			}
		}
	}()
	return out
}

func sq(done <-chan struct{}, in <-chan int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for n := range in {
			select {
			case out <- n * n:
			case <-done:
				return
			}
		}
	}()
	return out
}

func merge(done <-chan struct{}, cs ...<-chan int) <-chan int {
	var wg sync.WaitGroup
	out := make(chan int)

	// Start an output goroutine for each input channel in cs.  output
	// copies values from c to out until c is closed or it receives a value
	// from done, then output calls wg.Done.
	output := func(c <-chan int) {
		defer wg.Done()
		for n := range c {
			select {
			case out <- n:
			case <-done:
				return
			}
		}

	}

	wg.Add(len(cs))
	for _, c := range cs {
		go output(c)
	}

	// Start a goroutine to close out once all the output goroutines are
	// done.  This must start after the wg.Add call.
	go func() {
		wg.Wait()
		close(out)
	}()
	return out
}

func main() {

	done := make(chan struct{})
	defer close(done)

//	in := gen(done, 2, 3, 5, 9)
//	nums :=[]int{1, 2, 3, 4,5,6}
	in := gen(done,[]int{1, 2, 3, 4,5,6}...)
	c1 := sq(done, in)
	c2 := sq(done, in)
	c3 := sq(done, in) // You could have a lot more channels. See below.


	out := merge(done, c1, c2, c3)
	for n :=range out	{
		fmt.Println(n) // 4 or 9
	}



// 2nd way of doing this

	fmt.Println("\n2nd way\n")
	done2 := make(chan struct{})
	defer close(done2)


// Generator that leverages append in prep stage to easly add 
// more numbers.
	nums := make([]int, 3)
	for i:= range nums {
		nums[i]=i+10
	}
	nums = append(nums,7,8)  // Easy way to add more

//	in2 := gen(done2,[]int{1, 2, 3, 4,5,6}...)
	in2 := gen(done2,nums...)

	all := make([]<-chan int, 20)  // Could add more or less here.

//	all:=[]<-chan int{sq(done2,in2),sq(done,in2),sq(done,in2)}
	for i:= range all {
		all[i]=sq(done2,in2)
	}

	out2 := merge(done2,all...)
	for n :=range out2	{
		fmt.Println(n) 
	}


}
