/*
 
 The MIT License (MIT)
 Copyright (c) 2009 mchirico@gmail.com
 
 
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 Location:
 /Users/mchirico/dev/github/mmc/src/Hash\ From\ Table/Hash\ From\ Table/hash.c
 
 
 
 
 //option click to split window
 
 So far this is only setup to throw away collisions. You
 need a way to deal with collusions. Also. Need to
 deal with bucket types.
 
 
 References:
 https://github.com/troydhanson/uthash
 http://svn.python.org/view/python/trunk/Objects/dictobject.c?view=markup
 */


#include <stdio.h>
#include <string.h>

/*  Begin HASHTABLE */
/*
 
 +---------------------------------------------------+
 |+-------------------------------------------------+|
 || HASHTABLE                                       ||
 ||                                                 ||
 ||      +--------+        +----------+             ||
 ||      +--------+ +--->  +----------+             ||
 ||                        +----------+             ||
 ||                        +----------+             ||
 ||                        +----------+             ||
 ||                        +----------+             ||
 ||                        +----------+             ||
 ||   getHashCode                                   ||
 ||   setValue                                      ||
 ||   getValue             +  Just a few simple     ||
 ||   getHitValue   <------+  functions             ||
 ||   zeroValue                                     ||
 ||                                                 ||
 |+-------------------------------------------------+|
 +---------------------------------------------------+
 
 For the latest version of this
 https://raw.github.com/mchirico/chirico/master/c/simple_but_common/hash.c
 
 */
#define HASH_TABLE_SIZE 1000
#define HASH_INITIAL_VALUE 5381   //Bernstein's function H
#define HASH_M_VALUE 33           //Bernstein's function M
#define HASH_BUCKET_LIMIT 1000


typedef struct HashTable {
    int  hits;
    char bucket[HASH_BUCKET_LIMIT];
    
} HashTable;


int getHashCode(char * key);
int setValue(char * key, char * val, HashTable ht[]);
char * getValue(char * key, HashTable ht[]);
int getHitValue(char * key, HashTable ht[]);
int zeroValue(char * key, HashTable ht[]);
void initHashTable(HashTable ht[]);

/*
 This uses Bernstein's function.
 
*/
int getHashCode(char * key)
{
    if (key == NULL || strlen(key) >= HASH_BUCKET_LIMIT )
        return -1;
    
    int hash = HASH_INITIAL_VALUE;
    int i;
    for (i=0;i < (int) strlen(key);i++)
        hash = HASH_M_VALUE * hash + key[i];
    
    if (hash < 0)
        hash = hash*-1;
    return hash % HASH_TABLE_SIZE;
}

int setValue(char * key, char * val, HashTable ht[])
{
    if (val == NULL || key == NULL)
        return 0;
    
    int hash = getHashCode(key);
    snprintf(ht[hash].bucket,HASH_BUCKET_LIMIT,"%s", val);
    ht[hash].hits+=1;
    return ht[hash].hits;
    
}


char * getValue(char * key, HashTable ht[])
{
    if (key == NULL)
        return NULL;
    
    unsigned int hash = getHashCode(key);
    if (ht[hash].hits == 0)
        return NULL;
    
    char * val = ht[hash].bucket;
    if (val != NULL)
        return val;
    
    return NULL;
}

int getHitValue(char * key, HashTable ht[])
{
    if (key == NULL)
        return -1;
    
    unsigned int hash = getHashCode(key);
    return ht[hash].hits;
    
}

int zeroValue(char * key, HashTable ht[])
{
    if (key == NULL)
        return 0;
    
    int hash = getHashCode(key);
    if (ht[hash].hits != 0)
    {
        ht[hash].bucket[0] = '\0';
        ht[hash].hits=0;
        return 1;
    } else
    {
        ht[hash].bucket[0] = '\0';
        ht[hash].hits=0;
        return 0;
    }
}

void initHashTable(HashTable ht[])
{
    int i;
    for(i=0; i < HASH_TABLE_SIZE; ++i)
    {
        ht[i].bucket[0]='\0';
        ht[i].hits=0;
        
    }
}
/*
 
 int main(int argc, const char * argv[])
 {
 HashTable ht[HASH_TABLE_SIZE];
 initHashTable(ht);
 
 
 setValue("one","1",ht);
 setValue("two","2",ht);
 setValue("three","3",ht);
 setValue("four","4",ht);
 
 printf("Answer ->%s<-\n",getValue("Two",ht));
 printf("Answer ->%s<-\n",getValue("two",ht));
 printf("getValue(%s,ht)= %s\n","two",getValue("two",ht));
 printf("getHitValue(%s,ht)= %d\n","two",getHitValue("two",ht));
 printf("zeroValue %d\n",zeroValue("two",ht));
 printf("zeroValue %d\n",zeroValue("two",ht));
 printf("getHitValue %d\n",getHitValue("two",ht));
 printf("getValue(%s,ht)= %s\n","two",getValue("two",ht));
 
 
 
 
 return 0;
 }
 
 */
/*  End HASHTABLE */

#include <stdio.h>
#include <stdlib.h>

double Plus (double a, double b) { return a+b; }
double Mult (double a, double b) { return a*b; }
double Minus (double a, double b) { return a-b; }
double Div (double a, double b) { return a/b; }

void SF(double a, double b, double (*ptF)(double, double))
{
    double result = ptF(a,b);
    printf("%lf\n",result);
}
/*
int main()
{

    return 0;
    
}
*/
int main(int argc, const char * argv[])
{
    HashTable ht[HASH_TABLE_SIZE];
    initHashTable(ht);
    
    
    setValue("one","1",ht);
    setValue("two","2",ht);
    setValue("three","3",ht);
    setValue("four","4",ht);
    
    printf("Answer ->%s<-\n",getValue("Two",ht));
    printf("Answer ->%s<-\n",getValue("two",ht));
    printf("getValue(%s,ht)= %s\n","two",getValue("two",ht));
    printf("getHitValue(%s,ht)= %d\n","two",getHitValue("two",ht));
    printf("zeroValue %d\n",zeroValue("two",ht));
    printf("zeroValue %d\n",zeroValue("two",ht));
    printf("getHitValue %d\n",getHitValue("two",ht));
    printf("getValue(%s,ht)= %s\n","two",getValue("two",ht));
    
    
    SF(10,23,&Plus);
    SF(10,23,&Mult);
    SF(10,23,&Minus);
    
    return 0;
}

