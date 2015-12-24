Preprocess
=============

Description
------------

It's part of my diploma, which makes the processing of the text prior to syntaxing analysis.

######	Сheckers

This part provide inspection of stylistic mistakes.
But also some stylistic mistakes are checked after syntaxing analysis, such as name checking.

[I'm	an	inline-style	link	with	title](https://www.google.com	"Google's	Homepage")

This	is	[an	example]	[id]	reference-style	link
[id]:	http://example.com/		"Optional	Title	Here"

#	Inline 
![Alternative	text](/path/to/img.jpg	"Optional	title")

#	Reference 
![Alternative	text][id]
[id]:	url/to/image		"Optional	title"


This	is	a	normal	paragraph:
	This	is	a	code	block.
	
This	is	a	`inline	code	block`

```sql
var	a	=	{};
```


Markdown | Less	| Pretty 
--- | --- | ---
*Still*	| `renders` | **nicely**
1 | 2 |	3


| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
] col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
} zebra stripes | are neat      |    $1 |
