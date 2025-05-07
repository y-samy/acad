#import "@preview/unify:0.7.0":*

#import "@preview/cetz:0.3.1" as cetz: *

#import "@preview/cetz-plot:0.1.0"

#let title = "Lab 1 Report\n EXAMPLE DOCUMENT"
#let authors = (
  (
    name: "Youssef Samy",
  ),
)
#set document(
    title: title, 
    author: authors.map(author => author.name)
)

#let organization = "Faculty of Engineering, Alexandria University\n Computer & Communications Program"
#let course-abrev = "EEC116"
#let course-name = "Analysis of Electrical Circuits"
#let experiment = "Low Pass Filters & High Pass Filters"
#set page(
    footer: context [#datetime.today().display()],
    paper: "a4",
  )

#align(center, text(20pt)[#smallcaps[
    #organization
  ]])
#v(1fr)
  #align(center, text(17pt)[#smallcaps[
    #course-abrev \ #course-name
  ]])
  #align(center, pad(y:0.5em,text(26pt)[
    #title
  ]))

    #align(center, text(17pt)[#smallcaps[
    #experiment
  ]])


#let auths = authors.map(auth=>[
    #auth.name \ 
    #if auth.keys().contains("id") {
      auth.id
    }
])

#let author-columns = 4

#let auths-align = auths.slice(
    0,
    auths.len() - calc.rem(auths.len(), author-columns)
)
#let auths-rest = auths.slice(
    auths.len() - calc.rem(auths.len(), author-columns)
  )

#v(1fr)
#grid(
      align:center,
      gutter: 1.5em,
      columns: (1fr,)*author-columns,
      grid.cell(colspan:author-columns,
        text(14pt,smallcaps(align(center)[*Author*]))
      ),
      ..auths-align,
      if calc.rem(auths.len(),author-columns) != 0 {grid.cell(
        colspan:author-columns,
        grid(
          columns: (1fr,)*auths-rest.len(),
          column-gutter: 3em,
          ..auths-rest
        )
      )}
    )
#v(2fr)
#pagebreak()
#counter(page).update(1)
#set page(footer: context [
    #h(1fr)
    #counter(page).display("1")]
)
#set text(hyphenate: true)
#set par(justify: true)


*_Abstract_---This lab report follows two experiments on each of Low and High Pass Filter circuits and frequency response in them. The theoretical transfer function will be compared to experimental and simulation data by plotting the magnitude of voltage gain $abs(V_"out"/V_"in")$ against frequency $("Hz")$ and/ or finding the cut-off frequency $F_"c"$ of each*

#set heading(numbering: "1.1.")
= Low Pass Filters

== The Circuit
The LPF in @lpf-circ is a schematic of the circuit connected to a function generator with the input voltage set to $10"V"_"p.p" " " [5"V"_max]$, and the output voltage measured across the $0.1 mu "F" $ capacitor.

#figure(image("Graphics/LPF Circuit.svg", scaling: "smooth", width: 50%), caption: [LPF circuit given in lab]) #label("lpf-circ")
== Theoretical Frequency Response
The transfer function $display(H(omega) = V_"out"/V_"in")$ can be written as
$ H(omega) = (1 /(j omega C))/(1/(j omega C) + R) = 1/(1 + j omega R C) = 1/(1+0.0001 j omega) $
And the magnitude is given by $ abs(H (omega)) = 1/(sqrt(1 + (omega R C)^2)) $
If we substitute with $omega = 0$ into $abs(H(omega))$, we obtain the maximum value $abs(H_max (omega)) = 1$, and if we substitute with $omega = infinity$, we obtain $abs(H_min (omega)) = 0$.
=== Theoretical Cut-off Frequency
The theoretical cut-off frequency $omega_"c"$ or $F_"c"$ as $F$ is proportional to $omega$, can be obtained at $ abs(H(omega)) = abs(H_max (omega))/sqrt(2) $
Which is $1/sqrt(2)$ in our circuit. Getting the theoretical cut-off frequency $F_"c"_"th"$ is as simple as substituting with $omega = 2 pi F$ into $abs(H(omega)) = 1/sqrt(2)$ $ 1/sqrt(2) = 1/sqrt(1 + (0.0001 times 2 pi F_"c")^2)\ 2 = 1 + (0.0001 times 2 pi F_"c")^2 \ 1/(0.0002 pi)  = F_"c"\ F_"c" = 1591.5 "Hz" $

== Experimental Data
=== Measurements
In the lab, we were tasked with obtaining the voltage gain at the seven frequencies noted in @measurements-lpf.
#figure(table(
    columns: (2fr, 1fr, 1fr, 1fr, 1fr, 1fr, 1fr, 1fr),
    inset: 8pt,
    align: center + horizon,
    row-gutter: 2pt,
    [*Frequency (Hz)*], [1000], [2000], [3000], [4000], [5000], [6000], [7000],
    [*$ abs(V_"o"/V_"in") $*], [0.768], [0.516], [0.38], [0.304], [0.252], [0.216], [0.188]
), caption: "LPF circuit voltage gain measurements") #label("measurements-lpf")

After obtaining the previous measurements, we should sketch the plot and obtain $F_"c"_"exp"$ from it.
=== Plot & Cut-off Frequency
The cut-off frequency can be obtained at $abs(H(omega)) = 1/sqrt(2) approx 0.707$

#figure(image("Graphics/lpf-exp-plot.svg", scaling: "smooth", width:100%),  caption: [Plot of the frequency response in LPF circuits using experimental data]) #label("lpf-exp-plot")

 As seen in @lpf-exp-plot, the cut-off frequency approximately equals $1220 "Hz"$.
#pagebreak()
== Simulated Data
By assembling the circuit in @lpf-circ-sim in NI Multisim, where the voltage is $5 "V"_"pk" = 5 "V"_max$, and by using the "AC Sweep" simulation type to parametrically change the frequency of the voltage source, we can obtain the plot of $V_"out"$ relative to the ground over $V_"in"$ as shown in @lpf-sim-plot.

#figure(image("Graphics/lpf-circ-sim.svg", scaling: "smooth", width: 50%), caption: [LPF circuit used in simulation]) #label("lpf-circ-sim")

#figure(image("Graphics/linear-lpf.svg", scaling: "smooth", width: 100%),  caption: [Linear plot of the frequency response in the simulated LPF circuit from NI Multisim]) #label("lpf-sim-plot")

== Conclusion

#figure(table(
    columns: (1fr, 1fr),
    inset: 3.9pt,
    align: center + horizon,
    [*Scenario*],
    [*$F_c "(Hz)"$*],
    [Theoretical], [$1591.5$],
    [Experimental], [$1209$],
    [Simulated], [$1592$]
), caption: "Cut-off frequencies compared") #label("conc-table-lpf")

In low-pass filter circuits, the components significantly reduce the voltage output as source frequencies rise above the cut-off frequency. The cut-off frequency obtained theoretically approximately matches that obtained from the simulation, with a large disparity to that obtained experimentally due to measurement error.

#pagebreak()

= High Pass Filters

== The Circuit
The HPF in @hpf-circ is a schematic of the circuit connected to a function generator with the input voltage set to $10"V"_"p.p" " " [5"V"_max]$, and the output voltage measured across the $3.9 "mH" $ inductor.

#figure(image("Graphics/hpf-circ.svg", scaling: "smooth", width: 50%), caption: [HPF circuit given in lab]) #label("hpf-circ")
== Theoretical Frequency Response
The transfer function $display(H(omega) = V_"out"/V_"in")$ can be written as
$ H(omega) = (j omega L)/(j omega L + R) = 1/(1 + R/(j omega L)) = 1/(1 - (256.41 times 10^3 j)/omega) $
And the magnitude is given by $ abs(H (omega)) = 1/(sqrt(1 + (R/(j omega L))^2)) $
If we substitute with $omega = 0$ into $abs(H(omega))$, we obtain the minimum value $abs(H_min (omega)) = 0$, and if we substitute with $omega = infinity$, we obtain $abs(H_max (omega)) = 1$.
=== Theoretical Cut-off Frequency
The theoretical cut-off frequency $omega_"c"$ or $F_"c"$ as $F$ is proportional to $omega$, can be obtained at $ abs(H(omega)) = abs(H_max (omega))/sqrt(2) $
Which is $1/sqrt(2)$ in our circuit. Getting the theoretical cut-off frequency $F_"c"_"th"$ is as simple as substituting with $omega = 2 pi F$ into $abs(H(omega)) = 1/sqrt(2)$ $ 1/sqrt(2) = 1/sqrt(1 + (- display(256.41 times 10^3)/display(2 pi F_"c"))^2)\ 2 = 1 + (- display(256.41 times 10^3)/display(2 pi F_"c"))^2 \ 1 = display(256.41 times 10^3)/display(2 pi F_"c")\ F_"c" = (256.41 times 10^3)/(2 pi)  = 40808.9 "Hz" $

== Experimental Data
=== Measurements
In the lab, we were tasked with obtaining the voltage gain at the seven frequencies noted in @measurements-hpf.
#figure(table(
    columns: (2fr, 1fr, 1fr, 1fr, 1fr, 1fr, 1fr, 1fr),
    inset: 8pt,
    align: center + horizon,
    row-gutter: 2pt,
    [*Frequency (Hz)*], [20000], [30000], [40000], [50000], [60000], [70000], [150000],
    [*$ abs(V_"o"/V_"in") $*], [0.40], [0.548], [0.656], [0.752], [0.816], [0.864], [0.992]
), caption: "HPF circuit voltage gain measurements") #label("measurements-hpf")

After obtaining the previous measurements, we should sketch the plot and obtain $F_"c"_"exp"$ from it.
=== Plot & Cut-off Frequency
The cut-off frequency can be obtained at $abs(H(omega)) = 1/sqrt(2) approx 0.707$

#figure(image("Graphics/hpf-plot-exp.svg", scaling: "smooth", width:100%),  caption: [Plot of the frequency response in HPF circuits using experimental data]) #label("hpf-exp-plot")

 As seen in @hpf-exp-plot, the cut-off frequency approximately equals $45090 "Hz"$.
#pagebreak()
== Simulated Data
Simulating the circuit in @hpf-circ-sim in NI Multisim, and using the "AC Sweep" simulation type to parametrically change the frequency of the voltage source, we obtain the plot shown in @hpf-sim-plot.

#figure(image("Graphics/hpf-circ-sim.svg", scaling: "smooth", width: 50%), caption: [HPF circuit used in simulation]) #label("hpf-circ-sim")

#figure(image("Graphics/linear-hpf.svg", scaling: "smooth", width: 100%),  caption: [Plot of the frequency response in the simulated HPF circuit from NI Multisim]) #label("hpf-sim-plot")

== Conclusion

#figure(table(
    columns: (1fr, 1fr),
    inset: 3.9pt,
    align: center + horizon,
    [*Scenario*],
    [*$F_c "(Hz)"$*],
    [Theoretical], [$40808$],
    [Experimental], [$45090$],
    [Simulated], [$40796$]
), caption: "Cut-off frequencies compared") #label("conc-table-hpf")

In high-pass filter circuits, the components significantly reduce the voltage output as source frequencies drop below the cut-off frequency. Theoretical and simulated cut-off frequencies approximately match, with relatively small disparity between either of them and the experimentally obtained one.
