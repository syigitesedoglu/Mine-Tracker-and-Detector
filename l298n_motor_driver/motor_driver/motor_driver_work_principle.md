# Motor Control Principle

| First Motor | Second Motor |
| -------- | -------- |
| IN1, IN2 | IN3, IN4 | 



|IN1   | IN2	|Motor Status|
| -------- | -------- | -------- |
|Low(0)	|Low(0)	|Motor OFF|
|High(1)	|Low(0)	|Forward|
|Low(0)	|High(1)	|Backward|
|High(1)	|High(1)	|Motor OFF|

# Pins of Speed Control

| ENA | ENB |
| -------- | -------- |
| ENA, MOTOR A | ENB, MOTOR B | 

## Step by Step Find the Calculation of Speed

* Speed = Perimeter of wheel * speed of wheel

* But perimeter is Pi times the Diameter of wheel

* So Speed = $π*D * speed of wheel$

* $Speed(m/s) = π * D(in meter) * rps$

* $Speed(km/hr) = π*D(in kilo meter) * rpm * 60$



## Add this in code

* ```const int D = ___ ; // Diameter in cm (include at the top)```

* ```speed = 3.14159*(D/100)*(rpm/60) // speed in m/s```

* ```speed = 3.15159*(D/100000)*(rpm*60) // speed in km/hr```
