"""Filename matching with shell patterns.

fnmatch(FILENAME, PATTERN) matches according to the local convention.
fnmatchcase(FILENAME, PATTERN) always takes case in account.

The functions operate by translating the pattern into a regular
expression.  They cache the compiled regular expressions for speed.

The function translate(PATTERN) returns a regular expression
corresponding to PATTERN.  (It does not compile it.)
"""

_cache = {}

def fnmatch(name, pat):
	"""Test whether FILENAME matches PATTERN.
	
	Patterns are Unix shell style:
	
	*	matches everything
	?	matches any single character
	[seq]	matches any character in seq
	[!seq]	matches any char not in seq
	
	An initial period in FILENAME is not special.
	Both FILENAME and PATTERN are first case-normalized
	if the operating system requires it.
	If you don't want this, use fnmatchcase(FILENAME, PATTERN).
	"""
	
	import os
	name = os.path.normcase(name)
	pat = os.path.normcase(pat)
	return fnmatchcase(name, pat)

def fnmatchcase(name, pat):
	"""Test wheter FILENAME matches PATTERN, including case.
	
	This is a version of fnmatch() which doesn't case-normalize
	its arguments.
	"""
	
	if not _cache.has_key(pat):
		res = translate(pat)
		import regex
		save_syntax = regex.set_syntax(0)
		_cache[pat] = regex.compile(res)
		save_syntax = regex.set_syntax(save_syntax)
	return _cache[pat].match(name) == len(name)

def translate(pat):
	"""Translate a shell PATTERN to a regular expression.
	
	There is no way to quote meta-characters.
	"""
	
	i, n = 0, len(pat)
	res = ''
	while i < n:
		c = pat[i]
		i = i+1
		if c == '*':
			res = res + '.*'
		elif c == '?':
			res = res + '.'
		elif c == '[':
			j = i
			if j < n and pat[j] == '!':
				j = j+1
			if j < n and pat[j] == ']':
				j = j+1
			while j < n and pat[j] != ']':
				j = j+1
			if j >= n:
				res = res + '\\['
			else:
				stuff = pat[i:j]
				i = j+1
				if stuff[0] == '!':
					stuff = '[^' + stuff[1:] + ']'
				elif stuff == '^'*len(stuff):
					stuff = '\\^'
				else:
					while stuff[0] == '^':
						stuff = stuff[1:] + stuff[0]
					stuff = '[' + stuff + ']'
				res = res + stuff
		elif c in '\\.+^$':
			res = res + ('\\' + c)
		else:
			res = res + c
	return res