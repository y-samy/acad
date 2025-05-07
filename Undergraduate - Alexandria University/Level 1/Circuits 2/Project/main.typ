#import "@preview/unify:0.7.0":*

#import "@preview/cetz:0.3.1" as cetz: *

#import "@preview/cetz-plot:0.1.0"

#let title = "Final Project Report"
#let authors = (
  (
    name: "Seif Diaa El-din Abd El Satar",
    id: "9345"
  ),
  (
    name: "Youssef Ahmed Samy",
    id: "9545"
  ),
)
#set document(
    title: title, 
    author: authors.map(author => author.name)
)

#let organization = "Faculty of Engineering, Alexandria University\n Computer & Communications Program"
#let course-abrev = "EEC116"
#let course-name = "Analysis of Electrical Circuits"
#let experiment = "Operational Amplifiers\nInverting, Non-Inverting & Buffer Applications"
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


*_Abstract_---This lab report aims to study ideal operational amplifiers (otherwise known as _op-amps_) and three of their applications, by using the simulation software NI Multisim and comparing the simulated measurements of the voltage gain to the theoretical values. Op-amps offer significant voltage gain, which this project will demonstrate.*

#set heading(numbering: "1.1.")
= The Inverting Closed Loop

== The Circuit
The circuit in @circuit1 is a layout of the inverting closed loop op-amp circuit connected to an oscilloscope that measures the input and output voltage.

#figure(image("Graphics/circuit1.svg", scaling: "smooth", width: 100%), caption: [Circuit design in NI Multisim]) #label("circuit1")
== Theoretical Gain
The theoretical formula for the voltage gain $display(G = V_"o"/V_"in")$ is $display( (-R_2)/R_1)$. This evaluates to $display((-47","000)/(1","000) = -47)$.

== Simulated Data
=== Oscilloscope Measurement
@osc1 is a screenshot of the oscilloscope window, showing the sine wave of the output voltage (Channel B) in red (higher peaks) and the and the input voltage (Channel A) in black (lower peaks).

#figure(image("Graphics/osc1.png", scaling: "smooth", width: 100%), caption: [Oscilloscope readings window in NI Multisim]) #label("osc1")

=== Calculation on Readings
$ G_"experimental" = (-28.182)/0.599722 = -46.99 approx -47 $
== Conclusion

$ G_"theoretical" = -47 \ G_"experimental" = -47 $
The theoretical and simulated gain in voltage match together.

#pagebreak()

= The Non-Inverting Closed Loop

== The Circuit
The circuit in @circuit2 is a layout of the non-inverting closed loop op-amp circuit connected to an oscilloscope that measures the input and output voltage.

#figure(image("Graphics/circuit2.svg", scaling: "smooth", width: 100%), caption: [Circuit design in NI Multisim]) #label("circuit2")
== Theoretical Gain
The theoretical formula for the voltage gain $display(G = V_"o"/V_"in")$ is $display( (R_1 + R_2)/R_1)$. This evaluates to $display((48","000)/(1","000) = 48)$.

== Simulated Data
=== Oscilloscope Measurement
@osc2 is a screenshot of the oscilloscope window, showing the sine wave of the output voltage (Channel B) in red (higher peaks) and the and the input voltage (Channel A) in black (lower peaks).

#figure(image("Graphics/osc2.png", scaling: "smooth", width: 100%), caption: [Oscilloscope readings window in NI Multisim]) #label("osc2")

=== Calculation on Readings
$ G_"experimental" = (-28.722)/(-0.598681) = 47.97 approx 48 $
== Conclusion

$ G_"theoretical" = 48 \ G_"experimental" = 48 $
The theoretical and simulated gain in voltage match together.

#pagebreak()

= Voltage Follower (Buffer)

== The Circuit
The circuit in @circuit3 is a layout of the buffer op-amp circuit connected to an oscilloscope that measures the input and output voltage.

#figure(image("Graphics/circuit3.svg", scaling: "smooth", width: 100%), caption: [Circuit design in NI Multisim]) #label("circuit3")
== Theoretical Gain
Theoretically, the output voltage is the same as the input voltage. Here the input voltage is set to $0.6 "V"_"p-p"$.

== Simulated Data
=== Oscilloscope Measurement
@osc3 is a screenshot of the oscilloscope window, showing the square wave of the output voltage (Channel B) in red (higher peaks) and the and the input voltage (Channel A) in black (lower peaks). The scaling does not represent the actual magnitude.

#figure(image("Graphics/osc3.png", scaling: "smooth", width: 100%), caption: [Oscilloscope readings window in NI Multisim]) #label("osc3")

=== Calculation on Readings
$ G_"experimental" = (0.601)/600 = 1.001 approx 1 $
== Conclusion

$ G_"experimental" = 1\ A_"p-p" = V/R = 0.6/220 = 2.72 "mA" $