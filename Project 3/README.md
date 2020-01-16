# Robotics-CSE4360

Project files for CSE 4360 - Autonomous Robots
Language: C++
Library : EV3 

University of Texas at Arlington - Fall 2019

Description of Project:

Simplified Soccer
For this project it is necessary that at least 2 teams choose it so they can play against each other.
The goal of the project is to build a robot that can play a simplified version of soccer using an IR
ball and IR seeker sensors. Two teams will play against each other on a field that has 3 zones:
two defense zones that only the robot of the defensive team can be in and a middle zone that both
teams’ robot can be in. The goal is for each team is to have the ball cross the other team’s base
line in order to score a goal. Once a goal is scored, the robots are moved into their team’s defense
zone and the ball is placed in the center. Then the game is started again with the team that has been
scored on getting a 1s head start.
Each participating team will receive an IR seeker sensor that provides a direction signal towards
the ball which is equipped with a set of IR LEDs. Each robot has to fit within 0.75ft × 0.75ft