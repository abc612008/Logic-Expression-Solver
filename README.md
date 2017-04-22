# Logic-Expression-Solver
A tool that can calculate all possible values for variables in a logic expression.

Support &, |, (, ), !.

## Example

```
Input expression: a&b|c
a:True  b:True  c:Any
a:True  b:False c:True
a:False b:True  c:True
a:False b:False c:True

Input expression: a&(!b|a)
a:True  b:Any

Input expression: a&(b|!a)
a:True  b:True
```

## How to compile

It should be cross-platform, but I have only tested it under Windows.

I am too lazy to write a makefile so please DIY. Sorry!

## License

MIT License.