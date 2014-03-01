#ifndef _ERRORS_H_
#define _ERRORS_H_

#include "notification.h"
#include "codes.h"

namespace ecc
{
    class error : public notification
    {
    public:

	error(errorcode cde, int line);
	virtual ~error();


    protected:
	virtual string get_template(void) const;

    };
    
}

#endif
