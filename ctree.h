/**
 * Canonical Tree
 */

#ifndef CTREE_H_
#define CTREE_H_

#include <cstring>
#include <functional>

#define SEPARATOR "::"

namespace test
{
    class ctree;
}

template<typename T>
class ctree
{
    friend test::ctree;

public:

    class notfound : public exception
    {
    public:
	virtual const char* what() const noexcept
	{
	    return "The requested item could not be found.";
	}
    };

    ctree() : name_(""),parent_(NULL) {}

protected:
    ctree(const string& nm, ctree<T>* parent) : name_(nm), parent_(parent) {}
public:

    virtual ~ctree() {}

    virtual void insert_member(T* v)
    {
	members_.push_back(v);
    }

    virtual ctree<T>& create_node(const string& name)
    {
	subnodes_.push_back( ctree<T>(name,this) );
	return subnodes_.back();
    }

    const ctree<T>* parent() const { return parent_; }
    ctree<T>* parent() { return parent_; }

    const std::string& name(void) const { return name_; }

    vector<T*>& members(void) { return members_; }
    const vector<T*>& members(void) const { return members_; }

    void push_member(T member) { members_.push_back(member); }
    
    ctree<T>& lookup(const string& target)
    {
	return const_cast<ctree<T>&>(lookup_alg(target));
    }

    const ctree<T>& lookup(const string& target) const
    {
	return lookup_alg(target);
    }

    bool operator==(const ctree<T>& other) const
    {
	return ( (name_==other.name_) && (members_==other.members_) &&
		 (subnodes_==other.subnodes_) && (parent_==other.parent_) );
    }

    std::string fqn(const string& sep = SEPARATOR) const
    {
	if (!parent_)
	{
	    return name();
	}
	else
	{
	    const std::string parent_fqn = parent_->fqn();
	    if (parent_fqn.length())
		return parent_fqn + sep + name();
	    else return name();
	}
    }

    ctree<T>& find_local_node(const string& nm)
    {
	return const_cast<ctree<T>&>(find_local_node_alg(nm));
    }

    const ctree<T>& find_local_node(const string& nm) const
    {
	return find_local_node_alg(nm);
    }

    bool has_local_node(const string& nm) const
    {
	for ( auto& n : subnodes_)
	{
	    if (nm==n.name())
		return true;
	}

	return false;
    }

    void create_path(string ref)
    {
	// If the string is empty, we are done
	if (ref.empty()) return;

	// Not done - pop the head
	string head = pop_head(ref);

	// Does this exist?
	if (!has_local_node(head))
	{
	    // No - create it
	    create_node(head);
	}

	ctree<T>& nextnode = find_local_node(head);

	// Carry on with the rest of the string
	nextnode.create_path(ref);
    }

    void dfs(std::function<void(const ctree<T>&)> cbStart,
	     std::function<void(const ctree<T>&)> cbEnd) const
    {
	// Start with this node ...
	cbStart(*this);

	// Now go down into the subnodes ...
	for ( auto subnode : subnodes_ )
	{
	    subnode.dfs(cbStart,cbEnd);
	}

	// This node is done
	cbEnd(*this);
    }

    bool is_root(void) const
    {
	return (NULL==parent_);
    }
    
protected:

    const ctree<T>& find_local_node_alg(const string& nm) const
    {
	for ( auto& n : subnodes_)
	{
	    if (nm==n.name())
		return n; 
	}
	
	throw notfound();
    }

    static string pop_head( string& ref )
    {
	if ( is_leaf(ref) )
	{
	    string retval = ref;
	    ref = "";
	    return retval;
	}
	else
	{
	    size_t idx = ref.find(SEPARATOR);
	    assert(idx!=string::npos);

	    string retval = ref.substr(0,idx);
	    ref.erase( 0, idx+strlen(SEPARATOR) );
	    return retval;
	}
    }

    static bool is_leaf(const string& ref)
    {
	size_t idx = ref.find(SEPARATOR);
	return (idx==string::npos);
    }

    const ctree<T>& lookup_alg(string target) const
    {
	// Pop the head, get the node
	string headref = pop_head(target);
	const ctree<T>& nextnode = find_local_node(headref);

	// Are we done?
	if (target.length())
	{
	    // Nope, delegate down
	    return nextnode.lookup_alg(target);
	}
	else
	    return nextnode;
    }

protected:
    const string name_;
    vector<T*> members_;
    vector<ctree<T> > subnodes_;
    ctree<T>* parent_;
};

#endif
