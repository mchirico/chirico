/*
What about white-listed IP's? Maybe we don't want them
to fill up the lot. The reset will zero these out.

make wrappers for a lot of these stuff to make it
cleaner.

Better check your logic here. This seems to be
better than other test. But, clean this up.
*/
#include <cstdio>
#include <cstdlib>

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <map>
#include "ipumap.h"






StringTokenizer::StringTokenizer(const char  *s, const char* delim) :
        str_(s), count_(-1), begin_(0), end_(0) {

    if (!delim)
        delim_ = " \f\n\r\t\v";  //default to whitespace
    else
        delim_ = delim;

    // Point to the first token
    begin_ = str_.find_first_not_of(delim_);
    end_ = str_.find_first_of(delim_, begin_);
}
StringTokenizer::~StringTokenizer() {
    fprintf(stderr,"exit StringTokenizer\n");
}



size_t StringTokenizer::countTokens( ) {
    if (count_ >= 0) // return if we've already counted
        return(count_);

    string::size_type n = 0;
    string::size_type i = 0;

    while (1) {
        // advance to the first token
        if ((i = str_.find_first_not_of(delim_, i)) == string::npos)
            break;
        // advance to the next delimiter
        i = str_.find_first_of(delim_, i+1);
        n++;
        if (i == string::npos)
            break;
    }
    return (count_ = n);
}
bool StringTokenizer::hasMoreTokens( ) {
    return(begin_ != end_);
}
void StringTokenizer::nextToken(string& s) {
    if (begin_ != string::npos && end_ != string::npos) {
        s = str_.substr(begin_, end_-begin_);
        begin_ = str_.find_first_not_of(delim_, end_);
        end_ = str_.find_first_of(delim_, begin_);
    }
    else if (begin_ != string::npos && end_ == string::npos)
    {
        s = str_.substr(begin_, str_.length( )-begin_);
        begin_ = str_.find_first_not_of(delim_, end_);
    }

}









IPUmap::IPUmap(const char *s ):white(new H()),database(new H()),st(s) {
    string tmp;
    while (st.hasMoreTokens( )) {
        st.nextToken(tmp);
        whiteadd(white,tmp);
    }
}
IPUmap::~IPUmap() {
    delete (white);
    delete (database);
}


bool IPUmap::check(const char *ip, const char *user) {
    if ( validate(database,ip,user) < 0 )
        return true;
    else
        return false;

}

void IPUmap::succlogin(const char *ip,const char *acct){
    reset(database,ip,acct);
}

void IPUmap::prw() {
    for (H::const_iterator iter = white->begin();
            iter != white->end(); ++iter )
        cout << iter->first << '\t' << iter->second << '\n';
}


void IPUmap::pr() {
    for (H::const_iterator iter = database->begin();
            iter != database->end(); ++iter )
        cout << iter->first << '\t' << iter->second << '\n';
}


void IPUmap::hpadd(Hp hp,string *ipu) {

    H::const_iterator result = hp->find(*ipu);
    if (result != hp->end()){
        (*hp)[*ipu]+=1;
    } else {
        (*hp)[*ipu]=1;
    }

    //hp->insert(H::value_type(*ipu,1));
}



long IPUmap::hpadd(Hp hp,const char *s) {
    string ipu=s;

    H::const_iterator result = hp->find(ipu);
    if (result != hp->end()){
        (*hp)[ipu]+=1;
    } else {
        (*hp)[ipu]=1;
    }
    return (*hp)[ipu];
    //hp->insert(H::value_type(*ipu,1));
}


long IPUmap::_validate(Hp hp, string ipu){
    string t=ipu.substr(ipu.find_first_of(":")+1);


    H::const_iterator result = hp->find(ipu);
    if (result != hp->end()){
        (*hp)[ipu]+=1;
    } else {
        (*hp)[ipu]=1;
    }

    // Look for whitelist. If find, give 10 chances. Otherwise, will only get 2 chances.
    H::const_iterator wresult = white->find(t);
    if (wresult != white->end()) {
        if ((*hp)[ipu] >= 11) {
            return -1;
        } else {
            return (*hp)[ipu];
        }
    }

    if ((*hp)[ipu] >= 3)
        return -1;
    else
        return  (*hp)[ipu];

    //hp->insert(H::value_type(*ipu,1));
}


long IPUmap::validate(Hp hp,string s) {
    string ipu(s);
    return _validate(hp, ipu);
}

long IPUmap::validate(Hp hp,const char *s) {
    string ipu(s);
    return _validate(hp, ipu);
}

long IPUmap::validate(Hp hp,const char *ip,const char *acct) {
    char s[100];
    snprintf(s,100,"%s:%s",ip,acct);
    string ipu(s);
    return _validate(hp, ipu);
}

long IPUmap::_reset(Hp hp, string ipu){
    string t=ipu.substr(ipu.find_first_of(":")+1);


    H::const_iterator result = hp->find(ipu);
    if (result != hp->end()){
        (*hp)[ipu]=0;
    } else {
        (*hp)[ipu]=1;
    }

    H::const_iterator wresult = white->find(t);
    if (wresult != white->end()) {
        if ((*hp)[ipu] >= 5) {
            (*hp)[ipu]=-5; // give extra chances?
        } else {
            (*hp)[ipu]=0; // give extra chances?
        }
    }

    return (*hp)[ipu];
    //hp->insert(H::value_type(*ipu,1));
}




long IPUmap::reset(Hp hp,const char *ip,const char *acct) {
    char s[100];
    snprintf(s,100,"%s:%s",ip,acct);
    string ipu(s);
    return _reset(hp,ipu);
}


long IPUmap::reset(Hp hp,string s) {
    string ipu=s;
    return _reset(hp,ipu);
}



long IPUmap::_whiteadd(Hp hp,string ipu) {

    H::const_iterator result = hp->find(ipu);
    if (result != hp->end()){
        (*hp)[ipu]+=1;
    } else {
        (*hp)[ipu]=1;
    }
    return (*hp)[ipu];
    //hp->insert(H::value_type(*ipu,1));
}

long IPUmap::whiteadd(Hp hp,const char *s) {
    string ipu(s);
    return _whiteadd(hp,ipu);
}

long IPUmap::whiteadd(Hp hp,string s) {
    string ipu(s);
    return _whiteadd(hp,ipu);
}
