/*
  This guy did a good job:
     http://blog.davidsingleton.org/parsing-huge-xml-files-with-go/

    go build xmlgarmin2.go && ./xmlgarmin2


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
	"math"
	"os"
	"os/signal"
	"regexp"
	"strings"
	"time"
	"strconv"

//	"regexp"
//	"net/url"
)

var FILE io.Reader

/*
   -- STANDARD HEADING --
*/
var VERSION string = "0.0.1"
var AUTHORS string = "mchirico@gmail.com"
var SRC string = "mmc/src/go/xmlgarmin.go"
var M_FILES string = "no"
var L_COL int = 65534

var mfiles *string = flag.String("f", M_FILES, "no")
var collen *int = flag.Int("r", L_COL, "Column max length")
var Usage = func() {
	fmt.Fprintf(os.Stderr, `
   
 Version 0.0.1a
 src: mmc/src/go/xmlappread.go    Author: mchirico@gmail.com

 Usage of xmlappread:

      ./xmlappread tfsvr724.AppTmiFxaDmd3_7_B28_2P11-TF.xml.2013-07-02-22.gz      

          or (It will take a look at the extension)

      ./xmlappread tfsvr724.AppTmiFxaDmd3_7_B28_2P11-TF.xml.2013-07-02-22

         Use the -f yes option to print out file info


      ./xmlappread -f yes tfsvr724.AppTmiFxaDmd3_7_B28_2P11-TF.xml.2013-07-02-22  




 `)

	//	fmt.Fprintf(os.Stderr, "Usage of %s:\n", os.Args[0])
	//	flag.PrintDefaults()

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

var HRzones = []int{118, 125, 130, 135, 142, 146, 150, 153, 156, 161, 163, 165, 167, 174, 195}
var hrZones = make(map[int]int32)

func zoneCalc(dt int32, hr int) {
	hrZones[indexOf(hr)] += dt

}

func clearZones() {

	for i := 0; i < len(hrZones); i++ {
		hrZones[i]=0
	}

}



func prHz() {
	fmt.Printf("Max Heart Rate %d\nInterval :(s)   Time%%         HR%%\n",MaxHR)
	s := "0"
	var total int32
	for i := 0; i < len(hrZones); i++ {
		total += hrZones[i]
	}

	for i := 0; i < len(hrZones); i++ {
		ts := fmt.Sprintf("[%3s-%d):", s, HRzones[i])
		h0,_:=strconv.Atoi(s)
		fmt.Printf("%s%-5d %4.1f%%  %4.1f-%2.1f%%\n", ts, hrZones[i], 
			float32(100*float32(hrZones[i])/float32(total)),float32(h0)/float32(MaxHR)*100,float32(HRzones[i])/float32(MaxHR)*100)
		s = fmt.Sprintf("%d", HRzones[i])

	}

}

func indexOf(i int) int {

	switch {
	case i < HRzones[0]: // 118
		return 0
	case i >= HRzones[0] && i < HRzones[1]: // 125 - <130
		return 1
	case i >= HRzones[1] && i < HRzones[2]: // 130 - <135
		return 2
	case i >= HRzones[2] && i < HRzones[3]: // 135 - <142
		return 3
	case i >= HRzones[3] && i < HRzones[4]: // 142 - <146
		return 4
	case i >= HRzones[4] && i < HRzones[5]: // 146 - <150
		return 5
	case i >= HRzones[5] && i < HRzones[6]: //  150 - <153
		return 6
	case i >= HRzones[6] && i < HRzones[7]:
		return 7
	case i >= HRzones[7] && i < HRzones[8]:
		return 8
	case i >= HRzones[8] && i < HRzones[9]:
		return 9
	case i >= HRzones[9] && i < HRzones[10]:
		return 10
	case i >= HRzones[10] && i < HRzones[11]:
		return 11
	case i >= HRzones[12] && i < HRzones[13]:
		return 12
	case i >= HRzones[13] && i <= (HRzones[14]+10) :  // Anything over maybe equipment failure.
		return 13   
	}

	return 0

}

type Lap struct {
	XMLName xml.Name `xml:"Lap"`
	Ltime   string   `xml:"StartTime,attr"`
	TotTime float32  `xml:"TotalTimeSeconds"`
	Dist    float32  `xml:"DistanceMeters"`
	MaxS    float32  `xml:"MaximumSpeed"`
	Cal     float32  `xml:"Calories"`
	AHr     float32  `xml:"AverageHeartRateBpm>Value"`
	MHr     float32  `xml:"MaximumHeartRateBpm>Value"`
	/*
		TptT    []string  `xml:"Track>Trackpoint>Time"`
		Lat    []float64  `xml:"Track>Trackpoint>Position>LatitudeDegrees"`
		Lon    []float64  `xml:"Track>Trackpoint>Position>LongitudeDegrees"`
		Alt    []float64  `xml:"Track>Trackpoint>AltitudeMeters"`
		DistP    []float64  `xml:"Track>Trackpoint>DistanceMeters"`
		HrT    []float64  `xml:"Track>Trackpoint>HeartRateBpm>Value"`
		Speed    []float64  `xml:"Track>Trackpoint>Extensions>TPX>Speed"`
	*/

}



type Trackpoint struct {
	XMLName xml.Name `xml:"Trackpoint"`
	TptT    string   `xml:"Time"`
	Lat     float64  `xml:"Position>LatitudeDegrees"`
	Lon     float64  `xml:"Position>LongitudeDegrees"`
	Alt     float64  `xml:"AltitudeMeters"`
	DistP   float64  `xml:"DistanceMeters"`
	HrT     int      `xml:"HeartRateBpm>Value"`
	Speed   float64  `xml:"Extensions>TPX>Speed"`
}

type TTrackpoint struct {
	T          time.Time
	Lat        float64
	Lon        float64
	Alt        float64
	DistP      float64
	HrT        int
	Speed      float64
	HrSlope    float64
	SpeedSlope float64
}

type TTT struct {
	T          time.Time
	HrSlope    float64
	idx        int
	SpeedSlope float64
	Trim       float64
	TotTrim    float64
}

func ConR(s string) string {
	s = strings.Replace(s, "\"", "_", -1)
	s = strings.Replace(s, "\n", "", -1)

	if len(s) > *collen {
		return s[0:*collen]
	} else {
		return s
	}
}

func Con(s string) string {

	s = strings.Replace(s, " ", ",", -1)
	s = strings.Replace(s, "\n", "", -1)
	return s
}

func TimeParse(s string) (string, time.Time) {

	//        t, err := time.Parse("02-Jan-06 15:04:05", s)
	//   2013-08-13T15:22:18.000Z
	//t, err := time.Parse("06/07/02 15:04:05", s)
	t, err := time.Parse("2006-01-02T15:04:05.000Z", s)
	if err != nil {
		fmt.Println(err)

	}

	tz := "America/New_York"
	location, _ := time.LoadLocation(tz)
	_, offset := t.In(location).Zone()
	t = t.Add(time.Duration(offset) * time.Second)

	const layout = "2006-01-02 15:04:06"
	return t.Format(layout), t

}

var reGz = regexp.MustCompile("(?P<heading>.*gz$)")

func gzFile(s string) bool {
	return reGz.MatchString(s)
}

func process(FILE string) {

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
	var stp []TTrackpoint

	spcount := 0 // For heading. Quick hack
	heading_s := ""
	for {
		t, _ := decoder.Token()
		if t == nil {
			break
		}

		switch se := t.(type) {
		case xml.StartElement:

			inElement = se.Name.Local
			//		fmt.Printf("inElement=%s\n",inElement)
			if inElement == "Trackpoint" {
				//var l Lap
				var tp Trackpoint
				decoder.DecodeElement(&tp, &se)
				ts, tts := TimeParse(tp.TptT) // Keep this for error checking
				tp.TptT = ts
				stp = append(stp, TTrackpoint{tts, tp.Lat, tp.Lon, tp.Alt, tp.DistP, tp.HrT, tp.Speed, 0, 0})
				if spcount == 0 {
					//fmt.Printf("\n%s,%f,%f,%f,%f,%d,%f\n",ts,tp.Lat,tp.Lon,tp.Alt,tp.DistP,tp.HrT,tp.Speed)
					//fmt.Printf("\n%s,%f,%f\n",ts,tp.Lat,tp.Lon)
					heading_s = fmt.Sprintf("%s,%f,%f", ts, tp.Lat, tp.Lon)
					spcount = 1
				}

			}

		default:
		}

	}
	analyzePrep(stp, heading_s)
}



/*
*  This prints out TrmExp
 */
func analyzePrep(tp []TTrackpoint, heading string) {
	// y=mx+b
	// y-y/x-x

	mT := []TTT{}
	tot_Trim := 0.0
	for i := 0; i < len(tp)-1; i++ {
		//HR
		a := tp[i].T
		b := tp[i+1].T
		dt := int32(b.Sub(a).Seconds())

		//Speed
		s0 := tp[i].Speed
		s1 := tp[i+1].Speed
		ds := s1 - s0

		//Time
		x := tp[i].HrT
		y := tp[i+1].HrT
		dhr := int32(y - x)

		if dt != 0 {
			slp := float64(dhr) / float64(dt)
			sslp := float64(ds) / float64(dt)
			if math.Abs(slp) < 5 {
				tp[i+1].HrSlope = slp

			}
			if math.Abs(sslp) < 5 {
				tp[i+1].SpeedSlope = sslp
			}
		}
		// This is the guy you sort
		tot_Trim += TrimExp(tp[i].HrT, dt)
		mT = append(mT, TTT{tp[i].T, tp[i].HrSlope, i, tp[i].SpeedSlope, TrimExp(tp[i].HrT, dt), tot_Trim})

		if 1 == 2 {
			fmt.Printf("%3d:(%s), dt:%2d, Hr:%3v, HrSlope:%5.2v, Speed:%5.3v, SpeedSlope:%7.3f, TRIMexp %6.3f,Sum(TrmExp):%7.3f\n", 
                                i, tp[i].T, dt, tp[i].HrT, tp[i].HrSlope,
				tp[i].Speed, tp[i].SpeedSlope,
				TrimExp(tp[i].HrT, dt), tot_Trim)
		}

		zoneCalc(dt, tp[i].HrT)

	}

	fmt.Printf("\nDate and Loc: %s\nLength %v\n", heading, len(mT))
	fmt.Printf("Sum(TrmExp): %4.2f\n", tot_Trim)

}

const MaxHR = 174  // http://www.digifit.com/heartratezones/maximum-heart-rate.asp?Age=50#table
func TrimExp(hr int, sec int32) float64 {
	//
	const RestHR = 45

	if hr <= 40 || sec <= 0 {
		return 0.0
	}
	c := float64(sec) / 60.0 * (float64(hr) - RestHR) / (MaxHR - RestHR) * math.Pow(math.E, (1.92*(float64(hr)-RestHR)/(MaxHR-RestHR)))
	return c

}

func process2(file string) {

	clearZones() 
	process(file)
	prHz()

}

func main() {

	FILE = os.Stdin
	flag.Parse()


	process2("./activity_358299155.tcx")
	process2("./activity_354716894.tcx")
	process2("./activity_353250477.tcx")
	process2("./activity_356626086.tcx") //acy.tcx
//	process2("./7.1_50.tcx")
	process2("./activity_361002204.tcx")
	process2("./activity_366180904.tcx")
	process2("./activity_366844284.tcx")
	process2("./activity_369107032.tcx")
	process2("./activity_370249411.tcx")
	process2("./activity_371013536.tcx")
	process2("./activity_378232679.tcx")
	process2("./activity_378671023.tcx")
	process2("./activity_389002502.tcx")
	process2("./activity_388328241.tcx")
	process2("./activity_381484405.tcx")

	process2("./activity_393892677.tcx")
	process2("./activity_394686466.tcx")
	process2("./activity_397493777.tcx")
	process2("./activity_397752766.tcx")

	process2("./activity_399483288.tcx")


	process2("./activity_399483322.tcx")

	process2("./activity_402457541.tcx")

	
	process2("./activity_402457558.tcx")

	process2("./activity_402457586.tcx")
	process2("./activity_402457613.tcx")
	process2("./activity_405340576.tcx")
	process2("./activity_405497429.tcx")
	process2("./activity_412396074.tcx")



}
