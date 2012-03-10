
#include <string>
#include <map>


class StringTokenizer {

public:

    StringTokenizer(const char  *s, const char* delim = NULL);
    ~StringTokenizer();

    size_t countTokens( );
    bool hasMoreTokens( );

    void nextToken(std::string& s);

private:
    StringTokenizer( ) {};
    std::string delim_;
    std::string str_;
    int count_;
    size_t begin_;
    size_t end_;
};




class IPUmap {

public:
    typedef std::map< std::string, long, std::less< std::string > > H;
    typedef std::map< std::string, long, std::less< std::string > > *Hp;


    IPUmap(const char *s );

    ~IPUmap();

    bool check(const char *ip, const char *user);
    void succlogin(const char *ip,const char *acct);
    void prw();
    void pr();

private:

    void hpadd(Hp hp,std::string *ipu);

    long hpadd(Hp hp,const char *s);

    long _validate(Hp hp, std::string ipu);

    long validate(Hp hp,std::string s);

    long validate(Hp hp,const char *s);

    long validate(Hp hp,const char *ip,const char *acct);

    long _reset(Hp hp, std::string ipu);

    long reset(Hp hp,const char *ip,const char *acct);
    long reset(Hp hp,std::string s);
    long _whiteadd(Hp hp,std::string ipu);
    long whiteadd(Hp hp,const char *s);
    long whiteadd(Hp hp,std::string s);

private:

    Hp white;
    Hp database;
    StringTokenizer st;
};
