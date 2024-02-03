#include <cassert>
#include "polynomial.h"
#include <list>

using namespace std;


bool constCheck (const Term&)
{
    return true;
}

bool constCheck (Term&)
{
    return false;
}


bool Polynomial::sanityCheck() const
{
    int n = degree;
    const list<Term> termList = terms;
    if (n > 1)
    {
        const_iterator start = begin();
        const_iterator next = start;
        ++next;
        while (next != end())
        {
            if (next->power <= start->power || next->coefficient == 0)
                return false;
            start = next;
            next++;
        }
    }
    if ( begin() == end())
        return true;
    Polynomial& p = (Polynomial&)(*this);
    return constCheck(*begin()) && !constCheck(*(p.begin()));
    
}

