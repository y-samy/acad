#import "lib.typ": *
#import "@preview/cetz:0.2.2": canvas, plot

#set page(paper: "a3", flipped: true, margin: 1cm)
#set text(font: "Arial", size: 16pt)

#show: cram-snap.with(
  title: [Series Summary],
  subtitle: [Summary for the series part of the Maths 2 course.\ Made with #emoji.heart.black by Youssef Samy using Typst.],
  column-number: 3,
)
#show math.equation.where(block: true): it => align(start, block(it))
== Sigma Notation
=== Basic Series
#table(
    table.header[],
    [$ sum_(i=n)^m C $ ], [$ = C dot (m-n+1) $],
    [$ sum_(i=n)^m i $], [$ = cases(f_1(m) &space "if " n in {0,1}, f_1(m)-f_1(n-1) &space "else") $],
    [$ sum_(i=n)^m i^2 $], [$ = cases(f_2(m) &space "if " n in {0,1}, f_2(m)-f_2(n-1) &space "else") $],
    [$ sum_(i=n)^m i^3 $], [$ = cases(f_3(m) &space "if " n in {0,1}, f_3(m)-f_3(n-1) &space "else") $],
    [$ sum_(i=n)^m a^i $], [$ = cases(g(a, m+1) &space "if" n=0, m+1 &space "if" n=0 "," a=1, g(a, m+1)-g(a,n) &space "else") $],
)
=== Index Manipulation
#table(
    table.header[],
    [$ sum_(&i=0\ i&:"even") $], [$ i = 2k $],
    [$ sum_(&i=1\ i&:"odd") $], [$ i = 2k plus.minus 1$],
    [$ sum_(i=3)^10 i^2 $], [$ = sum_(i=1)^8 (i+2)^2 = sum_(i=1)^8 i^2 + 4i + 4 $],
    [$ sum_(i=n)^m a^i $], [$ script(i=k+n) arrow sum_(k+n=n)^(k+n=m) a^(k+n) &= sum_(k=0)^(k=m-n) a^n dot a^k \ &= a^n dot g(a, m-n + 1) $],
)
#colbreak()
== Infinite Series
=== Famous Infinite Series
#table(
  table.header([]),
  [$ sum_(n=0)^infinity a^n $], [Geometric Series\ $ cases(abs(a) < 1 &space "converges", abs(a) >= 1 &space "diverges") $],
  [$ sum_(n=1)^infinity 1/n $], [Harmonic Series\ $"diverges"$],
  [$ sum_(n=1)^infinity 1/n^p $], [P Series\ $ cases(P>1 &space "converges", P<=1 &space "diverges") $],
  [$ C plus.minus C $], [$ = C $],
  [$ C plus.minus D $], [$ = D $],
  [$ D + D $], [$ = D $],
  [$ D - D $], [$ = "?" $],
)
=== Strength of terms
#table(
  table.header([]),
  [Most], [$ f^n (n) : n^n, ln(n)^n $],
  [], [$ n! $],
  [], [$ a^n $],
  [], [$ n^a $],
  [], [$ log_a (n), ln(n) space : space log_n > log_m " if " m>n $],
  [], [$ a $],
  [Least], [$ cases(a^n &space space a<1, a^(-n) &space space a>1) $]
)
=== Series Tests
#table(
  table.header([]), columns: (4.5cm, auto),
  [General Term], [$ lim_(n->oo) U_n cases(!= 0 &space "diverges", = 0 &space "test fails") $],
  [Integral], [$ integral_i^oo U_n cases("number" &space "converges", plus.minus oo &space "diverges") $],
  [$ "Alternating Series"\ "for" sum^(n=oo) (-1)^n b_n $], [$ lim_(n->oo) b_n cases(=0 &space "converges", !=0 &space "diverges") $],
  [$ "Root"\ "for" sum^(n=oo) (f(n))^n $], [$ lim_(n->oo) f(n) cases(<1 space "converges", >1 space "diverges", =1 space "test fails") $],
  [$ "Ratio"\ 2^n,n,n^2,n!\ "in" U_n $], [$ lim_(n->oo) abs(U_(n+1) / U_n) cases(<1 "converges", >1 "diverges", =1 "test  fails") $],
  [Comparison], [$ "Choose known" V_n "to compare"\ V_n cases("convergent" &cases(U_n<V_n "conv.", U_n>V_n "fail")\ , "divergent" &cases(U_n<V_n "fail", U_n>V_n "div.")) $],
  [Limit Comparison], [$ lim_(n->oo) U_n/V_n "or" V_n/U_n \ cases(=0 &"fail", =oo &"fail", "else" &U_n "as" V_n) $],
  [Partial Sum\ $ S_n = sum_(i=1)^n U_i $], [$ lim_(n->oo) S_n cases("number" &space "conv.", oo &space "div.", "oscillating" &space "div.") $]
)
=== Power Series
$ sum_(n=0)^oo a_n (x-x_0)^n = a_0 + a_1 (x-x_0) + a_2 (x-x_0)^2 ... $
Series is convergent for all $x in "I.C" $
$ lim_(n->oo) abs(U_(n+1)/U_n)<1 "all values of" x "satisfying the"\ "inequality define the I.C, but the boundaries must"\ "be tested separately with other tests." $
== Taylor & Maclaurin Series
=== Maclaurin Expansion
$ "I.C = " RR "in elementary functions"\ "about" x = 0 $
#table(
  table.header([]),
  [$ f(x) $], [$ = f(0) + (f prime (0))/1! x + (f prime prime (0))/2! x^2 + (f prime prime prime (0))/3! x^3 + ... $],
  [$ e^x $], [$ = sum_(n=0)^oo 1/n! x^n = 1 + x + x^2/2! + x^3/3! + ... $],
  [$ sin(x) $], [$ = sum_(n=0)^oo (-1)^n/(2n+1)! x^(2n+1) = x - x^3/3! + x^5/5! - ... $],
  [$ cos(x) $], [$ = sum_(n=0)^oo (-1)^n/(2n)! x^(2n) = 1 - x^2/2! + x^4/4! - ... $],
  [$ sinh(x) $], [$ = sum_(n=0)^oo 1/(2n+1)! x^(2n+1) = x + x^3/3! + x^5/5! + ... $],
  [$ cosh(x) $], [$ = sum_(n=0)^oo 1/(2n)! x^(2n) = 1 + x^2/2! + x^4/4! + ... $]
)
=== Taylor Expansion
$ f(a), (x-a) "(about " x = a ")" \ abs(x-a)<1\ "I.C determined using ratio test" $
#table(
  table.header([]),
  [$ f(x) $],[$ = f(a) + (f prime (a))/1! (x-a) + (f prime prime (a))/2! (x-a)^2 + ... $]
)

== Binomial Series
=== Combinatorics
#table(
  table.header([]), columns: (5cm, 8cm),
  [$ attach(C, tl: n, br: r) = n!/(r! (n-r)!) $], [$ n>=r, attach(C, tl: n, br: a) = attach(C, tl: n, br: n-a) $]
)
=== Binomial Expansion: Positive Integer $n$
#sym.hash of terms $= n+1$\
$"I.C" : x in RR$
#table(
  table.header([]), columns: (3cm, 10cm),
  [$ (1+x)^n $], [$ = 1 + attach(C, tl: n, br: 1)x + attach(C, tl: n, br: 2)x^2 + attach(C, tl: n, br: 3)x^3 + ... + x^n $],
  [General Term], [$ attach(C, tl: n, br: r) x^r $]
)
=== Binomial Expansion: Negative or Fraction $n$
#sym.hash of terms $= oo$\
$"I.C" : abs(x) < 1$
#table(
  table.header([]), columns: (3cm, 10.5cm),
  [$ (1+x)^n $], [$=1 + n x + n(n-1)/2! x^2 + (n(n-1)(n-2))/3! x^3 + ... $],
  [$ (1-x)^(-1) $], [$ = x^r = 1 + x + x^2 + x^3 + ... $],
  [$ (1+x)^(-1) $], [$ = (-1)^r x^r = 1 - x + x^2 - x^3 + ... $],
  [$ (1-x)^(-2) $], [$ = (r+1) x^r = 1 + 2x + 3x^2 + 4x^3 + ... $],
  [$ (1+x)^(-2) $], [$ = (-1)^r (r+1) x^r = 1 - 2x + 3x^2 - ... $]
)
== Fourier Series
#table(
  table.header([]),
  [$ f(x) $], [$f(x) "is a periodic function with period" p$$ &= f(x+p)\ &= A + sum_(n=1)^oo a_n cos(n omega_0 x) + b_n sin(n omega_0 x) $],
  [$ f_"DC" $], [$ "DC Component":\ = cases(A  = ("area of" f(x))/"length of period", "avg of" f(x)) $],
  [$ f_"AC" $], [$ "AC Component":\ = cases( sum_(n=1)^oo a_n cos(n omega_0 x) + b_n sin(n omega_0 x), f(x) - A) $],
)
#colbreak()
=== General Definitions
#table(
  table.header([]),
  [$ omega_0 $], [$ = (2pi)/p = 2pi f $],
  [$ a_0 $], [$ = 1/("half period") limits(integral)_#box(width: 1em, [full~period], inset: (x: -14pt, y: 1pt)) f(x) dif x $],
  [$ A $], [$ = 1/("full period") limits(integral)_#box(width: 1em, [full~period], inset: (x: -14pt, y: 1pt)) f(x) dif x = a_0/2 $],
  [$ a_n $], [$ = 1/("half period") limits(integral)_#box(width: 1em, [full~period], inset: (x: -14pt, y: 1pt)) f(x) dot cos(n omega_0 x) dif x $],
  [$ b_n $], [$ = 1/("half period") limits(integral)_#box(width: 1em, [full~period], inset: (x: -14pt, y: 1pt)) f(x) dot sin(n omega_0 x) dif x $]
)
#let fn = (stroke: black, fill: rgb(0, 0, 200, 75))
#let negfn = (stroke: black, fill: rgb(200, 0, 0, 75))
#let dotted = (stroke : (dash: "loosely-dash-dotted", paint: rgb(0, 0, 0)))
=== Extra Notes
- A function can be shifted horizontally to be able to see its periodic nature, but it can't be shifted vertically.
- If $x$ is not defined at the boundaries, for example:
$-3<x<0 "and" 0<x<3$\ if $f(x_0)$ is needed (here $x_0$ can be $-3,0,3$)
$ f(x_0) = (f(x_0^+) + f(x_0^-))/2 $
- Sine and cosine properties for simplification:
$ sin(n pi) &= 0\ cos(n pi) &= (-1)^n\
sin((n pi)/2) &= cases(0 &n : "even", (-1)^((n-1)/2) space space &n : "odd" )\ cos((n pi)/2) &= cases(0 &n : "odd", (-1)^(n/2) space space space space &n : "even") $
#colbreak()
=== Generalization for Special Cases
$ A = "area of one sub-repetition"/"length of one sub-repetition" $
$ mu &= "length of smallest sub-repetition"\ &= cases(p &"generally", p\/2 space space &"sines/cosines only, even/odd harmonic", p\/4 space space &"combinations of two of the above") $
$ A = 1/mu dot integral_0^mu f(x) dif x\ 
a_n = 2/mu integral_0^mu f(x) dot cos(n omega_0 x) dif x\
b_n = 2/mu integral_0^mu f(x) dot cos(n omega_0 x) dif x $
=== Special Cases
Special cases of the fourier series may include one or two specifically oriented repetitions within one period. For example, in a cosines-only function, one half of the period is mirrored in the other half.\ In the following examples and drawings, the center of the period is assumed to be the origin.\
Whenever that is not the case, you should either shift the origin to be at the center of the period, or replace all the short forms like:
$ a_n = 1/(p\/2) integral_0^(p) f(x) dot cos(n omega_0 x) dif x $
with their original form, as in:
$ a_n = 1/("half period") limits(integral)_#box(width: 1em, [full~period], inset: (x: -14pt, y: 1pt)) f(x) dot cos(n omega_0 x) dif x $
#colbreak()
=== Cosines Only (Even Function)
The first special case. The function is mirrored on the $y$-axis within one period. Example:
$ f(x) = cases(x\, space &0 &< x &< 3, -x\, space -&3 &< x &< 0) $
#canvas(length: 1cm, {

  plot.plot(size: (8, 3),
    x-tick-step: none,
    x-ticks: (-3, 3),
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        hypograph: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: fn,
        domain: (-3,0),
        y=>-y
      )
    })
})
*Properties*\
Only even components. $b_n=0$
$ f(x) &= f(-x) = f(x+p)\ &= A + sum_(n=1)^oo a_n cos(n omega_0 x) dif x $
$ a_n = 2/(p\/2) integral_0^(p\/2) f(x) dot cos(n omega_0 x) dif x $
$ A &= "highlighted area (half period)"/("half period length")\ &= a_0/2 = 1/2 dot 2/(p\/2) integral_0^(p\/2) f(x) dif x $
#colbreak()
=== Sines Only (Odd Function)
The function is mirrored on the $y$-axis then flipped on the $x$-axis, within one period.
Example:
$ f(x) = x, -3 < x < 3 $
#canvas(length: 1cm, {

  plot.plot(size: (8, 6),
    x-tick-step: none,
    x-ticks: (-3, 3),
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (-3,0),
        y=>y
      )
      plot.add(
        style: dotted,
        domain: (-3,0),
        y=>-y
      )
    })
})
*Properties*\
Truly sines only.\
Because $A$ is an even component, $A=0$ here. It can also be proven
from the fact that the area over the full period will be $0$.
$ f(x) &= -f(-x) = f(x + p) \ &= sum_(n=1)^oo b_n sin(n omega_0 x) $
$ A = 0, a_0 = 0, a_n = 0\
b_n = 2/(p\/2) integral_0^(p\/2) f(x) dot sin(n omega_0 x) dif x $
#colbreak()
=== Even Harmonic
The function is repeated twice in one period.\  $n$ is even. Example:
$ f(x) = cases(x\, space &0 &< x &< 3, x+3\, space -&3 &< x &< 0) $
#canvas(length: 1cm, {

  plot.plot(size: (8, 3),
    x-tick-step: none,
    x-ticks: (-3, 3),
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: fn,
        domain: (-3,0),
        y=>y+3
      )
    })
})
*Properties*
$ f(x) &= f(x+p) = f(x + p/2)\ &= A + sum_(n:"even")^oo a_n cos(n omega_0 x) + b_n sin(n omega_0 x) $ 
$ A &= "highlighted area (half period)"/"half period length" \
&= a_0/2 = 1/2 dot 2/(p\/2) integral_0^(p\/2) f(x) dif x $
$ a_n = 2/(p\/2) integral_0^(p\/2) f(x) dot cos(n omega_0 x) dif x\
b_n = 2/(p\/2) integral_0^(p\/2) f(x) dot sin(n omega_0 x) dif x $
#colbreak()
=== Odd Harmonic
The function is repeated twice in one period, but will be flipped about the $x$-axis every other repetition. $n$ is odd. Example:
$ f(x) = cases(x\, space &0 &< x &< 3,
 -3-x\, space -&3 &< x &< 0) $
#canvas(length: 1cm, {

  plot.plot(size: (8, 6),
    x-tick-step: none,
    x-ticks: (-3, 3),
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: dotted,
        domain: (-3, 0),
        y=>y+3
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (-3,0),
        y=>-y -3
      )
    })
})
*Properties*
$ f(x) &= f(x + p) = -f(x+p/2) \ &= sum_(n:"odd")^oo a_n cos(n omega_0 x) + b_n sin(n omega_0 x) $
$ A = 0 "(from graph)", a_0 = 0\
a_n = 2/(p\/2) integral_0^(p\/2) f(x) dot cos(n omega_0 x) dif x\
b_n = 2/(p\/2) integral_0^(p\/2) f(x) dot sin(n omega_0 x) dif x $

#colbreak()
=== Even Cosines
Mirror about $y$-axis, then repeat after half-period.
Example:
$ f(x) = cases(6+x\, space -&6 &< x &< -3, -x\, space space space space -&3 &< x &< 0, x\, space &0 &< x &< 3,6-x\, space &3 &< x &< 6) $
#canvas(length: 1cm, {

  plot.plot(size: (12, 3),
    x-tick-step: 3,
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: fn,
        domain: (-3,0),
        y=>-y
      )
      plot.add(
        style: fn,
        domain: (3, 6),
        y=>-y+6
      )
      plot.add(
        style: fn,
        domain: (-6, -3),
        y=>y+6
      )
    })
})
_or_
#canvas(length: 1cm, {

  plot.plot(size: (12, 3),
    x-tick-step: 3,
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: fn,
        domain: (-3,0),
        y=>-y
      )
      plot.add(
        style: fn,
        domain: (3, 6),
        y=>-y+6
      )
      plot.add(
        style: fn,
        domain: (6, 9),
        y=>-6+y
      )
    })
})
*Properties*
$ f(x) &= f(-x) = f(x + p) = f(x + p/2)\
&= A + sum_(n:"even")^oo a_n cos(n omega_0 x) + b_n sin(n omega_0 x)\ A &= a_0/2 = 1/2 dot 4/(p\/2) integral_0^(p\/4) f(x) dif x\
a_n &= 4/(p\/2) integral_0^(p\/4) f(x) cos(n omega_0 x) dif x\
b_n &= 2/(p\/2) integral_0^(p\/4) f(x) sin(n omega_0 x) dif x $
#colbreak()
=== Odd Cosines
Mirror about $y$-axis, then repeat flipped about $x$-axis after half-period.
Example:
$ f(x) = cases(-x-6\, space -&6 &< x &< -3, -x\, space space space space space space -&3 &< x &< 0, x\, space &0 &< x &< 3,x-6\, space &3 &< x &< 6) $
#canvas(length: 1cm, {

  plot.plot(size: (12, 6),
    x-tick-step: 3,
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: fn,
        fill: true,
        domain: (-3,0),
        y=>-y
      )
      plot.add(
        style: dotted,
        domain: (3, 6),
        y=>6-y
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (3, 6),
        y=>-6+y
      )
      plot.add(
        style: dotted,
        domain: (-6, -3),
        y=>y+6
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (-6, -3),
        y=>-6-y
      )
    })
})
_or_
#canvas(length: 1cm, {

  plot.plot(size: (12, 6),
    x-tick-step: 3,
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: fn,
        fill: true,
        domain: (-3,0),
        y=>-y
      )
      plot.add(
        style: dotted,
        domain: (3, 6),
        y=>6-y
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (3, 6),
        y=>-6+y
      )
      plot.add(
        style: dotted,
        domain: (6, 9),
        y=> -6+y
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (6, 9),
        y=>6-y
      )
    })
})
$ f(x) &= f(-x) = f(x + p) = -f(x + p/2)\
&= sum_(n:"odd")^oo a_n cos(n omega_0 x) + b_n sin(n omega_0 x) $
$ a_n "and" b_n "are the same as those in even cosines" $
#colbreak()
=== Even Sines
Mirror about $y$-axis then flip about $x$-axis. Then repeat after half-period.
$ f(x) = cases(x\, space& &0 &< x &< 3, x-6\, space& &3 &< x &< 9) $
#canvas(length: 1cm, {

  plot.plot(size: (12, 6),
    x-tick-step: 3,
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: fn,
        fill: true,
        domain: (-6, -3),
        y=>y+6
      )
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (-3,0),
        y=>y
      )
      plot.add(
        style: dotted,
        domain: (-3,0),
        y=>-y
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (3, 6),
        y=>-6+y
      )
      plot.add(
        style: dotted,
        domain: (3, 6),
        y=>6-y
      )
      plot.add(
        style: fn,
        domain: (6, 9),
        y=>-6+y
      )
    })
})
$ f(x) &= -f(-x) = f(x+p) = f(x+p/2)\ 
&=  sum_(n:"even")^oo b_n sin(n omega_0 x) $
$ b_n = 4/(p\/2) integral_0^(p\/4) f(x) dot sin(n omega_0 x) dif x $
#colbreak()
=== Odd Sines
Mirror about $y$-axis, then flip about $x$-axis. Then repeat flipped after half-period.
$ f(x) = cases(x\, space& &0 &< x &< 3, 6-x\, space& &3 &< x &< 9) $
#canvas(length: 1cm, {

  plot.plot(size: (12, 6),
    x-tick-step: 3,
    y-tick-step: 1,
    axis-style: "school-book",
    {
      plot.add(
        style: negfn,
        fill: true,
        domain: (-6, -3),
        y=>-6-y
      )
      plot.add(
        style: fn,
        fill: true,
        domain: (0, 3),
        y=>y
      )
      plot.add(
        style: negfn,
        fill: true,
        domain: (-3,0),
        y=>y
      )
      plot.add(
        style: dotted,
        domain: (-6,-3),
        y=>y+6
      )
      plot.add(
        style: dotted,
        domain: (3, 6),
        y=>-6+y
      )
      plot.add(
        style: fn,
        fill: true,
        domain: (3, 6),
        y=>6-y
      )
      plot.add(
        style: dotted,
        domain: (6, 9),
        y=>-6+y
      )
        plot.add(
        style: negfn,
        domain: (6, 9),
        y=>-y+6
      )
    })
})
$ f(x) &= -f(-x) = f(x+p) = -f(x+p/2)\ 
&=  sum_(n:"odd")^oo b_n sin(n omega_0 x) $
$ b_n = 4/(p\/2) integral_0^(p\/4) f(x) dot sin(n omega_0 x) dif x $

