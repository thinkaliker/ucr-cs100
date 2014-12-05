#Regular Expressions


This is a general overview on regular expressions, commonly shortened to "regex".

This tutorial will cover the basics of regex, but more specifically, POSIX regex.

But first we'll start with the basics.

##What is it?

Regex is a short pattern of letters and symbols which has can match certain strings.

###1. Basic characters aka Literal characters

Any letter or character `a-z`, `A-Z`, `0-9` by itself will match a single instance of that character. There are a few extra symbols which do not follow this rule but we'll get to that in a bit.

> ###Example
> `a` will match "c`a`t" and "p`a`tch" but not "dog"

###2. Special characters aka Metacharacters

These characters are special and cannot be used to match for that character. However, if you need to match the literal character you need to use an escape character, `\\`, in front of the metacharacter.

	> ###Example
	> Match: ?
	> String: Are you a hacker?
	> Use: \?
	> Result: Are you a hacker`?`

Here are all the metacharacters: `\`, `^`, `$`, `.`, `|`, `?`, `*`, `+`, `(`, `)`, `[ and ]`, and `{ and }`.

+ `\` - The escape character. You'll need it for the next few symbols.

	> Match: \
	> String: C:\Windows
	> Use: \
	> Result: <code>C:**\**Windows</code>

+ `^` - The caret. It matches at the beginning of a string or line.

	> Match: First instance of `he`
	> String: `heavyheaded`
	> Use: `^he`
	> Result: <pre><b>he</b>avyheaded</pre>
	
+ `$` - The dollar sign. It matches at the end of a string or line.

	> Add

+ `.` - The period. Or dot. Matches any character you can think of.

	> Add

+ `|` - The pipe. Or logical OR. Used in conjunction with `(` and `)`

	> Add

+ `?` - Indicates an optional character (or group).

	> Add

+ `*` - Indicates **zero or more repetitions** of a character (or group).

	> Add

+ `+` - Indicates **one or more repetitions** of a character (or group).

	> Add

+ `[ ]` - Indicates a group of characters

	> rework these later
	> [abc] - abc
	> [^abc] - not abc
	> [a-z] - a through z

+ `{ }` - A specified number of repetitions

	> rework later
	> {n} - n repetitions
	> {n, m} - n to m repetitions

+ `(` and `)` - Captures variables.

	> Add  stuff here but we probably wont need it much




###2. POSIX Specific items

----------------------------------
