/*
  This guy did a good job:
     http://blog.davidsingleton.org/parsing-huge-xml-files-with-go/



*/

///Users/mchirico/weekend/July4
//tfsvr723.AppTmiFxaDmd2_7_B28_2P11-TF.xml.2013-07-02-22

package main

import (
	//	"bufio"
	"compress/gzip"
	"encoding/xml"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"os/signal"
	"regexp"
	"strings"
	"time"

//	"regexp"
//	"net/url"
)

var FILE io.Reader

/*
   -- STANDARD HEADING --
*/
var VERSION string = "0.0.1"
var AUTHORS string = "mchirico@gmail.com"
var SRC string = "mmc/src/go/mainFlag.go"

var version *string = flag.String("v", VERSION, "verson")
var authors *string = flag.String("a", AUTHORS, "authors")
var Usage = func() {
	fmt.Fprintf(os.Stderr, "%s,%s,%s\n", VERSION, SRC, AUTHORS)
	fmt.Fprintf(os.Stderr, "Usage of %:\n", os.Args[0])
	flag.PrintDefaults()
	//Remove this
	fmt.Fprintf(os.Stderr, "\n     tail -f ~/junk.txt|./main\n\n")
}

func init() {
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

type Event struct {
	XMLName   xml.Name `xml:"log4j\:event"`
	Logger    string   `xml:"logger,attr"`
	Timestamp string   `xml:"timestamp,attr"`
	Epoch     string   `xml:"timestampepoch,attr"`
	Level     string   `xml:"level,attr"`
	Thread    string   `xml:"thread,attr"`
}

type Message struct {
	MS string `xml:"message"`
}
type NDC struct {
	Data string `xml:"NDC"`
}

type Page struct {
	Event
	Message
	NDC
}

func ConR(s string) string {
	s = strings.Replace(s, "\"", "_", -1)
	s = strings.Replace(s, "\n", "", -1)
	return s
}

func Con(s string) string {

	s = strings.Replace(s, " ", ",", -1)
	s = strings.Replace(s, "\n", "", -1)
	return s
}

func TimeParse(s string) string {

	//        t, err := time.Parse("02-Jan-06 15:04:05", s)
	t, err := time.Parse("06/01/02 15:04:05", s)
	if err != nil {
		fmt.Println(err)

	}
	const layout = "2006-01-02 15:04:06"
	return t.Format(layout)

}

var reGz = regexp.MustCompile("(?P<heading>.*gz$)")

func gzFile(s string) bool {
	return reGz.MatchString(s)
}

func process(FILE string) {

	//xmlFile, err := os.Open("/Users/mchirico/weekend/July4/tfsvr723.AppTmiFxaDmd2_7_B28_2P11-TF.xml.2013-07-02-22t")
	xmlFile, err := os.Open(FILE)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return
	}
	defer xmlFile.Close()

	var decoder *xml.Decoder
	if gzFile(FILE) {
		reader, err := gzip.NewReader(xmlFile)
		if err != nil {
			fmt.Println("Error opening file:", err)
			return
		}
		decoder = xml.NewDecoder(reader)
	} else {
		decoder = xml.NewDecoder(xmlFile)
	}

	var inElement string
	for {
		t, _ := decoder.Token()
		if t == nil {
			break
		}

		switch se := t.(type) {
		case xml.StartElement:

			inElement = se.Name.Local
			if inElement == "event" {
				var p Page
				decoder.DecodeElement(&p, &se)
				fmt.Printf("%v,%v,%v,\"%v\"\n", TimeParse(p.Timestamp), p.Epoch, Con(p.Data), ConR(p.MS))

			}

		default:
		}

	}

}

func main() {

	FILE = os.Stdin
	flag.Parse()

	//process("/Users/mchirico/weekend/July4/tfsvr723.AppTmiFxaDmd2_7_B28_2P11-TF.xml.2013-07-02-22t.gz")

	for i := 0; i < flag.NArg(); i++ {
		process(flag.Arg(i))
	}

	/*
		// Deal with this later
		//./xmlB.go:191: cannot use FILE (type io.Reader) as type string in function argument
		if flag.NArg() == 0 {
			process(FILE)
	        }
	*/

}
