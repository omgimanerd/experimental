# WRO Soccer

## General
All robots must have (1) compass and (1) infrared seeker sensors. A light switch trip mechanism where a light sensor detects the light from another sensor is used to detect the presence of a ball if the beam of light is broken (may also detect a robot).

## Strategy
"Strategy", per se, is unfeasible due to the randomness factor in the game. Our goal is to use a subroutine optimized to keep the ball on the other side of the field as much as possible. We simply move towards the ball if we are facing the opposing goal, or try to maneuver around it if we are facing our own goal.

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
