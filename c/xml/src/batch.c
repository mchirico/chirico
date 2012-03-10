/*  
# Copyright 2008 Mike Chirico mchirico@gmail.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>



int create_batch(xmlNodePtr parent_node, char *id, char *operation)
{
	xmlNodePtr node = NULL;

	xmlNewChild(parent_node, NULL, BAD_CAST "batch:id", BAD_CAST id);
	node = xmlNewChild(parent_node, NULL, BAD_CAST "batch:operation",
			   BAD_CAST NULL);
	xmlNewProp(node, BAD_CAST "type", BAD_CAST operation);
	return 0;

}

int create_link(xmlNodePtr parent_node, char *rel, char *href)
{
	xmlNodePtr node = NULL;

	node = xmlNewChild(parent_node, NULL, BAD_CAST "link",
			   BAD_CAST NULL);
	xmlNewProp(node, BAD_CAST "rel", BAD_CAST rel);
	xmlNewProp(node, BAD_CAST "type", BAD_CAST "application/atom+xml");
	xmlNewProp(node, BAD_CAST "href", BAD_CAST href);
	return 0;

}

int create_id(xmlNodePtr parent_node, char *id)
{
	xmlNodePtr node = NULL;

	node = xmlNewChild(parent_node, NULL, BAD_CAST "id", BAD_CAST id);
	return 0;
}


int create_cell(xmlNodePtr parent_node, int row, int col, char *inputValue)
{
	xmlNodePtr node = NULL;
	char srow[256];
	char scol[256];

	snprintf(srow, 256, "%d", row);
	snprintf(scol, 256, "%d", col);

	node =
	    xmlNewChild(parent_node, NULL, BAD_CAST "gs:cell",
			BAD_CAST NULL);
	xmlNewProp(node, BAD_CAST "row", BAD_CAST srow);
	xmlNewProp(node, BAD_CAST "col", BAD_CAST scol);
	xmlNewProp(node, BAD_CAST "inputValue", BAD_CAST inputValue);

	return 0;

}

int create_entry(xmlNodePtr parent_node, int row, int col,
		 char *inputValue, char *batchid, char *batchtype,
		 char *id, char *linktype, char *linkvalue)
{
	xmlNodePtr node = NULL;

	node = xmlNewChild(parent_node, NULL, BAD_CAST "entry", NULL);

	create_batch(node, batchid, batchtype);
	create_id(node, id);

	create_link(node, linktype, linkvalue);
	create_cell(node, row, col, inputValue);
}

int init_feed(xmlDocPtr * doc, xmlNodePtr * root)
{

	*doc = xmlNewDoc(BAD_CAST "1.0");
	*root = xmlNewNode(NULL, BAD_CAST "feed");
	xmlDocSetRootElement(*doc, *root);
	xmlNewProp(*root, BAD_CAST "xmlns",
		   BAD_CAST "http://www.w3.org/2005/Atom");
	xmlNewProp(*root, BAD_CAST "xmlns:batch",
		   BAD_CAST "http://schemas.google.com/gdata/batch");
	xmlNewProp(*root, BAD_CAST "xmlns:gs",
		   BAD_CAST "http://schemas.google.com/spreadsheets/2006");

	return 0;

}

int delete_feed(xmlDocPtr * doc)
{
	xmlFreeDoc(*doc);
	xmlCleanupParser();
	return 0;

}


/* Current can view this as a sample way to drive the batch creation */
int create_xmlbatch()
{
	xmlDocPtr doc = NULL;	/* document pointer */
	xmlNodePtr feed_node = NULL;	/* node pointers */


	init_feed(&doc, &feed_node);

	create_entry(feed_node, 1, 1,
		     "=GoogleFinance(\"AAPL\", \"close\", \"1/1/2003\", \"1/31/2008\", \"1\")",
		     "A1",
		     "update",
		     "http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R5C1",
		     "edit",
		     "http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R5C3/bepji");

	create_entry(feed_node, 2, 1,
		     "Stuff",
		     "A2",
		     "update",
		     "http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R5C1",
		     "edit",
		     "http://spreadsheets.google.com/feeds/cells/o02033738628008092337.7901402712316103813/od7/private/full/R5C3/bepji");


	/* xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1); */
	xmlSaveFormatFileEnc("-", doc, "UTF-8", 1);

	delete_feed(&doc);

	return 0;
}




int main(int argc, char **argv)
{

	create_xmlbatch();
	return (0);
}
