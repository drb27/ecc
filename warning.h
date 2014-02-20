#ifndef WARNING_H_
#define WARNING_H_

namespace ecc
{
    class warning
    {
    public:

	typedef enum
	{
	    invalid=0,
	    duplicateValue
	} code;

	warning(code cde,const string& file, int line);
	virtual ~warning();

    protected:
	const code code_;
	const string file_;
	const int line_;

	friend ostream& operator<<(ostream&, const warning&);
    };
    
    ostream& operator<<(ostream&, const warning&);
}
#endif
