#ifndef INDENT_H
#define INDENT_H

namespace ecc
{
    class indent
    {
    public:
	indent(int width=4);
	~indent();

	indent& operator++(int);
	indent& operator--(int);
	void reset(void);
	const string& operator() () const;

    private:

	void update_cache(void);

	const int indentWidth;	/**< Number of spaces per indent level */
	int indentLevel;        /**< Current level of indentation (0=no indentation) */
	string indentString;    /**< Cache for the current indent string */
    };

}

#endif
