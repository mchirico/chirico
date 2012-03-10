/* Copyright (C) GPL 2004 Mike Chirico mchirico@users.sourceforge.net mchirico@comcast.net
 *
 */
#ifndef EXTRACT_H
#define EXTRACT_H
class extract {
public:

    extract(std::string d=" \n")
    {
        delims=d;
    }

    void setdelims(std::string d)
    {
        delims=d;
    }
    void setterm(std::string t="")
    {
        terminator=t;
    }


    void strip(std::string s ) {
      v.clear();
        bidx=s.find_first_not_of(delims);
        while(bidx != std::string::npos) {
            eidx=s.find_first_of(delims,bidx);
            if (eidx == std::string::npos) {
                eidx = s.length();
            }

            v.push_back(s.substr(bidx,(eidx-bidx)));
            bidx=s.find_first_not_of(delims,eidx);
        }
	index();
    }

    std::vector<std::string>::iterator BEGIN()
      {
	return indexv.begin();
      }

    std::vector<std::string>::iterator END()
      {
	return indexv.end();
      }

  std::string I(unsigned int i)
  {
    if ( i < indexv.size() && indexv.size() > 0  )
      return indexv[i];
    else
      if ( indexv.size() > 0 )
	return indexv[ indexv.size()-1];
      else
	return "";

  }

  std::string F()
  {
    std::string s="";
    std::string d="";
    for(std::vector<std::string>::iterator i = indexv.begin(); i < indexv.end(); ++i)
      {
	s=s + d + *i;
	d=",";
      }
    return s;
  }

  std::string NF()
  {
    std::string s="(";
    std::string d="";
    for(std::vector<std::string>::iterator i = indexv.begin(); i < indexv.end(); ++i)
      {
	s=s + d + *i;
	d=",";
      }
    s+=")";
    return s;
  }

  int TL()
    {
      return tree_level;
    }

private:
  void index()
  {
    int rcount=0;
    tree_level=0;
    
    std::string t="";
    indexv.clear();
    
    for(std::vector<std::string>::iterator i = v.begin(); i < v.end(); ++i)
      {
      for(std::string::iterator j = i->begin(); j < i->end(); ++j)
	{
	while( *j == '(' && j < i->end() )
	  {
	   rcount++;
           if(rcount > tree_level)
	     tree_level=rcount;
	   if ( rcount > 1)
	     t+=*j;
           j++;
          }	  
        while( *j != ')' && j < i->end() ) {
	  t+=*j;
	  j++;
	}
        while( *j == ')' && j < i->end() ) {
          if ( rcount > 1)
	    t+=*j;
	  rcount--;
	  j++;
	}

	if ( rcount <= 1)
	  {
	    indexv.push_back(t);
	    t="";
	  } else { t+=","; }
	}
      }
  }


    std::string::size_type bidx,eidx;
    std::string delims,terminator;
    std::vector<std::string> indexv;
    std::vector<std::string> v;
    int tree_level;

};

#endif
