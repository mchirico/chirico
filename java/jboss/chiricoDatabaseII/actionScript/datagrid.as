import fl.controls.DataGrid;
import fl.data.DataProvider;
import fl.controls.ScrollPolicy;
import fl.controls.Button;
import fl.controls.Slider;
import fl.events.SliderEvent;

/*
Reference:
http://www.adobe.com/devnet/flash/quickstart/datagrid_pt1/



*/



// Button
// Create a new Button component instance and add it to the display list.
var btn0:Button = new Button();
btn0.label = "enabled = true";
btn0.useHandCursor = true;
btn0.emphasized = true;
btn0.move(10, 120);
btn0.addEventListener(MouseEvent.CLICK, clickHandler);

addChild(btn0);



/* Handler function for the enabledButton and disabledButton button instances. This
   function updates the target button's label property when the button is clicked. */
function clickHandler(event:MouseEvent):void {
    var btn:Button = event.currentTarget as Button;
    if (btn.label == "enabled = true") {
    btn.label = "Clicked!";
    } else {
      btn.label="enabled = true";
      }
}
        






var dp:DataProvider;


var myDataGrid:DataGrid = new DataGrid();
myDataGrid.addColumn("column1");
myDataGrid.addColumn("column2");
myDataGrid.addColumn("column3");
myDataGrid.addColumn("column4");
myDataGrid.addColumn("column5");
myDataGrid.addColumn("column6");
myDataGrid.addColumn("column7");
myDataGrid.width = 800;
myDataGrid.height = 1200;
myDataGrid.move(10, 200);
addChild(myDataGrid);

var url:String = "examples2/itemsDP2";
var req:URLRequest = new URLRequest(url);
var uLdr:URLLoader = new URLLoader();
uLdr.addEventListener(Event.COMPLETE, completeHandler);
uLdr.load(req);

// Second grid
var dp2:DataProvider;


var myDataGrid2:DataGrid = new DataGrid();
myDataGrid2.addColumn("column1");
myDataGrid2.addColumn("column2");
myDataGrid2.addColumn("column3");
myDataGrid2.addColumn("column4");
myDataGrid2.addColumn("column5");
myDataGrid2.addColumn("column6");
myDataGrid2.addColumn("column7");
myDataGrid2.width = 800;
myDataGrid2.move(10, 10);
addChild(myDataGrid2);

var url2:String = "examples2/statsT";
var req2:URLRequest = new URLRequest(url2);
var uLdr2:URLLoader = new URLLoader();
uLdr2.addEventListener(Event.COMPLETE, completeHandler2);
uLdr2.load(req2);




function completeHandler(event:Event):void {
	 var ldr:URLLoader = event.currentTarget as URLLoader;
	 var xmlDP:XML = new XML(ldr.data);
	 dp = new DataProvider(xmlDP);
	 myDataGrid.dataProvider = dp;
}


function completeHandler2(event:Event):void {
	 var ldr:URLLoader = event.currentTarget as URLLoader;
	 var xmlDP:XML = new XML(ldr.data);
	 dp2 = new DataProvider(xmlDP);
	 myDataGrid2.dataProvider = dp2;
}



