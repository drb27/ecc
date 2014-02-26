#ifndef WARNING_H_
#define WARNING_H_

#include "warn.h"

namespace ecc
{
    class warning
    {
    public:

	warning(warningcode cde,int line);
	virtual ~warning();

    protected:
	const warningcode code_;
	const int line_;

	friend ostream& operator<<(ostream&, const warning&);
    };
    
    ostream& operator<<(ostream&, const warning&);
}
#endif
