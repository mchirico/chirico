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




int delete_doc(xmlDocPtr * doc);
int create_doc(xmlDocPtr * doc, xmlNodePtr * root, char *value);
void add_attrib(xmlNodePtr node, char *key, char *value);
xmlNodePtr add_child(xmlNodePtr parent_node, char *key, char *value);


int delete_doc(xmlDocPtr * doc)
{
	xmlFreeDoc(*doc);
	xmlCleanupParser();
	return 0;
}


int create_doc(xmlDocPtr * doc, xmlNodePtr * root, char *value)
{

	*doc = xmlNewDoc(BAD_CAST "1.0");
	*root = xmlNewNode(NULL, BAD_CAST value);

	xmlDocSetRootElement(*doc, *root);
	return 0;
}


void add_attrib(xmlNodePtr node, char *key, char *value)
{
	xmlNewProp(node, BAD_CAST key, BAD_CAST value);
}

xmlNodePtr add_child(xmlNodePtr parent_node, char *key, char *value)
{
	xmlNodePtr node = NULL;
	node = xmlNewChild(parent_node, NULL, BAD_CAST key,
			   BAD_CAST value);
	return node;

}

static void pr_nodes(xmlNode * node)
{
	xmlNode *cur = NULL;

	for (cur = node; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			printf("node type: Element, name: %s\n",
			       cur->name);
		}

		pr_nodes(cur->children);
	}
}




int Pr_curr_node(xmlNode *node)
{
 xmlNode *cur=NULL;
  cur=node;
  if(!cur)
    return;
  if(cur->type == XML_ELEMENT_NODE)
    printf("****  Pr_curr_node: ->%s<-\n",cur->name);
}



static find_node(xmlNode * node, char *value, int (*ptF)(xmlNode *))
{
	xmlNode *cur = NULL;

	for (cur = node; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {

			if ((!xmlStrcmp
			     (cur->name, (const xmlChar *) value))) {
			  ptF(cur);



			}
		}

				find_node(cur->children, value, ptF);
	}
}


/**********************************************************************
   End general functions

************************************************************************/





int create_batch(xmlNodePtr parent_node, char *id, char *operation)
{
	xmlNodePtr node = NULL;
	add_child(parent_node, "batch:id", id);
	node = add_child(parent_node, "batch:operation", NULL);
	add_attrib(node, "type", operation);
	return 0;

}

xmlNodePtr create_link(xmlNodePtr parent_node, char *rel, char *href)
{
	xmlNodePtr node = NULL;
	node = add_child(parent_node, "link", NULL);
	add_attrib(node, "rel", rel);
	add_attrib(node, "type", "application/atom+xml");
	add_attrib(node, "href", href);
	return node;

}



int create_id(xmlNodePtr parent_node, char *id)
{
	xmlNodePtr node = NULL;
	add_child(parent_node, "id", id);
	return 0;
}


int create_cell(xmlNodePtr parent_node, int row, int col, char *inputValue)
{
	xmlNodePtr node = NULL;
	char srow[256];
	char scol[256];

	snprintf(srow, 256, "%d", row);
	snprintf(scol, 256, "%d", col);

	node = add_child(parent_node, "gs:cell", NULL);
	add_attrib(node, "row", srow);
	add_attrib(node, "col", scol);
	add_attrib(node, "inputValue", inputValue);

	return 0;

}

int create_entry(xmlNodePtr parent_node, int row, int col,
		 char *inputValue, char *batchid, char *batchtype,
		 char *id, char *linktype, char *linkvalue)
{
	xmlNodePtr node = NULL;

	node = add_child(parent_node, "entry", NULL);

	create_batch(node, batchid, batchtype);
	create_id(node, id);

	create_link(node, linktype, linkvalue);
	create_cell(node, row, col, inputValue);
}

int init_feed(xmlDocPtr * doc, xmlNodePtr * root)
{


	create_doc(doc, root, "feed");

	add_attrib(*root, "xmlns", "http://www.w3.org/2005/Atom");
	add_attrib(*root, "xmlns:batch",
		   "http://schemas.google.com/gdata/batch");
	add_attrib(*root, "xmlns:gs",
		   "http://schemas.google.com/spreadsheets/2006");

	return 0;

}



int delete_feed(xmlDocPtr * doc)
{

	return delete_doc(doc);

}


/* Current can view this as a sample way to drive the batch creation */
int create_xmlbatch()
{
	xmlDocPtr doc = NULL;	/* document pointer */
	xmlNodePtr feed_node = NULL, cur = NULL;	/* node pointers */


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

	printf("\n\n\n\n\n");
	/* pr_nodes(feed_node); */
	find_node(feed_node, "link",&Pr_curr_node);

	delete_feed(&doc);

	return 0;
}




int main(int argc, char **argv)
{

	create_xmlbatch();
	return (0);
}
