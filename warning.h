#ifndef WARNING_H_
#define WARNING_H_

#include "notification.h"
#include "codes.h"

namespace ecc
{
    class warning : public notification
    {
    public:

	warning(warningcode cde, int line);
	virtual ~warning();


    protected:
	virtual string get_template(void) const;

    };
    
}
#endif
