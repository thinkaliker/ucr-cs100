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

These characters are special and cannot be used to match for that character. However, if you need to match the literal character you need to use an escape character, `\`, in front of the metacharacter.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep '\['
Array[5]
Array<strong><em>[</em></strong>5]</code></pre>
    </td>
    <td>
    <pre><code>$ grep '\\'
C:\Windows
C:<strong><em>\</em></strong>Windows</code></pre>
    </td>
  </tr>
</table> 

Here are all the metacharacters:
<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>\^$.*[]</code></pre>
    </td>
    <td>
    <pre><code>\^$.|?*+()[]{}</code></pre>
    </td>
  </tr>
</table> 
+ `\` - The escape character. You'll need it if you want to match the literal character for all of the next few symbols.

+ `[ ]` - Indicates a group of characters to match. Adding a `^` in front of the characters indicates not those characters.

<table>
  <tr>
    <th>Example</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep '[pft]a[^rtp]'
pan fan tan man par tap fat
<strong><em>pan fan tan</em></strong> man par tap fat</code></pre>
    </td>
  </tr>
</table>  

NOTE: The brackets can use ranges, which is what they are commonly known for.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep '[A-Z]'
abcdefgABCEFG
abcdefg<strong><em>ABCEFGv</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ grep '[2-5c-g]'
012345678abcdefghi
01<strong><em>2345</em></strong>678ab<strong><em>cdefg</em></strong>hi</code></pre>
    </td>
  </tr>
</table>   

+ `.` - The period. Or dot. Matches any character you can think of.

<table>
  <tr>
    <th>Example 1</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep '.'
abcDEF123!@#[]
<strong><em>abcDEF123!@#[]</em></strong></code></pre>
    </td>
  </tr>
</table>

+ `^` - The caret matches at the beginning of a string or line.  `$` - The dollar sign matches at the end of a string or line.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep '^he'
heavyheaded
<strong><em>he</em></strong>avyheaded</code></pre>
    </td>
    <td>
    <pre><code>$ grep 'cess$'
successful success
successful suc<strong><em>cess</em></strong></code></pre>
    </td>
  </tr>
</table>

+ `*` - Indicates **zero or more repetitions** of a character (or group). `+` - Indicates **one or more repetitions** of a character (or group).

<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep 'el*s'
shell
sh<strong><em>ells</em></strong> fe<strong><em>es</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ egrep 'is+'
hi this hiss
hi th<strong><em>is</em></strong> h<strong><em>iss</em></strong></code></pre>
    </td>
  </tr>
</table>

+ `?` - Indicates an optional character (or group). It is extended posix only. Use `\{0,1\}` in standard posix.

<table>
  <tr>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ egrep 'colou?r'
color colour
<strong><em>color colour</em></strong></pre>
    </td>
  </tr>
</table>

+ `|` - The pipe. Or logical OR. Best used inside of `(` and `)`. You must escape in standard Posix
<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep 'cat\|dog'
I like cats and dogs 
I like <strong><em>cat</em></strong>s and <strong><em>dog</em></strong>s</code></pre>
    </td>
    <td>
    <pre><code>$ egrep 'to(day|morrow)'
today or tomorrow
<strong><em>today</em></strong> or <strong><em>tomorrow</em></strong>
    </td>
  </tr>
</table>

+ `{ }` - A specified number of repetitions

`{n}` - Matches exactly n repetitions    
`{n,}` - Matches n or more repetitions    
`{n, m}` - Matches no more than `m` repetitions but no less than `n` repetitions    
The brackets must be escaped in standard regex

<table>
  <tr>
    <th>Posix</th>
    <th>Extended Posix</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep 'we\{3\}'
weee
<em><strong>weee</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ egrep 'ya{2,5}y'
yaaaay
<em><strong>yaaaay</em></strong></code></pre>
    </td>
  </tr>
</table>

+ `(` and `)` - Captures variables and creates character groups.    
The parenthesis must be escaped in standard regex

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep '\(.*\)\.jpg'
Image012.jpg
<em><strong>Image012.jpg</em></strong>
#Image012 is in capture group 1</code></pre>
    </td>
    <td>
    <pre><code>$ egrep '(a.)+'
a1a2a3
<em><strong>a1a2a3</em></strong></code></pre>
    </td>
  </tr>
</table>

+ `\n` - refers back to the nth capture group. This does not exist in Extended Regex.

<table>
  <tr>
    <th>Example 1</th>
    <th>Example 2</th>
    <th>sed Example</th>
  </tr>
  <tr>
    <td>
    <pre><code>$ grep '\(...\) \1'
cat cat
<em><strong>abc abc</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ grep '\(a\(.+\)\)d \1 \2'
ago ag a OR amend amen men
<em><strong>ago ag a</em></strong> OR <em><strong>amend amen men</em></strong></code></pre>
    </td>
    <td>
    <pre><code>$ sed 's/"\([^"]*\)"/&lt;\1>/g'
"head" "body"
&lt;head> &lt;body></code></pre>
    </td>
  </tr>
</table>


[Back to table of contents](#top)

<a name="escaped"/>
###Table of Escaped Literals

These are used to indicate special characters or characteristics. These are **case sensitive**.
Escaped Symbols are only in **Extended Posix**.

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
