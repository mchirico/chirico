import fl.controls.DataGrid;
import fl.controls.dataGridClasses.DataGridColumn;
import fl.data.DataProvider;

var dp:DataProvider = new DataProvider();
dp.addItem({name:"Item 1", price:1234.00});
dp.addItem({name:"Item 2", price:56.30});
dp.addItem({name:"Item 3", price:789.12});

var nameCol:DataGridColumn = new DataGridColumn("name");
nameCol.headerText = "Name:";

var priceCol:DataGridColumn = new DataGridColumn("price");
priceCol.headerText = "Price (USD):";
priceCol.sortOptions = Array.NUMERIC;
priceCol.labelFunction = dollarLabelFunction;
priceCol.cellRenderer = RightAlignCell;

var myDataGrid:DataGrid = new DataGrid();
myDataGrid.addColumn(nameCol);
myDataGrid.addColumn(priceCol);
myDataGrid.dataProvider = dp;
myDataGrid.width = 200;
myDataGrid.rowCount = myDataGrid.length;
myDataGrid.move(10, 10);
addChild(myDataGrid);

function dollarLabelFunction(item:Object):String {
    return "$" + Number(item.price).toFixed(2);
}
