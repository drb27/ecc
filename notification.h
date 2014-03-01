#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

namespace ecc
{
    class notification
    {
    public:

	virtual ~notification();

	void push_token(const string& tk, const string& val);
	void push_token(const string& tk, int val);
	bool is_fatal() const;

	string& operator[](const string& key);
    
	friend ostream& operator<<(ostream&, const notification&);

    protected:

	notification(int code, bool fatal, int line, const string& cat);
	virtual string prep_string(void) const;
	virtual string get_template(void) const=0;
	void sub_tokens_in_place(string& tmpl) const;

	const int code_;
	map<string,string> dict_;
	const bool fatal_;
	const string& category_;

    };
    
    ostream& operator<<(ostream&, const notification&);

}

#endif
