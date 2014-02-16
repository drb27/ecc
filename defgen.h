#ifndef DEFGEN_H_
#define DEFGEN_H

namespace ecc
{
    class defgen : public generator
    {
    public:
	defgen() {}
    protected:
	virtual string tl_head(outfile_t fileType, const string& fHeader);
	virtual string tl_typedef(const enumdef& ed);
	virtual string tl_prototype(const enumdef& item, outfile_t fileType);
	virtual string tl_codebody(const elist_t& items);

	virtual string tl_constants(const elist_t& items);
	virtual string tl_function_regular(const enumdef& item);
	virtual string tl_function_flags_attr(const enumdef& item);
    };
}

#endif
