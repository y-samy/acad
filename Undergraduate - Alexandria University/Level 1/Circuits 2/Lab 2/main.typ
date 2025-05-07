#import "@preview/unify:0.7.0":*

#import "@preview/cetz:0.3.1" as cetz: *

#import "@preview/cetz-plot:0.1.0"

#let title = "Lab 2 Report\n EXAMPLE DOCUMENT"
#let authors = (
  (
    name: "Yousef Shawer",
    id: "9685"
  ),
  (
    name: "Youssef Samy",
    id: "9545"
  ),
  (
    name: "Ali Tarek",
    id: "9676"
  ),
  (
    name: "Ahmed Essam",
    id: "9684"
  ),
)
#set document(
    title: title, 
    author: authors.map(author => author.name)
)

#let organization = "Faculty of Engineering, Alexandria University\n Computer & Communications Program"
#let course-abrev = "EEC116"
#let course-name = "Analysis of Electrical Circuits"
#let experiment = "Transient Response\nin RC & RL Circuits"
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
        text(14pt,smallcaps(align(center)[*Authors*]))
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


*_Abstract_---This lab report follows an experiment measuring the transient response of RC and RL circuits, where the step response is taken to illustrate how capacitors resist instantaneous change in voltage, and inductors resist instantaneous change in current.*

#set heading(numbering: "1.1.")
= RC Step Response

== The Circuit
The RC circuit in @rc-circ is a schematic of the circuit connected to a function generator with the input voltage set to $10"V"_"p.p", 500 "Hz", 5"V offset"$, and the output voltage measured across the $100 "nF" $ capacitor.

#figure(image("Graphics/rc-circ.svg", scaling: "smooth", width: 50%), caption: [RC circuit given in lab]) #label("rc-circ")
== Theoretical Step Response
The expression for the time constant $tau$ used to describe the voltage across the capacitor is $tau = R C$.

Therefore, the theoretical value for $tau$ in this circuit is known to be $1000 times 100 times 10^(-9) = 100 times 10^(-6)"s"$. The duration of time after which the circuit settles from a transient response to a steady-state response is approximately $tau_"setting" = 5 tau = 500 times 10^(-6)"s"$.

== Experimental Data
The equation describing the voltage across an uncharged capacitor in a series RC circuit following a voltage step is $ v_"C" (t) = V_"S" (1 - e^(-t\/tau)) $
In our circuit, the voltage when the time $t = tau$ is $ 10(1 - 1/e) = 6.321 "V" $
We can look for the duration of time that has passed until this voltage is measured across the capacitor using an oscilloscope. Doing so in the lab, we have obtained the value $t = tau = 180 mu "s"$.

By also looking at the beginning of the plateau on the plot from the oscilloscope, we have also obtained the $tau_"setting" = 580 mu "s"$.

== Simulated Data
By assembling the circuit in @rc-sim-circ in NI Multisim, where the V1 is a `STEP_VOLTAGE` component, with an initial voltage of $0"V"$ and a final voltage of $10"V"$, and by measuring the voltage across the capacitor in the "Transient" simulation type, we can obtain the plot of $V_"out"$ relative to the ground as shown in @rc-sim-plot.

#figure(image("Graphics/rc-sim-circ.svg", scaling: "smooth", width: 50%), caption: [RC circuit used in simulation]) #label("rc-sim-circ")

#figure(image("Graphics/rc-sim-plot.svg", scaling: "smooth", width: 100%),  caption: [Plot of the transient response from the simulated RC circuit from NI Multisim, showing the simulated $tau = 100 mu "s"$ and the estimated $tau_"setting" = 488 mu "s"$]) #label("rc-sim-plot")

== Conclusion

#figure(table(
    columns: (1fr, 1fr, 1fr),
    inset: 3.9pt,
    align: center + horizon,
    [*Scenario*], [*$tau (mu"s")$*], [*$tau_"setting" (mu"s")$*],
    [*Theoretical*], [$100$], [$500$],
    [*Experimental*], [$180$], [$580$],
    [*Simulated*], [$100$], [$488$]
), caption: $tau "values compared"$ ) #label("conc-table-lpf")

#pagebreak()

= RL Step Response

== The Circuit
The RL circuit in @rl-circ is a schematic of the circuit connected to a function generator with the input voltage set to $10"V"_"p.p", 20 "kHz", 5"V offset"$, and the output voltage measured across the $1 "k" Omega $ resistor.

#figure(image("Graphics/rl-circ.svg", scaling: "smooth", width: 50%), caption: [RL circuit given in lab]) #label("rl-circ")
== Theoretical Step Response
The expression for the time constant $tau$ used to describe the voltage across the capacitor is $tau = L/R$.

Therefore, the theoretical value for $tau$ in this circuit is known to be $(3.9 times 10^(-3))/1000 = 3.9 times 10^(-6)"s"$. The duration of time after which the circuit settles from a transient response to a steady-state response is approximately $tau_"setting" = 5 tau = 19.5 times 10^(-6)"s"$.

== Experimental Data
The equation describing the voltage drop across an inductor in a series RL circuit following a voltage step is $ v_"L" (t) = V_"S" (e^(-t\/tau)) $
In our circuit, the voltage when the time $t = tau$ is $ 10/e = 3.678 "V" $
Since measuring the voltage difference across the inductor is difficult in practice, we will instead look at the voltage difference across the resistor. When $v_"L" = 3.678"V"$, $v_"R" = 6.321"V"$.

We can look for the duration of time that has passed until this voltage is measured across the resistor using an oscilloscope. Doing so in the lab, we have obtained the value $t = tau = 6 mu "s"$.

By also looking at the beginning of the plateau on the plot from the oscilloscope, we have also obtained the $tau_"setting" = 16 mu "s"$.

== Simulated Data
By assembling the circuit in @rl-sim-circ in NI Multisim, where the V1 is a `STEP_VOLTAGE` component, with an initial voltage of $0"V"$ and a final voltage of $10"V"$, and by measuring the voltage across the capacitor in the "Transient" simulation type, we can obtain the plot of $V_"+" - V_"-"$ (voltage across resistor) as shown in @rl-sim-plot.

#figure(image("Graphics/rl-sim-circ.svg", scaling: "smooth", width: 50%), caption: [RL circuit used in simulation]) #label("rl-sim-circ")

#figure(image("Graphics/rl-sim-plot.svg", scaling: "smooth", width: 100%),  caption: [Plot of the transient response from the simulated RL circuit from NI Multisim, showing the simulated $tau = 3.89 mu "s"$ and the estimated $tau_"setting" = 19.52 mu "s"$]) #label("rl-sim-plot")

== Conclusion

#figure(table(
    columns: (1fr, 1fr, 1fr),
    inset: 3.9pt,
    align: center + horizon,
    [*Scenario*], [*$tau (mu"s")$*], [*$tau_"setting" (mu"s")$*],
    [*Theoretical*], [$3.9$], [$19.5$],
    [*Experimental*], [$6$], [$16$],
    [*Simulated*], [$3.89$], [$19.52$]
), caption: $tau "values compared"$ ) #label("conc-table-lpf")