/*
   Example:
     tail -f ~/junk.txt|./main

*/
package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"os/signal"
	"strings"

//	"time"
)

var FILE io.Reader

type chanT uint64 // Counting lines read. So make big.

/*
   -- STANDARD HEADING --
*/
var VERSION string = "0.0.1"
var AUTHORS string = "mchirico@gmail.com"
var SRC string = "mmc/src/go/main.go"

var debug bool
var version bool
var DEBUG bool = false



var Usage = func() {
	fmt.Fprintf(os.Stderr, "%s,%s,%s\n", VERSION, SRC, AUTHORS)
	fmt.Fprintf(os.Stderr, "Usage of %s:\n", os.Args[0])
	flag.PrintDefaults()
	//Remove this
	fmt.Fprintf(os.Stderr, "\n     tail -f ~/junk.txt|./main\n\n")
}
func versionTxt() {
	s := `

`
	if version {
		fmt.Fprintf(os.Stderr, "VERSION: %s, AUTHORS: %s, SRC: %s\n%s\n", VERSION, AUTHORS, SRC, s)
		os.Exit(0)
	}

}
func init() {
	const (
		defaultDebug   = false
		debugText      = " turns on/off debugging. Normally just use -d with not arguments to turn on."
		defaultVersion = false
		versionText    = " version information.  -v to show the version and exit. "
	)

	flag.BoolVar(&debug, "d", defaultDebug, debugText+" ")
	flag.BoolVar(&version, "v", false, versionText+" ")
	flag.Usage = Usage

}

/*
   -- END STANDARD HEADING --
*/

func setupSignal(d chan int) {
	c := make(chan os.Signal, 1)
	signal.Notify(c, os.Interrupt)
	go func() {
		for sig := range c {
			log.Printf("\nCaptured signal %v\n", sig)
			d <- 0
			//os.Exit(1)
		}
	}()

}

func Open(name string) (file *os.File, err error) {
	file, err = os.OpenFile(name, os.O_RDONLY, 0)
	if err != nil {
		panic(err)
	}
	return file, err
}

func read(f chan io.Reader, c chan string, d chan chanT) {
	var count chanT
	reader := bufio.NewReader(<-f)
	for {
		line, err := reader.ReadString('\n')
		//line,_, err := reader.ReadLine()  //line would have to be type []byte
		if err != nil {
			d <- count
			break
		}
		c <- line
		count++

	}
}

func sliceExamp() {
	amount := []float64{1.0, 3, 28.3}
	for m, i := range amount {
		fmt.Printf("m=%d,i=%f\n", m, i)
	}

}

/*
  Example print filter.
*/
func pr(c chan string, d chan chanT) {
	var count chanT
	for {
		line := <-c
		s := strings.SplitAfter(line, ",")
		if len(s) == 3 {
			server := s[0][0 : len(s[0])-1]
			alias := s[1][0 : len(s[1])-1]
			cpu := s[2][0 : len(s[2])-1]
			if alias != "nil" {
				fmt.Printf("server:%v,alias:%v,cpu:%v\n", server, alias, cpu)
			}
		}
		count++
		d <- count
	}
}

/*
   This will wait until everything is processed.
*/
func wait(d0 chan chanT, d1 chan chanT, sig chan int, nargs int) {
	var td0 chanT
	var td1 chanT
        var i int
	log.Printf("nargs = %v\n",nargs)
	for {
		select {
		case <-sig:
			fmt.Printf("Yikes. Hit sig chan. Will exit\n")
			os.Exit(2)
		case td0 = <-d0:
		case td1 = <-d1:
			// Ready to exit. But still need td0 to match td1
                        // We finished a read here
                        i++
		}
		if (td1 > 0) && (td1 == td0) && (i == nargs)  {
			log.Printf("i=%v,nargs=%v  td1=%v,td0=%v\n",i,nargs,td1,td0)
			return
		}

	}

}

func main() {
	FILE = os.Stdin
	flag.Parse()
	versionTxt()
	sigChan := make(chan int, 0)

	d0 := make(chan chanT, 0)
	d1 := make(chan chanT, 0)
	c := make(chan string, 30)
	f := make(chan io.Reader, 5)

	setupSignal(sigChan)

	go pr(c, d0)

	// As soon as you introduce more than one file, your output
	// will get mixed up. How do you fix that?
	for i := 0; i < flag.NArg(); i++ {
		FILE, _ = Open(flag.Arg(i))
		f <- FILE
		go read(f, c, d1)

	}
		

	if flag.NArg() == 0 {
		f <- FILE
		go read(f, c, d1)
	}

	wait(d0, d1, sigChan, flag.NArg())


}
