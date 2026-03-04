# Grp-1_AIE-B_Robotics_ArtBot
ArtBot is a 4-DOF AI-powered robotic drawing system that converts natural language prompts into physical artwork. The system integrates Generative AI, inverse kinematics, real-time trajectory planning, and embedded control to bridge digital intelligence with mechanical motion.


# ArtBot – Autonomous AI-Driven Robotic Drawing System

ArtBot is an intelligent robotic drawing system that integrates Artificial Intelligence, mathematical modeling, and embedded control systems to transform natural language prompts into physical artwork.

Unlike traditional robotic arms that rely on predefined motion commands, ArtBot enables:

*  Natural Language Interaction
*  Automated Coordinate Generation
*  Inverse Kinematics-Based Motion Planning
*  Real-Time Robotic Arm Control
*  Physical Reproduction of AI-Generated Shapes

This project demonstrates embodied AI — where digital intelligence produces tangible real-world output.

---

#  Project Motivation

While robotics has largely focused on industrial automation and repetitive precision tasks, creative robotics remains underexplored.

ArtBot was developed to:

1. Bridge Generative AI with physical robotic systems
2. Apply inverse kinematics in real-world hardware
3. Create a cost-effective educational robotics platform

---

#  System Architecture

The complete pipeline follows this flow:

### 1️ User Prompt

User provides a natural language command:

```
"Draw a square"
```

### 2️ Generative AI Model

The prompt is processed using **Google Gemini**, which converts the instruction into structured 2D coordinate points.

### 3️ Coordinate Extraction

AI-generated Cartesian coordinates (x, y) are parsed in Python.

Example:

```
(100, -20)
(120, -20)
(120, 20)
(100, 20)
```

### 4️ Path Interpolation

Linear interpolation generates dense intermediate points between vertices to ensure smooth straight-line drawing.

Formula used:

```
xi = x1 + i((x2 − x1)/N)
yi = y1 + i((y2 − y1)/N)
```

### 5️ Inverse Kinematics (IK)

Each (x, y, z) coordinate is converted into joint angles:

* θ₁ → Base
* θ₂ → Shoulder
* θ₃ → Elbow
* θ₄ → Wrist

Key equations:

Base Rotation:

```
θ₁ = atan2(y, x) + 90°
```

Elbow:

```
cos(θ₃) = (L₁² + L₂² − d²) / (2L₁L₂)
```

Shoulder:

```
θ₂ = α + β
```

Wrist:

```
θ₄ = 180° − (θ₂ + θ₃)
```

---

#  Hardware Architecture

##  Robotic Manipulator

4-DOF Serial Manipulator:

* Joint 1 → Base (Yaw)
* Joint 2 → Shoulder (Pitch)
* Joint 3 → Elbow (Pitch)
* Joint 4 → Wrist (Pitch)

This configuration allows accurate positioning of the pen tip within the workspace.

---

##  Electronic Components

### Microcontroller

* Arduino Uno

### Servo Driver

* PCA9685 16-Channel PWM Driver

  * 12-bit resolution
  * Multi-servo control
  * Reduced microcontroller load

### Power System

* 5V 5A Dedicated SMPS
* Isolated servo supply to prevent voltage drops

---

#  Software Stack

* Python (Main Controller)
* Serial Communication (UART – 115200 baud)
* Generative AI API (Google Gemini)
* Arduino Firmware (Servo Control)
* Mathematical IK Computation

---

#  Control Loop

1. Generate interpolated trajectory points
2. Compute inverse kinematics
3. Convert angles to servo commands
4. Send via serial communication
5. Execute PWM motor control
6. Physically draw the shape

Command Format:

```
Base,Shoulder,Elbow,Wrist
```

Example:

```
90,110,45,25
```

---

#  Experimental Results

*  Smooth multi-joint coordinated motion
*  Accurate coordinate tracking
*  Drawing accuracy ≈ ±2 mm
*  Response time ≈ 3 seconds
*  Stable servo performance

Successfully tested with:

* Square
* Triangle

---

#  Challenges & Solutions

| Challenge         | Cause                  | Solution                 |
| ----------------- | ---------------------- | ------------------------ |
| Servo Instability | Voltage Drop           | Dedicated SMPS + PCA9685 |
| Curved Lines      | Direct Vertex Movement | Linear Interpolation     |
| Pen Height Issues | Mechanical Tolerance   | Adjustable Z-offset      |

---

#  Key Advantages

* Integrates Generative AI with real-time robotics
* Demonstrates practical inverse kinematics implementation
* Low-cost and scalable hardware setup
* Modular architecture (AI + Math + Hardware separation)
* Strong educational value for robotics learning

---

#  Educational Value

ArtBot serves as a hands-on platform for learning:

* Robotics
* Inverse Kinematics
* Trajectory Planning
* Embedded Systems
* AI-to-Hardware Integration

---

#  Future Improvements

* Curve and freehand drawing support
* Vision-based feedback system
* Closed-loop PID control
* Multi-color pen switching
* 6-DOF arm upgrade

---

#  Conclusion

ArtBot successfully bridges Artificial Intelligence and robotic actuation by converting natural language prompts into precise mechanical motion.

The project validates a complete AI-to-hardware pipeline:

Text Input → AI Processing → Mathematical Modeling → Embedded Control → Physical Output

It unifies AI, robotics, mathematics, and embedded systems into a functional creative robotics platform.

---

#  Team

* CH Vaishnavi Krishna
* Diya Prakash
* Dondluru Keerthana
* V R Sridevi

Course: 22AIE214 – Introduction to AI & Robotics

---
