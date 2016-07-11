# WRO Soccer

## General
All robots must have (1) compass and (1) infrared seeker sensors. A light switch trip mechanism where a light sensor detects the light from another sensor is used to detect the presence of a ball if the beam of light is broken (may also detect a robot).

## Strategy
"Strategy", per se, is unfeasible due to the randomness factor in the game. Our goal is to use a subroutine optimized to keep the ball on the other side of the field as much as possible. We simply move towards the ball if we are facing the opposing goal, or try to maneuver around it if we are facing our own goal.

**Minutiae**:
  - We believe that on the field, if we can either acquire the ball or push the opposing robot out of the way, it would be more advantageous to us to push the opposing robot out of the way.


## Code Overview
```
Let IR be the value read by the infrared sensor, which can be a value from 0 through 9. The sensor returns 0 if the ball is not detected. The sensor returns a value from 1-9 depending on which zone the ball is detected in.

Let LMOTOR be the power of the left motor, and RMOTOR be the power of the right motor.

Let K be the scaling factor that affects how fast the robot will turn towards the ball.

Let B be the base speed that the robot will move at.

Let S be the shift parameter of the IR value.

S = 5
K = 80
B = 100
These values were chosen by experimentation and are only applied to SKT_Faker and kennyS. Tune these values to suit your own robots.

LMOTOR = B + ((IR - S) * K)
RMOTOR = B - ((IR - S) * K)
```
```
We set S to 5 when we want our robot to drive directly towards the infrared ball. We set S to 3 or 7 when we want the robot to curve around the left/right side of the ball, respectively. We want the robot to drive directly towards the ball if we are facing the opposing goal. We want the robot to curve around the left/right side of the ball if we are facing our own goal. We could potentially use the ultrasonic sensor to determine if there is a wall/robot next to us and determine which way to turn.
```

## Offense bot
  - Build
    - Build a kicker capable of being a WMD (questionably legal). This could possible use a nautilus cam and/or springs/rubber bands and/or crank sliders.

  - Program
    - The program tracks the ball. If we are facing our own goal, we maneuver around the ball. If we are facing the opposing goal, we drive straight towards the ball.

  - Testing
    - The most important test is the turn test.
    - The second most important test is the kicker test.
    - The third most important test is the crash/wall test.

## Defense bot
  - Build
    - Build a kicker capable of being a WMD.
    - Prototype a thin robot with a shifting wall that is backed by the goal in order to block more.

  - Program
    - One program stays in place (curve turns back and forth [questionably legal]).
    - The other program turns to face the ball and moves forward if the ball is close enough.

  - Testing
    - The most important test is the goalie test.
    - The second most important test is the kicker test.
    - The third most important test is the push test.

## Tests
  - **Crash Test**: The robot is driven straight towards a wall and its robustness is objectively measured by how much the robot breaks. We also test a head-on collision between two robots. Test collisions against the side of the robot to check the robustness of the various connections.
  - **Turn Test**: A ball is rolled down a ramp at an angle relative to the robot and the robot is measured objectively by how fast it can get to the ball. The faster the robot is able to make contact with the ball, the better the robot is.
  - **Goalie Test**: Balls are rolled towards the goal at a variety of angles and speeds. The robot is measured objectively based on how well it can intercept these balls and prevent a goal from being scored.
  - **Push Test**: The robot strength is objectively measured based on how many heavy bricks it can push. This is determined by the robot's construction (ie: center of gravity, wheel size, wheel position, etc).
  - **Kicker Test**: The robot kicker is tested by kicking the ball and measuring how fast it can travel 5 feet.
