#Regular Expressions


This is a general overview on regular expressions, commonly shortened to "regex".

This tutorial will cover the basics of regex, but more specifically, POSIX regex.

But first we'll start with the basics.

##What is it?

Regex is a short pattern of letters and symbols which has can match certain strings.

###1. Basic characters

Any letter or character `a-z`, `A-Z`, `0-9` by itself will match a single instance of that character. There are a few extra symbols which do not follow this rule but we'll get to that in a bit.

> ###Example
> `a` will match *c**a**t* and *p**a**tch* but not *dog*

----------------------------------
