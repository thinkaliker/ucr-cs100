#Regular Expressions


This is a general overview on regular expressions, commonly shortened to "regex".

This tutorial will cover the basics of regex, but more specifically, **POSIX regex**.

<a name="top"/>
##Table of Contents
[1. What is it?](#what)    
[2. Basic characters/Literal characters](#literal)    
[3. Special/Metacharacters](#meta)    
[4. Escaped literals](#escaped)    
[5. POSIX specific syntax](#posix)    
[6. Additional resources](#resources)    

<a name="what"/>
###What is Regex?

Regex is a short pattern of letters and symbols which has can match certain strings. Depending on the environment these strings are parsed in, you can match multiple instances or a single instance of a pattern. Regular regex returns the **first** matching string that it finds. Regex is most commonly used for searching and replacing string patterns, and while this may not be the only use, it is very powerful because of the syntax behind regex.

[Back to table of contents](#top)

<a name="literal"/>
###Basic Characters aka Literal Characters

Any letter or character `a-z`, `A-Z`, `0-9` by itself will match a single instance of that character. There are a few extra symbols which do not follow this rule but we'll get to that in a bit.

####Example
`a` will match "c **_a_** t " and "p **_a_** tch" but not "dog"

[Back to table of contents](#top)

<a name="meta"/>
###Special Characters aka Metacharacters

These characters are special and cannot be used to match for that character. However, if you need to match the literal character you need to use an escape character, `\\`, in front of the metacharacter.

Match: `?`    
String: Are you a hacker?    
Use: `\?`    
Result: Are you a hacker **_?_**    

Here are all the metacharacters: `\`, `^`, `$`, `.`, `|`, `?`, `*`, `+`, `(`, `)`, `[ and ]`, and `{ and }`.
+ `\` - The escape character. You'll need it if you want to match the literal character for all of the next few symbols.

Match: `\`    
String: C:\Windows    
Use: `\`    
Result: C: **_\_** Windows    

+ `^` - The caret matches at the beginning of a string or line.  `$` - The dollar sign matches at the end of a string or line.

Match: First instance of `he`    
String: heavyheaded    
Use: `^he`    
Result: **_he_**avyheaded    
	
Match: Last instance of `cess`    
String: sucessful success    
Use: `cess$`    
Result: sucessful suc **_cess_**    

+ `.` - The period. Or dot. Matches any character you can think of.

Match: Any character (it matches the first character)    
String: sample text    
Use: `.`    
Result: **_s_** ample text    

+ `?` - Indicates an optional character (or group).

Match:  Anything with `and`    
String: sand    OR    hand    
Use: `?and`    
Result: s **_and_**    OR    h **_and_**    

+ `*` - Indicates **zero or more repetitions** of a character (or group). `+` - Indicates **one or more repetitions** of a character (or group).

Match: Match `el` or `e`    
String: shell feet    
Use: `el*`    
Result: sh **_el_** l  f **_e_** et   
	
Match: Match `is` or `iss`    
String: this hiss    
Use: `is+`    
Result: th **_is_** h **_iss_**    

+ `|` - The pipe. Or logical OR. Used inside of `(` and `)`. This is important because without the `|` the parenthesis means something else entirely. (see below)

Match: Match `cats` or `dogs`    
String: I like cats and dogs    
Use: `(cat|dog)`     
Result: I like **_cat_** s and **_dog_** s    

+ `[ ]` - Indicates a group of characters to match. Adding a `^` in front of the characters indicates not those characters.

Match: Match `pan` and `fan` and `tan` but not `man`, `can` or `dan`    
String: pan fan tan man can dan    
Use: `[pft]` OR `[^mcd]`     
Result: **_pan fan tan_** man can dan    

NOTE: The brackets can use ranges, which is what they are commonly known for.

Match: Match any uppercase letter    
String: fkjdsklajfKSDFJLKFJDFK    
Use: `[A-Z]`     
Result: fkjdsklajf **_KSDFJLKFJDFK_**    

+ `{ }` - A specified number of repetitions

`{n}` - Only matches n repetitions or more

Match: Match `weeeee` but not `flee`     
String: weeee flee   
Use: `e{3}`     
Result: **_weeee_** flee    

`{n, m}` - Only matches no more than `m` repetitions but no less than `n` repetitions

Match: Match `weee` but not `leeeee` or `less`     
String: leeeee weee less   
Use: `e{2,3}`     
Result: leeeee **_weee_** less    

+ `(` and `)` - Captures variables. It isn't used in POSIX regex much.

Match: Capture only the file name without extension     
String: reallylegitpicture.png   
Use: `^(.+)\.png$`     
Result: Captured: **_reallylegitpicture_**     

[Back to table of contents](#top)

<a name="escaped"/>
###Table of Escaped Literals

These are used to indicate special characters or characteristics. These are **case sensitive**.

Symbol | Explaination
-------|-------------
 `\d`  |  Any digit
 `\D`  |  Any **non**-digit character
 `\s`  |  Any whitespace
 `\S`  |  Any **non**-whitespace character
 `\w`  |  Any alphanumeric character
 `\W`  |  Any **non**-alphanumeric character

[Back to table of contents](#top)

<a name="posix"/>
##POSIX Specific Syntax

There are a few key differences  POSIX standard says that the **longest** match is returned. Normal regex usually stops with the **first** match found. However, it will still match the **leftmost** result.

Match: GetStatus     
String: GetStatus Get   
Use: `Get`     
Result: **_GetStatus_** Get    

Match: SetStatus     
String: Set SetStatus   
Use: `(Set|SetStatus)`     
Result: Set **_SetStatus_**   

Additionally, every metacharacter except `?` and `+` require escaping  with `\` for use as a metacharacter (`+` and `?` are not part of POSIX standards). Without escaping, those metacharacters are interpreted literally.

[Back to table of contents](#top)

<a name="resources"/>
##Additional Resources
http://regexone.com is an excellent learning tool which provides an interactive tutorial which walks through the basics of regex.    
http://www.regular-expressions.info has many pages dedicated to both quickly learning regex and POSIX specific regex.

[Back to table of contents](#top)

----------------------------------
