#ifndef WARNING_H_
#define WARNING_H_

#include "warn.h"
#include "notification.h"

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
