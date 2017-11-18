#include "regex.hh"
#include <iostream>

/* Initialize the regex operator to apply exactly once. */
RegexOperator::RegexOperator() {
    minRepeat = 1;
    maxRepeat = 1;
}


/* Returns the "minimum repeat count" value. */
int RegexOperator::getMinRepeat() const {
    return minRepeat;
}


/* Returns the "maximum repeat count" value. */
int RegexOperator::getMaxRepeat() const {
    return maxRepeat;
}


/* Sets the "minimum repeat count" value. */
void RegexOperator::setMinRepeat(int n) {
    assert(n >= 0);
    minRepeat = n;
}


/* Sets the "maximum repeat count" value. */
void RegexOperator::setMaxRepeat(int n) {
    assert(n >= -1);
    maxRepeat = n;
}


/* Clears the list of matches stored in the regex operator.  Typically done
 * in preparation to try to match the regex to a new string.
 */
void RegexOperator::clearMatches() {
    matches.clear();
}


/* Records a new match of the operator in the list of matches. */
void RegexOperator::pushMatch(const Range &r) {
    matches.push_back(r);
}


/* Reports how many times the regex operator has successfully matched in the
 * string.
 */
int RegexOperator::numMatches() const {
    return (int) matches.size();
}


/* Removes the last match the operator successfully matched against.  Used for
 * backtracking by the regex engine.
 */
Range RegexOperator::popMatch() {
    Range r = matches.back();
    matches.pop_back();
    return r;
}

// BELOW IS ALL ADDED CODE //

/* Matching single character */
MatchChar::MatchChar(const char c)
{
	this->toMatch = c;
}

bool MatchChar::match(const string &s, Range &r) const
{
	// making sure we have valid inputs
	if (string::size_type(r.start) >= s.length() || r.start < 0)
	{
		return false;
	}

	if (s[r.start] == this->toMatch)
	{
		r.end = r.start + 1;
		return true;
	}

	return false;
}

/* Matching any character */
bool MatchAny::match(const string &s, Range &r) const
{
	if (string::size_type(r.start) >= s.length() || r.start < 0)
	{
		return false;
	}
	r.end = r.start + 1;
	return true;
}

/* Matches character with any character from a set of chars */
MatchFromSubset::MatchFromSubset(const string s)
{
	this->subset = s;
}

bool MatchFromSubset::match(const string &s, Range &r) const
{
	if (string::size_type(r.start) >= s.length() || r.start < 0)
	{
		return false;
	}

	for (string::size_type i = 0; i < this->subset.length(); i++)
	{
		if (s[r.start] == this->subset[i])
		{
			r.end += 1;
			return true;
		}
	}
	return false;
}

/* Matches character with any character NOT in set of chars */

ExcludeFromSubset::ExcludeFromSubset(const string s)
{
	this->subset = s;
}

bool ExcludeFromSubset::match(const string &s, Range &r) const
{
	if (string::size_type(r.start) >= s.length() || r.start < 0)
	{
		return false;
	}

	for (string::size_type i = 0; i < this->subset.length(); i++)
	{
		if (s[r.start] == this->subset[i])
		{
			return false;
		}
	}
	r.end += 1;
	return true;
}

/* Converts regex string into a vector of RegexOperator* objects
 * that match the string 
*/
vector<RegexOperator *> parseRegex(const string &expr)
{
	vector<RegexOperator *> ops;
	for (string::size_type i = 0; i < expr.length(); i++)
	{
		if (expr[i] == '.')
		{
			RegexOperator *op = new MatchAny();
			ops.push_back(op);
		}
		else if (expr[i] == '+')
		{
			ops.back()->setMinRepeat(1);
			ops.back()->setMaxRepeat(-1);
		}
		else if (expr[i] == '*')
		{
			ops.back()->setMinRepeat(0);
			ops.back()->setMaxRepeat(-1);
		}
		else if (expr[i] == '?')
		{
			ops.back()->setMinRepeat(0);
			ops.back()->setMaxRepeat(1);
		}
		else if (expr[i] == '[')
		{
			string runningSet = "";
			bool in = (expr[++i] != '^');
			if (!in)
			{
				i += 1;
			}

			while (expr[i] != ']')
			{
				runningSet += expr[i];
				i += 1;
			}

			if (in)
			{
				RegexOperator *op = new MatchFromSubset(runningSet);
				ops.push_back(op);
			}
			else
			{
				RegexOperator *op = new ExcludeFromSubset(runningSet);
				ops.push_back(op);
			}

		}
		else
		{
			ops.push_back(new MatchChar(expr[i]));
		}
	}
	return ops;
}

/* Frees memory */

void clearRegex(vector<RegexOperator *> regex)
{
	while (!regex.empty())
	{
		delete regex.back();
		regex.pop_back();
	}
}